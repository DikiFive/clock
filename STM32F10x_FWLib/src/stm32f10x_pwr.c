/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR
  * @brief PWR driver modules
  * @{
  */

/** @defgroup PWR_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup PWR_Private_Defines
  * @{
  */

/* --------- PWR registers bit address in the alias region ---------- */
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* --- CR Register ---*/

/* Alias word address of DBP bit */
#define CR_OFFSET                (PWR_OFFSET + 0x00)
#define DBP_BitNumber            0x08
#define CR_DBP_BB                (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber           0x04
#define CR_PVDE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of EWUP bit */
#define CSR_OFFSET               (PWR_OFFSET + 0x04)
#define EWUP_BitNumber           0x08
#define CSR_EWUP_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP_BitNumber * 4))

/* ------------------ PWR registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_DS_MASK               ((uint32_t)0xFFFFFFFC)
#define CR_PLS_MASK              ((uint32_t)0xFFFFFF1F)


/**
  * @}
  */

/** @defgroup PWR_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup PWR_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup PWR_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup PWR_Private_Functions
  * @{
  */

/**
 * @brief 将 PWR 外设寄存器取消初始化为其默认复位值。
 * @param 无
 * @retval 无
 */
void PWR_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
 * @brief 启用或禁用对 RTC 和备份寄存器的访问。
 * @param NewState：访问 RTC 和备份寄存器的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)NewState;
}

/**
 * @brief 启用或禁用电源电压检测器 (PVD)。
 * @param NewState：PVD 的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void PWR_PVDCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)NewState;
}

/**
 * @brief 配置电源电压检测器 (PVD) 检测到的电压阈值。
 * @param PWR_PVDLevel：指定PVD检测级别
 * 此参数可以是以下值之一：
 * @arg PWR_PVDLevel_2V2：PVD 检测电平设置为 2.2V
 * @arg PWR_PVDLevel_2V3：PVD检测电平设置为2.3V
 * @arg PWR_PVDLevel_2V4：PVD检测电平设置为2.4V
 * @arg PWR_PVDLevel_2V5：PVD检测电平设置为2.5V
 * @arg PWR_PVDLevel_2V6：PVD 检测电平设置为 2.6V
 * @arg PWR_PVDLevel_2V7：PVD 检测电平设置为 2.7V
 * @arg PWR_PVDLevel_2V8：PVD 检测电平设置为 2.8V
 * @arg PWR_PVDLevel_2V9：PVD 检测电平设置为 2.9V
 * @retval 无
 */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
  tmpreg = PWR->CR;
  /* Clear PLS[7:5] bits */
  tmpreg &= CR_PLS_MASK;
  /* Set PLS[7:5] bits according to PWR_PVDLevel value */
  tmpreg |= PWR_PVDLevel;
  /* Store the new value */
  PWR->CR = tmpreg;
}

/**
 * @brief 启用或禁用唤醒引脚功能。
 * @param NewState：唤醒引脚功能的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void PWR_WakeUpPinCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_EWUP_BB = (uint32_t)NewState;
}

/**
 * @brief 进入停止模式。
 * @param PWR_Regulator：指定 STOP 模式下的稳压器状态。
 * 此参数可以是以下值之一：
 * @arg PWR_Regulator_ON：调节器开启的停止模式
 * @arg PWR_Regulator_LowPower：STOP 模式，稳压器处于低功耗模式
 * @param PWR_STOPEntry：指定是否使用 WFI 或 WFE 指令进入 STOP 模式。
 * 此参数可以是以下值之一：
 * @arg PWR_STOPEntry_WFI：使用 WFI 指令进入 STOP 模式
 * @arg PWR_STOPEntry_WFE：使用 WFE 指令进入 STOP 模式
 * @retval 无
 */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(PWR_Regulator));
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

  /* Select the regulator state in STOP mode ---------------------------------*/
  tmpreg = PWR->CR;
  /* Clear PDDS and LPDS bits */
  tmpreg &= CR_DS_MASK;
  /* Set LPDS bit according to PWR_Regulator value */
  tmpreg |= PWR_Regulator;
  /* Store the new value */
  PWR->CR = tmpreg;
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP;

  /* Select STOP mode entry --------------------------------------------------*/
  if(PWR_STOPEntry == PWR_STOPEntry_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);
}

/**
 * @brief 进入待机模式。
 * @param 无
 * @retval 无
 */
void PWR_EnterSTANDBYMode(void)
{
  /* Clear Wake-up flag */
  PWR->CR |= PWR_CR_CWUF;
  /* Select STANDBY mode */
  PWR->CR |= PWR_CR_PDDS;
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP;
/* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM   )
  __force_stores();
#endif
  /* Request Wait For Interrupt */
  __WFI();
}

/**
 * @brief 检查是否设置了指定的 PWR 标志。
 * @param PWR_FLAG：指定要检查的标志。
 * 此参数可以是以下值之一：
 * @arg PWR_FLAG_WU: 唤醒标志
 * @arg PWR_FLAG_SB：待机标志
 * @arg PWR_FLAG_PVDO：PVD 输出
 * @retval PWR_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

  if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
 * @brief 清除 PWR 的挂起标志。
 * @param PWR_FLAG：指定要清除的标志。
 * 此参数可以是以下值之一：
 * @arg PWR_FLAG_WU: 唤醒标志
 * @arg PWR_FLAG_SB：待机标志
 * @retval 无
 */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
  /* Check the parameters */
  assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

  PWR->CR |=  PWR_FLAG << 2;
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
