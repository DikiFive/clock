/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_exti.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI
  * @brief EXTI driver modules
  * @{
  */

/** @defgroup EXTI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Private_Defines
  * @{
  */

#define EXTI_LINENONE    ((uint32_t)0x00000)  /* No interrupt selected */

/**
  * @}
  */

/** @defgroup EXTI_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Private_Functions
  * @{
  */

/**
 * @brief 将 EXTI 外设寄存器取消初始化为其默认复位值。
 * @param 无
 * @retval 无
 */
void EXTI_DeInit(void)
{
  EXTI->IMR = 0x00000000;
  EXTI->EMR = 0x00000000;
  EXTI->RTSR = 0x00000000;
  EXTI->FTSR = 0x00000000;
  EXTI->PR = 0x000FFFFF;
}

/**
 * @brief 根据指定初始化EXTI外设
 * EXTI_InitStruct 中的参数。
 * @param EXTI_InitStruct: 指向 EXTI_InitTypeDef 结构的指针
 * 包含 EXTI 外设的配置信息。
 * @retval 无
 */
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

  tmp = (uint32_t)EXTI_BASE;

  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* Clear EXTI line configuration */
    EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;

    tmp += EXTI_InitStruct->EXTI_Mode;

    *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;

    /* Clear Rising Falling edge configuration */
    EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;

    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
      EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;

      *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;

    /* Disable the selected external lines */
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}

/**
 * @brief 用其重置值填充每个 EXTI_InitStruct 成员。
 * @param EXTI_InitStruct：指向 EXTI_InitTypeDef 结构的指针，该结构将
 * 被初始化。
 * @retval 无
 */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
 * @brief 生成软件中断。
 * @param EXTI_Line：指定要启用或禁用的 EXTI 行。
 * 此参数可以是 EXTI_Linex 的任意组合，其中 x 可以是 (0..19)。
 * @retval 无
 */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->SWIER |= EXTI_Line;
}

/**
 * @brief 检查是否设置了指定的 EXTI 行标志。
 * @param EXTI_Line：指定要检查的 EXTI 行标志。
 * 该参数可以是：
 * @arg EXTI_Linex：外部中断线 x 其中 x(0..19)
 * @retval EXTI_Line 的新状态（SET 或 RESET）。
 */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));

  if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
 * @brief 清除 EXTI 的行挂起标志。
 * @param EXTI_Line：指定要清除的 EXTI 行标志。
 * 此参数可以是 EXTI_Linex 的任意组合，其中 x 可以是 (0..19)。
 * @retval 无
 */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->PR = EXTI_Line;
}

/**
 * @brief 检查指定的 EXTI 行是否被断言。
 * @param EXTI_Line：指定要检查的 EXTI 行。
 * 该参数可以是：
 * @arg EXTI_Linex：外部中断线 x 其中 x(0..19)
 * @retval EXTI_Line 的新状态（SET 或 RESET）。
 */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));

  enablestatus =  EXTI->IMR & EXTI_Line;
  if (((EXTI->PR & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
 * @brief 清除 EXTI 的行挂起位。
 * @param EXTI_Line：指定要清除的 EXTI 行。
 * 此参数可以是 EXTI_Linex 的任意组合，其中 x 可以是 (0..19)。
 * @retval 无
 */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->PR = EXTI_Line;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
