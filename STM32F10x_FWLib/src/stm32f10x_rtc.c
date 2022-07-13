/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_rtc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC
  * @brief RTC driver modules
  * @{
  */

/** @defgroup RTC_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup RTC_Private_Defines
  * @{
  */
#define RTC_LSB_MASK     ((uint32_t)0x0000FFFF)  /*!< RTC LSB Mask */
#define PRLH_MSB_MASK    ((uint32_t)0x000F0000)  /*!< RTC Prescaler MSB Mask */

/**
  * @}
  */

/** @defgroup RTC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_Private_Functions
  * @{
  */

/**
 * @brief 启用或禁用指定的 RTC 中断。
 * @param RTC_IT：指定要启用或禁用的 RTC 中断源。
 * 该参数可以是以下值的任意组合：
 * @arg RTC_IT_OW: 溢出中断
 * @arg RTC_IT_ALR：报警中断
 * @arg RTC_IT_SEC：第二次中断
 * @param NewState：指定 RTC 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_IT(RTC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RTC->CRH |= RTC_IT;
  }
  else
  {
    RTC->CRH &= (uint16_t)~RTC_IT;
  }
}

/**
 * @brief 进入 RTC 配置模式。
 * @param 无
 * @retval 无
 */
void RTC_EnterConfigMode(void)
{
  /* Set the CNF flag to enter in the Configuration Mode */
  RTC->CRL |= RTC_CRL_CNF;
}

/**
 * @brief 退出 RTC 配置模式。
 * @param 无
 * @retval 无
 */
void RTC_ExitConfigMode(void)
{
  /* Reset the CNF flag to exit from the Configuration Mode */
  RTC->CRL &= (uint16_t)~((uint16_t)RTC_CRL_CNF);
}

/**
 * @brief 获取 RTC 计数器值。
 * @param 无
 * @retval RTC 计数器值。
 */
uint32_t RTC_GetCounter(void)
{
  uint16_t tmp = 0;
  tmp = RTC->CNTL;
  return (((uint32_t)RTC->CNTH << 16 ) | tmp) ;
}

/**
 * @brief 设置 RTC 计数器值。
 * @param CounterValue：RTC 计数器新值。
 * @retval 无
 */
void RTC_SetCounter(uint32_t CounterValue)
{
  RTC_EnterConfigMode();
  /* Set RTC COUNTER MSB word */
  RTC->CNTH = CounterValue >> 16;
  /* Set RTC COUNTER LSB word */
  RTC->CNTL = (CounterValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/**
 * @brief 设置 RTC 预分频器值。
 * @param PrescalerValue：RTC 预分频器新值。
 * @retval 无
 */
void RTC_SetPrescaler(uint32_t PrescalerValue)
{
  /* Check the parameters */
  assert_param(IS_RTC_PRESCALER(PrescalerValue));

  RTC_EnterConfigMode();
  /* Set RTC PRESCALER MSB word */
  RTC->PRLH = (PrescalerValue & PRLH_MSB_MASK) >> 16;
  /* Set RTC PRESCALER LSB word */
  RTC->PRLL = (PrescalerValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/**
 * @brief 设置 RTC 警报值。
 * @param AlarmValue：RTC 报警新值。
 * @retval 无
 */
void RTC_SetAlarm(uint32_t AlarmValue)
{
  RTC_EnterConfigMode();
  /* Set the ALARM MSB word */
  RTC->ALRH = AlarmValue >> 16;
  /* Set the ALARM LSB word */
  RTC->ALRL = (AlarmValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/**
 * @brief 获取 RTC 分频器值。
 * @param 无
 * @retval RTC 分频器值。
 */
uint32_t RTC_GetDivider(void)
{
  uint32_t tmp = 0x00;
  tmp = ((uint32_t)RTC->DIVH & (uint32_t)0x000F) << 16;
  tmp |= RTC->DIVL;
  return tmp;
}

/**
 * @brief 等待 RTC 寄存器的最后一次写操作完成。
 * @note 必须在对 RTC 寄存器进行任何写入之前调用此函数。
 * @param 无
 * @retval 无
 */
void RTC_WaitForLastTask(void)
{
  /* Loop until RTOFF flag is set */
  while ((RTC->CRL & RTC_FLAG_RTOFF) == (uint16_t)RESET)
  {
  }
}

/**
 * @brief 等待 RTC 寄存器（RTC_CNT、RTC_ALR 和 RTC_PRL）
 * 与 RTC APB 时钟同步。
 * @note 此函数必须在 APB 复位后的任何读取操作之前调用
 * 或 APB 时钟停止。
 * @param 无
 * @retval 无
 */
void RTC_WaitForSynchro(void)
{
  /* Clear RSF flag */
  RTC->CRL &= (uint16_t)~RTC_FLAG_RSF;
  /* Loop until RSF flag is set */
  while ((RTC->CRL & RTC_FLAG_RSF) == (uint16_t)RESET)
  {
  }
}

/**
 * @brief 检查是否设置了指定的 RTC 标志。
 * @param RTC_FLAG：指定要检查的标志。
 * 此参数可以是以下值之一：
 * @arg RTC_FLAG_RTOFF：RTC 操作关闭标志
 * @arg RTC_FLAG_RSF：注册同步标志
 * @arg RTC_FLAG_OW: 溢出标志
 * @arg RTC_FLAG_ALR：报警标志
 * @arg RTC_FLAG_SEC：第二个标志
 * @retval RTC_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG));

  if ((RTC->CRL & RTC_FLAG) != (uint16_t)RESET)
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
 * @brief 清除 RTC 的挂起标志。
 * @param RTC_FLAG：指定要清除的标志。
 * 该参数可以是以下值的任意组合：
 * @arg RTC_FLAG_RSF：注册同步标志。 该标志仅在之后被清除
 * APB 复位或 APB 时钟停止。
 * @arg RTC_FLAG_OW: 溢出标志
 * @arg RTC_FLAG_ALR：报警标志
 * @arg RTC_FLAG_SEC：第二个标志
 * @retval 无
 */
void RTC_ClearFlag(uint16_t RTC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));

  /* Clear the corresponding RTC flag */
  RTC->CRL &= (uint16_t)~RTC_FLAG;
}

/**
 * @brief 检查指定的 RTC 中断是否发生。
 * @param RTC_IT：指定要检查的 RTC 中断源。
 * 此参数可以是以下值之一：
 * @arg RTC_IT_OW: 溢出中断
 * @arg RTC_IT_ALR：报警中断
 * @arg RTC_IT_SEC：第二次中断
 * @retval RTC_IT 的新状态（SET 或 RESET）。
 */
ITStatus RTC_GetITStatus(uint16_t RTC_IT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RTC_GET_IT(RTC_IT));

  bitstatus = (ITStatus)(RTC->CRL & RTC_IT);
  if (((RTC->CRH & RTC_IT) != (uint16_t)RESET) && (bitstatus != (uint16_t)RESET))
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
 * @brief 清除 RTC 的中断挂起位。
 * @param RTC_IT：指定要清除的中断挂起位。
 * 该参数可以是以下值的任意组合：
 * @arg RTC_IT_OW: 溢出中断
 * @arg RTC_IT_ALR：报警中断
 * @arg RTC_IT_SEC：第二次中断
 * @retval 无
 */
void RTC_ClearITPendingBit(uint16_t RTC_IT)
{
  /* Check the parameters */
  assert_param(IS_RTC_IT(RTC_IT));

  /* Clear the corresponding RTC pending bit */
  RTC->CRL &= (uint16_t)~RTC_IT;
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
