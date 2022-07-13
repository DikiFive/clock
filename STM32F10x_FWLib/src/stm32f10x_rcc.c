/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup RCC
 * @brief RCC driver modules
 * @{
 */

/** @defgroup RCC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup RCC_Private_Defines
 * @{
 */

/* ------------ RCC registers bit address in the alias region ----------- */
#define RCC_OFFSET (RCC_BASE - PERIPH_BASE)

/* --- CR Register ---*/

/* Alias word address of HSION bit */
#define CR_OFFSET (RCC_OFFSET + 0x00)
#define HSION_BitNumber 0x00
#define CR_HSION_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (HSION_BitNumber * 4))

/* Alias word address of PLLON bit */
#define PLLON_BitNumber 0x18
#define CR_PLLON_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLLON_BitNumber * 4))

#ifdef STM32F10X_CL
/* Alias word address of PLL2ON bit */
#define PLL2ON_BitNumber 0x1A
#define CR_PLL2ON_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLL2ON_BitNumber * 4))

/* Alias word address of PLL3ON bit */
#define PLL3ON_BitNumber 0x1C
#define CR_PLL3ON_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLL3ON_BitNumber * 4))
#endif /* STM32F10X_CL */

/* Alias word address of CSSON bit */
#define CSSON_BitNumber 0x13
#define CR_CSSON_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (CSSON_BitNumber * 4))

/* --- CFGR Register ---*/

/* Alias word address of USBPRE bit */
#define CFGR_OFFSET (RCC_OFFSET + 0x04)

#ifndef STM32F10X_CL
#define USBPRE_BitNumber 0x16
#define CFGR_USBPRE_BB (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (USBPRE_BitNumber * 4))
#else
#define OTGFSPRE_BitNumber 0x16
#define CFGR_OTGFSPRE_BB (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (OTGFSPRE_BitNumber * 4))
#endif /* STM32F10X_CL */

/* --- BDCR Register ---*/

/* Alias word address of RTCEN bit */
#define BDCR_OFFSET (RCC_OFFSET + 0x20)
#define RTCEN_BitNumber 0x0F
#define BDCR_RTCEN_BB (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (RTCEN_BitNumber * 4))

/* Alias word address of BDRST bit */
#define BDRST_BitNumber 0x10
#define BDCR_BDRST_BB (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (BDRST_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of LSION bit */
#define CSR_OFFSET (RCC_OFFSET + 0x24)
#define LSION_BitNumber 0x00
#define CSR_LSION_BB (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (LSION_BitNumber * 4))

#ifdef STM32F10X_CL
/* --- CFGR2 Register ---*/

/* Alias word address of I2S2SRC bit */
#define CFGR2_OFFSET (RCC_OFFSET + 0x2C)
#define I2S2SRC_BitNumber 0x11
#define CFGR2_I2S2SRC_BB (PERIPH_BB_BASE + (CFGR2_OFFSET * 32) + (I2S2SRC_BitNumber * 4))

/* Alias word address of I2S3SRC bit */
#define I2S3SRC_BitNumber 0x12
#define CFGR2_I2S3SRC_BB (PERIPH_BB_BASE + (CFGR2_OFFSET * 32) + (I2S3SRC_BitNumber * 4))
#endif /* STM32F10X_CL */

/* ---------------------- RCC registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_HSEBYP_Reset ((uint32_t)0xFFFBFFFF)
#define CR_HSEBYP_Set ((uint32_t)0x00040000)
#define CR_HSEON_Reset ((uint32_t)0xFFFEFFFF)
#define CR_HSEON_Set ((uint32_t)0x00010000)
#define CR_HSITRIM_Mask ((uint32_t)0xFFFFFF07)

/* CFGR register bit mask */
#if defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL) || defined(STM32F10X_CL)
#define CFGR_PLL_Mask ((uint32_t)0xFFC2FFFF)
#else
#define CFGR_PLL_Mask ((uint32_t)0xFFC0FFFF)
#endif /* STM32F10X_CL */

#define CFGR_PLLMull_Mask ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask ((uint32_t)0x00020000)
#define CFGR_SWS_Mask ((uint32_t)0x0000000C)
#define CFGR_SW_Mask ((uint32_t)0xFFFFFFFC)
#define CFGR_HPRE_Reset_Mask ((uint32_t)0xFFFFFF0F)
#define CFGR_HPRE_Set_Mask ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Reset_Mask ((uint32_t)0xFFFFF8FF)
#define CFGR_PPRE1_Set_Mask ((uint32_t)0x00000700)
#define CFGR_PPRE2_Reset_Mask ((uint32_t)0xFFFFC7FF)
#define CFGR_PPRE2_Set_Mask ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Reset_Mask ((uint32_t)0xFFFF3FFF)
#define CFGR_ADCPRE_Set_Mask ((uint32_t)0x0000C000)

/* CSR register bit mask */
#define CSR_RMVF_Set ((uint32_t)0x01000000)

#if defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL) || defined(STM32F10X_CL)
/* CFGR2 register bit mask */
#define CFGR2_PREDIV1SRC ((uint32_t)0x00010000)
#define CFGR2_PREDIV1 ((uint32_t)0x0000000F)
#endif
#ifdef STM32F10X_CL
#define CFGR2_PREDIV2 ((uint32_t)0x000000F0)
#define CFGR2_PLL2MUL ((uint32_t)0x00000F00)
#define CFGR2_PLL3MUL ((uint32_t)0x0000F000)
#endif /* STM32F10X_CL */

/* RCC Flag Mask */
#define FLAG_Mask ((uint8_t)0x1F)

/* CIR register byte 2 (Bits[15:8]) base address */
#define CIR_BYTE2_ADDRESS ((uint32_t)0x40021009)

/* CIR register byte 3 (Bits[23:16]) base address */
#define CIR_BYTE3_ADDRESS ((uint32_t)0x4002100A)

/* CFGR register byte 4 (Bits[31:24]) base address */
#define CFGR_BYTE4_ADDRESS ((uint32_t)0x40021007)

/* BDCR register base address */
#define BDCR_ADDRESS (PERIPH_BASE + BDCR_OFFSET)

/**
 * @}
 */

/** @defgroup RCC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup RCC_Private_Variables
 * @{
 */

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

/**
 * @}
 */

/** @defgroup RCC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup RCC_Private_Functions
 * @{
 */

/**
 * @brief 将 RCC 时钟配置重置为默认重置状态。
 * @param 无
 * @retval 无
 */
void RCC_DeInit(void)
{
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#ifndef STM32F10X_CL
  RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif /* STM32F10X_CL */

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifdef STM32F10X_CL
  /* Reset PLL2ON and PLL3ON bits */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x00FF0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#elif defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#else
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;
#endif /* STM32F10X_CL */
}

/**
 * @brief 配置外部高速振荡器 (HSE)。
 * @note 如果直接使用或通过 PLL 作为系统时钟，HSE 不能停止。
 * @param RCC_HSE：指定 HSE 的新状态。
 * 此参数可以是以下值之一：
 * @arg RCC_HSE_OFF: HSE 振荡器关闭
 * @arg RCC_HSE_ON: HSE 振荡器开启
 * @arg RCC_HSE_Bypass：HSE 振荡器被外部时钟旁路
 * @retval 无
 */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSE(RCC_HSE));
  /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
  /* Reset HSEON bit */
  RCC->CR &= CR_HSEON_Reset;
  /* Reset HSEBYP bit */
  RCC->CR &= CR_HSEBYP_Reset;
  /* Configure HSE (RCC_HSE_OFF is already covered by the code section above) */
  switch (RCC_HSE)
  {
  case RCC_HSE_ON:
    /* Set HSEON bit */
    RCC->CR |= CR_HSEON_Set;
    break;

  case RCC_HSE_Bypass:
    /* Set HSEBYP and HSEON bits */
    RCC->CR |= CR_HSEBYP_Set | CR_HSEON_Set;
    break;

  default:
    break;
  }
}

/**
 * @brief 等待 HSE 启动。
 * @param 无
 * @retval 一个 ErrorStatus 枚举值：
 * - 成功：HSE 振荡器稳定且可以使用
 * - 错误：HSE 振荡器尚未准备好
 */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;
  } while ((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));

  if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }
  return (status);
}

/**
 * @brief 调整内部高速振荡器 (HSI) 校准值。
 * @param HSCalibrationValue：指定校准微调值。
 * 此参数必须是介于 0 和 0x1F 之间的数字。
 * @retval 无
 */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_CALIBRATION_VALUE(HSICalibrationValue));
  tmpreg = RCC->CR;
  /* Clear HSITRIM[4:0] bits */
  tmpreg &= CR_HSITRIM_Mask;
  /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
  tmpreg |= (uint32_t)HSICalibrationValue << 3;
  /* Store the new value */
  RCC->CR = tmpreg;
}

/**
 * @brief 启用或禁用内部高速振荡器 (HSI)。
 * @note 如果直接使用 HSI 或通过 PLL 作为系统时钟，则无法停止 HSI。
 * @param NewState：恒指的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_HSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *)CR_HSION_BB = (uint32_t)NewState;
}

/**
 * @brief 配置 PLL 时钟源和倍频因子。
 * @note 此函数必须仅在 PLL 被禁用时使用。
 * @param RCC_PLLSource：指定 PLL 入口时钟源。
 * 对于@b STM32_Connectivity_line_devices 或@b STM32_Value_line_devices，
 * 此参数可以是以下值之一：
 * @arg RCC_PLLSource_HSI_Div2：HSI 振荡器时钟除以 2 被选为 PLL 时钟入口
 * @arg RCC_PLLSource_PREDIV1：PREDIV1 时钟被选为 PLL 时钟入口
 * 对于@b other_STM32_devices，该参数可以是以下值之一：
 * @arg RCC_PLLSource_HSI_Div2：HSI 振荡器时钟除以 2 被选为 PLL 时钟入口
 * @arg RCC_PLLSource_HSE_Div1：HSE 振荡器时钟选择为 PLL 时钟入口
 * @arg RCC_PLLSource_HSE_Div2：HSE 振荡器时钟除以 2 被选为 PLL 时钟入口
 * @param RCC_PLLMul：指定 PLL 倍增因子。
 * 对于@b STM32_Connectivity_line_devices，这个参数可以是RCC_PLLMul_x 其中x:{[4,9], 6_5}
 * 对于@b other_STM32_devices，这个参数可以是RCC_PLLMul_x 其中x:[2,16]
 * @retval 无
 */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));

  tmpreg = RCC->CFGR;
  /* Clear PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  tmpreg &= CFGR_PLL_Mask;
  /* Set the PLL configuration bits */
  tmpreg |= RCC_PLLSource | RCC_PLLMul;
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
 * @brief 启用或禁用 PLL。
 * @note 如果将 PLL 用作系统时钟，则不能禁用它。
 * @param NewState：PLL 的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_PLLCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *)CR_PLLON_BB = (uint32_t)NewState;
}

#if defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL) || defined(STM32F10X_CL)
/**
 * @brief  Configures the PREDIV1 division factor.
 * @note
 *   - This function must be used only when the PLL is disabled.
 *   - This function applies only to STM32 Connectivity line and Value line
 *     devices.
 * @param  RCC_PREDIV1_Source: specifies the PREDIV1 clock source.
 *   This parameter can be one of the following values:
 *     @arg RCC_PREDIV1_Source_HSE: HSE selected as PREDIV1 clock
 *     @arg RCC_PREDIV1_Source_PLL2: PLL2 selected as PREDIV1 clock
 * @note
 *   For @b STM32_Value_line_devices this parameter is always RCC_PREDIV1_Source_HSE
 * @param  RCC_PREDIV1_Div: specifies the PREDIV1 clock division factor.
 *   This parameter can be RCC_PREDIV1_Divx where x:[1,16]
 * @retval None
 */
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Source, uint32_t RCC_PREDIV1_Div)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PREDIV1_SOURCE(RCC_PREDIV1_Source));
  assert_param(IS_RCC_PREDIV1(RCC_PREDIV1_Div));

  tmpreg = RCC->CFGR2;
  /* Clear PREDIV1[3:0] and PREDIV1SRC bits */
  tmpreg &= ~(CFGR2_PREDIV1 | CFGR2_PREDIV1SRC);
  /* Set the PREDIV1 clock source and division factor */
  tmpreg |= RCC_PREDIV1_Source | RCC_PREDIV1_Div;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}
#endif

#ifdef STM32F10X_CL
/**
 * @brief  Configures the PREDIV2 division factor.
 * @note
 *   - This function must be used only when both PLL2 and PLL3 are disabled.
 *   - This function applies only to STM32 Connectivity line devices.
 * @param  RCC_PREDIV2_Div: specifies the PREDIV2 clock division factor.
 *   This parameter can be RCC_PREDIV2_Divx where x:[1,16]
 * @retval None
 */
void RCC_PREDIV2Config(uint32_t RCC_PREDIV2_Div)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PREDIV2(RCC_PREDIV2_Div));

  tmpreg = RCC->CFGR2;
  /* Clear PREDIV2[3:0] bits */
  tmpreg &= ~CFGR2_PREDIV2;
  /* Set the PREDIV2 division factor */
  tmpreg |= RCC_PREDIV2_Div;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}

/**
 * @brief  Configures the PLL2 multiplication factor.
 * @note
 *   - This function must be used only when the PLL2 is disabled.
 *   - This function applies only to STM32 Connectivity line devices.
 * @param  RCC_PLL2Mul: specifies the PLL2 multiplication factor.
 *   This parameter can be RCC_PLL2Mul_x where x:{[8,14], 16, 20}
 * @retval None
 */
void RCC_PLL2Config(uint32_t RCC_PLL2Mul)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PLL2_MUL(RCC_PLL2Mul));

  tmpreg = RCC->CFGR2;
  /* Clear PLL2Mul[3:0] bits */
  tmpreg &= ~CFGR2_PLL2MUL;
  /* Set the PLL2 configuration bits */
  tmpreg |= RCC_PLL2Mul;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}

/**
 * @brief  Enables or disables the PLL2.
 * @note
 *   - The PLL2 can not be disabled if it is used indirectly as system clock
 *     (i.e. it is used as PLL clock entry that is used as System clock).
 *   - This function applies only to STM32 Connectivity line devices.
 * @param  NewState: new state of the PLL2. This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_PLL2Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *)CR_PLL2ON_BB = (uint32_t)NewState;
}

/**
 * @brief  Configures the PLL3 multiplication factor.
 * @note
 *   - This function must be used only when the PLL3 is disabled.
 *   - This function applies only to STM32 Connectivity line devices.
 * @param  RCC_PLL3Mul: specifies the PLL3 multiplication factor.
 *   This parameter can be RCC_PLL3Mul_x where x:{[8,14], 16, 20}
 * @retval None
 */
void RCC_PLL3Config(uint32_t RCC_PLL3Mul)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PLL3_MUL(RCC_PLL3Mul));

  tmpreg = RCC->CFGR2;
  /* Clear PLL3Mul[3:0] bits */
  tmpreg &= ~CFGR2_PLL3MUL;
  /* Set the PLL3 configuration bits */
  tmpreg |= RCC_PLL3Mul;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}

/**
 * @brief  Enables or disables the PLL3.
 * @note   This function applies only to STM32 Connectivity line devices.
 * @param  NewState: new state of the PLL3. This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_PLL3Cmd(FunctionalState NewState)
{
  /* Check the parameters */

  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *)CR_PLL3ON_BB = (uint32_t)NewState;
}
#endif /* STM32F10X_CL */

/**
 * @brief 配置系统时钟 (SYSCLK)。
 * @param RCC_SYSCLKSource：指定用作系统时钟的时钟源。
 * 此参数可以是以下值之一：
 * @arg RCC_SYSCLKSource_HSI: 选择 HSI 作为系统时钟
 * @arg RCC_SYSCLKSource_HSE: 选择 HSE 作为系统时钟
 * @arg RCC_SYSCLKSource_PLLCLK：选择 PLL 作为系统时钟
 * @retval 无
 */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
  tmpreg = RCC->CFGR;
  /* Clear SW[1:0] bits */
  tmpreg &= CFGR_SW_Mask;
  /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
  tmpreg |= RCC_SYSCLKSource;
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
 * @brief 返回用作系统时钟的时钟源。
 * @param 无
 * @retval 用作系统时钟的时钟源。 返回值可以
 * 是以下之一：
 * - 0x00: HSI 用作系统时钟
 * - 0x04: HSE 用作系统时钟
 * - 0x08: PLL 用作系统时钟
 */
uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR & CFGR_SWS_Mask));
}

/**
 * @brief 配置 AHB 时钟 (HCLK)。
 * @param RCC_SYSCLK：定义 AHB 时钟分频器。 这个时钟来自
 * 系统时钟 (SYSCLK)。
 * 此参数可以是以下值之一：
 * @arg RCC_SYSCLK_Div1：AHB 时钟 = SYSCLK
 * @arg RCC_SYSCLK_Div2：AHB 时钟 = SYSCLK/2
 * @arg RCC_SYSCLK_Div4：AHB 时钟 = SYSCLK/4
 * @arg RCC_SYSCLK_Div8：AHB 时钟 = SYSCLK/8
 * @arg RCC_SYSCLK_Div16：AHB 时钟 = SYSCLK/16
 * @arg RCC_SYSCLK_Div64：AHB 时钟 = SYSCLK/64
 * @arg RCC_SYSCLK_Div128：AHB 时钟 = SYSCLK/128
 * @arg RCC_SYSCLK_Div256：AHB 时钟 = SYSCLK/256
 * @arg RCC_SYSCLK_Div512：AHB 时钟 = SYSCLK/512
 * @retval 无
 */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_HCLK(RCC_SYSCLK));
  tmpreg = RCC->CFGR;
  /* Clear HPRE[3:0] bits */
  tmpreg &= CFGR_HPRE_Reset_Mask;
  /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
  tmpreg |= RCC_SYSCLK;
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
 * @brief 配置低速 APB 时钟 (PCLK1)。
 * @param RCC_HCLK：定义 APB1 时钟分频器。 这个时钟来自
 * AHB 时钟 (HCLK)。
 * 此参数可以是以下值之一：
 * @arg RCC_HCLK_Div1: APB1 时钟 = HCLK
 * @arg RCC_HCLK_Div2：APB1 时钟 = HCLK/2
 * @arg RCC_HCLK_Div4: APB1 时钟 = HCLK/4
 * @arg RCC_HCLK_Div8: APB1 时钟 = HCLK/8
 * @arg RCC_HCLK_Div16：APB1 时钟 = HCLK/16
 * @retval 无
 */
void RCC_PCLK1Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  tmpreg = RCC->CFGR;
  /* Clear PPRE1[2:0] bits */
  tmpreg &= CFGR_PPRE1_Reset_Mask;
  /* Set PPRE1[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK;
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
 * @brief 配置高速 APB 时钟 (PCLK2)。
 * @param RCC_HCLK：定义 APB2 时钟分频器。 这个时钟来自
 * AHB 时钟 (HCLK)。
 * 此参数可以是以下值之一：
 * @arg RCC_HCLK_Div1: APB2 时钟 = HCLK
 * @arg RCC_HCLK_Div2：APB2 时钟 = HCLK/2
 * @arg RCC_HCLK_Div4: APB2 时钟 = HCLK/4
 * @arg RCC_HCLK_Div8: APB2 时钟 = HCLK/8
 * @arg RCC_HCLK_Div16: APB2 时钟 = HCLK/16
 * @retval 无
 */
void RCC_PCLK2Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  tmpreg = RCC->CFGR;
  /* Clear PPRE2[2:0] bits */
  tmpreg &= CFGR_PPRE2_Reset_Mask;
  /* Set PPRE2[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK << 3;
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/**
 * @brief 启用或禁用指定的 RCC 中断。
 * @param RCC_IT：指定要启用或禁用的 RCC 中断源。
 *
 * 对于@b STM32_Connectivity_line_devices，该参数可以任意组合
 * 以下值
 * @arg RCC_IT_LSIRDY: LSI 就绪中断
 * @arg RCC_IT_LSERDY: LSE 就绪中断
 * @arg RCC_IT_HSIRDY: HSI 就绪中断
 * @arg RCC_IT_HSERDY：HSE 就绪中断
 * @arg RCC_IT_PLLRDY：PLL 就绪中断
 * @arg RCC_IT_PLL2RDY：PLL2 就绪中断
 * @arg RCC_IT_PLL3RDY：PLL3 就绪中断
 *
 * 对于@b other_STM32_devices，该参数可以是任意组合
 * 以下值
 * @arg RCC_IT_LSIRDY: LSI 就绪中断
 * @arg RCC_IT_LSERDY: LSE 就绪中断
 * @arg RCC_IT_HSIRDY: HSI 就绪中断
 * @arg RCC_IT_HSERDY：HSE 就绪中断
 * @arg RCC_IT_PLLRDY：PLL 就绪中断
 *
 * @param NewState：指定 RCC 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_IT(RCC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Perform Byte access to RCC_CIR bits to enable the selected interrupts */
    *(__IO uint8_t *)CIR_BYTE2_ADDRESS |= RCC_IT;
  }
  else
  {
    /* Perform Byte access to RCC_CIR bits to disable the selected interrupts */
    *(__IO uint8_t *)CIR_BYTE2_ADDRESS &= (uint8_t)~RCC_IT;
  }
}

#ifndef STM32F10X_CL
/**
 * @brief 配置 USB 时钟 (USBCLK)。
 * @param RCC_USBCLKSource：指定 USB 时钟源。 这个时钟是
 * 源自 PLL 输出。
 * 此参数可以是以下值之一：
 * @arg RCC_USBCLKSource_PLLCLK_1Div5：PLL 时钟除以 1,5 选择为 USB
 * 时钟源
 * @arg RCC_USBCLKSource_PLLCLK_Div1：PLL 时钟选择为 USB 时钟源
 * @retval 无
 */
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_USBCLK_SOURCE(RCC_USBCLKSource));

  *(__IO uint32_t *)CFGR_USBPRE_BB = RCC_USBCLKSource;
}
#else
/**
 * @brief 配置 USB OTG FS 时钟 (OTGFSCLK)。
 * 此功能仅适用于 STM32 Connectivity 线路设备。
 * @param RCC_OTGFSCLKSource：指定 USB OTG FS 时钟源。
 * 该时钟来自 PLL 输出。
 * 此参数可以是以下值之一：
 * @arg RCC_OTGFSCLKSource_PLLVCO_Div3：PLL VCO 时钟除以 2 被选为 USB OTG FS 时钟源
 * @arg RCC_OTGFSCLKSource_PLLVCO_Div2：PLL VCO 时钟除以 2 被选为 USB OTG FS 时钟源
 * @retval 无
 */
void RCC_OTGFSCLKConfig(uint32_t RCC_OTGFSCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_OTGFSCLK_SOURCE(RCC_OTGFSCLKSource));

  *(__IO uint32_t *)CFGR_OTGFSPRE_BB = RCC_OTGFSCLKSource;
}
#endif /* STM32F10X_CL */

/**
 * @brief  Configures the ADC clock (ADCCLK).
 * @param  RCC_PCLK2: defines the ADC clock divider. This clock is derived from
 *   the APB2 clock (PCLK2).
 *   This parameter can be one of the following values:
 *     @arg RCC_PCLK2_Div2: ADC clock = PCLK2/2
 *     @arg RCC_PCLK2_Div4: ADC clock = PCLK2/4
 *     @arg RCC_PCLK2_Div6: ADC clock = PCLK2/6
 *     @arg RCC_PCLK2_Div8: ADC clock = PCLK2/8
 * @retval None
 */
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_ADCCLK(RCC_PCLK2));
  tmpreg = RCC->CFGR;
  /* Clear ADCPRE[1:0] bits */
  tmpreg &= CFGR_ADCPRE_Reset_Mask;
  /* Set ADCPRE[1:0] bits according to RCC_PCLK2 value */
  tmpreg |= RCC_PCLK2;
  /* Store the new value */
  RCC->CFGR = tmpreg;
}

#ifdef STM32F10X_CL
/**
 * @brief 配置 I2S2 时钟源 (I2S2CLK)。
 * @笔记
 * - 此函数必须在启用 I2S2 APB 时钟之前调用。
 * - 此功能仅适用于 STM32 Connectivity 线路设备。
 * @param RCC_I2S2CLKSource：指定 I2S2 时钟源。
 * 此参数可以是以下值之一：
 * @arg RCC_I2S2CLKSource_SYSCLK：系统时钟选择为 I2S2 时钟入口
 * @arg RCC_I2S2CLKSource_PLL3_VCO：PLL3 VCO 时钟选择为 I2S2 时钟入口
 * @retval 无
 */
void RCC_I2S2CLKConfig(uint32_t RCC_I2S2CLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_I2S2CLK_SOURCE(RCC_I2S2CLKSource));

  *(__IO uint32_t *)CFGR2_I2S2SRC_BB = RCC_I2S2CLKSource;
}

/**
 * @brief 配置 I2S3 时钟源 (I2S2CLK)。
 * @笔记
 * - 此函数必须在启用 I2S3 APB 时钟之前调用。
 * - 此功能仅适用于 STM32 Connectivity 线路设备。
 * @param RCC_I2S3CLKSource：指定 I2S3 时钟源。
 * 此参数可以是以下值之一：
 * @arg RCC_I2S3CLKSource_SYSCLK：系统时钟选择为 I2S3 时钟入口
 * @arg RCC_I2S3CLKSource_PLL3_VCO：PLL3 VCO 时钟选择为 I2S3 时钟入口
 * @retval 无
 */
void RCC_I2S3CLKConfig(uint32_t RCC_I2S3CLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_I2S3CLK_SOURCE(RCC_I2S3CLKSource));

  *(__IO uint32_t *)CFGR2_I2S3SRC_BB = RCC_I2S3CLKSource;
}
#endif /* STM32F10X_CL */

/**
 * @brief 配置外部低速振荡器 (LSE)。
 * @param RCC_LSE：指定 LSE 的新状态。
 * 此参数可以是以下值之一：
 * @arg RCC_LSE_OFF: LSE 振荡器关闭
 * @arg RCC_LSE_ON: LSE 振荡器开启
 * @arg RCC_LSE_Bypass：LSE 振荡器被外部时钟旁路
 * @retval 无
 */
void RCC_LSEConfig(uint8_t RCC_LSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE(RCC_LSE));
  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* Reset LSEON bit */
  *(__IO uint8_t *)BDCR_ADDRESS = RCC_LSE_OFF;
  /* Reset LSEBYP bit */
  *(__IO uint8_t *)BDCR_ADDRESS = RCC_LSE_OFF;
  /* Configure LSE (RCC_LSE_OFF is already covered by the code section above) */
  switch (RCC_LSE)
  {
  case RCC_LSE_ON:
    /* Set LSEON bit */
    *(__IO uint8_t *)BDCR_ADDRESS = RCC_LSE_ON;
    break;

  case RCC_LSE_Bypass:
    /* Set LSEBYP and LSEON bits */
    *(__IO uint8_t *)BDCR_ADDRESS = RCC_LSE_Bypass | RCC_LSE_ON;
    break;

  default:
    break;
  }
}

/**
 * @brief 启用或禁用内部低速振荡器 (LSI)。
 * @note 如果 IWDG 正在运行，则无法禁用 LSI。
 * @param NewState：LSI 的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_LSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *)CSR_LSION_BB = (uint32_t)NewState;
}

/**
 * @brief 配置 RTC 时钟 (RTCCLK)。
 * @note 一旦选择了 RTC 时钟，它就无法更改，除非备份域被重置。
 * @param RCC_RTCCLKSource：指定 RTC 时钟源。
 * 此参数可以是以下值之一：
 * @arg RCC_RTCCLKSource_LSE：选择 LSE 作为 RTC 时钟
 * @arg RCC_RTCCLKSource_LSI: LSI 被选为 RTC 时钟
 * @arg RCC_RTCCLKSource_HSE_Div128：HSE 时钟除以 128 选择为 RTC 时钟
 * @retval 无
 */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));
  /* Select the RTC clock source */
  RCC->BDCR |= RCC_RTCCLKSource;
}

/**
 * @brief 启用或禁用 RTC 时钟。
 * @note 只有在使用 RCC_RTCCLKConfig 函数选择了 RTC 时钟后才能使用此函数。
 * @param NewState：RTC 时钟的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *)BDCR_RTCEN_BB = (uint32_t)NewState;
}

/**
 * @brief 返回不同片上时钟的频率。
 * @param RCC_Clocks：指向 RCC_ClocksTypeDef 结构的指针，该结构将持有
 *时钟频率。
 * @note 使用时该函数的结果可能不正确
 * HSE 晶体的小数值。
 * @retval 无
 */
void RCC_GetClocksFreq(RCC_ClocksTypeDef *RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

#ifdef STM32F10X_CL
  uint32_t prediv1source = 0, prediv1factor = 0, prediv2factor = 0, pll2mull = 0;
#endif /* STM32F10X_CL */

#if defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
  uint32_t prediv1factor = 0;
#endif

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;

  switch (tmp)
  {
  case 0x00: /* HSI used as system clock */
    RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
    break;
  case 0x04: /* HSE used as system clock */
    RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
    break;
  case 0x08: /* PLL used as system clock */

    /* Get PLL clock source and multiplication factor ----------------------*/
    pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
    pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;

#ifndef STM32F10X_CL
    pllmull = (pllmull >> 18) + 2;

    if (pllsource == 0x00)
    { /* HSI oscillator clock divided by 2 selected as PLL clock entry */
      RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >> 1) * pllmull;
    }
    else
    {
#if defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD_VL)
      prediv1factor = (RCC->CFGR2 & CFGR2_PREDIV1) + 1;
      /* HSE oscillator clock selected as PREDIV1 clock entry */
      RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE / prediv1factor) * pllmull;
#else
      /* HSE selected as PLL clock entry */
      if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)RESET)
      { /* HSE oscillator clock divided by 2 */
        RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE >> 1) * pllmull;
      }
      else
      {
        RCC_Clocks->SYSCLK_Frequency = HSE_VALUE * pllmull;
      }
#endif
    }
#else
    pllmull = pllmull >> 18;

    if (pllmull != 0x0D)
    {
      pllmull += 2;
    }
    else
    { /* PLL multiplication factor = PLL input clock * 6.5 */
      pllmull = 13 / 2;
    }

    if (pllsource == 0x00)
    { /* HSI oscillator clock divided by 2 selected as PLL clock entry */
      RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >> 1) * pllmull;
    }
    else
    { /* PREDIV1 selected as PLL clock entry */

      /* Get PREDIV1 clock source and division factor */
      prediv1source = RCC->CFGR2 & CFGR2_PREDIV1SRC;
      prediv1factor = (RCC->CFGR2 & CFGR2_PREDIV1) + 1;

      if (prediv1source == 0)
      { /* HSE oscillator clock selected as PREDIV1 clock entry */
        RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE / prediv1factor) * pllmull;
      }
      else
      { /* PLL2 clock selected as PREDIV1 clock entry */

        /* Get PREDIV2 division factor and PLL2 multiplication factor */
        prediv2factor = ((RCC->CFGR2 & CFGR2_PREDIV2) >> 4) + 1;
        pll2mull = ((RCC->CFGR2 & CFGR2_PLL2MUL) >> 8) + 2;
        RCC_Clocks->SYSCLK_Frequency = (((HSE_VALUE / prediv2factor) * pll2mull) / prediv1factor) * pllmull;
      }
    }
#endif /* STM32F10X_CL */
    break;

  default:
    RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
    break;
  }

  /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* Get ADCCLK prescaler */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK clock frequency */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}

/**
 * @brief 启用或禁用 AHB 外设时钟。
 * @param RCC_AHBPeriph：指定 AHB 外设来门控其时钟。
 *
 * 对于@b STM32_Connectivity_line_devices，该参数可以任意组合
 * 以下值：
 * @arg RCC_AHBPeriph_DMA1
 * @arg RCC_AHBPeriph_DMA2
 * @arg RCC_AHBPeriph_SRAM
 * @arg RCC_AHBPeriph_FLITF
 * @arg RCC_AHBPeriph_CRC
 * @arg RCC_AHBPeriph_OTG_FS
 * @arg RCC_AHBPeriph_ETH_MAC
 * @arg RCC_AHBPeriph_ETH_MAC_Tx
 * @arg RCC_AHBPeriph_ETH_MAC_Rx
 *
 * 对于@b other_STM32_devices，该参数可以是任意组合
 * 以下值：
 * @arg RCC_AHBPeriph_DMA1
 * @arg RCC_AHBPeriph_DMA2
 * @arg RCC_AHBPeriph_SRAM
 * @arg RCC_AHBPeriph_FLITF
 * @arg RCC_AHBPeriph_CRC
 * @arg RCC_AHBPeriph_FSMC
 * @arg RCC_AHBPeriph_SDIO
 *
 * @note SRAM 和 FLITF 时钟只能在睡眠模式下禁用。
 * @param NewState：指定外设时钟的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}

/**
 * @brief 启用或禁用高速 APB (APB2) 外设时钟。
 * @param RCC_APB2Periph：指定 APB2 外设来门控其时钟。
 * 该参数可以是以下值的任意组合：
 * @arg RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
 * RCC_APB2Periph_GPIOC、RCC_APB2Periph_GPIOD、RCC_APB2Periph_GPIOE、
 * RCC_APB2Periph_GPIOF、RCC_APB2Periph_GPIOG、RCC_APB2Periph_ADC1、
 * RCC_APB2Periph_ADC2、RCC_APB2Periph_TIM1、RCC_APB2Periph_SPI1、
 * RCC_APB2Periph_TIM8、RCC_APB2Periph_USART1、RCC_APB2Periph_ADC3、
 * RCC_APB2Periph_TIM15、RCC_APB2Periph_TIM16、RCC_APB2Periph_TIM17、
 * RCC_APB2Periph_TIM9、RCC_APB2Periph_TIM10、RCC_APB2Periph_TIM11
 * @param NewState：指定外设时钟的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/**
 * @brief 启用或禁用低速 APB (APB1) 外设时钟。
 * @param RCC_APB1Periph：指定 APB1 外设来门控其时钟。
 * 该参数可以是以下值的任意组合：
 * @arg RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
 * RCC_APB1Periph_TIM5、RCC_APB1Periph_TIM6、RCC_APB1Periph_TIM7、
 * RCC_APB1Periph_WWDG、RCC_APB1Periph_SPI2、RCC_APB1Periph_SPI3、
 * RCC_APB1Periph_USART2、RCC_APB1Periph_USART3、RCC_APB1Periph_USART4、
 * RCC_APB1Periph_USART5、RCC_APB1Periph_I2C1、RCC_APB1Periph_I2C2、
 * RCC_APB1Periph_USB、RCC_APB1Periph_CAN1、RCC_APB1Periph_BKP、
 * RCC_APB1Periph_PWR、RCC_APB1Periph_DAC、RCC_APB1Periph_CEC、
 * RCC_APB1Periph_TIM12、RCC_APB1Periph_TIM13、RCC_APB1Periph_TIM14
 * @param NewState：指定外设时钟的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

#ifdef STM32F10X_CL
/**
 * @brief  Forces or releases AHB peripheral reset.
 * @note   This function applies only to STM32 Connectivity line devices.
 * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
 *   This parameter can be any combination of the following values:
 *     @arg RCC_AHBPeriph_OTG_FS
 *     @arg RCC_AHBPeriph_ETH_MAC
 * @param  NewState: new state of the specified peripheral reset.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH_RESET(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBRSTR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBRSTR &= ~RCC_AHBPeriph;
  }
}
#endif /* STM32F10X_CL */

/**
 * @brief 强制或释放高速 APB (APB2) 外设复位。
 * @param RCC_APB2Periph：指定要重置的 APB2 外设。
 * 该参数可以是以下值的任意组合：
 * @arg RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
 * RCC_APB2Periph_GPIOC、RCC_APB2Periph_GPIOD、RCC_APB2Periph_GPIOE、
 * RCC_APB2Periph_GPIOF、RCC_APB2Periph_GPIOG、RCC_APB2Periph_ADC1、
 * RCC_APB2Periph_ADC2、RCC_APB2Periph_TIM1、RCC_APB2Periph_SPI1、
 * RCC_APB2Periph_TIM8、RCC_APB2Periph_USART1、RCC_APB2Periph_ADC3、
 * RCC_APB2Periph_TIM15、RCC_APB2Periph_TIM16、RCC_APB2Periph_TIM17、
 * RCC_APB2Periph_TIM9、RCC_APB2Periph_TIM10、RCC_APB2Periph_TIM11
 * @param NewState：指定外设重置的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
 * @brief 强制或释放低速 APB (APB1) 外设复位。
 * @param RCC_APB1Periph：指定要复位的 APB1 外设。
 * 该参数可以是以下值的任意组合：
 * @arg RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
 * RCC_APB1Periph_TIM5、RCC_APB1Periph_TIM6、RCC_APB1Periph_TIM7、
 * RCC_APB1Periph_WWDG、RCC_APB1Periph_SPI2、RCC_APB1Periph_SPI3、
 * RCC_APB1Periph_USART2、RCC_APB1Periph_USART3、RCC_APB1Periph_USART4、
 * RCC_APB1Periph_USART5、RCC_APB1Periph_I2C1、RCC_APB1Periph_I2C2、
 * RCC_APB1Periph_USB、RCC_APB1Periph_CAN1、RCC_APB1Periph_BKP、
 * RCC_APB1Periph_PWR、RCC_APB1Periph_DAC、RCC_APB1Periph_CEC、
 * RCC_APB1Periph_TIM12、RCC_APB1Periph_TIM13、RCC_APB1Periph_TIM14
 * @param NewState：指定外设时钟的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
 * @brief 强制或释放备份域重置。
 * @param NewState：备份域重置的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void RCC_BackupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *)BDCR_BDRST_BB = (uint32_t)NewState;
}

/**
 * @brief  Enables or disables the Clock Security System.
 * @param  NewState: new state of the Clock Security System..
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *)CR_CSSON_BB = (uint32_t)NewState;
}

/**
 * @brief 选择要在 MCO 引脚上输出的时钟源。
 * @param RCC_MCO：指定要输出的时钟源。
 *
 * 对于@b STM32_Connectivity_line_devices，该参数可以是
 * 以下值：
 * @arg RCC_MCO_NoClock: 没有选择时钟
 * @arg RCC_MCO_SYSCLK：选择系统时钟
 * @arg RCC_MCO_HSI: 选择 HSI 振荡器时钟
 * @arg RCC_MCO_HSE: 选择 HSE 振荡器时钟
 * @arg RCC_MCO_PLLCLK_Div2：选择 PLL 时钟除以 2
 * @arg RCC_MCO_PLL2CLK：选择 PLL2 时钟
 * @arg RCC_MCO_PLL3CLK_Div2：选择 PLL3 时钟除以 2
 * @arg RCC_MCO_XT1：选择外部 3-25 MHz 振荡器时钟
 * @arg RCC_MCO_PLL3CLK：选择 PLL3 时钟
 *
 * 对于@b other_STM32_devices，该参数可以是以下值之一：
 * @arg RCC_MCO_NoClock: 没有选择时钟
 * @arg RCC_MCO_SYSCLK：选择系统时钟
 * @arg RCC_MCO_HSI: 选择 HSI 振荡器时钟
 * @arg RCC_MCO_HSE: 选择 HSE 振荡器时钟
 * @arg RCC_MCO_PLLCLK_Div2：选择 PLL 时钟除以 2
 *
 * @retval 无
 */
void RCC_MCOConfig(uint8_t RCC_MCO)
{
  /* Check the parameters */
  assert_param(IS_RCC_MCO(RCC_MCO));

  /* Perform Byte access to MCO bits to select the MCO source */
  *(__IO uint8_t *)CFGR_BYTE4_ADDRESS = RCC_MCO;
}

/**
 * @brief 检查是否设置了指定的 RCC 标志。
 * @param RCC_FLAG：指定要检查的标志。
 *
 * 对于@b STM32_Connectivity_line_devices，该参数可以是
 * 以下值：
 * @arg RCC_FLAG_HSIRDY: HSI 振荡器时钟就绪
 * @arg RCC_FLAG_HSERDY：HSE 振荡器时钟就绪
 * @arg RCC_FLAG_PLLRDY：PLL 时钟就绪
 * @arg RCC_FLAG_PLL2RDY：PLL2 时钟就绪
 * @arg RCC_FLAG_PLL3RDY：PLL3 时钟就绪
 * @arg RCC_FLAG_LSERDY: LSE 振荡器时钟就绪
 * @arg RCC_FLAG_LSIRDY: LSI 振荡器时钟就绪
 * @arg RCC_FLAG_PINRST：引脚复位
 * @arg RCC_FLAG_PORRST：POR/PDR 重置
 * @arg RCC_FLAG_SFTRST：软件复位
 * @arg RCC_FLAG_IWDGRST：独立看门狗复位
 * @arg RCC_FLAG_WWDGRST：窗口看门狗重置
 * @arg RCC_FLAG_LPWRRST：低功耗复位
 *
 * 对于@b other_STM32_devices，该参数可以是以下值之一：
 * @arg RCC_FLAG_HSIRDY: HSI 振荡器时钟就绪
 * @arg RCC_FLAG_HSERDY：HSE 振荡器时钟就绪
 * @arg RCC_FLAG_PLLRDY：PLL 时钟就绪
 * @arg RCC_FLAG_LSERDY: LSE 振荡器时钟就绪
 * @arg RCC_FLAG_LSIRDY: LSI 振荡器时钟就绪
 * @arg RCC_FLAG_PINRST：引脚复位
 * @arg RCC_FLAG_PORRST：POR/PDR 重置
 * @arg RCC_FLAG_SFTRST：软件复位
 * @arg RCC_FLAG_IWDGRST：独立看门狗复位
 * @arg RCC_FLAG_WWDGRST：窗口看门狗重置
 * @arg RCC_FLAG_LPWRRST：低功耗复位
 *
 * @retval RCC_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RCC_FLAG(RCC_FLAG));

  /* Get the RCC register index */
  tmp = RCC_FLAG >> 5;
  if (tmp == 1) /* The flag to check is in CR register */
  {
    statusreg = RCC->CR;
  }
  else if (tmp == 2) /* The flag to check is in BDCR register */
  {
    statusreg = RCC->BDCR;
  }
  else /* The flag to check is in CSR register */
  {
    statusreg = RCC->CSR;
  }

  /* Get the flag position */
  tmp = RCC_FLAG & FLAG_Mask;
  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
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
 * @brief 清除 RCC 重置标志。
 * @note 重置标志为：RCC_FLAG_PINRST、RCC_FLAG_PORRST、RCC_FLAG_SFTRST、
 * RCC_FLAG_IWDGRST、RCC_FLAG_WWDGRST、RCC_FLAG_LPWRRST
 * @param 无
 * @retval None
 */
void RCC_ClearFlag(void)
{
  /* Set RMVF bit to clear the reset flags */
  RCC->CSR |= CSR_RMVF_Set;
}

/**
 * @brief 检查指定的 RCC 中断是否发生。
 * @param RCC_IT：指定要检查的 RCC 中断源。
 *
 * 对于@b STM32_Connectivity_line_devices，该参数可以是
 * 以下值：
 * @arg RCC_IT_LSIRDY: LSI 就绪中断
 * @arg RCC_IT_LSERDY: LSE 就绪中断
 * @arg RCC_IT_HSIRDY: HSI 就绪中断
 * @arg RCC_IT_HSERDY：HSE 就绪中断
 * @arg RCC_IT_PLLRDY：PLL 就绪中断
 * @arg RCC_IT_PLL2RDY：PLL2 就绪中断
 * @arg RCC_IT_PLL3RDY：PLL3 就绪中断
 * @arg RCC_IT_CSS: 时钟安全系统中断
 *
 * 对于@b other_STM32_devices，该参数可以是以下值之一：
 * @arg RCC_IT_LSIRDY: LSI 就绪中断
 * @arg RCC_IT_LSERDY: LSE 就绪中断
 * @arg RCC_IT_HSIRDY: HSI 就绪中断
 * @arg RCC_IT_HSERDY：HSE 就绪中断
 * @arg RCC_IT_PLLRDY：PLL 就绪中断
 * @arg RCC_IT_CSS: 时钟安全系统中断
 *
 * @retval RCC_IT 的新状态（SET 或 RESET）。
 */
ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RCC_GET_IT(RCC_IT));

  /* Check the status of the specified RCC interrupt */
  if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the RCC_IT status */
  return bitstatus;
}

/**
 * @brief 清除 RCC 的中断挂起位。
 * @param RCC_IT：指定要清除的中断挂起位。
 *
 * 对于@b STM32_Connectivity_line_devices，该参数可以任意组合
 * 以下值：
 * @arg RCC_IT_LSIRDY: LSI 就绪中断
 * @arg RCC_IT_LSERDY: LSE 就绪中断
 * @arg RCC_IT_HSIRDY: HSI 就绪中断
 * @arg RCC_IT_HSERDY：HSE 就绪中断
 * @arg RCC_IT_PLLRDY：PLL 就绪中断
 * @arg RCC_IT_PLL2RDY：PLL2 就绪中断
 * @arg RCC_IT_PLL3RDY：PLL3 就绪中断
 * @arg RCC_IT_CSS: 时钟安全系统中断
 *
 * 对于@b other_STM32_devices，该参数可以是任意组合
 * 以下值：
 * @arg RCC_IT_LSIRDY: LSI 就绪中断
 * @arg RCC_IT_LSERDY: LSE 就绪中断
 * @arg RCC_IT_HSIRDY: HSI 就绪中断
 * @arg RCC_IT_HSERDY：HSE 就绪中断
 * @arg RCC_IT_PLLRDY：PLL 就绪中断
 *
 * @arg RCC_IT_CSS: 时钟安全系统中断
 * @retval 无
 */
void RCC_ClearITPendingBit(uint8_t RCC_IT)
{
  /* Check the parameters */
  assert_param(IS_RCC_CLEAR_IT(RCC_IT));

  /* Perform Byte access to RCC_CIR[23:16] bits to clear the selected interrupt
     pending bits */
  *(__IO uint8_t *)CIR_BYTE3_ADDRESS = RCC_IT;
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
