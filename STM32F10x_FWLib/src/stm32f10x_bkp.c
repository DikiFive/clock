/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_bkp.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup BKP
  * @brief BKP driver modules
  * @{
  */

/** @defgroup BKP_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Private_Defines
  * @{
  */

/* ------------ BKP registers bit address in the alias region --------------- */
#define BKP_OFFSET        (BKP_BASE - PERIPH_BASE)

/* --- CR Register ----*/

/* Alias word address of TPAL bit */
#define CR_OFFSET         (BKP_OFFSET + 0x30)
#define TPAL_BitNumber    0x01
#define CR_TPAL_BB        (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPAL_BitNumber * 4))

/* Alias word address of TPE bit */
#define TPE_BitNumber     0x00
#define CR_TPE_BB         (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPE_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of TPIE bit */
#define CSR_OFFSET        (BKP_OFFSET + 0x34)
#define TPIE_BitNumber    0x02
#define CSR_TPIE_BB       (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TPIE_BitNumber * 4))

/* Alias word address of TIF bit */
#define TIF_BitNumber     0x09
#define CSR_TIF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TIF_BitNumber * 4))

/* Alias word address of TEF bit */
#define TEF_BitNumber     0x08
#define CSR_TEF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TEF_BitNumber * 4))

/* ---------------------- BKP registers bit mask ------------------------ */

/* RTCCR register bit mask */
#define RTCCR_CAL_MASK    ((uint16_t)0xFF80)
#define RTCCR_MASK        ((uint16_t)0xFC7F)

/**
  * @}
  */


/** @defgroup BKP_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup BKP_Private_Functions
  * @{
  */

/**
 * @brief 将 BKP 外设寄存器取消初始化为其默认复位值。
 * @param 无
 * @retval 无
 */
void BKP_DeInit(void)
{
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
}

/**
 * @brief 配置篡改引脚活动级别。
 * @param BKP_TamperPinLevel：指定 Tamper Pin 活动电平。
 * 此参数可以是以下值之一：
 * @arg BKP_TamperPinLevel_High：篡改引脚在高电平有效
 * @arg BKP_TamperPinLevel_Low：篡改引脚低电平有效
 * @retval 无
 */
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel)
{
  /* Check the parameters */
  assert_param(IS_BKP_TAMPER_PIN_LEVEL(BKP_TamperPinLevel));
  *(__IO uint32_t *) CR_TPAL_BB = BKP_TamperPinLevel;
}

/**
 * @brief 启用或禁用篡改引脚激活。
 * @param NewState：篡改密码激活的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void BKP_TamperPinCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_TPE_BB = (uint32_t)NewState;
}

/**
 * @brief 启用或禁用篡改引脚中断。
 * @param NewState：篡改引脚中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void BKP_ITConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_TPIE_BB = (uint32_t)NewState;
}

/**
 * @brief 选择要在 Tamper 引脚上输出的 RTC 输出源。
 * @param BKP_RTCOutputSource：指定 RTC 输出源。
 * 此参数可以是以下值之一：
 * @arg BKP_RTCOutputSource_None：篡改引脚上没有 RTC 输出。
 * @arg BKP_RTCOutputSource_CalibClock：输出带有频率的RTC时钟
 * 在篡改销上除以 64。
 * @arg BKP_RTCOutputSource_Alarm：输出RTC报警脉冲信号on
 * 篡改销。
 * @arg BKP_RTCOutputSource_Second：输出RTC秒脉冲信号on
 * 篡改销。
 * @retval 无
 */
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource)
{
  uint16_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_BKP_RTC_OUTPUT_SOURCE(BKP_RTCOutputSource));
  tmpreg = BKP->RTCCR;
  /* Clear CCO, ASOE and ASOS bits */
  tmpreg &= RTCCR_MASK;

  /* Set CCO, ASOE and ASOS bits according to BKP_RTCOutputSource value */
  tmpreg |= BKP_RTCOutputSource;
  /* Store the new value */
  BKP->RTCCR = tmpreg;
}

/**
 * @brief 设置 RTC 时钟校准值。
 * @param CalibrationValue：指定 RTC 时钟校准值。
 * 此参数必须是介于 0 和 0x7F 之间的数字。
 * @retval 无
 */
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue)
{
  uint16_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_BKP_CALIBRATION_VALUE(CalibrationValue));
  tmpreg = BKP->RTCCR;
  /* Clear CAL[6:0] bits */
  tmpreg &= RTCCR_CAL_MASK;
  /* Set CAL[6:0] bits according to CalibrationValue value */
  tmpreg |= CalibrationValue;
  /* Store the new value */
  BKP->RTCCR = tmpreg;
}

/**
 * @brief 将用户数据写入指定的数据备份寄存器。
 * @param BKP_DR：指定数据备份寄存器。
 * 该参数可以是 BKP_DRx 其中 x:[1, 42]
 * @param Data：要写入的数据
 * @retval 无
 */
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_BKP_DR(BKP_DR));

  tmp = (uint32_t)BKP_BASE;
  tmp += BKP_DR;

  *(__IO uint32_t *) tmp = Data;
}

/**
 * @brief 从指定的数据备份寄存器中读取数据。
 * @param BKP_DR：指定数据备份寄存器。
 * 该参数可以是 BKP_DRx 其中 x:[1, 42]
 * @retval 指定数据备份寄存器的内容
 */
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_BKP_DR(BKP_DR));

  tmp = (uint32_t)BKP_BASE;
  tmp += BKP_DR;

  return (*(__IO uint16_t *) tmp);
}

/**
 * @brief 检查是否设置了篡改引脚事件标志。
 * @param 无
 * @retval 篡改引脚事件标志的新状态（SET 或 RESET）。
 */
FlagStatus BKP_GetFlagStatus(void)
{
  return (FlagStatus)(*(__IO uint32_t *) CSR_TEF_BB);
}

/**
 * @brief 清除篡改引脚事件挂起标志。
 * @param 无
 * @retval 无
 */
void BKP_ClearFlag(void)
{
  /* Set CTE bit to clear Tamper Pin Event flag */
  BKP->CSR |= BKP_CSR_CTE;
}

/**
 * @brief 检查是否发生了篡改引脚中断。
 * @param 无
 * @retval 篡改引脚中断的新状态（SET 或 RESET）。
 */
ITStatus BKP_GetITStatus(void)
{
  return (ITStatus)(*(__IO uint32_t *) CSR_TIF_BB);
}

/**
 * @brief 清除篡改引脚中断挂起位。
 * @param 无
 * @retval 无
 */
void BKP_ClearITPendingBit(void)
{
  /* Set CTI bit to clear Tamper Pin Interrupt pending bit */
  BKP->CSR |= BKP_CSR_CTI;
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
