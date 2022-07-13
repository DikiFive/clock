/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_dbgmcu.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup DBGMCU
 * @brief DBGMCU driver modules
 * @{
 */

/** @defgroup DBGMCU_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup DBGMCU_Private_Defines
 * @{
 */

#define IDCODE_DEVID_MASK ((uint32_t)0x00000FFF)
/**
 * @}
 */

/** @defgroup DBGMCU_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup DBGMCU_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup DBGMCU_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup DBGMCU_Private_Functions
 * @{
 */

/**
 * @brief 返回设备修订标识符。
 * @param 无
 * @retval 设备修订标识符
 */
uint32_t DBGMCU_GetREVID(void)
{
  return (DBGMCU->IDCODE >> 16);
}

/**
 * @brief 返回设备标识符。
 * @param 无
 * @retval 设备标识符
 */
uint32_t DBGMCU_GetDEVID(void)
{
  return (DBGMCU->IDCODE & IDCODE_DEVID_MASK);
}

/**
 * @brief 配置指定的外设和低功耗模式行为
 * 当 MCU 处于 Debug 模式时。
 * @param DBGMCU_Periph：指定外设和低功耗模式。
 * 该参数可以是以下值的任意组合：
 * @arg DBGMCU_SLEEP：在 SLEEP 模式下保持调试器连接
 * @arg DBGMCU_STOP：在 STOP 模式下保持调试器连接
 * @arg DBGMCU_STANDBY：在待机模式下保持调试器连接
 * @arg DBGMCU_IWDG_STOP：当内核停止时，调试 IWDG 停止
 * @arg DBGMCU_WWDG_STOP：当核心停止时，调试 WWDG 停止
 * @arg DBGMCU_TIM1_STOP: TIM1 计数器在内核停止时停止
 * @arg DBGMCU_TIM2_STOP: TIM2 计数器在内核停止时停止
 * @arg DBGMCU_TIM3_STOP: TIM3 计数器在内核停止时停止
 * @arg DBGMCU_TIM4_STOP: TIM4 计数器在内核停止时停止
 * @arg DBGMCU_CAN1_STOP：当内核停止时，调试 CAN2 停止
 * @arg DBGMCU_I2C1_SMBUS_TIMEOUT：当核心停止时，I2C1 SMBUS 超时模式停止
 * @arg DBGMCU_I2C2_SMBUS_TIMEOUT：当核心停止时，I2C2 SMBUS 超时模式停止
 * @arg DBGMCU_TIM5_STOP: TIM5 计数器在内核停止时停止
 * @arg DBGMCU_TIM6_STOP：内核停止时 TIM6 计数器停止
 * @arg DBGMCU_TIM7_STOP: TIM7 计数器在内核停止时停止
 * @arg DBGMCU_TIM8_STOP: TIM8 计数器在内核停止时停止
 * @arg DBGMCU_CAN2_STOP：当核心停止时，调试 CAN2 停止
 * @arg DBGMCU_TIM15_STOP: TIM15 计数器在内核停止时停止
 * @arg DBGMCU_TIM16_STOP：内核停止时 TIM16 计数器停止
 * @arg DBGMCU_TIM17_STOP：内核停止时 TIM17 计数器停止
 * @arg DBGMCU_TIM9_STOP: TIM9 计数器在内核停止时停止
 * @arg DBGMCU_TIM10_STOP：内核停止时 TIM10 计数器停止
 * @arg DBGMCU_TIM11_STOP: TIM11 计数器在内核停止时停止
 * @arg DBGMCU_TIM12_STOP: TIM12 计数器在内核停止时停止
 * @arg DBGMCU_TIM13_STOP: TIM13 计数器在内核停止时停止
 * @arg DBGMCU_TIM14_STOP: TIM14 计数器在内核停止时停止
 * @param NewState：指定外设在调试模式下的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->CR |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->CR &= ~DBGMCU_Periph;
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
