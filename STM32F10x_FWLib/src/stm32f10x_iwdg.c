/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_iwdg.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup IWDG
  * @brief IWDG driver modules
  * @{
  */

/** @defgroup IWDG_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Private_Defines
  * @{
  */

/* ---------------------- IWDG registers bit mask ----------------------------*/

/* KR register bit mask */
#define KR_KEY_Reload    ((uint16_t)0xAAAA)
#define KR_KEY_Enable    ((uint16_t)0xCCCC)

/**
  * @}
  */

/** @defgroup IWDG_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Private_Functions
  * @{
  */

/**
 * @brief 启用或禁用对 IWDG_PR 和 IWDG_RLR 寄存器的写访问。
 * @param IWDG_WriteAccess：对 IWDG_PR 和 IWDG_RLR 寄存器的写访问的新状态。
 * 此参数可以是以下值之一：
 * @arg IWDG_WriteAccess_Enable：启用对 IWDG_PR 和 IWDG_RLR 寄存器的写访问
 * @arg IWDG_WriteAccess_Disable：禁用对 IWDG_PR 和 IWDG_RLR 寄存器的写访问
 * @retval 无
 */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess)
{
  /* Check the parameters */
  assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
  IWDG->KR = IWDG_WriteAccess;
}

/**
 * @brief 设置 IWDG 预分频器值。
 * @param IWDG_Prescaler：指定 IWDG 预分频器值。
 * 此参数可以是以下值之一：
 * @arg IWDG_Prescaler_4：IWDG 预分频器设置为 4
 * @arg IWDG_Prescaler_8：IWDG 预分频器设置为 8
 * @arg IWDG_Prescaler_16：IWDG 预分频器设置为 16
 * @arg IWDG_Prescaler_32：IWDG 预分频器设置为 32
 * @arg IWDG_Prescaler_64：IWDG 预分频器设置为 64
 * @arg IWDG_Prescaler_128：IWDG 预分频器设置为 128
 * @arg IWDG_Prescaler_256：IWDG 预分频器设置为 256
 * @retval 无
 */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));
  IWDG->PR = IWDG_Prescaler;
}

/**
 * @brief 设置 IWDG 重新加载值。
 * @param Reload：指定 IWDG 重新加载值。
 * 此参数必须是介于 0 和 0x0FFF 之间的数字。
 * @retval 无
 */
void IWDG_SetReload(uint16_t Reload)
{
  /* Check the parameters */
  assert_param(IS_IWDG_RELOAD(Reload));
  IWDG->RLR = Reload;
}

/**
 * @brief 使用重新加载寄存器中定义的值重新加载 IWDG 计数器
 *（禁用对 IWDG_PR 和 IWDG_RLR 寄存器的写访问）。
 * @param 无
 * @retval 无
 */
void IWDG_ReloadCounter(void)
{
  IWDG->KR = KR_KEY_Reload;
}

/**
 * @brief 启用 IWDG（禁用对 IWDG_PR 和 IWDG_RLR 寄存器的写访问）。
 * @param 无
 * @retval 无
 */
void IWDG_Enable(void)
{
  IWDG->KR = KR_KEY_Enable;
}

/**
 * @brief 检查是否设置了指定的 IWDG 标志。
 * @param IWDG_FLAG：指定要检查的标志。
 * 此参数可以是以下值之一：
 * @arg IWDG_FLAG_PVU：预分频器值更新正在进行
 * @arg IWDG_FLAG_RVU：重新加载值更新
 * @retval IWDG_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_IWDG_FLAG(IWDG_FLAG));
  if ((IWDG->SR & IWDG_FLAG) != (uint32_t)RESET)
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
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
