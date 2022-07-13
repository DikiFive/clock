/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup ADC
 * @brief ADC driver modules
 * @{
 */

/** @defgroup ADC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup ADC_Private_Defines
 * @{
 */

/* ADC DISCNUM mask */
#define CR1_DISCNUM_Reset ((uint32_t)0xFFFF1FFF)

/* ADC DISCEN mask */
#define CR1_DISCEN_Set ((uint32_t)0x00000800)
#define CR1_DISCEN_Reset ((uint32_t)0xFFFFF7FF)

/* ADC JAUTO mask */
#define CR1_JAUTO_Set ((uint32_t)0x00000400)
#define CR1_JAUTO_Reset ((uint32_t)0xFFFFFBFF)

/* ADC JDISCEN mask */
#define CR1_JDISCEN_Set ((uint32_t)0x00001000)
#define CR1_JDISCEN_Reset ((uint32_t)0xFFFFEFFF)

/* ADC AWDCH mask */
#define CR1_AWDCH_Reset ((uint32_t)0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CR1_AWDMode_Reset ((uint32_t)0xFF3FFDFF)

/* CR1 register Mask */
#define CR1_CLEAR_Mask ((uint32_t)0xFFF0FEFF)

/* ADC ADON mask */
#define CR2_ADON_Set ((uint32_t)0x00000001)
#define CR2_ADON_Reset ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define CR2_DMA_Set ((uint32_t)0x00000100)
#define CR2_DMA_Reset ((uint32_t)0xFFFFFEFF)

/* ADC RSTCAL mask */
#define CR2_RSTCAL_Set ((uint32_t)0x00000008)

/* ADC CAL mask */
#define CR2_CAL_Set ((uint32_t)0x00000004)

/* ADC SWSTART mask */
#define CR2_SWSTART_Set ((uint32_t)0x00400000)

/* ADC EXTTRIG mask */
#define CR2_EXTTRIG_Set ((uint32_t)0x00100000)
#define CR2_EXTTRIG_Reset ((uint32_t)0xFFEFFFFF)

/* ADC Software start mask */
#define CR2_EXTTRIG_SWSTART_Set ((uint32_t)0x00500000)
#define CR2_EXTTRIG_SWSTART_Reset ((uint32_t)0xFFAFFFFF)

/* ADC JEXTSEL mask */
#define CR2_JEXTSEL_Reset ((uint32_t)0xFFFF8FFF)

/* ADC JEXTTRIG mask */
#define CR2_JEXTTRIG_Set ((uint32_t)0x00008000)
#define CR2_JEXTTRIG_Reset ((uint32_t)0xFFFF7FFF)

/* ADC JSWSTART mask */
#define CR2_JSWSTART_Set ((uint32_t)0x00200000)

/* ADC injected software start mask */
#define CR2_JEXTTRIG_JSWSTART_Set ((uint32_t)0x00208000)
#define CR2_JEXTTRIG_JSWSTART_Reset ((uint32_t)0xFFDF7FFF)

/* ADC TSPD mask */
#define CR2_TSVREFE_Set ((uint32_t)0x00800000)
#define CR2_TSVREFE_Reset ((uint32_t)0xFF7FFFFF)

/* CR2 register Mask */
#define CR2_CLEAR_Mask ((uint32_t)0xFFF1F7FD)

/* ADC SQx mask */
#define SQR3_SQ_Set ((uint32_t)0x0000001F)
#define SQR2_SQ_Set ((uint32_t)0x0000001F)
#define SQR1_SQ_Set ((uint32_t)0x0000001F)

/* SQR1 register Mask */
#define SQR1_CLEAR_Mask ((uint32_t)0xFF0FFFFF)

/* ADC JSQx mask */
#define JSQR_JSQ_Set ((uint32_t)0x0000001F)

/* ADC JL mask */
#define JSQR_JL_Set ((uint32_t)0x00300000)
#define JSQR_JL_Reset ((uint32_t)0xFFCFFFFF)

/* ADC SMPx mask */
#define SMPR1_SMP_Set ((uint32_t)0x00000007)
#define SMPR2_SMP_Set ((uint32_t)0x00000007)

/* ADC JDRx registers offset */
#define JDR_Offset ((uint8_t)0x28)

/* ADC1 DR register base address */
#define DR_ADDRESS ((uint32_t)0x4001244C)

/**
 * @}
 */

/** @defgroup ADC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup ADC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup ADC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup ADC_Private_Functions
 * @{
 */

/**
 * @brief 将 ADCx 外设寄存器取消初始化为其默认复位值。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @retval 无
 */
void ADC_DeInit(ADC_TypeDef *ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  if (ADCx == ADC1)
  {
    /* Enable ADC1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
    /* Release ADC1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
  }
  else if (ADCx == ADC2)
  {
    /* Enable ADC2 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, ENABLE);
    /* Release ADC2 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);
  }
  else
  {
    if (ADCx == ADC3)
    {
      /* Enable ADC3 reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
      /* Release ADC3 from reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);
    }
  }
}

/**
 * @brief 根据指定参数初始化 ADCx 外设
 * 在 ADC_InitStruct 中。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_InitStruct：指向 ADC_InitTypeDef 结构的指针，该结构包含
 * 指定 ADC 外设的配置信息。
 * @retval 无
 */
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{
  uint32_t tmpreg1 = 0;
  uint8_t tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_MODE(ADC_InitStruct->ADC_Mode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ScanConvMode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
  assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrigConv));
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
  assert_param(IS_ADC_REGULAR_LENGTH(ADC_InitStruct->ADC_NbrOfChannel));

  /*---------------------------- ADCx CR1 Configuration -----------------*/
  /* Get the ADCx CR1 value */
  tmpreg1 = ADCx->CR1;
  /* Clear DUALMOD and SCAN bits */
  tmpreg1 &= CR1_CLEAR_Mask;
  /* Configure ADCx: Dual mode and scan conversion mode */
  /* Set DUALMOD bits according to ADC_Mode value */
  /* Set SCAN bit according to ADC_ScanConvMode value */
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_Mode | ((uint32_t)ADC_InitStruct->ADC_ScanConvMode << 8));
  /* Write to ADCx CR1 */
  ADCx->CR1 = tmpreg1;

  /*---------------------------- ADCx CR2 Configuration -----------------*/
  /* Get the ADCx CR2 value */
  tmpreg1 = ADCx->CR2;
  /* Clear CONT, ALIGN and EXTSEL bits */
  tmpreg1 &= CR2_CLEAR_Mask;
  /* Configure ADCx: external trigger event and continuous conversion mode */
  /* Set ALIGN bit according to ADC_DataAlign value */
  /* Set EXTSEL bits according to ADC_ExternalTrigConv value */
  /* Set CONT bit according to ADC_ContinuousConvMode value */
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ExternalTrigConv |
                        ((uint32_t)ADC_InitStruct->ADC_ContinuousConvMode << 1));
  /* Write to ADCx CR2 */
  ADCx->CR2 = tmpreg1;

  /*---------------------------- ADCx SQR1 Configuration -----------------*/
  /* Get the ADCx SQR1 value */
  tmpreg1 = ADCx->SQR1;
  /* Clear L bits */
  tmpreg1 &= SQR1_CLEAR_Mask;
  /* Configure ADCx: regular channel sequence length */
  /* Set L bits according to ADC_NbrOfChannel value */
  tmpreg2 |= (uint8_t)(ADC_InitStruct->ADC_NbrOfChannel - (uint8_t)1);
  tmpreg1 |= (uint32_t)tmpreg2 << 20;
  /* Write to ADCx SQR1 */
  ADCx->SQR1 = tmpreg1;
}

/**
 * @brief 用默认值填充每个 ADC_InitStruct 成员。
 * @param ADC_InitStruct ：指向将被初始化的 ADC_InitTypeDef 结构的指针。
 * @retval 无
 */
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */
  /* Initialize the ADC_Mode member */
  ADC_InitStruct->ADC_Mode = ADC_Mode_Independent;
  /* initialize the ADC_ScanConvMode member */
  ADC_InitStruct->ADC_ScanConvMode = DISABLE;
  /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;
  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;
  /* Initialize the ADC_NbrOfChannel member */
  ADC_InitStruct->ADC_NbrOfChannel = 1;
}

/**
 * @brief 启用或禁用指定的 ADC 外设。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param NewState：ADCx 外设的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_Cmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the ADON bit to wake up the ADC from power down mode */
    ADCx->CR2 |= CR2_ADON_Set;
  }
  else
  {
    /* Disable the selected ADC peripheral */
    ADCx->CR2 &= CR2_ADON_Reset;
  }
}

/**
 * @brief 启用或禁用指定的 ADC DMA 请求。
 * @param ADCx：其中 x 可以是 1 或 3 以选择 ADC 外设。
 * 注意：ADC2 没有 DMA 功能。
 * @param NewState：所选 ADC DMA 传输的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_DMACmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_DMA_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC DMA request */
    ADCx->CR2 |= CR2_DMA_Set;
  }
  else
  {
    /* Disable the selected ADC DMA request */
    ADCx->CR2 &= CR2_DMA_Reset;
  }
}

/**
 * @brief 启用或禁用指定的 ADC 中断。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_IT：指定要启用或禁用的 ADC 中断源。
 * 该参数可以是以下值的任意组合：
 * @arg ADC_IT_EOC: 转换结束中断掩码
 * @arg ADC_IT_AWD：模拟看门狗中断屏蔽
 * @arg ADC_IT_JEOC: 注入转换中断掩码结束
 * @param NewState：指定 ADC 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_ITConfig(ADC_TypeDef *ADCx, uint16_t ADC_IT, FunctionalState NewState)
{
  uint8_t itmask = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_IT(ADC_IT));
  /* Get the ADC IT index */
  itmask = (uint8_t)ADC_IT;
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->CR1 |= itmask;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->CR1 &= (~(uint32_t)itmask);
  }
}

/**
 * @brief 重置选定的 ADC 校准寄存器。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @retval 无
 */
void ADC_ResetCalibration(ADC_TypeDef *ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Resets the selected ADC calibration registers */
  ADCx->CR2 |= CR2_RSTCAL_Set;
}

/**
 * @brief 获取选定的 ADC 复位校准寄存器状态。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @retval ADC 复位校准寄存器（SET 或 RESET）的新状态。
 */
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef *ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Check the status of RSTCAL bit */
  if ((ADCx->CR2 & CR2_RSTCAL_Set) != (uint32_t)RESET)
  {
    /* RSTCAL bit is set */
    bitstatus = SET;
  }
  else
  {
    /* RSTCAL bit is reset */
    bitstatus = RESET;
  }
  /* Return the RSTCAL bit status */
  return bitstatus;
}

/**
 * @brief 启动选定的 ADC 校准过程。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @retval 无
 */
void ADC_StartCalibration(ADC_TypeDef *ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Enable the selected ADC calibration process */
  ADCx->CR2 |= CR2_CAL_Set;
}

/**
 * @brief 获取选定的 ADC 校准状态。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @retval ADC 校准的新状态（SET 或 RESET）。
 */
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef *ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Check the status of CAL bit */
  if ((ADCx->CR2 & CR2_CAL_Set) != (uint32_t)RESET)
  {
    /* CAL bit is set: calibration on going */
    bitstatus = SET;
  }
  else
  {
    /* CAL bit is reset: end of calibration */
    bitstatus = RESET;
  }
  /* Return the CAL bit status */
  return bitstatus;
}

/**
 * @brief 启用或禁用选定的 ADC 软件启动转换。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param NewState：所选 ADC 软件开始转换的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_SoftwareStartConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion on external event and start the selected
       ADC conversion */
    ADCx->CR2 |= CR2_EXTTRIG_SWSTART_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event and stop the selected
       ADC conversion */
    ADCx->CR2 &= CR2_EXTTRIG_SWSTART_Reset;
  }
}

/**
 * @brief 获取选定的 ADC 软件启动转换状态。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @retval ADC 软件开始转换的新状态（SET 或 RESET）。
 */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef *ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Check the status of SWSTART bit */
  if ((ADCx->CR2 & CR2_SWSTART_Set) != (uint32_t)RESET)
  {
    /* SWSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* SWSTART bit is reset */
    bitstatus = RESET;
  }
  /* Return the SWSTART bit status */
  return bitstatus;
}

/**
 * @brief 为选定的 ADC 常规配置不连续模式
 * 群组频道。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param Number：指定非连续模式常规通道
 * 计数值。 此数字必须介于 1 和 8 之间。
 * @retval 无
 */
void ADC_DiscModeChannelCountConfig(ADC_TypeDef *ADCx, uint8_t Number)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_REGULAR_DISC_NUMBER(Number));
  /* Get the old register value */
  tmpreg1 = ADCx->CR1;
  /* Clear the old discontinuous mode channel count */
  tmpreg1 &= CR1_DISCNUM_Reset;
  /* Set the discontinuous mode channel count */
  tmpreg2 = Number - 1;
  tmpreg1 |= tmpreg2 << 13;
  /* Store the new register value */
  ADCx->CR1 = tmpreg1;
}

/**
 * @brief 启用或禁用常规组的不连续模式
 * 指定ADC的通道
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param NewState：所选ADC不连续模式的新状态
 * 在常规群组频道上。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_DiscModeCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC regular discontinuous mode */
    ADCx->CR1 |= CR1_DISCEN_Set;
  }
  else
  {
    /* Disable the selected ADC regular discontinuous mode */
    ADCx->CR1 &= CR1_DISCEN_Reset;
  }
}

/**
 * @brief 为选定的 ADC 常规通道配置其对应的
 * 在音序器中排名及其采样时间。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_Channel：要配置的 ADC 通道。
 * 此参数可以是以下值之一：
 * @arg ADC_Channel_0：选择 ADC 通道 0
 * @arg ADC_Channel_1: 选择 ADC 通道 1
 * @arg ADC_Channel_2: 选择 ADC 通道 2
 * @arg ADC_Channel_3: 选择 ADC 通道 3
 * @arg ADC_Channel_4: 选择 ADC 通道 4
 * @arg ADC_Channel_5：选择 ADC 通道 5
 * @arg ADC_Channel_6: 选择 ADC 通道 6
 * @arg ADC_Channel_7: 选择 ADC 通道 7
 * @arg ADC_Channel_8: 选择 ADC 通道 8
 * @arg ADC_Channel_9: 选择 ADC 通道 9
 * @arg ADC_Channel_10: 选择 ADC 通道 10
 * @arg ADC_Channel_11: 选择 ADC 通道 11
 * @arg ADC_Channel_12：选择 ADC 通道 12
 * @arg ADC_Channel_13: 选择 ADC 通道 13
 * @arg ADC_Channel_14: 选择 ADC 通道 14
 * @arg ADC_Channel_15: 选择 ADC 通道 15
 * @arg ADC_Channel_16: 选择 ADC 通道 16
 * @arg ADC_Channel_17: 选择 ADC 通道 17
 * @param Rank：常规组排序器中的排名。此参数必须介于 1 到 16 之间。
 * @param ADC_SampleTime：为所选通道设置的采样时间值。
 * 此参数可以是以下值之一：
 * @arg ADC_SampleTime_1Cycles5：采样时间等于 1.5 个周期
 * @arg ADC_SampleTime_7Cycles5：采样时间等于 7.5 个周期
 * @arg ADC_SampleTime_13Cycles5：采样时间等于 13.5 个周期
 * @arg ADC_SampleTime_28Cycles5：采样时间等于 28.5 个周期
 * @arg ADC_SampleTime_41Cycles5：采样时间等于 41.5 个周期
 * @arg ADC_SampleTime_55Cycles5：采样时间等于 55.5 个周期
 * @arg ADC_SampleTime_71Cycles5：采样时间等于 71.5 个周期
 * @arg ADC_SampleTime_239Cycles5：采样时间等于 239.5 个周期
 * @retval 无
 */
void ADC_RegularChannelConfig(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_REGULAR_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
  /* if ADC_Channel_10 ... ADC_Channel_17 is selected */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR1;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR1_SMP_Set << (3 * (ADC_Channel - 10));
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR2;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR2_SMP_Set << (3 * ADC_Channel);
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPR2 = tmpreg1;
  }
  /* For Rank 1 to 6 */
  if (Rank < 7)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR3;
    /* Calculate the mask to clear */
    tmpreg2 = SQR3_SQ_Set << (5 * (Rank - 1));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Rank < 13)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR2;
    /* Calculate the mask to clear */
    tmpreg2 = SQR2_SQ_Set << (5 * (Rank - 7));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SQR1;
    /* Calculate the mask to clear */
    tmpreg2 = SQR1_SQ_Set << (5 * (Rank - 13));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SQR1 = tmpreg1;
  }
}

/**
 * @brief 通过外部触发启用或禁用 ADCx 转换。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param NewState：所选 ADC 外部触发转换开始的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_ExternalTrigConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion on external event */
    ADCx->CR2 |= CR2_EXTTRIG_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event */
    ADCx->CR2 &= CR2_EXTTRIG_Reset;
  }
}

/**
 * @brief 返回常规通道的最后一次 ADCx 转换结果数据。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @retval 数据转换值。
 */
uint16_t ADC_GetConversionValue(ADC_TypeDef *ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Return the selected ADC conversion value */
  return (uint16_t)ADCx->DR;
}

/**
 * @brief 返回双模式下最后的 ADC1 和 ADC2 转换结果数据。
 * @retval 数据转换值。
 */
uint32_t ADC_GetDualModeConversionValue(void)
{
  /* Return the dual mode conversion value */
  return (*(__IO uint32_t *)DR_ADDRESS);
}

/**
 * @brief 启用或禁用选定的 ADC 自动注入组
 * 常规转换后的转换。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param NewState: 所选 ADC 自动注入转换的新状态
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_AutoInjectedConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC automatic injected group conversion */
    ADCx->CR1 |= CR1_JAUTO_Set;
  }
  else
  {
    /* Disable the selected ADC automatic injected group conversion */
    ADCx->CR1 &= CR1_JAUTO_Reset;
  }
}

/**
 * @brief 启用或禁用注入组的不连续模式
 * 指定ADC的通道
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param NewState：所选ADC不连续模式的新状态
 * 在注入组频道上。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_InjectedDiscModeCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC injected discontinuous mode */
    ADCx->CR1 |= CR1_JDISCEN_Set;
  }
  else
  {
    /* Disable the selected ADC injected discontinuous mode */
    ADCx->CR1 &= CR1_JDISCEN_Reset;
  }
}

/**
 * @brief 为注入通道转换配置 ADCx 外部触发。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_ExternalTrigInjecConv：指定启动注入转换的 ADC 触发器。
 * 此参数可以是以下值之一：
 * @arg ADC_ExternalTrigInjecConv_T1_TRGO：已选择 Timer1 TRGO 事件（用于 ADC1、ADC2 和 ADC3）
 * @arg ADC_ExternalTrigInjecConv_T1_CC4：选择 Timer1 捕捉比较 4（用于 ADC1、ADC2 和 ADC3）
 * @arg ADC_ExternalTrigInjecConv_T2_TRGO：选择了 Timer2 TRGO 事件（用于 ADC1 和 ADC2）
 * @arg ADC_ExternalTrigInjecConv_T2_CC1: Timer2 capture compare1 selected (用于 ADC1 和 ADC2)
 * @arg ADC_ExternalTrigInjecConv_T3_CC4: Timer3 capture compare4 selected (用于 ADC1 和 ADC2)
 * @arg ADC_ExternalTrigInjecConv_T4_TRGO：已选择 Timer4 TRGO 事件（用于 ADC1 和 ADC2）
 * @arg ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4：外部中断线 15 或 Timer8
 * 捕获选择的 compare4 事件（用于 ADC1 和 ADC2）
 * @arg ADC_ExternalTrigInjecConv_T4_CC3: Timer4 capture compare3 selected (仅适用于 ADC3)
 * @arg ADC_ExternalTrigInjecConv_T8_CC2: Timer8 capture compare2 selected (仅适用于 ADC3)
 * @arg ADC_ExternalTrigInjecConv_T8_CC4：选择 Timer8 捕获比较 4（仅适用于 ADC3）
 * @arg ADC_ExternalTrigInjecConv_T5_TRGO：已选择 Timer5 TRGO 事件（仅适用于 ADC3）
 * @arg ADC_ExternalTrigInjecConv_T5_CC4: Timer5 capture compare4 selected (仅适用于 ADC3)
 * @arg ADC_ExternalTrigInjecConv_None：注入转换由软件启动而不是
 * 通过外部触发（用于 ADC1、ADC2 和 ADC3）
 * @retval 无
 */
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef *ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_ExternalTrigInjecConv));
  /* Get the old register value */
  tmpreg = ADCx->CR2;
  /* Clear the old external event selection for injected group */
  tmpreg &= CR2_JEXTSEL_Reset;
  /* Set the external event selection for injected group */
  tmpreg |= ADC_ExternalTrigInjecConv;
  /* Store the new register value */
  ADCx->CR2 = tmpreg;
}

/**
 * @brief 通过启用或禁用 ADCx 注入通道转换
 * 外部触发
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param NewState: 所选 ADC 外部触发开始的新状态
 * 注入转换。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC external event selection for injected group */
    ADCx->CR2 |= CR2_JEXTTRIG_Set;
  }
  else
  {
    /* Disable the selected ADC external event selection for injected group */
    ADCx->CR2 &= CR2_JEXTTRIG_Reset;
  }
}

/**
 * @brief 启用或禁用注入的选定 ADC 启动
 * 频道转换。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param NewState：所选 ADC 软件的新状态开始注入转换。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC conversion for injected group on external event and start the selected
       ADC injected conversion */
    ADCx->CR2 |= CR2_JEXTTRIG_JSWSTART_Set;
  }
  else
  {
    /* Disable the selected ADC conversion on external event for injected group and stop the selected
       ADC injected conversion */
    ADCx->CR2 &= CR2_JEXTTRIG_JSWSTART_Reset;
  }
}

/**
 * @brief 获取选定的 ADC 软件开始注入转换状态。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @retval ADC 软件的新状态开始注入转换（SET 或 RESET）。
 */
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef *ADCx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Check the status of JSWSTART bit */
  if ((ADCx->CR2 & CR2_JSWSTART_Set) != (uint32_t)RESET)
  {
    /* JSWSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* JSWSTART bit is reset */
    bitstatus = RESET;
  }
  /* Return the JSWSTART bit status */
  return bitstatus;
}

/**
 * @brief 为选定的 ADC 注入通道配置其对应的
 * 在音序器中排名及其采样时间。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_Channel：要配置的 ADC 通道。
 * 此参数可以是以下值之一：
 * @arg ADC_Channel_0：选择 ADC 通道 0
 * @arg ADC_Channel_1: 选择 ADC 通道 1
 * @arg ADC_Channel_2: 选择 ADC 通道 2
 * @arg ADC_Channel_3: 选择 ADC 通道 3
 * @arg ADC_Channel_4: 选择 ADC 通道 4
 * @arg ADC_Channel_5：选择 ADC 通道 5
 * @arg ADC_Channel_6: 选择 ADC 通道 6
 * @arg ADC_Channel_7: 选择 ADC 通道 7
 * @arg ADC_Channel_8: 选择 ADC 通道 8
 * @arg ADC_Channel_9: 选择 ADC 通道 9
 * @arg ADC_Channel_10: 选择 ADC 通道 10
 * @arg ADC_Channel_11: 选择 ADC 通道 11
 * @arg ADC_Channel_12：选择 ADC 通道 12
 * @arg ADC_Channel_13: 选择 ADC 通道 13
 * @arg ADC_Channel_14: 选择 ADC 通道 14
 * @arg ADC_Channel_15: 选择 ADC 通道 15
 * @arg ADC_Channel_16: 选择 ADC 通道 16
 * @arg ADC_Channel_17: 选择 ADC 通道 17
 * @param Rank：注入组排序器中的排名。此参数必须介于 1 和 4 之间。
 * @param ADC_SampleTime：为所选通道设置的采样时间值。
 * 此参数可以是以下值之一：
 * @arg ADC_SampleTime_1Cycles5：采样时间等于 1.5 个周期
 * @arg ADC_SampleTime_7Cycles5：采样时间等于 7.5 个周期
 * @arg ADC_SampleTime_13Cycles5：采样时间等于 13.5 个周期
 * @arg ADC_SampleTime_28Cycles5：采样时间等于 28.5 个周期
 * @arg ADC_SampleTime_41Cycles5：采样时间等于 41.5 个周期
 * @arg ADC_SampleTime_55Cycles5：采样时间等于 55.5 个周期
 * @arg ADC_SampleTime_71Cycles5：采样时间等于 71.5 个周期
 * @arg ADC_SampleTime_239Cycles5：采样时间等于 239.5 个周期
 * @retval 无
 */
void ADC_InjectedChannelConfig(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_INJECTED_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
  /* if ADC_Channel_10 ... ADC_Channel_17 is selected */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR1;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR1_SMP_Set << (3 * (ADC_Channel - 10));
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADCx->SMPR2;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR2_SMP_Set << (3 * ADC_Channel);
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->SMPR2 = tmpreg1;
  }
  /* Rank configuration */
  /* Get the old register value */
  tmpreg1 = ADCx->JSQR;
  /* Get JL value: Number = JL+1 */
  tmpreg3 = (tmpreg1 & JSQR_JL_Set) >> 20;
  /* Calculate the mask to clear: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = JSQR_JSQ_Set << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  /* Clear the old JSQx bits for the selected rank */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  /* Set the JSQx bits for the selected rank */
  tmpreg1 |= tmpreg2;
  /* Store the new register value */
  ADCx->JSQR = tmpreg1;
}

/**
 * @brief 配置注入通道的序列器长度
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param Length：序列器长度。
 * 此参数必须是 1 到 4 之间的数字。
 * @retval 无
 */
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef *ADCx, uint8_t Length)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_LENGTH(Length));

  /* Get the old register value */
  tmpreg1 = ADCx->JSQR;
  /* Clear the old injected sequnence lenght JL bits */
  tmpreg1 &= JSQR_JL_Reset;
  /* Set the injected sequnence lenght JL bits */
  tmpreg2 = Length - 1;
  tmpreg1 |= tmpreg2 << 20;
  /* Store the new register value */
  ADCx->JSQR = tmpreg1;
}

/**
 * @brief 设置注入通道转换值偏移
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_InjectedChannel：ADC 注入通道以设置其偏移量。
 * 此参数可以是以下值之一：
 * @arg ADC_InjectedChannel_1: 选择注入通道1
 * @arg ADC_InjectedChannel_2: 选择注入通道 2
 * @arg ADC_InjectedChannel_3: 选择注入通道 3
 * @arg ADC_InjectedChannel_4: 选择注入通道4
 * @param Offset：所选 ADC 注入通道的偏移值
 * 此参数必须为 12 位值。
 * @retval 无
 */
void ADC_SetInjectedOffset(ADC_TypeDef *ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
  assert_param(IS_ADC_OFFSET(Offset));

  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel;

  /* Set the selected injected channel data offset */
  *(__IO uint32_t *)tmp = (uint32_t)Offset;
}

/**
 * @brief 返回 ADC 注入的通道转换结果
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_InjectedChannel：转换后的 ADC 注入通道。
 * 此参数可以是以下值之一：
 * @arg ADC_InjectedChannel_1: 选择注入通道1
 * @arg ADC_InjectedChannel_2: 选择注入通道 2
 * @arg ADC_InjectedChannel_3: 选择注入通道 3
 * @arg ADC_InjectedChannel_4: 选择注入通道4
 * @retval 数据转换值。
 */
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef *ADCx, uint8_t ADC_InjectedChannel)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));

  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel + JDR_Offset;

  /* Returns the selected injected channel conversion data value */
  return (uint16_t)(*(__IO uint32_t *)tmp);
}

/**
 * @brief 在单个/所有常规上启用或禁用模拟看门狗
 * 或注入通道
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_AnalogWatchdog：ADC 模拟看门狗配置。
 * 此参数可以是以下值之一：
 * @arg ADC_AnalogWatchdog_SingleRegEnable：单个常规通道上的模拟看门狗
 * @arg ADC_AnalogWatchdog_SingleInjecEnable：单个注入通道上的模拟看门狗
 * @arg ADC_AnalogWatchdog_SingleRegOrInjecEnable：单个常规或注入通道上的模拟看门狗
 * @arg ADC_AnalogWatchdog_AllRegEnable：所有常规通道上的模拟看门狗
 * @arg ADC_AnalogWatchdog_AllInjecEnable：所有注入通道上的模拟看门狗
 * @arg ADC_AnalogWatchdog_AllRegAllInjecEnable：所有常规和注入通道上的模拟看门狗
 * @arg ADC_AnalogWatchdog_None：模拟看门狗没有保护通道
 * @retval 无
 */
void ADC_AnalogWatchdogCmd(ADC_TypeDef *ADCx, uint32_t ADC_AnalogWatchdog)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_ANALOG_WATCHDOG(ADC_AnalogWatchdog));
  /* Get the old register value */
  tmpreg = ADCx->CR1;
  /* Clear AWDEN, AWDENJ and AWDSGL bits */
  tmpreg &= CR1_AWDMode_Reset;
  /* Set the analog watchdog enable mode */
  tmpreg |= ADC_AnalogWatchdog;
  /* Store the new register value */
  ADCx->CR1 = tmpreg;
}

/**
 * @brief 配置模拟看门狗的高低阈值。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param HighThreshold：ADC 模拟看门狗高阈值。
 * 此参数必须为 12 位值。
 * @param LowThreshold：ADC 模拟看门狗低阈值。
 * 此参数必须为 12 位值。
 * @retval 无
 */
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef *ADCx, uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));
  /* Set the ADCx high threshold */
  ADCx->HTR = HighThreshold;
  /* Set the ADCx low threshold */
  ADCx->LTR = LowThreshold;
}

/**
 * @brief 配置模拟看门狗保护的单通道
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_Channel：为模拟看门狗配置的 ADC 通道。
 * 此参数可以是以下值之一：
 * @arg ADC_Channel_0：选择 ADC 通道 0
 * @arg ADC_Channel_1: 选择 ADC 通道 1
 * @arg ADC_Channel_2: 选择 ADC 通道 2
 * @arg ADC_Channel_3: 选择 ADC 通道 3
 * @arg ADC_Channel_4: 选择 ADC 通道 4
 * @arg ADC_Channel_5：选择 ADC 通道 5
 * @arg ADC_Channel_6: 选择 ADC 通道 6
 * @arg ADC_Channel_7: 选择 ADC 通道 7
 * @arg ADC_Channel_8: 选择 ADC 通道 8
 * @arg ADC_Channel_9: 选择 ADC 通道 9
 * @arg ADC_Channel_10: 选择 ADC 通道 10
 * @arg ADC_Channel_11: 选择 ADC 通道 11
 * @arg ADC_Channel_12：选择 ADC 通道 12
 * @arg ADC_Channel_13: 选择 ADC 通道 13
 * @arg ADC_Channel_14: 选择 ADC 通道 14
 * @arg ADC_Channel_15: 选择 ADC 通道 15
 * @arg ADC_Channel_16: 选择 ADC 通道 16
 * @arg ADC_Channel_17: 选择 ADC 通道 17
 * @retval 无
 */
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef *ADCx, uint8_t ADC_Channel)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  /* Get the old register value */
  tmpreg = ADCx->CR1;
  /* Clear the Analog watchdog channel select bits */
  tmpreg &= CR1_AWDCH_Reset;
  /* Set the Analog watchdog channel */
  tmpreg |= ADC_Channel;
  /* Store the new register value */
  ADCx->CR1 = tmpreg;
}

/**
 * @brief 启用或禁用温度传感器和 Vrefint 通道。
 * @param NewState：温度传感器的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void ADC_TempSensorVrefintCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the temperature sensor and Vrefint channel*/
    ADC1->CR2 |= CR2_TSVREFE_Set;
  }
  else
  {
    /* Disable the temperature sensor and Vrefint channel*/
    ADC1->CR2 &= CR2_TSVREFE_Reset;
  }
}

/**
 * @brief 检查是否设置了指定的 ADC 标志。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_FLAG：指定要检查的标志。
 * 此参数可以是以下值之一：
 * @arg ADC_FLAG_AWD：模拟看门狗标志
 * @arg ADC_FLAG_EOC: 转换结束标志
 * @arg ADC_FLAG_JEOC: 注入组转换结束标志
 * @arg ADC_FLAG_JSTRT: 注入组转换标志的开始
 * @arg ADC_FLAG_STRT：常规组转换标志的开始
 * @retval ADC_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef *ADCx, uint8_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));
  /* Check the status of the specified ADC flag */
  if ((ADCx->SR & ADC_FLAG) != (uint8_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return bitstatus;
}

/**
 * @brief 清除 ADCx 的挂起标志。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_FLAG：指定要清除的标志。
 * 该参数可以是以下值的任意组合：
 * @arg ADC_FLAG_AWD：模拟看门狗标志
 * @arg ADC_FLAG_EOC: 转换结束标志
 * @arg ADC_FLAG_JEOC: 注入组转换结束标志
 * @arg ADC_FLAG_JSTRT: 注入组转换标志的开始
 * @arg ADC_FLAG_STRT：常规组转换标志的开始
 * @retval 无
 */
void ADC_ClearFlag(ADC_TypeDef *ADCx, uint8_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));
  /* Clear the selected ADC flags */
  ADCx->SR = ~(uint32_t)ADC_FLAG;
}

/**
 * @brief 检查是否发生了指定的 ADC 中断。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_IT：指定要检查的 ADC 中断源。
 * 此参数可以是以下值之一：
 * @arg ADC_IT_EOC: 转换结束中断掩码
 * @arg ADC_IT_AWD：模拟看门狗中断屏蔽
 * @arg ADC_IT_JEOC: 注入转换中断掩码结束
 * @retval ADC_IT 的新状态（SET 或 RESET）。
 */
ITStatus ADC_GetITStatus(ADC_TypeDef *ADCx, uint16_t ADC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t itmask = 0, enablestatus = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_IT(ADC_IT));
  /* Get the ADC IT index */
  itmask = ADC_IT >> 8;
  /* Get the ADC_IT enable bit status */
  enablestatus = (ADCx->CR1 & (uint8_t)ADC_IT);
  /* Check the status of the specified ADC interrupt */
  if (((ADCx->SR & itmask) != (uint32_t)RESET) && enablestatus)
  {
    /* ADC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_IT status */
  return bitstatus;
}

/**
 * @brief 清除 ADCx 的中断挂起位。
 * @param ADCx：其中 x 可以是 1、2 或 3 以选择 ADC 外设。
 * @param ADC_IT：指定要清除的 ADC 中断挂起位。
 * 该参数可以是以下值的任意组合：
 * @arg ADC_IT_EOC: 转换结束中断掩码
 * @arg ADC_IT_AWD：模拟看门狗中断屏蔽
 * @arg ADC_IT_JEOC: 注入转换中断掩码结束
 * @retval 无
 */
void ADC_ClearITPendingBit(ADC_TypeDef *ADCx, uint16_t ADC_IT)
{
  uint8_t itmask = 0;
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_IT(ADC_IT));
  /* Get the ADC IT index */
  itmask = (uint8_t)(ADC_IT >> 8);
  /* Clear the selected ADC interrupt pending bits */
  ADCx->SR = ~(uint32_t)itmask;
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
