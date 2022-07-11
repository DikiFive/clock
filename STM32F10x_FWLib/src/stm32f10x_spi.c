/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup SPI
 * @brief SPI driver modules
 * @{
 */

/** @defgroup SPI_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup SPI_Private_Defines
 * @{
 */

/* SPI SPE mask */
#define CR1_SPE_Set ((uint16_t)0x0040)
#define CR1_SPE_Reset ((uint16_t)0xFFBF)

/* I2S I2SE mask */
#define I2SCFGR_I2SE_Set ((uint16_t)0x0400)
#define I2SCFGR_I2SE_Reset ((uint16_t)0xFBFF)

/* SPI CRCNext mask */
#define CR1_CRCNext_Set ((uint16_t)0x1000)

/* SPI CRCEN mask */
#define CR1_CRCEN_Set ((uint16_t)0x2000)
#define CR1_CRCEN_Reset ((uint16_t)0xDFFF)

/* SPI SSOE mask */
#define CR2_SSOE_Set ((uint16_t)0x0004)
#define CR2_SSOE_Reset ((uint16_t)0xFFFB)

/* SPI registers Masks */
#define CR1_CLEAR_Mask ((uint16_t)0x3040)
#define I2SCFGR_CLEAR_Mask ((uint16_t)0xF040)

/* SPI or I2S mode selection masks */
#define SPI_Mode_Select ((uint16_t)0xF7FF)
#define I2S_Mode_Select ((uint16_t)0x0800)

/* I2S clock source selection masks */
#define I2S2_CLOCK_SRC ((uint32_t)(0x00020000))
#define I2S3_CLOCK_SRC ((uint32_t)(0x00040000))
#define I2S_MUL_MASK ((uint32_t)(0x0000F000))
#define I2S_DIV_MASK ((uint32_t)(0x000000F0))

/**
 * @}
 */

/** @defgroup SPI_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup SPI_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup SPI_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup SPI_Private_Functions
 * @{
 */

/**
 * @brief 将 SPIx 外设寄存器取消初始化为其默认值
 * 重置值（也影响 I2S）。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @retval 无
 */
void SPI_I2S_DeInit(SPI_TypeDef *SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if (SPIx == SPI1)
  {
    /* Enable SPI1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
    /* Release SPI1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
  }
  else if (SPIx == SPI2)
  {
    /* Enable SPI2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
    /* Release SPI2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
  }
  else
  {
    if (SPIx == SPI3)
    {
      /* Enable SPI3 reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
      /* Release SPI3 from reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
    }
  }
}

/**
 * @brief 根据指定初始化 SPIx 外设
 * SPI_InitStruct 中的参数。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @param SPI_InitStruct：指向 SPI_InitTypeDef 结构的指针
 * 包含指定 SPI 外设的配置信息。
 * @retval 无
 */
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct)
{
  uint16_t tmpreg = 0;

  /* check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Check the SPI parameters */
  assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));

  /*---------------------------- SPIx CR1 Configuration ------------------------*/
  /* Get the SPIx CR1 value */
  tmpreg = SPIx->CR1;
  /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
  tmpreg &= CR1_CLEAR_Mask;
  /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
     master/salve mode, CPOL and CPHA */
  /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
  /* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
  /* Set LSBFirst bit according to SPI_FirstBit value */
  /* Set BR bits according to SPI_BaudRatePrescaler value */
  /* Set CPOL bit according to SPI_CPOL value */
  /* Set CPHA bit according to SPI_CPHA value */
  tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
                       SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |
                       SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |
                       SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit);
  /* Write to SPIx CR1 */
  SPIx->CR1 = tmpreg;

  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
  SPIx->I2SCFGR &= SPI_Mode_Select;

  /*---------------------------- SPIx CRCPOLY Configuration --------------------*/
  /* Write to SPIx CRCPOLY */
  SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
}

/**
 * @brief 根据指定初始化 SPIx 外设
 * I2S_InitStruct 中的参数。
 * @param SPIx：其中 x 可以是 2 或 3 以选择 SPI 外设
 *（在 I2S 模式下配置）。
 * @param I2S_InitStruct：指向 I2S_InitTypeDef 结构的指针
 * 包含指定 SPI 外设的配置信息
 * 在 I2S 模式下配置。
 * @笔记
 * 该函数计算获得最大所需的最佳预分频器
 * 准确的音频频率（取决于 I2S 时钟源、PLL 值
 * 和产品配置）。 但如果预分频器值更大
 * 大于 511，将改为配置默认值 (0x02)。 *
 * @retval 无
 */
void I2S_Init(SPI_TypeDef *SPIx, I2S_InitTypeDef *I2S_InitStruct)
{
  uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  uint32_t tmp = 0;
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t sourceclock = 0;

  /* Check the I2S parameters */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));

  /*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  SPIx->I2SCFGR &= I2SCFGR_CLEAR_Mask;
  SPIx->I2SPR = 0x0002;

  /* Get the I2SCFGR register value */
  tmpreg = SPIx->I2SCFGR;

  /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
  if (I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default)
  {
    i2sodd = (uint16_t)0;
    i2sdiv = (uint16_t)2;
  }
  /* If the requested audio frequency is not the default, compute the prescaler */
  else
  {
    /* Check the frame length (For the Prescaler computing) */
    if (I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b)
    {
      /* Packet length is 16 bits */
      packetlength = 1;
    }
    else
    {
      /* Packet length is 32 bits */
      packetlength = 2;
    }

    /* Get the I2S clock source mask depending on the peripheral number */
    if (((uint32_t)SPIx) == SPI2_BASE)
    {
      /* The mask is relative to I2S2 */
      tmp = I2S2_CLOCK_SRC;
    }
    else
    {
      /* The mask is relative to I2S3 */
      tmp = I2S3_CLOCK_SRC;
    }

    /* Check the I2S clock source configuration depending on the Device:
       Only Connectivity line devices have the PLL3 VCO clock */
#ifdef STM32F10X_CL
    if ((RCC->CFGR2 & tmp) != 0)
    {
      /* Get the configuration bits of RCC PLL3 multiplier */
      tmp = (uint32_t)((RCC->CFGR2 & I2S_MUL_MASK) >> 12);

      /* Get the value of the PLL3 multiplier */
      if ((tmp > 5) && (tmp < 15))
      {
        /* Multiplier is between 8 and 14 (value 15 is forbidden) */
        tmp += 2;
      }
      else
      {
        if (tmp == 15)
        {
          /* Multiplier is 20 */
          tmp = 20;
        }
      }
      /* Get the PREDIV2 value */
      sourceclock = (uint32_t)(((RCC->CFGR2 & I2S_DIV_MASK) >> 4) + 1);

      /* Calculate the Source Clock frequency based on PLL3 and PREDIV2 values */
      sourceclock = (uint32_t)((HSE_Value / sourceclock) * tmp * 2);
    }
    else
    {
      /* I2S Clock source is System clock: Get System Clock frequency */
      RCC_GetClocksFreq(&RCC_Clocks);

      /* Get the source clock value: based on System Clock value */
      sourceclock = RCC_Clocks.SYSCLK_Frequency;
    }
#else  /* STM32F10X_HD */
    /* I2S Clock source is System clock: Get System Clock frequency */
    RCC_GetClocksFreq(&RCC_Clocks);

    /* Get the source clock value: based on System Clock value */
    sourceclock = RCC_Clocks.SYSCLK_Frequency;
#endif /* STM32F10X_CL */

    /* Compute the Real divider depending on the MCLK output state with a floating point */
    if (I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable)
    {
      /* MCLK output is enabled */
      tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    else
    {
      /* MCLK output is disabled */
      tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }

    /* Remove the floating point */
    tmp = tmp / 10;

    /* Check the parity of the divider */
    i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

    /* Compute the i2sdiv prescaler */
    i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

    /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
    i2sodd = (uint16_t)(i2sodd << 8);
  }

  /* Test if the divider is 1 or 0 or greater than 0xFF */
  if ((i2sdiv < 2) || (i2sdiv > 0xFF))
  {
    /* Set the default values */
    i2sdiv = 2;
    i2sodd = 0;
  }

  /* Write to SPIx I2SPR register the computed value */
  SPIx->I2SPR = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOutput));

  /* Configure the I2S with the SPI_InitStruct values */
  tmpreg |= (uint16_t)(I2S_Mode_Select | (uint16_t)(I2S_InitStruct->I2S_Mode |
                                                    (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat |
                                                                                                         (uint16_t)I2S_InitStruct->I2S_CPOL))));

  /* Write to SPIx I2SCFGR */
  SPIx->I2SCFGR = tmpreg;
}

/**
 * @brief 用其默认值填充每个 SPI_InitStruct 成员。
 * @param SPI_InitStruct : 指向将被初始化的 SPI_InitTypeDef 结构的指针。
 * @retval 无
 */
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct)
{
  /*--------------- Reset SPI init structure parameters values -----------------*/
  /* Initialize the SPI_Direction member */
  SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  /* initialize the SPI_Mode member */
  SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
  /* initialize the SPI_DataSize member */
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
  /* Initialize the SPI_CPOL member */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  /* Initialize the SPI_CPHA member */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  /* Initialize the SPI_NSS member */
  SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
  /* Initialize the SPI_BaudRatePrescaler member */
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  /* Initialize the SPI_FirstBit member */
  SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
  /* Initialize the SPI_CRCPolynomial member */
  SPI_InitStruct->SPI_CRCPolynomial = 7;
}

/**
 * @brief 用默认值填充每个 I2S_InitStruct 成员。
 * @param I2S_InitStruct ：指向将被初始化的 I2S_InitTypeDef 结构的指针。
 * @retval 无
 */
void I2S_StructInit(I2S_InitTypeDef *I2S_InitStruct)
{
  /*--------------- Reset I2S init structure parameters values -----------------*/
  /* Initialize the I2S_Mode member */
  I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;

  /* Initialize the I2S_Standard member */
  I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;

  /* Initialize the I2S_DataFormat member */
  I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;

  /* Initialize the I2S_MCLKOutput member */
  I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;

  /* Initialize the I2S_AudioFreq member */
  I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;

  /* Initialize the I2S_CPOL member */
  I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}

/**
 * @brief 启用或禁用指定的 SPI 外设。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @param NewState：SPIx 外设的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral */
    SPIx->CR1 |= CR1_SPE_Set;
  }
  else
  {
    /* Disable the selected SPI peripheral */
    SPIx->CR1 &= CR1_SPE_Reset;
  }
}

/**
 * @brief 启用或禁用指定的 SPI 外设（在 I2S 模式下）。
 * @param SPIx：其中 x 可以是 2 或 3 以选择 SPI 外设。
 * @param NewState：SPIx 外设的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void I2S_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral (in I2S mode) */
    SPIx->I2SCFGR |= I2SCFGR_I2SE_Set;
  }
  else
  {
    /* Disable the selected SPI peripheral (in I2S mode) */
    SPIx->I2SCFGR &= I2SCFGR_I2SE_Reset;
  }
}

/**
 * @brief 启用或禁用指定的 SPI/I2S 中断。
 * @param SPIx: 其中 x 可以是
 * - SPI 模式下为 1、2 或 3
 * - I2S 模式下为 2 或 3
 * @param SPI_I2S_IT：指定启用或禁用的 SPI/I2S 中断源。
 * 此参数可以是以下值之一：
 * @arg SPI_I2S_IT_TXE: Tx 缓冲区空中断掩码
 * @arg SPI_I2S_IT_RXNE: Rx 缓冲区不为空中断掩码
 * @arg SPI_I2S_IT_ERR：错误中断掩码
 * @param NewState：指定 SPI/I2S 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SPI_I2S_ITConfig(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState)
{
  uint16_t itpos = 0, itmask = 0;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_CONFIG_IT(SPI_I2S_IT));

  /* Get the SPI/I2S IT index */
  itpos = SPI_I2S_IT >> 4;

  /* Set the IT mask */
  itmask = (uint16_t)1 << (uint16_t)itpos;

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI/I2S interrupt */
    SPIx->CR2 |= itmask;
  }
  else
  {
    /* Disable the selected SPI/I2S interrupt */
    SPIx->CR2 &= (uint16_t)~itmask;
  }
}

/**
 * @brief 启用或禁用 SPIx/I2Sx DMA 接口。
 * @param SPIx: 其中 x 可以是
 * - SPI 模式下为 1、2 或 3
 * - I2S 模式下为 2 或 3
 * @param SPI_I2S_DMAReq：指定启用或禁用的 SPI/I2S DMA 传输请求。
 * 该参数可以是以下值的任意组合：
 * @arg SPI_I2S_DMAReq_Tx：Tx 缓冲区 DMA 传输请求
 * @arg SPI_I2S_DMAReq_Rx：Rx 缓冲区 DMA 传输请求
 * @param NewState：所选 SPI/I2S DMA 传输请求的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SPI_I2S_DMACmd(SPI_TypeDef *SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_DMAREQ(SPI_I2S_DMAReq));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI/I2S DMA requests */
    SPIx->CR2 |= SPI_I2S_DMAReq;
  }
  else
  {
    /* Disable the selected SPI/I2S DMA requests */
    SPIx->CR2 &= (uint16_t)~SPI_I2S_DMAReq;
  }
}

/**
 * @brief 通过 SPIx/I2Sx 外设传输数据。
 * @param SPIx: 其中 x 可以是
 * - SPI 模式下为 1、2 或 3
 * - I2S 模式下为 2 或 3
 * @param Data : 要传输的数据。
 * @retval 无
 */
void SPI_I2S_SendData(SPI_TypeDef *SPIx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Write in the DR register the data to be sent */
  SPIx->DR = Data;
}

/**
 * @brief 返回 SPIx/I2Sx 外设最近接收到的数据。
 * @param SPIx: 其中 x 可以是
 * - SPI 模式下为 1、2 或 3
 * - I2S 模式下为 2 或 3
 * @retval 接收到的数据的值。
 */
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef *SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Return the data in the DR register */
  return SPIx->DR;
}

/**
 * @brief 通过软件在内部配置所选 SPI 的 NSS 引脚。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @param SPI_NSSInternalSoft：指定 SPI NSS 内部状态。
 * 此参数可以是以下值之一：
 * @arg SPI_NSSInternalSoft_Set：内部设置 NSS 引脚
 * @arg SPI_NSSInternalSoft_Reset：内部复位 NSS 引脚
 * @retval 无
 */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef *SPIx, uint16_t SPI_NSSInternalSoft)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));
  if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
  {
    /* Set NSS pin internally by software */
    SPIx->CR1 |= SPI_NSSInternalSoft_Set;
  }
  else
  {
    /* Reset NSS pin internally by software */
    SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
  }
}
/**
 * @brief 启用或禁用选定 SPI 的 SS 输出。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @param NewState：SPIx SS 输出的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SPI_SSOutputCmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI SS output */
    SPIx->CR2 |= CR2_SSOE_Set;
  }
  else
  {
    /* Disable the selected SPI SS output */
    SPIx->CR2 &= CR2_SSOE_Reset;
  }
}

/**
 * @brief 配置所选 SPI 的数据大小。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @param SPI_DataSize：指定 SPI 数据大小。
 * 此参数可以是以下值之一：
 * @arg SPI_DataSize_16b: 设置数据帧格式为 16bit
 * @arg SPI_DataSize_8b: 设置数据帧格式为 8bit
 * @retval 无
 */
void SPI_DataSizeConfig(SPI_TypeDef *SPIx, uint16_t SPI_DataSize)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DATASIZE(SPI_DataSize));
  /* Clear DFF bit */
  SPIx->CR1 &= (uint16_t)~SPI_DataSize_16b;
  /* Set new DFF bit value */
  SPIx->CR1 |= SPI_DataSize;
}

/**
 * @brief 发送 SPIx CRC 值。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @retval 无
 */
void SPI_TransmitCRC(SPI_TypeDef *SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Enable the selected SPI CRC transmission */
  SPIx->CR1 |= CR1_CRCNext_Set;
}

/**
 * @brief 启用或禁用传输字节的 CRC 值计算。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @param NewState：SPIx CRC 值计算的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SPI_CalculateCRC(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI CRC calculation */
    SPIx->CR1 |= CR1_CRCEN_Set;
  }
  else
  {
    /* Disable the selected SPI CRC calculation */
    SPIx->CR1 &= CR1_CRCEN_Reset;
  }
}

/**
 * @brief 返回指定 SPI 的发送或接收 CRC 寄存器值。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @param SPI_CRC：指定要读取的 CRC 寄存器。
 * 此参数可以是以下值之一：
 * @arg SPI_CRC_Tx：选择 Tx CRC 寄存器
 * @arg SPI_CRC_Rx：选择 Rx CRC 寄存器
 * @retval 选择的 CRC 寄存器值..
 */
uint16_t SPI_GetCRC(SPI_TypeDef *SPIx, uint8_t SPI_CRC)
{
  uint16_t crcreg = 0;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC(SPI_CRC));
  if (SPI_CRC != SPI_CRC_Rx)
  {
    /* Get the Tx CRC register */
    crcreg = SPIx->TXCRCR;
  }
  else
  {
    /* Get the Rx CRC register */
    crcreg = SPIx->RXCRCR;
  }
  /* Return the selected CRC register */
  return crcreg;
}

/**
 * @brief 返回指定 SPI 的 CRC 多项式寄存器值。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @retval CRC 多项式寄存器值。
 */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef *SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Return the CRC polynomial register */
  return SPIx->CRCPR;
}

/**
 * @brief 为指定的 SPI 选择双向模式下的数据传输方向。
 * @param SPIx：其中 x 可以是 1、2 或 3 以选择 SPI 外设。
 * @param SPI_Direction：指定双向模式下的数据传输方向。
 * 此参数可以是以下值之一：
 * @arg SPI_Direction_Tx：选择 Tx 传输方向
 * @arg SPI_Direction_Rx: 选择 Rx 接收方向
 * @retval 无
 */
void SPI_BiDirectionalLineConfig(SPI_TypeDef *SPIx, uint16_t SPI_Direction)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DIRECTION(SPI_Direction));
  if (SPI_Direction == SPI_Direction_Tx)
  {
    /* Set the Tx only mode */
    SPIx->CR1 |= SPI_Direction_Tx;
  }
  else
  {
    /* Set the Rx only mode */
    SPIx->CR1 &= SPI_Direction_Rx;
  }
}

/**
 * @brief 检查是否设置了指定的 SPI/I2S 标志。
 * @param SPIx: 其中 x 可以是
 * - SPI 模式下为 1、2 或 3
 * - I2S 模式下为 2 或 3
 * @param SPI_I2S_FLAG：指定要检查的 SPI/I2S 标志。
 * 此参数可以是以下值之一：
 * @arg SPI_I2S_FLAG_TXE：发送缓冲区空标志。
 * @arg SPI_I2S_FLAG_RXNE：接收缓冲区非空标志。
 * @arg SPI_I2S_FLAG_BSY：忙碌标志。
 * @arg SPI_I2S_FLAG_OVR：溢出标志。
 * @arg SPI_FLAG_MODF：模式故障标志。
 * @arg SPI_FLAG_CRCERR：CRC 错误标志。
 * @arg I2S_FLAG_UDR：欠载错误标志。
 * @arg I2S_FLAG_CHSIDE：通道侧标志。
 * @retval SPI_I2S_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));
  /* Check the status of the specified SPI/I2S flag */
  if ((SPIx->SR & SPI_I2S_FLAG) != (uint16_t)RESET)
  {
    /* SPI_I2S_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_FLAG status */
  return bitstatus;
}

/**
 * @brief 清除 SPIx CRC 错误 (CRCERR) 标志。
 * @param SPIx: 其中 x 可以是
 * - SPI 模式下为 1、2 或 3
 * @param SPI_I2S_FLAG：指定要清除的 SPI 标志。
 * 此函数仅清除 CRCERR 标志。
 * @笔记
 * - OVR（溢出错误）标志由软件序列清除：读取
 * 对 SPI_DR 寄存器 (SPI_I2S_ReceiveData()) 的操作，然后进行读取
 * 对 SPI_SR 寄存器的操作 (SPI_I2S_GetFlagStatus())。
 * - UDR（欠载错误）标志由读取操作清除以
 * SPI_SR 寄存器 (SPI_I2S_GetFlagStatus())。
 * - MODF（模式故障）标志由软件序列清除：读/写
 * 对 SPI_SR 寄存器 (SPI_I2S_GetFlagStatus()) 的操作，后跟一个
 * 对 SPI_CR1 寄存器的写操作（SPI_Cmd() 以启用 SPI）。
 * @retval 无
 */
void SPI_I2S_ClearFlag(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_FLAG(SPI_I2S_FLAG));

  /* Clear the selected SPI CRC Error (CRCERR) flag */
  SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}

/**
 * @brief 检查指定的 SPI/I2S 中断是否发生。
 * @param SPIx: 其中 x 可以是
 * - SPI 模式下为 1、2 或 3
 * - I2S 模式下为 2 或 3
 * @param SPI_I2S_IT：指定要检查的 SPI/I2S 中断源。
 * 此参数可以是以下值之一：
 * @arg SPI_I2S_IT_TXE：发送缓冲区空中断。
 * @arg SPI_I2S_IT_RXNE：接收缓冲区非空中断。
 * @arg SPI_I2S_IT_OVR：溢出中断。
 * @arg SPI_IT_MODF：模式故障中断。
 * @arg SPI_IT_CRCERR：CRC 错误中断。
 * @arg I2S_IT_UDR：欠载错误中断。
 * @retval SPI_I2S_IT 的新状态（SET 或 RESET）。
 */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT)
{
  ITStatus bitstatus = RESET;
  uint16_t itpos = 0, itmask = 0, enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_IT(SPI_I2S_IT));

  /* Get the SPI/I2S IT index */
  itpos = 0x01 << (SPI_I2S_IT & 0x0F);

  /* Get the SPI/I2S IT mask */
  itmask = SPI_I2S_IT >> 4;

  /* Set the IT mask */
  itmask = 0x01 << itmask;

  /* Get the SPI_I2S_IT enable bit status */
  enablestatus = (SPIx->CR2 & itmask);

  /* Check the status of the specified SPI/I2S interrupt */
  if (((SPIx->SR & itpos) != (uint16_t)RESET) && enablestatus)
  {
    /* SPI_I2S_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_IT is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_IT status */
  return bitstatus;
}

/**
 * @brief 清除 SPIx CRC 错误 (CRCERR) 中断挂起位。
 * @param SPIx: 其中 x 可以是
 * - SPI 模式下为 1、2 或 3
 * @param SPI_I2S_IT：指定要清除的 SPI 中断挂起位。
 * 此函数仅清除 CRCERR 中断挂起位。
 * @笔记
 * - OVR (OverRun Error) 中断挂起位由软件清除
 * 序列：对 SPI_DR 寄存器的读取操作 (SPI_I2S_ReceiveData())
 * 之后是对 SPI_SR 寄存器 (SPI_I2S_GetITStatus()) 的读取操作。
 * - UDR（欠载错误）中断挂起位通过读取清除
 * 对 SPI_SR 寄存器的操作 (SPI_I2S_GetITStatus())。
 * - MODF（模式故障）中断挂起位由软件序列清除：
 * 对 SPI_SR 寄存器的读/写操作 (SPI_I2S_GetITStatus())
 * 之后是对 SPI_CR1 寄存器的写操作（SPI_Cmd() 以启用
 * SPI）。
 * @retval 无
 */
void SPI_I2S_ClearITPendingBit(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT)
{
  uint16_t itpos = 0;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_IT(SPI_I2S_IT));

  /* Get the SPI IT index */
  itpos = 0x01 << (SPI_I2S_IT & 0x0F);

  /* Clear the selected SPI CRC Error (CRCERR) interrupt pending bit */
  SPIx->SR = (uint16_t)~itpos;
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
