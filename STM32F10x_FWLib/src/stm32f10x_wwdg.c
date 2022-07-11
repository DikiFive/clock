/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_wwdg.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup WWDG
 * @brief WWDG driver modules
 * @{
 */

/** @defgroup WWDG_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup WWDG_Private_Defines
 * @{
 */

/* ----------- WWDG registers bit address in the alias region ----------- */
#define WWDG_OFFSET (WWDG_BASE - PERIPH_BASE)

/* Alias word address of EWI bit */
#define CFR_OFFSET (WWDG_OFFSET + 0x04)
#define EWI_BitNumber 0x09
#define CFR_EWI_BB (PERIPH_BB_BASE + (CFR_OFFSET * 32) + (EWI_BitNumber * 4))

/* --------------------- WWDG registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_WDGA_Set ((uint32_t)0x00000080)

/* CFR register bit mask */
#define CFR_WDGTB_Mask ((uint32_t)0xFFFFFE7F)
#define CFR_W_Mask ((uint32_t)0xFFFFFF80)
#define BIT_Mask ((uint8_t)0x7F)

/**
 * @}
 */

/** @defgroup WWDG_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup WWDG_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup WWDG_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup WWDG_Private_Functions
 * @{
 */

/**
 * @brief 将 WWDG 外设寄存器取消初始化为其默认复位值。
 * @param 无
 * @retval 无
 */
void WWDG_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}
/**
 * @brief 设置 WWDG 预分频器。
 * @param WWDG_Prescaler：指定 WWDG 预分频器。
 * 此参数可以是以下值之一：
 * @arg WWDG_Prescaler_1: WWDG 计数器时钟 = (PCLK1/4096)/1
 * @arg WWDG_Prescaler_2：WWDG 计数器时钟 = (PCLK1/4096)/2
 * @arg WWDG_Prescaler_4: WWDG 计数器时钟 = (PCLK1/4096)/4
 * @arg WWDG_Prescaler_8: WWDG 计数器时钟 = (PCLK1/4096)/8
 * @retval 无
 */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
  /* Clear WDGTB[1:0] bits */
  tmpreg = WWDG->CFR & CFR_WDGTB_Mask;
  /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
  tmpreg |= WWDG_Prescaler;
  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/**
 * @brief 设置 WWDG 窗口值。
 * @param WindowValue：指定要与递减计数器比较的窗口值。
 * 此参数值必须小于 0x80。
 * @retval 无
 */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
  /* Clear W[6:0] bits */

  tmpreg = WWDG->CFR & CFR_W_Mask;

  /* Set W[6:0] bits according to WindowValue value */
  tmpreg |= WindowValue & (uint32_t)BIT_Mask;

  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/**
 * @brief 启用 WWDG 早期唤醒中断 (EWI)。
 * @param 无
 * @retval 无
 */
void WWDG_EnableIT(void)
{
  *(__IO uint32_t *)CFR_EWI_BB = (uint32_t)ENABLE;
}

/**
 * @brief 设置 WWDG 计数器值。
 * @param Counter：指定看门狗计数器值。
 * 此参数必须是介于 0x40 和 0x7F 之间的数字。
 * @retval 无
 */
void WWDG_SetCounter(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  /* Write to T[6:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CR = Counter & BIT_Mask;
}

/**
 * @brief 启用 WWDG 并加载计数器值。
 * @param Counter：指定看门狗计数器值。
 * 此参数必须是介于 0x40 和 0x7F 之间的数字。
 * @retval None
 */
void WWDG_Enable(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  WWDG->CR = CR_WDGA_Set | Counter;
}

/**
 * @brief 检查是否设置了 Early Wakeup 中断标志。
 * @param 无
 * @retval 早期唤醒中断标志的新状态（SET 或 RESET）
 */
FlagStatus WWDG_GetFlagStatus(void)
{
  return (FlagStatus)(WWDG->SR);
}

/**
 * @brief 清除早期唤醒中断标志。
 * @param 无
 * @retval 无
 */
void WWDG_ClearFlag(void)
{
  WWDG->SR = (uint32_t)RESET;
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
