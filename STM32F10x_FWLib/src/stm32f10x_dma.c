/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup DMA
  * @brief DMA driver modules
  * @{
  */

/** @defgroup DMA_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup DMA_Private_Defines
  * @{
  */


/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_Channel1_IT_Mask    ((uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1))
#define DMA1_Channel2_IT_Mask    ((uint32_t)(DMA_ISR_GIF2 | DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TEIF2))
#define DMA1_Channel3_IT_Mask    ((uint32_t)(DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TEIF3))
#define DMA1_Channel4_IT_Mask    ((uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4))
#define DMA1_Channel5_IT_Mask    ((uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5))
#define DMA1_Channel6_IT_Mask    ((uint32_t)(DMA_ISR_GIF6 | DMA_ISR_TCIF6 | DMA_ISR_HTIF6 | DMA_ISR_TEIF6))
#define DMA1_Channel7_IT_Mask    ((uint32_t)(DMA_ISR_GIF7 | DMA_ISR_TCIF7 | DMA_ISR_HTIF7 | DMA_ISR_TEIF7))

/* DMA2 Channelx interrupt pending bit masks */
#define DMA2_Channel1_IT_Mask    ((uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1))
#define DMA2_Channel2_IT_Mask    ((uint32_t)(DMA_ISR_GIF2 | DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TEIF2))
#define DMA2_Channel3_IT_Mask    ((uint32_t)(DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TEIF3))
#define DMA2_Channel4_IT_Mask    ((uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4))
#define DMA2_Channel5_IT_Mask    ((uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5))

/* DMA2 FLAG mask */
#define FLAG_Mask                ((uint32_t)0x10000000)

/* DMA registers Masks */
#define CCR_CLEAR_Mask           ((uint32_t)0xFFFF800F)

/**
  * @}
  */

/** @defgroup DMA_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DMA_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup DMA_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup DMA_Private_Functions
  * @{
  */

/**
 * @brief 将 DMAy Channelx 寄存器取消初始化为默认复位
 * 值。
 * @param DMAy_Channelx: 其中 y 可以是 1 或 2 来选择 DMA 和
 * x 对于 DMA1 可以是 1 到 7，对于 DMA2 可以是 1 到 5 来选择 DMA 通道。
 * @retval 无
 */
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

  /* Disable the selected DMAy Channelx */
  DMAy_Channelx->CCR &= (uint16_t)(~DMA_CCR1_EN);

  /* Reset DMAy Channelx control register */
  DMAy_Channelx->CCR  = 0;

  /* Reset DMAy Channelx remaining bytes register */
  DMAy_Channelx->CNDTR = 0;

  /* Reset DMAy Channelx peripheral address register */
  DMAy_Channelx->CPAR  = 0;

  /* Reset DMAy Channelx memory address register */
  DMAy_Channelx->CMAR = 0;

  if (DMAy_Channelx == DMA1_Channel1)
  {
    /* Reset interrupt pending bits for DMA1 Channel1 */
    DMA1->IFCR |= DMA1_Channel1_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel2)
  {
    /* Reset interrupt pending bits for DMA1 Channel2 */
    DMA1->IFCR |= DMA1_Channel2_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel3)
  {
    /* Reset interrupt pending bits for DMA1 Channel3 */
    DMA1->IFCR |= DMA1_Channel3_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel4)
  {
    /* Reset interrupt pending bits for DMA1 Channel4 */
    DMA1->IFCR |= DMA1_Channel4_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel5)
  {
    /* Reset interrupt pending bits for DMA1 Channel5 */
    DMA1->IFCR |= DMA1_Channel5_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel6)
  {
    /* Reset interrupt pending bits for DMA1 Channel6 */
    DMA1->IFCR |= DMA1_Channel6_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel7)
  {
    /* Reset interrupt pending bits for DMA1 Channel7 */
    DMA1->IFCR |= DMA1_Channel7_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel1)
  {
    /* Reset interrupt pending bits for DMA2 Channel1 */
    DMA2->IFCR |= DMA2_Channel1_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel2)
  {
    /* Reset interrupt pending bits for DMA2 Channel2 */
    DMA2->IFCR |= DMA2_Channel2_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel3)
  {
    /* Reset interrupt pending bits for DMA2 Channel3 */
    DMA2->IFCR |= DMA2_Channel3_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel4)
  {
    /* Reset interrupt pending bits for DMA2 Channel4 */
    DMA2->IFCR |= DMA2_Channel4_IT_Mask;
  }
  else
  {
    if (DMAy_Channelx == DMA2_Channel5)
    {
      /* Reset interrupt pending bits for DMA2 Channel5 */
      DMA2->IFCR |= DMA2_Channel5_IT_Mask;
    }
  }
}

/**
 * @brief 根据指定初始化 DMAy Channelx
 * DMA_InitStruct 中的参数。
 * @param DMAy_Channelx: 其中 y 可以是 1 或 2 来选择 DMA 和
 * x 对于 DMA1 可以是 1 到 7，对于 DMA2 可以是 1 到 5 来选择 DMA 通道。
 * @param DMA_InitStruct：指向 DMA_InitTypeDef 结构的指针
 * 包含指定 DMA 通道的配置信息。
 * @retval 无
 */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_DIR(DMA_InitStruct->DMA_DIR));
  assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
  assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
  assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
  assert_param(IS_DMA_M2M_STATE(DMA_InitStruct->DMA_M2M));

/*--------------------------- DMAy Channelx CCR Configuration -----------------*/
  /* Get the DMAy_Channelx CCR value */
  tmpreg = DMAy_Channelx->CCR;
  /* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
  tmpreg &= CCR_CLEAR_Mask;
  /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
  /* Set DIR bit according to DMA_DIR value */
  /* Set CIRC bit according to DMA_Mode value */
  /* Set PINC bit according to DMA_PeripheralInc value */
  /* Set MINC bit according to DMA_MemoryInc value */
  /* Set PSIZE bits according to DMA_PeripheralDataSize value */
  /* Set MSIZE bits according to DMA_MemoryDataSize value */
  /* Set PL bits according to DMA_Priority value */
  /* Set the MEM2MEM bit according to DMA_M2M value */
  tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
            DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
            DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
            DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;

  /* Write to DMAy Channelx CCR */
  DMAy_Channelx->CCR = tmpreg;

/*--------------------------- DMAy Channelx CNDTR Configuration ---------------*/
  /* Write to DMAy Channelx CNDTR */
  DMAy_Channelx->CNDTR = DMA_InitStruct->DMA_BufferSize;

/*--------------------------- DMAy Channelx CPAR Configuration ----------------*/
  /* Write to DMAy Channelx CPAR */
  DMAy_Channelx->CPAR = DMA_InitStruct->DMA_PeripheralBaseAddr;

/*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
  /* Write to DMAy Channelx CMAR */
  DMAy_Channelx->CMAR = DMA_InitStruct->DMA_MemoryBaseAddr;
}

/**
 * @brief 用默认值填充每个 DMA_InitStruct 成员。
 * @param DMA_InitStruct : 指向 DMA_InitTypeDef 结构的指针，该结构将
 * 被初始化。
 * @retval 无
 */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
/*-------------- Reset DMA init structure parameters values ------------------*/
  /* Initialize the DMA_PeripheralBaseAddr member */
  DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
  /* Initialize the DMA_MemoryBaseAddr member */
  DMA_InitStruct->DMA_MemoryBaseAddr = 0;
  /* Initialize the DMA_DIR member */
  DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralSRC;
  /* Initialize the DMA_BufferSize member */
  DMA_InitStruct->DMA_BufferSize = 0;
  /* Initialize the DMA_PeripheralInc member */
  DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  /* Initialize the DMA_MemoryInc member */
  DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;
  /* Initialize the DMA_PeripheralDataSize member */
  DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  /* Initialize the DMA_MemoryDataSize member */
  DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  /* Initialize the DMA_Mode member */
  DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
  /* Initialize the DMA_Priority member */
  DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
  /* Initialize the DMA_M2M member */
  DMA_InitStruct->DMA_M2M = DMA_M2M_Disable;
}

/**
 * @brief 启用或禁用指定的 DMAy Channelx。
 * @param DMAy_Channelx: 其中 y 可以是 1 或 2 来选择 DMA 和
 * x 对于 DMA1 可以是 1 到 7，对于 DMA2 可以是 1 到 5 来选择 DMA 通道。
 * @param NewState：DMAy Channelx 的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMAy Channelx */
    DMAy_Channelx->CCR |= DMA_CCR1_EN;
  }
  else
  {
    /* Disable the selected DMAy Channelx */
    DMAy_Channelx->CCR &= (uint16_t)(~DMA_CCR1_EN);
  }
}

/**
 * @brief 启用或禁用指定的 DMAy Channelx 中断。
 * @param DMAy_Channelx: 其中 y 可以是 1 或 2 来选择 DMA 和
 * x 对于 DMA1 可以是 1 到 7，对于 DMA2 可以是 1 到 5 来选择 DMA 通道。
 * @param DMA_IT：指定要启用的 DMA 中断源
 * 或禁用。
 * 该参数可以是以下值的任意组合：
 * @arg DMA_IT_TC: 传输完成中断屏蔽
 * @arg DMA_IT_HT: 半传输中断屏蔽
 * @arg DMA_IT_TE：传输错误中断掩码
 * @param NewState：指定 DMA 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_CONFIG_IT(DMA_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected DMA interrupts */
    DMAy_Channelx->CCR |= DMA_IT;
  }
  else
  {
    /* Disable the selected DMA interrupts */
    DMAy_Channelx->CCR &= ~DMA_IT;
  }
}

/**
 * @brief 设置当前 DMAy Channelx 传输中的数据单元数。
 * @param DMAy_Channelx: 其中 y 可以是 1 或 2 来选择 DMA 和
 * x 对于 DMA1 可以是 1 到 7，对于 DMA2 可以是 1 到 5 来选择 DMA 通道。
 * @param DataNumber：当前 DMAy Channelx 中的数据单元数
 *         转移。
 * @note 此函数只能在禁用 DMAy_Channelx 时使用。
 * @retval 无。
 */
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

/*--------------------------- DMAy Channelx CNDTR Configuration ---------------*/
  /* Write to DMAy Channelx CNDTR */
  DMAy_Channelx->CNDTR = DataNumber;
}

/**
 * @brief 返回当前剩余数据单元的数量
 * DMAy Channelx 传输。
 * @param DMAy_Channelx: 其中 y 可以是 1 或 2 来选择 DMA 和
 * x 对于 DMA1 可以是 1 到 7，对于 DMA2 可以是 1 到 5 来选择 DMA 通道。
 * @retval 当前 DMAy Channelx 中剩余数据单元的数量
 *         转移。
 */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* Return the number of remaining data units for DMAy Channelx */
  return ((uint16_t)(DMAy_Channelx->CNDTR));
}

/**
 * @brief 检查是否设置了指定的 DMAy Channelx 标志。
 * @param DMAy_FLAG：指定要检查的标志。
 * 此参数可以是以下值之一：
 * @arg DMA1_FLAG_GL1：DMA1 通道 1 全局标志。
 * @arg DMA1_FLAG_TC1：DMA1 通道 1 传输完成标志。
 * @arg DMA1_FLAG_HT1：DMA1 通道 1 半传输标志。
 * @arg DMA1_FLAG_TE1：DMA1 通道 1 传输错误标志。
 * @arg DMA1_FLAG_GL2：DMA1 通道 2 全局标志。
 * @arg DMA1_FLAG_TC2：DMA1 通道 2 传输完成标志。
 * @arg DMA1_FLAG_HT2：DMA1 通道 2 半传输标志。
 * @arg DMA1_FLAG_TE2：DMA1 Channel2 传输错误标志。
 * @arg DMA1_FLAG_GL3：DMA1 通道 3 全局标志。
 * @arg DMA1_FLAG_TC3：DMA1 Channel3 传输完成标志。
 * @arg DMA1_FLAG_HT3：DMA1 Channel3 半传输标志。
 * @arg DMA1_FLAG_TE3：DMA1 Channel3 传输错误标志。
 * @arg DMA1_FLAG_GL4：DMA1 Channel4 全局标志。
 * @arg DMA1_FLAG_TC4：DMA1 Channel4 传输完成标志。
 * @arg DMA1_FLAG_HT4：DMA1 通道 4 半传输标志。
 * @arg DMA1_FLAG_TE4：DMA1 Channel4 传输错误标志。
 * @arg DMA1_FLAG_GL5：DMA1 Channel5 全局标志。
 * @arg DMA1_FLAG_TC5：DMA1 Channel5 传输完成标志。
 * @arg DMA1_FLAG_HT5：DMA1 Channel5 半传输标志。
 * @arg DMA1_FLAG_TE5：DMA1 Channel5 传输错误标志。
 * @arg DMA1_FLAG_GL6：DMA1 通道 6 全局标志。
 * @arg DMA1_FLAG_TC6：DMA1 Channel6 传输完成标志。
 * @arg DMA1_FLAG_HT6：DMA1 通道 6 半传输标志。
 * @arg DMA1_FLAG_TE6：DMA1 Channel6 传输错误标志。
 * @arg DMA1_FLAG_GL7：DMA1 Channel7 全局标志。
 * @arg DMA1_FLAG_TC7：DMA1 Channel7 传输完成标志。
 * @arg DMA1_FLAG_HT7：DMA1 Channel7 半传输标志。
 * @arg DMA1_FLAG_TE7：DMA1 Channel7 传输错误标志。
 * @arg DMA2_FLAG_GL1：DMA2 通道 1 全局标志。
 * @arg DMA2_FLAG_TC1：DMA2 通道 1 传输完成标志。
 * @arg DMA2_FLAG_HT1：DMA2 通道 1 半传输标志。
 * @arg DMA2_FLAG_TE1：DMA2 通道 1 传输错误标志。
 * @arg DMA2_FLAG_GL2：DMA2 通道 2 全局标志。
 * @arg DMA2_FLAG_TC2：DMA2 通道 2 传输完成标志。
 * @arg DMA2_FLAG_HT2：DMA2 通道 2 半传输标志。
 * @arg DMA2_FLAG_TE2：DMA2 通道 2 传输错误标志。
 * @arg DMA2_FLAG_GL3：DMA2 Channel3 全局标志。
 * @arg DMA2_FLAG_TC3：DMA2 Channel3 传输完成标志。
 * @arg DMA2_FLAG_HT3：DMA2 Channel3 半传输标志。
 * @arg DMA2_FLAG_TE3：DMA2 Channel3 传输错误标志。
 * @arg DMA2_FLAG_GL4：DMA2 Channel4 全局标志。
 * @arg DMA2_FLAG_TC4：DMA2 Channel4 传输完成标志。
 * @arg DMA2_FLAG_HT4：DMA2 Channel4 半传输标志。
 * @arg DMA2_FLAG_TE4：DMA2 Channel4 传输错误标志。
 * @arg DMA2_FLAG_GL5：DMA2 Channel5 全局标志。
 * @arg DMA2_FLAG_TC5：DMA2 Channel5 传输完成标志。
 * @arg DMA2_FLAG_HT5：DMA2 Channel5 半传输标志。
 * @arg DMA2_FLAG_TE5：DMA2 Channel5 传输错误标志。
 * @retval DMAy_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_GET_FLAG(DMAy_FLAG));

  /* Calculate the used DMAy */
  if ((DMAy_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Get DMA2 ISR register value */
    tmpreg = DMA2->ISR ;
  }
  else
  {
    /* Get DMA1 ISR register value */
    tmpreg = DMA1->ISR ;
  }

  /* Check the status of the specified DMAy flag */
  if ((tmpreg & DMAy_FLAG) != (uint32_t)RESET)
  {
    /* DMAy_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* DMAy_FLAG is reset */
    bitstatus = RESET;
  }

  /* Return the DMAy_FLAG status */
  return  bitstatus;
}

/**
 * @brief 清除 DMAy Channelx 的挂起标志。
 * @param DMAy_FLAG：指定要清除的标志。
 * 此参数可以是以下值的任意组合（对于相同的 DMA）：
 * @arg DMA1_FLAG_GL1：DMA1 通道 1 全局标志。
 * @arg DMA1_FLAG_TC1：DMA1 通道 1 传输完成标志。
 * @arg DMA1_FLAG_HT1：DMA1 通道 1 半传输标志。
 * @arg DMA1_FLAG_TE1：DMA1 通道 1 传输错误标志。
 * @arg DMA1_FLAG_GL2：DMA1 通道 2 全局标志。
 * @arg DMA1_FLAG_TC2：DMA1 通道 2 传输完成标志。
 * @arg DMA1_FLAG_HT2：DMA1 通道 2 半传输标志。
 * @arg DMA1_FLAG_TE2：DMA1 Channel2 传输错误标志。
 * @arg DMA1_FLAG_GL3：DMA1 通道 3 全局标志。
 * @arg DMA1_FLAG_TC3：DMA1 Channel3 传输完成标志。
 * @arg DMA1_FLAG_HT3：DMA1 Channel3 半传输标志。
 * @arg DMA1_FLAG_TE3：DMA1 Channel3 传输错误标志。
 * @arg DMA1_FLAG_GL4：DMA1 Channel4 全局标志。
 * @arg DMA1_FLAG_TC4：DMA1 Channel4 传输完成标志。
 * @arg DMA1_FLAG_HT4：DMA1 通道 4 半传输标志。
 * @arg DMA1_FLAG_TE4：DMA1 Channel4 传输错误标志。
 * @arg DMA1_FLAG_GL5：DMA1 Channel5 全局标志。
 * @arg DMA1_FLAG_TC5：DMA1 Channel5 传输完成标志。
 * @arg DMA1_FLAG_HT5：DMA1 Channel5 半传输标志。
 * @arg DMA1_FLAG_TE5：DMA1 Channel5 传输错误标志。
 * @arg DMA1_FLAG_GL6：DMA1 通道 6 全局标志。
 * @arg DMA1_FLAG_TC6：DMA1 Channel6 传输完成标志。
 * @arg DMA1_FLAG_HT6：DMA1 通道 6 半传输标志。
 * @arg DMA1_FLAG_TE6：DMA1 Channel6 传输错误标志。
 * @arg DMA1_FLAG_GL7：DMA1 Channel7 全局标志。
 * @arg DMA1_FLAG_TC7：DMA1 Channel7 传输完成标志。
 * @arg DMA1_FLAG_HT7：DMA1 Channel7 半传输标志。
 * @arg DMA1_FLAG_TE7：DMA1 Channel7 传输错误标志。
 * @arg DMA2_FLAG_GL1：DMA2 通道 1 全局标志。
 * @arg DMA2_FLAG_TC1：DMA2 通道 1 传输完成标志。
 * @arg DMA2_FLAG_HT1：DMA2 通道 1 半传输标志。
 * @arg DMA2_FLAG_TE1：DMA2 通道 1 传输错误标志。
 * @arg DMA2_FLAG_GL2：DMA2 通道 2 全局标志。
 * @arg DMA2_FLAG_TC2：DMA2 通道 2 传输完成标志。
 * @arg DMA2_FLAG_HT2：DMA2 通道 2 半传输标志。
 * @arg DMA2_FLAG_TE2：DMA2 通道 2 传输错误标志。
 * @arg DMA2_FLAG_GL3：DMA2 Channel3 全局标志。
 * @arg DMA2_FLAG_TC3：DMA2 Channel3 传输完成标志。
 * @arg DMA2_FLAG_HT3：DMA2 Channel3 半传输标志。
 * @arg DMA2_FLAG_TE3：DMA2 Channel3 传输错误标志。
 * @arg DMA2_FLAG_GL4：DMA2 Channel4 全局标志。
 * @arg DMA2_FLAG_TC4：DMA2 Channel4 传输完成标志。
 * @arg DMA2_FLAG_HT4：DMA2 Channel4 半传输标志。
 * @arg DMA2_FLAG_TE4：DMA2 Channel4 传输错误标志。
 * @arg DMA2_FLAG_GL5：DMA2 Channel5 全局标志。
 * @arg DMA2_FLAG_TC5：DMA2 Channel5 传输完成标志。
 * @arg DMA2_FLAG_HT5：DMA2 Channel5 半传输标志。
 * @arg DMA2_FLAG_TE5：DMA2 Channel5 传输错误标志。
 * @retval 无
 */
void DMA_ClearFlag(uint32_t DMAy_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_FLAG(DMAy_FLAG));

  /* Calculate the used DMAy */
  if ((DMAy_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Clear the selected DMAy flags */
    DMA2->IFCR = DMAy_FLAG;
  }
  else
  {
    /* Clear the selected DMAy flags */
    DMA1->IFCR = DMAy_FLAG;
  }
}

/**
 * @brief 检查是否发生了指定的 DMAy Channelx 中断。
 * @param DMAy_IT：指定要检查的 DMAy 中断源。
 * 此参数可以是以下值之一：
 * @arg DMA1_IT_GL1：DMA1 通道 1 全局中断。
 * @arg DMA1_IT_TC1：DMA1 通道 1 传输完成中断。
 * @arg DMA1_IT_HT1: DMA1 Channel1 半传输中断。
 * @arg DMA1_IT_TE1：DMA1 通道 1 传输错误中断。
 * @arg DMA1_IT_GL2：DMA1 通道 2 全局中断。
 * @arg DMA1_IT_TC2：DMA1 通道 2 传输完成中断。
 * @arg DMA1_IT_HT2: DMA1 Channel2 半传输中断。
 * @arg DMA1_IT_TE2：DMA1 Channel2 传输错误中断。
 * @arg DMA1_IT_GL3：DMA1 通道 3 全局中断。
 * @arg DMA1_IT_TC3：DMA1 Channel3 传输完成中断。
 * @arg DMA1_IT_HT3: DMA1 Channel3 半传输中断。
 * @arg DMA1_IT_TE3：DMA1 Channel3 传输错误中断。
 * @arg DMA1_IT_GL4：DMA1 通道 4 全局中断。
 * @arg DMA1_IT_TC4：DMA1 Channel4 传输完成中断。
 * @arg DMA1_IT_HT4: DMA1 Channel4 半传输中断。
 * @arg DMA1_IT_TE4: DMA1 Channel4 传输错误中断。
 * @arg DMA1_IT_GL5：DMA1 通道 5 全局中断。
 * @arg DMA1_IT_TC5：DMA1 Channel5 传输完成中断。
 * @arg DMA1_IT_HT5: DMA1 Channel5 半传输中断。
 * @arg DMA1_IT_TE5：DMA1 Channel5 传输错误中断。
 * @arg DMA1_IT_GL6：DMA1 通道 6 全局中断。
 * @arg DMA1_IT_TC6：DMA1 通道 6 传输完成中断。
 * @arg DMA1_IT_HT6: DMA1 Channel6 半传输中断。
 * @arg DMA1_IT_TE6：DMA1 Channel6 传输错误中断。
 * @arg DMA1_IT_GL7：DMA1 Channel7 全局中断。
 * @arg DMA1_IT_TC7：DMA1 Channel7 传输完成中断。
 * @arg DMA1_IT_HT7: DMA1 Channel7 半传输中断。
 * @arg DMA1_IT_TE7: DMA1 Channel7 传输错误中断。
 * @arg DMA2_IT_GL1：DMA2 通道 1 全局中断。
 * @arg DMA2_IT_TC1：DMA2 通道 1 传输完成中断。
 * @arg DMA2_IT_HT1：DMA2 通道 1 半传输中断。
 * @arg DMA2_IT_TE1：DMA2 通道 1 传输错误中断。
 * @arg DMA2_IT_GL2：DMA2 通道 2 全局中断。
 * @arg DMA2_IT_TC2：DMA2 通道 2 传输完成中断。
 * @arg DMA2_IT_HT2：DMA2 通道 2 半传输中断。
 * @arg DMA2_IT_TE2：DMA2 通道 2 传输错误中断。
 * @arg DMA2_IT_GL3：DMA2 通道 3 全局中断。
 * @arg DMA2_IT_TC3：DMA2 Channel3 传输完成中断。
 * @arg DMA2_IT_HT3: DMA2 Channel3 半传输中断。
 * @arg DMA2_IT_TE3：DMA2 Channel3 传输错误中断。
 * @arg DMA2_IT_GL4：DMA2 通道 4 全局中断。
 * @arg DMA2_IT_TC4：DMA2 通道 4 传输完成中断。
 * @arg DMA2_IT_HT4: DMA2 Channel4 半传输中断。
 * @arg DMA2_IT_TE4：DMA2 Channel4 传输错误中断。
 * @arg DMA2_IT_GL5：DMA2 通道 5 全局中断。
 * @arg DMA2_IT_TC5：DMA2 通道 5 传输完成中断。
 * @arg DMA2_IT_HT5: DMA2 Channel5 半传输中断。
 * @arg DMA2_IT_TE5：DMA2 Channel5 传输错误中断。
 * @retval DMAy_IT 的新状态（SET 或 RESET）。
 */
ITStatus DMA_GetITStatus(uint32_t DMAy_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_GET_IT(DMAy_IT));

  /* Calculate the used DMA */
  if ((DMAy_IT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Get DMA2 ISR register value */
    tmpreg = DMA2->ISR;
  }
  else
  {
    /* Get DMA1 ISR register value */
    tmpreg = DMA1->ISR;
  }

  /* Check the status of the specified DMAy interrupt */
  if ((tmpreg & DMAy_IT) != (uint32_t)RESET)
  {
    /* DMAy_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* DMAy_IT is reset */
    bitstatus = RESET;
  }
  /* Return the DMA_IT status */
  return  bitstatus;
}

/**
 * @brief 清除 DMAy Channelx 的中断挂起位。
 * @param DMAy_IT：指定要清除的 DMAy 中断挂起位。
 * 此参数可以是以下值的任意组合（对于相同的 DMA）：
 * @arg DMA1_IT_GL1：DMA1 通道 1 全局中断。
 * @arg DMA1_IT_TC1：DMA1 通道 1 传输完成中断。
 * @arg DMA1_IT_HT1: DMA1 Channel1 半传输中断。
 * @arg DMA1_IT_TE1：DMA1 通道 1 传输错误中断。
 * @arg DMA1_IT_GL2：DMA1 通道 2 全局中断。
 * @arg DMA1_IT_TC2：DMA1 通道 2 传输完成中断。
 * @arg DMA1_IT_HT2: DMA1 Channel2 半传输中断。
 * @arg DMA1_IT_TE2：DMA1 Channel2 传输错误中断。
 * @arg DMA1_IT_GL3：DMA1 通道 3 全局中断。
 * @arg DMA1_IT_TC3：DMA1 Channel3 传输完成中断。
 * @arg DMA1_IT_HT3: DMA1 Channel3 半传输中断。
 * @arg DMA1_IT_TE3：DMA1 Channel3 传输错误中断。
 * @arg DMA1_IT_GL4：DMA1 通道 4 全局中断。
 * @arg DMA1_IT_TC4：DMA1 Channel4 传输完成中断。
 * @arg DMA1_IT_HT4: DMA1 Channel4 半传输中断。
 * @arg DMA1_IT_TE4: DMA1 Channel4 传输错误中断。
 * @arg DMA1_IT_GL5：DMA1 通道 5 全局中断。
 * @arg DMA1_IT_TC5：DMA1 Channel5 传输完成中断。
 * @arg DMA1_IT_HT5: DMA1 Channel5 半传输中断。
 * @arg DMA1_IT_TE5：DMA1 Channel5 传输错误中断。
 * @arg DMA1_IT_GL6：DMA1 通道 6 全局中断。
 * @arg DMA1_IT_TC6：DMA1 通道 6 传输完成中断。
 * @arg DMA1_IT_HT6: DMA1 Channel6 半传输中断。
 * @arg DMA1_IT_TE6：DMA1 Channel6 传输错误中断。
 * @arg DMA1_IT_GL7：DMA1 Channel7 全局中断。
 * @arg DMA1_IT_TC7：DMA1 Channel7 传输完成中断。
 * @arg DMA1_IT_HT7: DMA1 Channel7 半传输中断。
 * @arg DMA1_IT_TE7: DMA1 Channel7 传输错误中断。
 * @arg DMA2_IT_GL1：DMA2 通道 1 全局中断。
 * @arg DMA2_IT_TC1：DMA2 通道 1 传输完成中断。
 * @arg DMA2_IT_HT1：DMA2 通道 1 半传输中断。
 * @arg DMA2_IT_TE1：DMA2 通道 1 传输错误中断。
 * @arg DMA2_IT_GL2：DMA2 通道 2 全局中断。
 * @arg DMA2_IT_TC2：DMA2 通道 2 传输完成中断。
 * @arg DMA2_IT_HT2：DMA2 通道 2 半传输中断。
 * @arg DMA2_IT_TE2：DMA2 通道 2 传输错误中断。
 * @arg DMA2_IT_GL3：DMA2 通道 3 全局中断。
 * @arg DMA2_IT_TC3：DMA2 Channel3 传输完成中断。
 * @arg DMA2_IT_HT3: DMA2 Channel3 半传输中断。
 * @arg DMA2_IT_TE3：DMA2 Channel3 传输错误中断。
 * @arg DMA2_IT_GL4：DMA2 通道 4 全局中断。
 * @arg DMA2_IT_TC4：DMA2 通道 4 传输完成中断。
 * @arg DMA2_IT_HT4: DMA2 Channel4 半传输中断。
 * @arg DMA2_IT_TE4：DMA2 Channel4 传输错误中断。
 * @arg DMA2_IT_GL5：DMA2 通道 5 全局中断。
 * @arg DMA2_IT_TC5：DMA2 通道 5 传输完成中断。
 * @arg DMA2_IT_HT5: DMA2 Channel5 半传输中断。
 * @arg DMA2_IT_TE5：DMA2 Channel5 传输错误中断。
 * @retval 无
 */
void DMA_ClearITPendingBit(uint32_t DMAy_IT)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_IT(DMAy_IT));

  /* Calculate the used DMAy */
  if ((DMAy_IT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Clear the selected DMAy interrupt pending bits */
    DMA2->IFCR = DMAy_IT;
  }
  else
  {
    /* Clear the selected DMAy interrupt pending bits */
    DMA1->IFCR = DMAy_IT;
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
