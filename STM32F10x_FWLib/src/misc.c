/* Includes ------------------------------------------------------------------*/
#include "misc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup MISC
 * @brief MISC 驱动模块
 * @{
 */

/** @defgroup MISC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup MISC_Private_Defines
 * @{
 */

#define AIRCR_VECTKEY_MASK ((uint32_t)0x05FA0000)
/**
 * @}
 */

/** @defgroup MISC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup MISC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup MISC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup MISC_Private_Functions
 * @{
 */

/**
 * @brief  配置优先级分组：抢占优先级和子优先级。
 *
 * @param  NVIC_PriorityGroup: 指定优先级分组位长度。
 *   此参数可以是以下值之一：
 *
 * @arg NVIC_PriorityGroup_0：0 位用于抢占优先级
 * 4 位用于子优先级
 *
 * @arg NVIC_PriorityGroup_1：1 位用于抢占优先级
 * 3 位用于子优先级
 *
 * @arg NVIC_PriorityGroup_2：2 位用于抢占优先级
 * 2 位用于子优先级
 *
 * @arg NVIC_PriorityGroup_3：3 位用于抢占优先级
 * 1 位用于子优先级
 *
 * @arg NVIC_PriorityGroup_4：4 位用于抢占优先级
 * 0 位表示子优先级
 *
 * @retval 无
 */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
  /* 检查参数 */
  assert_param(IS_NVIC_PRIORITY_GROUP(NVIC_PriorityGroup));

  /*根据 NVIC_PriorityGroup 值设置 PRIGROUP[10:8] 位 */
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
 * @brief  根据指定初始化 NVIC 外设
 *         NVIC_InitStruct 中的参数。
 * @param  NVIC_InitStruct: 指向包含 NVIC_InitTypeDef 结构的指针
 * 指定 NVIC 外设的配置信息。
 * @retval None
 */
void NVIC_Init(NVIC_InitTypeDef *NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

  /* 检查参数 */
  assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority));
  assert_param(IS_NVIC_SUB_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelSubPriority));

  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* 计算相应的 IRQ 优先级 */
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700)) >> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |= NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;

    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;

    /* 启用选定的 IRQ 通道*/
    NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
        (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* 禁用选定的 IRQ 通道*/
    NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
        (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/**
 * @brief 设置向量表位置和偏移量。
 * @param NVIC_VectTab：指定向量表是在 RAM 还是 FLASH 存储器中。
 * 此参数可以是以下值之一：
 * @arg NVIC_VectTab_RAM
 * @arg NVIC_VectTab_FLASH
 * @param Offset：向量表基本偏移字段。 此值必须是0x200的倍数
 *
 * @retval 无
 */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));

  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
 * @brief 选择系统进入低功耗模式的条件。
 * @param LowPowerMode：指定系统进入低功耗模式的新模式。
 * 此参数可以是以下值之一：
 * @arg NVIC_LP_SEVONPEND
 * @arg NVIC_LP_SLEEPDEEP
 * @arg NVIC_LP_SLEEPONEXIT
 * @param NewState：LP 条件的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_NVIC_LP(LowPowerMode));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SCB->SCR |= LowPowerMode;
  }
  else
  {
    SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
  }
}

/**
 * @brief 配置 SysTick 时钟源。
 * @param SysTick_CLKSource：指定 SysTick 时钟源。
 * 此参数可以是以下值之一：
 * @arg SysTick_CLKSource_HCLK_Div8：AHB 时钟除以 8 被选为 SysTick 时钟源。
 * @arg SysTick_CLKSource_HCLK：选择 AHB 时钟作为 SysTick 时钟源。
 * @retval 无
 */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* Check the parameters */
  assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
  if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
  }
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
