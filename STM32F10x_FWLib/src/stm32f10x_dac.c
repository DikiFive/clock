/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_dac.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup DAC
  * @brief DAC driver modules
  * @{
  */

/** @defgroup DAC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup DAC_Private_Defines
  * @{
  */

/* CR register Mask */
#define CR_CLEAR_MASK              ((uint32_t)0x00000FFE)

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_SET            ((uint32_t)0x00000003)
#define DUAL_SWTRIG_RESET          ((uint32_t)0xFFFFFFFC)

/* DHR registers offsets */
#define DHR12R1_OFFSET             ((uint32_t)0x00000008)
#define DHR12R2_OFFSET             ((uint32_t)0x00000014)
#define DHR12RD_OFFSET             ((uint32_t)0x00000020)

/* DOR register offset */
#define DOR_OFFSET                 ((uint32_t)0x0000002C)
/**
  * @}
  */

/** @defgroup DAC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DAC_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup DAC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup DAC_Private_Functions
  * @{
  */

/**
 * @brief 将 DAC 外设寄存器取消初始化为其默认复位值。
 * @param 无
 * @retval 无
 */
void DAC_DeInit(void)
{
  /* Enable DAC reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, ENABLE);
  /* Release DAC from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, DISABLE);
}

/**
 * @brief 根据指定初始化DAC外设
 * DAC_InitStruct 中的参数。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param DAC_InitStruct：指向 DAC_InitTypeDef 结构的指针
 * 包含指定 DAC 通道的配置信息。
 * @retval 无
 */
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* Check the DAC parameters */
  assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
  assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
  assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));
/*---------------------------- DAC CR Configuration --------------------------*/
  /* Get the DAC CR value */
  tmpreg1 = DAC->CR;
  /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
  tmpreg1 &= ~(CR_CLEAR_MASK << DAC_Channel);
  /* Configure for the selected DAC channel: buffer output, trigger, wave generation,
     mask/amplitude for wave generation */
  /* Set TSELx and TENx bits according to DAC_Trigger value */
  /* Set WAVEx bits according to DAC_WaveGeneration value */
  /* Set MAMPx bits according to DAC_LFSRUnmask_TriangleAmplitude value */
  /* Set BOFFx bit according to DAC_OutputBuffer value */
  tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
             DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | DAC_InitStruct->DAC_OutputBuffer);
  /* Calculate CR register value depending on DAC_Channel */
  tmpreg1 |= tmpreg2 << DAC_Channel;
  /* Write to DAC CR */
  DAC->CR = tmpreg1;
}

/**
 * @brief 用默认值填充每个 DAC_InitStruct 成员。
 * @param DAC_InitStruct : 指向 DAC_InitTypeDef 结构的指针，该结构将
 * 被初始化。
 * @retval 无
 */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
/*--------------- Reset DAC init structure parameters values -----------------*/
  /* Initialize the DAC_Trigger member */
  DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
  /* Initialize the DAC_WaveGeneration member */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
  /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  /* Initialize the DAC_OutputBuffer member */
  DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/**
 * @brief 启用或禁用指定的 DAC 通道。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param NewState：DAC 通道的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel */
    DAC->CR |= (DAC_CR_EN1 << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC channel */
    DAC->CR &= ~(DAC_CR_EN1 << DAC_Channel);
  }
}
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
/**
  * @brief  Enables or disables the specified DAC interrupts.
  * @param  DAC_Channel: the selected DAC channel.
  *   This parameter can be one of the following values:
  *     @arg DAC_Channel_1: DAC Channel1 selected
  *     @arg DAC_Channel_2: DAC Channel2 selected
  * @param  DAC_IT: specifies the DAC interrupt sources to be enabled or disabled.
  *   This parameter can be the following values:
  *     @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
  * @param  NewState: new state of the specified DAC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_ITConfig(uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_DAC_IT(DAC_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC interrupts */
    DAC->CR |=  (DAC_IT << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC interrupts */
    DAC->CR &= (~(uint32_t)(DAC_IT << DAC_Channel));
  }
}
#endif

/**
 * @brief 启用或禁用指定的 DAC 通道 DMA 请求。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param NewState：所选 DAC 通道 DMA 请求的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel DMA request */
    DAC->CR |= (DAC_CR_DMAEN1 << DAC_Channel);
  }
  else
  {
    /* Disable the selected DAC channel DMA request */
    DAC->CR &= ~(DAC_CR_DMAEN1 << DAC_Channel);
  }
}

/**
 * @brief 启用或禁用选定的 DAC 通道软件触发。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param NewState：所选 DAC 通道软件触发的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable software trigger for the selected DAC channel */
    DAC->SWTRIGR |= (uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4);
  }
  else
  {
    /* Disable software trigger for the selected DAC channel */
    DAC->SWTRIGR &= ~((uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4));
  }
}

/**
 * @brief 同时启用或禁用两个 DAC 通道软件
 * 触发器。
 * @param NewState：DAC 通道软件触发的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable software trigger for both DAC channels */
    DAC->SWTRIGR |= DUAL_SWTRIG_SET ;
  }
  else
  {
    /* Disable software trigger for both DAC channels */
    DAC->SWTRIGR &= DUAL_SWTRIG_RESET;
  }
}

/**
 * @brief 启用或禁用选定的 DAC 通道波形生成。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param DAC_Wave：指定要启用或禁用的波形类型。
 * 此参数可以是以下值之一：
 * @arg DAC_Wave_Noise：噪声波生成
 * @arg DAC_Wave_Triangle：三角波生成
 * @param NewState：选定 DAC 通道波形生成的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_WAVE(DAC_Wave));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected wave generation for the selected DAC channel */
    DAC->CR |= DAC_Wave << DAC_Channel;
  }
  else
  {
    /* Disable the selected wave generation for the selected DAC channel */
    DAC->CR &= ~(DAC_Wave << DAC_Channel);
  }
}

/**
 * @brief 为 DAC 通道 1 设置指定的数据保持寄存器值。
 * @param DAC_Align：指定 DAC 通道 1 的数据对齐方式。
 * 此参数可以是以下值之一：
 * @arg DAC_Align_8b_R: 选择 8 位右数据对齐
 * @arg DAC_Align_12b_L: 选择 12 位左数据对齐
 * @arg DAC_Align_12b_R: 选择 12 位右数据对齐
 * @param Data : 要加载到所选数据保持寄存器中的数据。
 * @retval 无
 */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));

  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12R1_OFFSET + DAC_Align;

  /* Set the DAC channel1 selected data holding register */
  *(__IO uint32_t *) tmp = Data;
}

/**
 * @brief 为 DAC 通道 2 设置指定的数据保持寄存器值。
 * @param DAC_Align：指定 DAC 通道 2 的数据对齐方式。
 * 此参数可以是以下值之一：
 * @arg DAC_Align_8b_R: 选择 8 位右数据对齐
 * @arg DAC_Align_12b_L: 选择 12 位左数据对齐
 * @arg DAC_Align_12b_R: 选择 12 位右数据对齐
 * @param Data : 要加载到所选数据保持寄存器中的数据。
 * @retval 无
 */
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));

  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12R2_OFFSET + DAC_Align;

  /* Set the DAC channel2 selected data holding register */
  *(__IO uint32_t *)tmp = Data;
}

/**
 * @brief 设置双通道的指定数据保持寄存器值
 * 数模转换器。
 * @param DAC_Align：指定双通道 DAC 的数据对齐方式。
 * 此参数可以是以下值之一：
 * @arg DAC_Align_8b_R: 选择 8 位右数据对齐
 * @arg DAC_Align_12b_L: 选择 12 位左数据对齐
 * @arg DAC_Align_12b_R: 选择 12 位右数据对齐
 * @param Data2: DAC Channel2 的数据要加载到所选数据中
 * 持有登记册。
 * @param Data1: DAC Channel1 的数据要加载到所选数据中
 * 持有登记册。
 * @retval 无
 */
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
  uint32_t data = 0, tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data1));
  assert_param(IS_DAC_DATA(Data2));

  /* Calculate and set dual DAC data holding register value */
  if (DAC_Align == DAC_Align_8b_R)
  {
    data = ((uint32_t)Data2 << 8) | Data1;
  }
  else
  {
    data = ((uint32_t)Data2 << 16) | Data1;
  }

  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12RD_OFFSET + DAC_Align;

  /* Set the dual DAC selected data holding register */
  *(__IO uint32_t *)tmp = data;
}

/**
 * @brief 返回所选 DAC 通道的最后一个数据输出值。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @retval 选定的 DAC 通道数据输出值。
 */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));

  tmp = (uint32_t) DAC_BASE ;
  tmp += DOR_OFFSET + ((uint32_t)DAC_Channel >> 2);

  /* Returns the DAC channel data output register value */
  return (uint16_t) (*(__IO uint32_t*) tmp);
}

#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
/**
 * @brief 检查是否设置了指定的 DAC 标志。
 * @param DAC_Channel：你选择的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param DAC_FLAG：指定要检查的标志。
 * 此参数只能是以下值：
 * @arg DAC_FLAG_DMAUDR: DMA 欠载标志
 * @retval DAC_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  /* Check the status of the specified DAC flag */
  if ((DAC->SR & (DAC_FLAG << DAC_Channel)) != (uint8_t)RESET)
  {
    /* DAC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* DAC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the DAC_FLAG status */
  return  bitstatus;
}

/**
 * @brief 清除 DAC 通道 x 的挂起标志。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param DAC_FLAG：指定要清除的标志。
 * 该参数可以是以下值：
 * @arg DAC_FLAG_DMAUDR: DMA 欠载标志
 * @retval 无
 */
void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  /* Clear the selected DAC flags */
  DAC->SR = (DAC_FLAG << DAC_Channel);
}

/**
 * @brief 检查是否发生了指定的 DAC 中断。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param DAC_IT：指定要检查的 DAC 中断源。
 * 该参数可以是以下值：
 * @arg DAC_IT_DMAUDR: DMA 欠载中断屏蔽
 * @retval DAC_IT 的新状态（SET 或 RESET）。
 */
ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT));

  /* Get the DAC_IT enable bit status */
  enablestatus = (DAC->CR & (DAC_IT << DAC_Channel)) ;

  /* Check the status of the specified DAC interrupt */
  if (((DAC->SR & (DAC_IT << DAC_Channel)) != (uint32_t)RESET) && enablestatus)
  {
    /* DAC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* DAC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the DAC_IT status */
  return  bitstatus;
}

/**
 * @brief 清除 DAC 通道 x 的中断挂起位。
 * @param DAC_Channel：选定的 DAC 通道。
 * 此参数可以是以下值之一：
 * @arg DAC_Channel_1: 选择了 DAC 通道 1
 * @arg DAC_Channel_2: 选择了 DAC 通道 2
 * @param DAC_IT：指定要清除的 DAC 中断挂起位。
 * 该参数可以是以下值：
 * @arg DAC_IT_DMAUDR: DMA 欠载中断屏蔽
 * @retval 无
 */
void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT));

  /* Clear the selected DAC interrupt pending bits */
  DAC->SR = (DAC_IT << DAC_Channel);
}
#endif

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
