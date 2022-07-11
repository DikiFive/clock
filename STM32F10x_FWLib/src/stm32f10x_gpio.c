
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup GPIO
 * @brief GPIO driver modules
 * @{
 */

/** @defgroup GPIO_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup GPIO_Private_Defines
 * @{
 */

/* ------------ RCC registers bit address in the alias region ----------------*/
#define AFIO_OFFSET (AFIO_BASE - PERIPH_BASE)

/* --- EVENTCR Register -----*/

/* Alias word address of EVOE bit */
#define EVCR_OFFSET (AFIO_OFFSET + 0x00)
#define EVOE_BitNumber ((uint8_t)0x07)
#define EVCR_EVOE_BB (PERIPH_BB_BASE + (EVCR_OFFSET * 32) + (EVOE_BitNumber * 4))

/* ---  MAPR Register ---*/
/* Alias word address of MII_RMII_SEL bit */
#define MAPR_OFFSET (AFIO_OFFSET + 0x04)
#define MII_RMII_SEL_BitNumber ((u8)0x17)
#define MAPR_MII_RMII_SEL_BB (PERIPH_BB_BASE + (MAPR_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4))

#define EVCR_PORTPINCONFIG_MASK ((uint16_t)0xFF80)
#define LSB_MASK ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK ((uint32_t)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK ((uint32_t)0x00100000)
/**
 * @}
 */

/** @defgroup GPIO_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup GPIO_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup GPIO_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup GPIO_Private_Functions
 * @{
 */

/**
 * @brief 将 GPIOx 外设寄存器取消初始化为其默认复位值。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @retval 无
 */
void GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if (GPIOx == GPIOA)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, DISABLE);
  }
  else if (GPIOx == GPIOC)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, DISABLE);
  }
  else if (GPIOx == GPIOD)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, DISABLE);
  }
  else if (GPIOx == GPIOE)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, DISABLE);
  }
  else if (GPIOx == GPIOF)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, DISABLE);
  }
  else
  {
    if (GPIOx == GPIOG)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, DISABLE);
    }
  }
}

/**
 * @brief 取消初始化备用函数（重映射、事件控制
 * 和 EXTI 配置）寄存器到它们的默认复位值。
 * @param 无
 * @retval 无
 */
void GPIO_AFIODeInit(void)
{
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, DISABLE);
}

/**
 * @brief 根据指定初始化 GPIOx 外设
 * GPIO_InitStruct 中的参数。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @param GPIO_InitStruct：指向 GPIO_InitTypeDef 结构的指针
 * 包含指定 GPIO 外设的配置信息。
 * @retval 无
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));

  /*---------------------------- GPIO Mode Configuration -----------------------*/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  {
    /* Check the parameters */
    assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
    /* Output mode */
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
  /*---------------------------- GPIO CRL Configuration ------------------------*/
  /* Configure the eight low port pins */
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* Set the corresponding ODR bit */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CRL = tmpreg;
  }
  /*---------------------------- GPIO CRH Configuration ------------------------*/
  /* Configure the eight high port pins */
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* Get the port pins position */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding high control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* Set the corresponding ODR bit */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}

/**
 * @brief 用默认值填充每个 GPIO_InitStruct 成员。
 * @param GPIO_InitStruct : 指向 GPIO_InitTypeDef 结构的指针
 * 被初始化。
 * @retval 无
 */
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}

/**
 * @brief 读取指定的输入端口引脚。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @param GPIO_Pin：指定要读取的端口位。
 * 此参数可以是 GPIO_Pin_x，其中 x 可以是 (0..15)。
 * @retval 输入端口引脚值。
 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
 * @brief 读取指定的 GPIO 输入数据端口。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @retval GPIO 输入数据端口值。
 */
uint16_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->IDR);
}

/**
 * @brief 读取指定的输出数据端口位。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @param GPIO_Pin：指定要读取的端口位。
 * 此参数可以是 GPIO_Pin_x，其中 x 可以是 (0..15)。
 * @retval 输出端口引脚值。
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
 * @brief 读取指定的 GPIO 输出数据端口。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @retval GPIO 输出数据端口值。
 */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->ODR);
}

/**
 * @brief 设置选定的数据端口位。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @param GPIO_Pin：指定要写入的端口位。
 * 此参数可以是 GPIO_Pin_x 的任意组合，其中 x 可以是 (0..15)。
 * @retval 无
 */
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->BSRR = GPIO_Pin;
}

/**
 * @brief 清除选定的数据端口位。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @param GPIO_Pin：指定要写入的端口位。
 * 此参数可以是 GPIO_Pin_x 的任意组合，其中 x 可以是 (0..15)。
 * @retval 无
 */
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->BRR = GPIO_Pin;
}

/**
 * @brief 设置或清除选定的数据端口位。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @param GPIO_Pin：指定要写入的端口位。
 * 此参数可以是 GPIO_Pin_x 之一，其中 x 可以是 (0..15)。
 * @param BitVal：指定要写入所选位的值。
 * 此参数可以是 BitAction 枚举值之一：
 * @arg Bit_RESET：清除端口引脚
 * @arg Bit_SET: 设置端口引脚
 * @retval 无
 */
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BRR = GPIO_Pin;
  }
}

/**
 * @brief 将数据写入指定的 GPIO 数据端口。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @param PortVal：指定要写入端口输出数据寄存器的值。
 * @retval 无
 */
void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR = PortVal;
}

/**
 * @brief 锁定 GPIO 引脚配置寄存器。
 * @param GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
 * @param GPIO_Pin：指定要写入的端口位。
 * 此参数可以是 GPIO_Pin_x 的任意组合，其中 x 可以是 (0..15)。
 * @retval 无
 */
void GPIO_PinLockConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0x00010000;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  tmp |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Reset LCKK bit */
  GPIOx->LCKR = GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
}

/**
 * @brief 选择用作事件输出的 GPIO 引脚。
 * @param GPIO_PortSource：选择用作源的 GPIO 端口
 * 用于事件输出。
 * 此参数可以是 GPIO_PortSourceGPIOx，其中 x 可以是 (A..E)。
 * @param GPIO_PinSource：指定事件输出的引脚。
 * 此参数可以是 GPIO_PinSourcex，其中 x 可以是 (0..15)。
 * @retval 无
 */
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmpreg = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_EVENTOUT_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));

  tmpreg = AFIO->EVCR;
  /* Clear the PORT[6:4] and PIN[3:0] bits */
  tmpreg &= EVCR_PORTPINCONFIG_MASK;
  tmpreg |= (uint32_t)GPIO_PortSource << 0x04;
  tmpreg |= GPIO_PinSource;
  AFIO->EVCR = tmpreg;
}

/**
 * @brief 启用或禁用事件输出。
 * @param NewState：事件输出的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void GPIO_EventOutputCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *)EVCR_EVOE_BB = (uint32_t)NewState;
}

/**
 * @brief 更改指定引脚的映射。
 * @param GPIO_Remap：选择要重新映射的引脚。
 * 此参数可以是以下值之一：
 * @arg GPIO_Remap_SPI1 : SPI1 备用函数映射
 * @arg GPIO_Remap_I2C1 : I2C1 备用函数映射
 * @arg GPIO_Remap_USART1 : USART1 备用函数映射
 * @arg GPIO_Remap_USART2 : USART2 备用函数映射
 * @arg GPIO_PartialRemap_USART3 : USART3 部分替代函数映射
 * @arg GPIO_FullRemap_USART3 : USART3 完整的备用函数映射
 * @arg GPIO_PartialRemap_TIM1 : TIM1 部分替代函数映射
 * @arg GPIO_FullRemap_TIM1 : TIM1 完整的备用函数映射
 * @arg GPIO_PartialRemap1_TIM2 : TIM2 Partial1 备用函数映射
 * @arg GPIO_PartialRemap2_TIM2 : TIM2 Partial2 备用函数映射
 * @arg GPIO_FullRemap_TIM2 : TIM2 完整的备用函数映射
 * @arg GPIO_PartialRemap_TIM3 : TIM3 部分替代函数映射
 * @arg GPIO_FullRemap_TIM3 : TIM3 完整的备用函数映射
 * @arg GPIO_Remap_TIM4 : TIM4 备用函数映射
 * @arg GPIO_Remap1_CAN1 : CAN1 备用功能映射
 * @arg GPIO_Remap2_CAN1 : CAN1 备用功能映射
 * @arg GPIO_Remap_PD01 : PD01 备用函数映射
 * @arg GPIO_Remap_TIM5CH4_LSI : LSI 连接到 TIM5 Channel4 输入捕捉以进行校准
 * @arg GPIO_Remap_ADC1_ETRGINJ : ADC1 外部触发注入转换重新映射
 * @arg GPIO_Remap_ADC1_ETRGREG : ADC1 外部触发规则转换重映射
 * @arg GPIO_Remap_ADC2_ETRGINJ : ADC2 外部触发注入转换重新映射
 * @arg GPIO_Remap_ADC2_ETRGREG : ADC2 外部触发规则转换重新映射
 * @arg GPIO_Remap_ETH : 以太网重映射（仅适用于连接线设备）
 * @arg GPIO_Remap_CAN2 : CAN2 重新映射（仅适用于连接线设备）
 * @arg GPIO_Remap_SWJ_NoJTRST : 完全启用 SWJ (JTAG-DP + SW-DP) 但没有 JTRST
 * @arg GPIO_Remap_SWJ_JTAGDisable : JTAG-DP 禁用和 SW-DP 启用
 * @arg GPIO_Remap_SWJ_Disable：完全禁用 SWJ (JTAG-DP + SW-DP)
 * @arg GPIO_Remap_SPI3 : SPI3/I2S3 备用功能映射（仅适用于连接线设备）
 * 当使用此函数重新映射 SPI3/I2S3 时，配置了 SWJ
 * 启用完全 SWJ (JTAG-DP + SW-DP) 但没有 JTRST。
 * @arg GPIO_Remap_TIM2ITR1_PTP_SOF：以太网 PTP 输出或 USB OTG SOF（帧开始）已连接
 * 到 TIM2 内部触发器 1 进行校准（仅适用于连接线设备）
 * 如果启用了 GPIO_Remap_TIM2ITR1_PTP_SOF，则 TIM2 ITR1 连接到
 * 以太网 PTP 输出。当 Reset TIM2 ITR1 连接到 USB OTG SOF 输出。
 * @arg GPIO_Remap_PTP_PPS : PB05 上的以太网 MAC PPS_PTS 输出（仅适用于连接线设备）
 * @arg GPIO_Remap_TIM15 : TIM15 备用函数映射（仅适用于 Value line 设备）
 * @arg GPIO_Remap_TIM16 : TIM16 备用函数映射（仅适用于 Value line 设备）
 * @arg GPIO_Remap_TIM17 : TIM17 备用函数映射（仅适用于 Value line 设备）
 * @arg GPIO_Remap_CEC : CEC 备用函数映射（仅适用于 Value line 设备）
 * @arg GPIO_Remap_TIM1_DMA : TIM1 DMA 请求映射（仅适用于 Value line 设备）
 * @arg GPIO_Remap_TIM9 : TIM9 备用功能映射（仅适用于 XL 密度设备）
 * @arg GPIO_Remap_TIM10 : TIM10 备用功能映射（仅适用于 XL 密度设备）
 * @arg GPIO_Remap_TIM11 : TIM11 备用功能映射（仅适用于 XL 密度设备）
 * @arg GPIO_Remap_TIM13 : TIM13 备用功能映射（仅适用于高密度值线和 XL 密度设备）
 * @arg GPIO_Remap_TIM14 : TIM14 备用功能映射（仅适用于高密度值线和 XL 密度设备）
 * @arg GPIO_Remap_FSMC_NADV : FSMC_NADV 备用功能映射（仅适用于高密度值线和 XL 密度器件）
 * @arg GPIO_Remap_TIM67_DAC_DMA : TIM6/TIM7 和 DAC DMA 请求重新映射（仅适用于高密度 Value line 设备）
 * @arg GPIO_Remap_TIM12 : TIM12 备用功能映射（仅适用于高密度价值线设备）
 * @arg GPIO_Remap_MISC：杂项重映射（DMA2 通道 5 位置和 DAC 触发器重映射，
 * 仅适用于高密度超值系列设备）
 * @param NewState：端口引脚重新映射的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)
{
  uint32_t tmp = 0x00, tmp1 = 0x00, tmpreg = 0x00, tmpmask = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_REMAP(GPIO_Remap));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if ((GPIO_Remap & 0x80000000) == 0x80000000)
  {
    tmpreg = AFIO->MAPR2;
  }
  else
  {
    tmpreg = AFIO->MAPR;
  }

  tmpmask = (GPIO_Remap & DBGAFR_POSITION_MASK) >> 0x10;
  tmp = GPIO_Remap & LSB_MASK;

  if ((GPIO_Remap & (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) == (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK))
  {
    tmpreg &= DBGAFR_SWJCFG_MASK;
    AFIO->MAPR &= DBGAFR_SWJCFG_MASK;
  }
  else if ((GPIO_Remap & DBGAFR_NUMBITS_MASK) == DBGAFR_NUMBITS_MASK)
  {
    tmp1 = ((uint32_t)0x03) << tmpmask;
    tmpreg &= ~tmp1;
    tmpreg |= ~DBGAFR_SWJCFG_MASK;
  }
  else
  {
    tmpreg &= ~(tmp << ((GPIO_Remap >> 0x15) * 0x10));
    tmpreg |= ~DBGAFR_SWJCFG_MASK;
  }

  if (NewState != DISABLE)
  {
    tmpreg |= (tmp << ((GPIO_Remap >> 0x15) * 0x10));
  }

  if ((GPIO_Remap & 0x80000000) == 0x80000000)
  {
    AFIO->MAPR2 = tmpreg;
  }
  else
  {
    AFIO->MAPR = tmpreg;
  }
}

/**
 * @brief 选择用作 EXTI 线的 GPIO 引脚。
 * @param GPIO_PortSource：选择用作 EXTI 线源的 GPIO 端口。
 * 此参数可以是 GPIO_PortSourceGPIOx，其中 x 可以是 (A..G)。
 * @param GPIO_PinSource：指定要配置的 EXTI 线。
 * 此参数可以是 GPIO_PinSourcex，其中 x 可以是 (0..15)。
 * @retval 无
 */
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_EXTI_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));

  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));
}

/**
 * @brief 选择以太网媒体接口。
 * @note 此功能仅适用于 STM32 Connectivity 线路设备。
 * @param GPIO_ETH_MediaInterface：指定媒体接口模式。
 * 此参数可以是以下值之一：
 * @arg GPIO_ETH_MediaInterface_MII：MII 模式
 * @arg GPIO_ETH_MediaInterface_RMII：RMII 模式
 * @retval 无
 */
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface)
{
  assert_param(IS_GPIO_ETH_MEDIA_INTERFACE(GPIO_ETH_MediaInterface));

  /* Configure MII_RMII selection bit */
  *(__IO uint32_t *)MAPR_MII_RMII_SEL_BB = GPIO_ETH_MediaInterface;
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
