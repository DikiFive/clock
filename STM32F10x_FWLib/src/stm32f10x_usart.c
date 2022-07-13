/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup USART
  * @brief USART driver modules
  * @{
  */

/** @defgroup USART_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_Defines
  * @{
  */

#define CR1_UE_Set                ((uint16_t)0x2000)  /*!< USART Enable Mask */
#define CR1_UE_Reset              ((uint16_t)0xDFFF)  /*!< USART Disable Mask */

#define CR1_WAKE_Mask             ((uint16_t)0xF7FF)  /*!< USART WakeUp Method Mask */

#define CR1_RWU_Set               ((uint16_t)0x0002)  /*!< USART mute mode Enable Mask */
#define CR1_RWU_Reset             ((uint16_t)0xFFFD)  /*!< USART mute mode Enable Mask */
#define CR1_SBK_Set               ((uint16_t)0x0001)  /*!< USART Break Character send Mask */
#define CR1_CLEAR_Mask            ((uint16_t)0xE9F3)  /*!< USART CR1 Mask */
#define CR2_Address_Mask          ((uint16_t)0xFFF0)  /*!< USART address Mask */

#define CR2_LINEN_Set              ((uint16_t)0x4000)  /*!< USART LIN Enable Mask */
#define CR2_LINEN_Reset            ((uint16_t)0xBFFF)  /*!< USART LIN Disable Mask */

#define CR2_LBDL_Mask             ((uint16_t)0xFFDF)  /*!< USART LIN Break detection Mask */
#define CR2_STOP_CLEAR_Mask       ((uint16_t)0xCFFF)  /*!< USART CR2 STOP Bits Mask */
#define CR2_CLOCK_CLEAR_Mask      ((uint16_t)0xF0FF)  /*!< USART CR2 Clock Mask */

#define CR3_SCEN_Set              ((uint16_t)0x0020)  /*!< USART SC Enable Mask */
#define CR3_SCEN_Reset            ((uint16_t)0xFFDF)  /*!< USART SC Disable Mask */

#define CR3_NACK_Set              ((uint16_t)0x0010)  /*!< USART SC NACK Enable Mask */
#define CR3_NACK_Reset            ((uint16_t)0xFFEF)  /*!< USART SC NACK Disable Mask */

#define CR3_HDSEL_Set             ((uint16_t)0x0008)  /*!< USART Half-Duplex Enable Mask */
#define CR3_HDSEL_Reset           ((uint16_t)0xFFF7)  /*!< USART Half-Duplex Disable Mask */

#define CR3_IRLP_Mask             ((uint16_t)0xFFFB)  /*!< USART IrDA LowPower mode Mask */
#define CR3_CLEAR_Mask            ((uint16_t)0xFCFF)  /*!< USART CR3 Mask */

#define CR3_IREN_Set              ((uint16_t)0x0002)  /*!< USART IrDA Enable Mask */
#define CR3_IREN_Reset            ((uint16_t)0xFFFD)  /*!< USART IrDA Disable Mask */
#define GTPR_LSB_Mask             ((uint16_t)0x00FF)  /*!< Guard Time Register LSB Mask */
#define GTPR_MSB_Mask             ((uint16_t)0xFF00)  /*!< Guard Time Register MSB Mask */
#define IT_Mask                   ((uint16_t)0x001F)  /*!< USART Interrupt Mask */

/* USART OverSampling-8 Mask */
#define CR1_OVER8_Set             ((u16)0x8000)  /* USART OVER8 mode Enable Mask */
#define CR1_OVER8_Reset           ((u16)0x7FFF)  /* USART OVER8 mode Disable Mask */

/* USART One Bit Sampling Mask */
#define CR3_ONEBITE_Set           ((u16)0x0800)  /* USART ONEBITE mode Enable Mask */
#define CR3_ONEBITE_Reset         ((u16)0xF7FF)  /* USART ONEBITE mode Disable Mask */

/**
  * @}
  */

/** @defgroup USART_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_Functions
  * @{
  */

/**
 * @brief ? USARTx ??????????????????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @retval ?
 */
void USART_DeInit(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  if (USARTx == USART1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
  }
  else if (USARTx == USART2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
  }
  else if (USARTx == USART3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
  }
  else if (USARTx == UART4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
  }
  else
  {
    if (USARTx == UART5)
    {
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
    }
  }
}

/**
 * @brief ??????? USARTx ??
 * USART_InitStruct ?????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_InitStruct??? USART_InitTypeDef ?????
 * ???? USART ?????
 * ?????
 * @retval ?
 */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  uint32_t usartxbase = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
  /* The hardware flow control is available only for USART1, USART2 and USART3 */
  if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  usartxbase = (uint32_t)USARTx;

/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear STOP[13:12] bits */
  tmpreg &= CR2_STOP_CLEAR_Mask;
  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
  /* Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;

  /* Write to USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;

/*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= CR1_CLEAR_Mask;
  /* Configure the USART Word Length, Parity and mode ----------------------- */
  /* Set the M bits according to USART_WordLength value */
  /* Set PCE and PS bits according to USART_Parity value */
  /* Set TE and RE bits according to USART_Mode value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;
  /* Write to USART CR1 */
  USARTx->CR1 = (uint16_t)tmpreg;

/*---------------------------- USART CR3 Configuration -----------------------*/
  tmpreg = USARTx->CR3;
  /* Clear CTSE and RTSE bits */
  tmpreg &= CR3_CLEAR_Mask;
  /* Configure the USART HFC -------------------------------------------------*/
  /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  /* Write to USART CR3 */
  USARTx->CR3 = (uint16_t)tmpreg;

/*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  if (usartxbase == USART1_BASE)
  {
    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
  }

  /* Determine the integer part */
  if ((USARTx->CR1 & CR1_OVER8_Set) != 0)
  {
    /* Integer part computing in case Oversampling mode is 8 Samples */
    integerdivider = ((25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate)));
  }
  else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
  {
    /* Integer part computing in case Oversampling mode is 16 Samples */
    integerdivider = ((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));
  }
  tmpreg = (integerdivider / 100) << 4;

  /* Determine the fractional part */
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

  /* Implement the fractional part in the register */
  if ((USARTx->CR1 & CR1_OVER8_Set) != 0)
  {
    tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
  }
  else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
  {
    tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
  }

  /* Write to USART BRR */
  USARTx->BRR = (uint16_t)tmpreg;
}

/**
 * @brief ???????? USART_InitStruct ???
 * @param USART_InitStruct??? USART_InitTypeDef ?????
 * ??????
 * @retval ?
 */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  /* USART_InitStruct members default value */
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_WordLength = USART_WordLength_8b;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity = USART_Parity_No ;
  USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
}

/**
 * @brief ??
 * USART_ClockInitStruct ???????
 * @param USARTx??? x ??? 1?2?3 ??? USART ???
 * @param USART_ClockInitStruct??? USART_ClockInitTypeDef ???
 * ???????????
 * USART ?????
 * @note ???????????? UART4 ? UART5?
 * @retval ?
 */
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0x00;
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));

/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear CLKEN, CPOL, CPHA and LBCL bits */
  tmpreg &= CR2_CLOCK_CLEAR_Mask;
  /* Configure the USART Clock, CPOL, CPHA and LastBit ------------*/
  /* Set CLKEN bit according to USART_Clock value */
  /* Set CPOL bit according to USART_CPOL value */
  /* Set CPHA bit according to USART_CPHA value */
  /* Set LBCL bit according to USART_LastBit value */
  tmpreg |= (uint32_t)USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL |
                 USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit;
  /* Write to USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;
}

/**
 * @brief ???????? USART_ClockInitStruct ???
 * @param USART_ClockInitStruct??? USART_ClockInitTypeDef ???
 * ?????????
 * @retval ?
 */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct members default value */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
 * @brief ???????? USART ???
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param NewState?USARTx ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= CR1_UE_Set;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= CR1_UE_Reset;
  }
}

/**
 * @brief ???????? USART ???
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_IT?????????? USART ????
 * ????????????
 * @arg USART_IT_CTS?CTS ????????? UART4 ? UART5?
 * @arg USART_IT_LBD?LIN ??????
 * @arg USART_IT_TXE???????????
 * @arg USART_IT_TC???????
 * @arg USART_IT_RXNE????????????
 * @arg USART_IT_IDLE?????????
 * @arg USART_IT_PE?????????
 * @arg USART_IT_ERR????????????????????
 * @param NewState??? USARTx ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState)
{
  uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
  uint32_t usartxbase = 0x00;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  /* The CTS interrupt is not available for UART4 and UART5 */
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  usartxbase = (uint32_t)USARTx;

  /* Get the USART register index */
  usartreg = (((uint8_t)USART_IT) >> 0x05);

  /* Get the interrupt position */
  itpos = USART_IT & IT_Mask;
  itmask = (((uint32_t)0x01) << itpos);

  if (usartreg == 0x01) /* The IT is in CR1 register */
  {
    usartxbase += 0x0C;
  }
  else if (usartreg == 0x02) /* The IT is in CR2 register */
  {
    usartxbase += 0x10;
  }
  else /* The IT is in CR3 register */
  {
    usartxbase += 0x14;
  }
  if (NewState != DISABLE)
  {
    *(__IO uint32_t*)usartxbase  |= itmask;
  }
  else
  {
    *(__IO uint32_t*)usartxbase &= ~itmask;
  }
}

/**
 * @brief ????? USART ? DMA ???
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_DMAReq??? DMA ???
 * ???????????????
 * @arg USART_DMAReq_Tx?USART DMA ????
 * @arg USART_DMAReq_Rx?USART DMA ????
 * @param NewState?DMA ????????
 * ???????ENABLE ? DISABLE?
 * @note DMA ?????? UART5?STM32 ??
 * ?????????STM32F10X_HD_VL??
 * @retval ?
 */
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DMAREQ(USART_DMAReq));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CR3 |= USART_DMAReq;
  }
  else
  {
    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CR3 &= (uint16_t)~USART_DMAReq;
  }
}

/**
 * @brief ?? USART ??????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_Address??? USART ??????
 * @retval ?
 */
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS(USART_Address));

  /* Clear the USART address */
  USARTx->CR2 &= CR2_Address_Mask;
  /* Set the USART address node */
  USARTx->CR2 |= USART_Address;
}

/**
 * @brief ?? USART ?????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_WakeUp??? USART ?????
 * ????????????
 * @arg USART_WakeUp_IdleLine???????????
 * @arg USART_WakeUp_AddressMark?????????
 * @retval ?
 */
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_WAKEUP(USART_WakeUp));

  USARTx->CR1 &= CR1_WAKE_Mask;
  USARTx->CR1 |= USART_WakeUp;
}

/**
 * @brief ?? USART ?????????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param NewState?USART ?????????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the USART mute mode  by setting the RWU bit in the CR1 register */
    USARTx->CR1 |= CR1_RWU_Set;
  }
  else
  {
    /* Disable the USART mute mode by clearing the RWU bit in the CR1 register */
    USARTx->CR1 &= CR1_RWU_Reset;
  }
}

/**
 * @brief ?? USART LIN ???????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_LINBreakDetectLength??? LIN ???????
 * ????????????
 * @arg USART_LINBreakDetectLength_10b?10 ?????
 * @arg USART_LINBreakDetectLength_11b?11 ?????
 * @retval ?
 */
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));

  USARTx->CR2 &= CR2_LBDL_Mask;
  USARTx->CR2 |= USART_LINBreakDetectLength;
}

/**
 * @brief ????? USART ? LIN ???
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param NewState?USART LIN ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the LIN mode by setting the LINEN bit in the CR2 register */
    USARTx->CR2 |= CR2_LINEN_Set;
  }
  else
  {
    /* Disable the LIN mode by clearing the LINEN bit in the CR2 register */
    USARTx->CR2 &= CR2_LINEN_Reset;
  }
}

/**
 * @brief ?? USARTx ?????????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param Data????????
 * @retval ?
 */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data));

  /* Transmit Data */
  USARTx->DR = (Data & (uint16_t)0x01FF);
}

/**
 * @brief ?? USARTx ??????????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @retval ???????
 */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Receive Data */
  return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}

/**
 * @brief ???????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @retval ?
 */
void USART_SendBreak(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Send break characters */
  USARTx->CR1 |= CR1_SBK_Set;
}

/**
 * @brief ????? USART ?????
 * @param USARTx??? x ??? 1?2 ? 3 ??? USART ???
 * @param USART_GuardTime????????
 * @note ????????? UART4 ? UART5?
 * @retval ?
 */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));

  /* Clear the USART Guard time */
  USARTx->GTPR &= GTPR_LSB_Mask;
  /* Set the USART guard time */
  USARTx->GTPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

/**
 * @brief ???????????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_Prescaler??????????
 * @note ????? UART4 ? UART5 ? IrDA ???
 * @retval ?
 */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Clear the USART prescaler */
  USARTx->GTPR &= GTPR_MSB_Mask;
  /* Set the USART prescaler */
  USARTx->GTPR |= USART_Prescaler;
}

/**
 * @brief ????? USART ???????
 * @param USARTx??? x ??? 1?2 ? 3 ??? USART ???
 * @param NewState???????????
 * ???????ENABLE ? DISABLE?
 * @note ????????? UART4 ? UART5?
 * @retval ?
 */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the SC mode by setting the SCEN bit in the CR3 register */
    USARTx->CR3 |= CR3_SCEN_Set;
  }
  else
  {
    /* Disable the SC mode by clearing the SCEN bit in the CR3 register */
    USARTx->CR3 &= CR3_SCEN_Reset;
  }
}
/**
 * @brief ????? NACK ???
 * @param USARTx??? x ??? 1?2 ? 3 ??? USART ???
 * @param NewState?NACK ???????
 * ???????ENABLE ? DISABLE?
 * @note ????????? UART4 ? UART5?
 * @retval ?
 */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the NACK transmission by setting the NACK bit in the CR3 register */
    USARTx->CR3 |= CR3_NACK_Set;
  }
  else
  {
    /* Disable the NACK transmission by clearing the NACK bit in the CR3 register */
    USARTx->CR3 &= CR3_NACK_Reset;
  }
}

/**
 * @brief ????? USART ???????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param NewState?USART ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Half-Duplex mode by setting the HDSEL bit in the CR3 register */
    USARTx->CR3 |= CR3_HDSEL_Set;
  }
  else
  {
    /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CR3 register */
    USARTx->CR3 &= CR3_HDSEL_Reset;
  }
}

/**
 * @brief ????? USART ? 8x ??????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param NewState?USART ???????????
 * ???????ENABLE ? DISABLE?
 * @??
 * ???????? USART_Init() ????
 * ????????????????
 * @retval ?
 */
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the 8x Oversampling mode by setting the OVER8 bit in the CR1 register */
    USARTx->CR1 |= CR1_OVER8_Set;
  }
  else
  {
    /* Disable the 8x Oversampling mode by clearing the OVER8 bit in the CR1 register */
    USARTx->CR1 &= CR1_OVER8_Reset;
  }
}

/**
 * @brief ????? USART ????????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param NewState?USART ???????????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the one bit method by setting the ONEBITE bit in the CR3 register */
    USARTx->CR3 |= CR3_ONEBITE_Set;
  }
  else
  {
    /* Disable tthe one bit method by clearing the ONEBITE bit in the CR3 register */
    USARTx->CR3 &= CR3_ONEBITE_Reset;
  }
}

/**
 * @brief ?? USART ? IrDA ???
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_IrDAMode??? IrDA ???
 * ????????????
 * @arg USART_IrDAMode_LowPower
 * @arg USART_IrDAMode_Normal
 * @retval None
 */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));

  USARTx->CR3 &= CR3_IRLP_Mask;
  USARTx->CR3 |= USART_IrDAMode;
}

/**
 * @brief ????? USART ? IrDA ???
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param NewState?IrDA ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    USARTx->CR3 |= CR3_IREN_Set;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    USARTx->CR3 &= CR3_IREN_Reset;
  }
}

/**
 * @brief ?????????? USART ???
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_FLAG??????????
 * ????????????
 * @arg USART_FLAG_CTS?CTS ????????? UART4 ? UART5?
 * @arg USART_FLAG_LBD?LIN ??????
 * @arg USART_FLAG_TXE???????????
 * @arg USART_FLAG_TC???????
 * @arg USART_FLAG_RXNE????????????
 * @arg USART_FLAG_IDLE?????????
 * @arg USART_FLAG_ORE???????
 * @arg USART_FLAG_NE???????
 * @arg USART_FLAG_FE??????
 * @arg USART_FLAG_PE?????????
 * @retval USART_FLAG ?????SET ? RESET??
 */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));
  /* The CTS flag is not available for UART4 and UART5 */
  if (USART_FLAG == USART_FLAG_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  if ((USARTx->SR & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
 * @brief ?? USARTx ??????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_FLAG??????????
 * ???????????????
 * @arg USART_FLAG_CTS?CTS ????????? UART4 ? UART5??
 * @arg USART_FLAG_LBD?LIN ???????
 * @arg USART_FLAG_TC????????
 * @arg USART_FLAG_RXNE?????????????
 *
 * @??
 * - PE?????????FE??????NE???????ORE????
 * ???? IDLE????????????????
 * ???? USART_SR ??????? (USART_GetFlagStatus())
 * ??? USART_DR ??? (USART_ReceiveData()) ???????
 * - RXNE ????????? USART_DR ??????
 * (USART_ReceiveData())?
 * - TC ?????????????????
 * USART_SR ??? (USART_GetFlagStatus()) ?????
 * ? USART_DR ??? (USART_SendData())?
 * - ???? USART_DR ??????? TXE ??
 * (USART_SendData())?
 * @retval ?
 */
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
  /* The CTS flag is not available for UART4 and UART5 */
  if ((USART_FLAG & USART_FLAG_CTS) == USART_FLAG_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  USARTx->SR = (uint16_t)~USART_FLAG;
}

/**
 * @brief ????? USART ???????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_IT??????? USART ????
 * ????????????
 * @arg USART_IT_CTS?CTS ????????? UART4 ? UART5?
 * @arg USART_IT_LBD?LIN ??????
 * @arg USART_IT_TXE: ??????????
 * @arg USART_IT_TC???????
 * @arg USART_IT_RXNE????????????
 * @arg USART_IT_IDLE?????????
 * @arg USART_IT_ORE???????
 * @arg USART_IT_NE???????
 * @arg USART_IT_FE??????
 * @arg USART_IT_PE?????????
 * @retval USART_IT ?????SET ? RESET??
 */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_GET_IT(USART_IT));
  /* The CTS interrupt is not available for UART4 and UART5 */
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  /* Get the USART register index */
  usartreg = (((uint8_t)USART_IT) >> 0x05);
  /* Get the interrupt position */
  itmask = USART_IT & IT_Mask;
  itmask = (uint32_t)0x01 << itmask;

  if (usartreg == 0x01) /* The IT  is in CR1 register */
  {
    itmask &= USARTx->CR1;
  }
  else if (usartreg == 0x02) /* The IT  is in CR2 register */
  {
    itmask &= USARTx->CR2;
  }
  else /* The IT  is in CR3 register */
  {
    itmask &= USARTx->CR3;
  }

  bitpos = USART_IT >> 0x08;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->SR;
  if ((itmask != (uint16_t)RESET)&&(bitpos != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
 * @brief ?? USARTx ???????
 * @param USARTx??? USART ? UART ???
 * ????????????
 * USART1?USART2?USART3?UART4 ? UART5?
 * @param USART_IT?????????????
 * ????????????
 * @arg USART_IT_CTS?CTS ????????? UART4 ? UART5?
 * @arg USART_IT_LBD?LIN ??????
 * @arg USART_IT_TC????????
 * @arg USART_IT_RXNE?????????????
 *
 * @??
 * - PE?????????FE??????NE???????ORE????
 * ???? IDLE???????????????
 * ?????? USART_SR ???????
 * (USART_GetITStatus()) ??? USART_DR ???????
 * (USART_ReceiveData())?
 * - RXNE ?????????? USART_DR ??????
 * (USART_ReceiveData())?
 * - TC ?????????????????
 * ? USART_SR ??? (USART_GetITStatus()) ??????????
 * ? USART_DR ??? (USART_SendData()) ????
 * - TXE ???????? USART_DR ??????
 * (USART_SendData())?
 * @retval ?
 */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint16_t bitpos = 0x00, itmask = 0x00;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT));
  /* The CTS interrupt is not available for UART4 and UART5 */
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  bitpos = USART_IT >> 0x08;
  itmask = ((uint16_t)0x01 << (uint16_t)bitpos);
  USARTx->SR = (uint16_t)~itmask;
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
