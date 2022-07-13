/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup I2C
 * @brief I2C driver modules
 * @{
 */

/** @defgroup I2C_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup I2C_Private_Defines
 * @{
 */

/* I2C SPE mask */
#define CR1_PE_Set ((uint16_t)0x0001)
#define CR1_PE_Reset ((uint16_t)0xFFFE)

/* I2C START mask */
#define CR1_START_Set ((uint16_t)0x0100)
#define CR1_START_Reset ((uint16_t)0xFEFF)

/* I2C STOP mask */
#define CR1_STOP_Set ((uint16_t)0x0200)
#define CR1_STOP_Reset ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CR1_ACK_Set ((uint16_t)0x0400)
#define CR1_ACK_Reset ((uint16_t)0xFBFF)

/* I2C ENGC mask */
#define CR1_ENGC_Set ((uint16_t)0x0040)
#define CR1_ENGC_Reset ((uint16_t)0xFFBF)

/* I2C SWRST mask */
#define CR1_SWRST_Set ((uint16_t)0x8000)
#define CR1_SWRST_Reset ((uint16_t)0x7FFF)

/* I2C PEC mask */
#define CR1_PEC_Set ((uint16_t)0x1000)
#define CR1_PEC_Reset ((uint16_t)0xEFFF)

/* I2C ENPEC mask */
#define CR1_ENPEC_Set ((uint16_t)0x0020)
#define CR1_ENPEC_Reset ((uint16_t)0xFFDF)

/* I2C ENARP mask */
#define CR1_ENARP_Set ((uint16_t)0x0010)
#define CR1_ENARP_Reset ((uint16_t)0xFFEF)

/* I2C NOSTRETCH mask */
#define CR1_NOSTRETCH_Set ((uint16_t)0x0080)
#define CR1_NOSTRETCH_Reset ((uint16_t)0xFF7F)

/* I2C registers Masks */
#define CR1_CLEAR_Mask ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CR2_DMAEN_Set ((uint16_t)0x0800)
#define CR2_DMAEN_Reset ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CR2_LAST_Set ((uint16_t)0x1000)
#define CR2_LAST_Reset ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CR2_FREQ_Reset ((uint16_t)0xFFC0)

/* I2C ADD0 mask */
#define OAR1_ADD0_Set ((uint16_t)0x0001)
#define OAR1_ADD0_Reset ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OAR2_ENDUAL_Set ((uint16_t)0x0001)
#define OAR2_ENDUAL_Reset ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OAR2_ADD2_Reset ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CCR_FS_Set ((uint16_t)0x8000)

/* I2C CCR mask */
#define CCR_CCR_Set ((uint16_t)0x0FFF)

/* I2C FLAG mask */
#define FLAG_Mask ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define ITEN_Mask ((uint32_t)0x07000000)

/**
 * @}
 */

/** @defgroup I2C_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup I2C_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup I2C_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup I2C_Private_Functions
 * @{
 */

/**
 * @brief ? I2Cx ??????????????????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @retval ?
 */
void I2C_DeInit(I2C_TypeDef *I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  if (I2Cx == I2C1)
  {
    /* Enable I2C1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    /* Release I2C1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
  }
  else
  {
    /* Enable I2C2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
    /* Release I2C2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
  }
}

/**
 * @brief ??????? I2Cx ??
 * I2C_InitStruct ?????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_InitStruct??? I2C_InitTypeDef ?????
 * ???? I2C ????????
 * @retval ?
 */
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct)
{
  uint16_t tmpreg = 0, freqrange = 0;
  uint16_t result = 0x04;
  uint32_t pclk1 = 8000000;
  RCC_ClocksTypeDef rcc_clocks;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));
  assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
  assert_param(IS_I2C_DUTY_CYCLE(I2C_InitStruct->I2C_DutyCycle));
  assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddress1));
  assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->I2C_Ack));
  assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AcknowledgedAddress));

  /*---------------------------- I2Cx CR2 Configuration ------------------------*/
  /* Get the I2Cx CR2 value */
  tmpreg = I2Cx->CR2;
  /* Clear frequency FREQ[5:0] bits */
  tmpreg &= CR2_FREQ_Reset;
  /* Get pclk1 frequency value */
  RCC_GetClocksFreq(&rcc_clocks);
  pclk1 = rcc_clocks.PCLK1_Frequency;
  /* Set frequency bits depending on pclk1 value */
  freqrange = (uint16_t)(pclk1 / 1000000);
  tmpreg |= freqrange;
  /* Write to I2Cx CR2 */
  I2Cx->CR2 = tmpreg;

  /*---------------------------- I2Cx CCR Configuration ------------------------*/
  /* Disable the selected I2C peripheral to configure TRISE */
  I2Cx->CR1 &= CR1_PE_Reset;
  /* Reset tmpreg value */
  /* Clear F/S, DUTY and CCR[11:0] bits */
  tmpreg = 0;

  /* Configure speed in standard mode */
  if (I2C_InitStruct->I2C_ClockSpeed <= 100000)
  {
    /* Standard mode speed calculate */
    result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));
    /* Test if CCR value is under 0x4*/
    if (result < 0x04)
    {
      /* Set minimum allowed value */
      result = 0x04;
    }
    /* Set speed value for standard mode */
    tmpreg |= result;
    /* Set Maximum Rise Time for standard mode */
    I2Cx->TRISE = freqrange + 1;
  }
  /* Configure speed in fast mode */
  else /*(I2C_InitStruct->I2C_ClockSpeed <= 400000)*/
  {
    if (I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_2)
    {
      /* Fast mode speed calculate: Tlow/Thigh = 2 */
      result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 3));
    }
    else /*I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_16_9*/
    {
      /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
      result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 25));
      /* Set DUTY bit */
      result |= I2C_DutyCycle_16_9;
    }

    /* Test if CCR value is under 0x1*/
    if ((result & CCR_CCR_Set) == 0)
    {
      /* Set minimum allowed value */
      result |= (uint16_t)0x0001;
    }
    /* Set speed value and set F/S bit for fast mode */
    tmpreg |= (uint16_t)(result | CCR_FS_Set);
    /* Set Maximum Rise Time for fast mode */
    I2Cx->TRISE = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
  }

  /* Write to I2Cx CCR */
  I2Cx->CCR = tmpreg;
  /* Enable the selected I2C peripheral */
  I2Cx->CR1 |= CR1_PE_Set;

  /*---------------------------- I2Cx CR1 Configuration ------------------------*/
  /* Get the I2Cx CR1 value */
  tmpreg = I2Cx->CR1;
  /* Clear ACK, SMBTYPE and  SMBUS bits */
  tmpreg &= CR1_CLEAR_Mask;
  /* Configure I2Cx: mode and acknowledgement */
  /* Set SMBTYPE and SMBUS bits according to I2C_Mode value */
  /* Set ACK bit according to I2C_Ack value */
  tmpreg |= (uint16_t)((uint32_t)I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack);
  /* Write to I2Cx CR1 */
  I2Cx->CR1 = tmpreg;

  /*---------------------------- I2Cx OAR1 Configuration -----------------------*/
  /* Set I2Cx Own Address1 and acknowledged address */
  I2Cx->OAR1 = (I2C_InitStruct->I2C_AcknowledgedAddress | I2C_InitStruct->I2C_OwnAddress1);
}

/**
 * @brief ???????? I2C_InitStruct ???
 * @param I2C_InitStruct????????? I2C_InitTypeDef ??????
 * @retval ?
 */
void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct)
{
  /*---------------- Reset I2C init structure parameters values ----------------*/
  /* initialize the I2C_ClockSpeed member */
  I2C_InitStruct->I2C_ClockSpeed = 5000;
  /* Initialize the I2C_Mode member */
  I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
  /* Initialize the I2C_DutyCycle member */
  I2C_InitStruct->I2C_DutyCycle = I2C_DutyCycle_2;
  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct->I2C_OwnAddress1 = 0;
  /* Initialize the I2C_Ack member */
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}

/**
 * @brief ???????? I2C ???
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2Cx ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_Cmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->CR1 |= CR1_PE_Set;
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->CR1 &= CR1_PE_Reset;
  }
}

/**
 * @brief ???????? I2C DMA ???
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C DMA ???????
 * ???????ENABLE ? DISABLE?
 * @retval None
 */
void I2C_DMACmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C DMA requests */
    I2Cx->CR2 |= CR2_DMAEN_Set;
  }
  else
  {
    /* Disable the selected I2C DMA requests */
    I2Cx->CR2 &= CR2_DMAEN_Reset;
  }
}

/**
 * @brief ????? DMA ??????????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C DMA ?????????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_DMALastTransferCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Next DMA transfer is the last transfer */
    I2Cx->CR2 |= CR2_LAST_Set;
  }
  else
  {
    /* Next DMA transfer is not the last transfer */
    I2Cx->CR2 &= CR2_LAST_Reset;
  }
}
/**
 * @brief ?? I2Cx ???????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C START ?????????
 * ???????ENABLE ? DISABLE?
 * @retval ??
 */
void I2C_GenerateSTART(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2Cx->CR1 |= CR1_START_Set;
  }
  else
  {
    /* Disable the START condition generation */
    I2Cx->CR1 &= CR1_START_Reset;
  }
}

/**
 * @brief ?? I2Cx ???????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C ???????????
 * ???????ENABLE ? DISABLE?
 * @retval ??
 */
void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2Cx->CR1 |= CR1_STOP_Set;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2Cx->CR1 &= CR1_STOP_Reset;
  }
}

/**
 * @brief ???????? I2C ?????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C ???????
 * ???????ENABLE ? DISABLE?
 * @retval ??
 */
void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    I2Cx->CR1 |= CR1_ACK_Set;
  }
  else
  {
    /* Disable the acknowledgement */
    I2Cx->CR1 &= CR1_ACK_Reset;
  }
}

/**
 * @brief ????? I2C ????? 2?
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param Address??? 7bit I2C ???? 2?
 * @retval ??
 */
void I2C_OwnAddress2Config(I2C_TypeDef *I2Cx, uint8_t Address)
{
  uint16_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  tmpreg = I2Cx->OAR2;

  /* Reset I2Cx Own address2 bit [7:1] */
  tmpreg &= OAR2_ADD2_Reset;

  /* Set I2Cx Own address2 */
  tmpreg |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);

  /* Store the new register value */
  I2Cx->OAR2 = tmpreg;
}

/**
 * @brief ???????? I2C ??????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C ??????????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_DualAddressCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable dual addressing mode */
    I2Cx->OAR2 |= OAR2_ENDUAL_Set;
  }
  else
  {
    /* Disable dual addressing mode */
    I2Cx->OAR2 &= OAR2_ENDUAL_Reset;
  }
}

/**
 * @brief ???????? I2C ???????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_GeneralCallCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable generall call */
    I2Cx->CR1 |= CR1_ENGC_Set;
  }
  else
  {
    /* Disable generall call */
    I2Cx->CR1 &= CR1_ENGC_Reset;
  }
}

/**
 * @brief ???????? I2C ???
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_IT?????????? I2C ????
 * ???????????????
 * @arg I2C_IT_BUF????????
 * @arg I2C_IT_EVT???????
 * @arg I2C_IT_ERR???????
 * @param NewState??? I2C ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_ITConfig(I2C_TypeDef *I2Cx, uint16_t I2C_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->CR2 |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->CR2 &= (uint16_t)~I2C_IT;
  }
}

/**
 * @brief ?? I2Cx ???????????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param ?????????..
 * @retval ?
 */
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Write in the DR register the data to be sent */
  I2Cx->DR = Data;
}

/**
 * @brief ?? I2Cx ??????????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @retval ?????????
 */
uint8_t I2C_ReceiveData(I2C_TypeDef *I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Return the data in the DR register */
  return (uint8_t)I2Cx->DR;
}

/**
 * @brief ?????????????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param Address: ??????????
 * @param I2C_Direction??? I2C ?????
 * ???????? ???????????
 * @arg I2C_Direction_Transmitter??????
 * @arg I2C_Direction_Receiver??????
 * @retval ??
 */
void I2C_Send7bitAddress(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));
  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction != I2C_Direction_Transmitter)
  {
    /* Set the address bit0 for read */
    Address |= OAR1_ADD0_Set;
  }
  else
  {
    /* Reset the address bit0 for write */
    Address &= OAR1_ADD0_Reset;
  }
  /* Send the address */
  I2Cx->DR = Address;
}

/**
 * @brief ????? I2C ?????????
 * @param I2C_Register???????????
 * ????????????
 * @arg I2C_Register_CR1?CR1 ????
 * @arg I2C_Register_CR2?CR2 ????
 * @arg I2C_Register_OAR1?OAR1 ????
 * @arg I2C_Register_OAR2?OAR2 ????
 * @arg I2C_Register_DR?DR ????
 * @arg I2C_Register_SR1?SR1 ????
 * @arg I2C_Register_SR2?SR2 ????
 * @arg I2C_Register_CCR?CCR ????
 * @arg I2C_Register_TRISE?TRISE ????
 * @retval ????????
 */
uint16_t I2C_ReadRegister(I2C_TypeDef *I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));

  tmp = (uint32_t)I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint16_t *)tmp);
}

/**
 * @brief ???????? I2C ?????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C ?????????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_SoftwareResetCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    I2Cx->CR1 |= CR1_SWRST_Set;
  }
  else
  {
    /* Peripheral not under reset */
    I2Cx->CR1 &= CR1_SWRST_Reset;
  }
}

/**
 * @brief ????????????? I2C NACK ???
 * ???? I2C Master Receiver ?????
 * ???????? 2???????????
 * ?????????????? I2C_NACKPosition_Next?
 * ?????? 2 ?????????
 * ?????????????????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_NACKPosition??? NACK ???
 * ????????????
 * @arg I2C_NACKPosition_Next??????????????
 * ??????
 * @arg I2C_NACKPosition_Current??????????????
 * ??????
 *
 * @note ?????? I2C_PECPositionConfig() ???? (POS)
 * ???? I2C_PECPositionConfig() ??? I2C ??
 * ???? SMBUS ???
 *
 * @retval ?
 */
void I2C_NACKPositionConfig(I2C_TypeDef *I2Cx, uint16_t I2C_NACKPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_NACK_POSITION(I2C_NACKPosition));

  /* Check the input parameter */
  if (I2C_NACKPosition == I2C_NACKPosition_Next)
  {
    /* Next byte in shift register is the last received byte */
    I2Cx->CR1 |= I2C_NACKPosition_Next;
  }
  else
  {
    /* Current byte in shift register is the last received byte */
    I2Cx->CR1 &= I2C_NACKPosition_Current;
  }
}

/**
 * @brief ? SMBusAlert ??????? I2C ?????????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_SMBusAlert??? SMBAlert ?????
 * ????????????
 * @arg I2C_SMBusAlert_Low?SMBAlert ????????
 * @arg I2C_SMBusAlert_High?SMBAlert ????????
 * @retval ?
 */
void I2C_SMBusAlertConfig(I2C_TypeDef *I2Cx, uint16_t I2C_SMBusAlert)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SMBUS_ALERT(I2C_SMBusAlert));
  if (I2C_SMBusAlert == I2C_SMBusAlert_Low)
  {
    /* Drive the SMBusAlert pin Low */
    I2Cx->CR1 |= I2C_SMBusAlert_Low;
  }
  else
  {
    /* Drive the SMBusAlert pin High  */
    I2Cx->CR1 &= I2C_SMBusAlert_High;
  }
}

/**
 * @brief ???????? I2C PEC ???
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2C PEC ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_TransmitPEC(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC transmission */
    I2Cx->CR1 |= CR1_PEC_Set;
  }
  else
  {
    /* Disable the selected I2C PEC transmission */
    I2Cx->CR1 &= CR1_PEC_Reset;
  }
}

/**
 * @brief ????? I2C PEC ???
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_PECPosition??? PEC ???
 * ????????????
 * @arg I2C_PECPosition_Next?????????PEC
 * @arg I2C_PECPosition_Current????????PEC
 *
 * @note ?????? I2C_NACKPositionConfig() ???? (POS)
 * ???? I2C_NACKPositionConfig() ??? SMBUS ??
 * ???? I2C ???
 *
 * @retval ?
 */
void I2C_PECPositionConfig(I2C_TypeDef *I2Cx, uint16_t I2C_PECPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_PEC_POSITION(I2C_PECPosition));
  if (I2C_PECPosition == I2C_PECPosition_Next)
  {
    /* Next byte in shift register is PEC */
    I2Cx->CR1 |= I2C_PECPosition_Next;
  }
  else
  {
    /* Current byte in shift register is PEC */
    I2Cx->CR1 &= I2C_PECPosition_Current;
  }
}

/**
 * @brief ?????????? PEC ????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2Cx PEC ????????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_CalculatePEC(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC calculation */
    I2Cx->CR1 |= CR1_ENPEC_Set;
  }
  else
  {
    /* Disable the selected I2C PEC calculation */
    I2Cx->CR1 &= CR1_ENPEC_Reset;
  }
}

/**
 * @brief ???? I2C ? PEC ??
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @retval PEC ??
 */
uint8_t I2C_GetPEC(I2C_TypeDef *I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Return the selected I2C PEC value */
  return ((I2Cx->SR2) >> 8);
}

/**
 * @brief ???????? I2C ARP?
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2Cx ARP ?????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_ARPCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C ARP */
    I2Cx->CR1 |= CR1_ENARP_Set;
  }
  else
  {
    /* Disable the selected I2C ARP */
    I2Cx->CR1 &= CR1_ENARP_Reset;
  }
}

/**
 * @brief ???????? I2C ?????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param NewState?I2Cx ?????????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void I2C_StretchClockCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState == DISABLE)
  {
    /* Enable the selected I2C Clock stretching */
    I2Cx->CR1 |= CR1_NOSTRETCH_Set;
  }
  else
  {
    /* Disable the selected I2C Clock stretching */
    I2Cx->CR1 &= CR1_NOSTRETCH_Reset;
  }
}

/**
 * @brief ????? I2C ????????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_DutyCycle???????????
 * ????????????
 * @arg I2C_DutyCycle_2?I2C ???? Tlow/Thigh = 2
 * @arg I2C_DutyCycle_16_9?I2C ???? Tlow/Thigh = 16/9
 * @retval ?
 */
void I2C_FastModeDutyCycleConfig(I2C_TypeDef *I2Cx, uint16_t I2C_DutyCycle)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));
  if (I2C_DutyCycle != I2C_DutyCycle_16_9)
  {
    /* I2C fast mode Tlow/Thigh=2 */
    I2Cx->CCR &= I2C_DutyCycle_2;
  }
  else
  {
    /* I2C fast mode Tlow/Thigh=16/9 */
    I2Cx->CCR |= I2C_DutyCycle_16_9;
  }
}

/**
 * @brief
 ****************************************************************************************
 *
 *                         I2C State Monitoring Functions
 *
 ****************************************************************************************
 * This I2C driver provides three different ways for I2C state monitoring
 *  depending on the application requirements and constraints:
 *
 *
 * 1) Basic state monitoring:
 *    Using I2C_CheckEvent() function:
 *    It compares the status registers (SR1 and SR2) content to a given event
 *    (can be the combination of one or more flags).
 *    It returns SUCCESS if the current status includes the given flags
 *    and returns ERROR if one or more flags are missing in the current status.
 *    - When to use:
 *      - This function is suitable for most applications as well as for startup
 *      activity since the events are fully described in the product reference manual
 *      (RM0008).
 *      - It is also suitable for users who need to define their own events.
 *    - Limitations:
 *      - If an error occurs (ie. error flags are set besides to the monitored flags),
 *        the I2C_CheckEvent() function may return SUCCESS despite the communication
 *        hold or corrupted real state.
 *        In this case, it is advised to use error interrupts to monitor the error
 *        events and handle them in the interrupt IRQ handler.
 *
 *        @note
 *        For error management, it is advised to use the following functions:
 *          - I2C_ITConfig() to configure and enable the error interrupts (I2C_IT_ERR).
 *          - I2Cx_ER_IRQHandler() which is called when the error interrupt occurs.
 *            Where x is the peripheral instance (I2C1, I2C2 ...)
 *          - I2C_GetFlagStatus() or I2C_GetITStatus() to be called into I2Cx_ER_IRQHandler()
 *            in order to determine which error occured.
 *          - I2C_ClearFlag() or I2C_ClearITPendingBit() and/or I2C_SoftwareResetCmd()
 *            and/or I2C_GenerateStop() in order to clear the error flag and source,
 *            and return to correct communication status.
 *
 *
 *  2) Advanced state monitoring:
 *     Using the function I2C_GetLastEvent() which returns the image of both status
 *     registers in a single word (uint32_t) (Status Register 2 value is shifted left
 *     by 16 bits and concatenated to Status Register 1).
 *     - When to use:
 *       - This function is suitable for the same applications above but it allows to
 *         overcome the mentioned limitation of I2C_GetFlagStatus() function.
 *         The returned value could be compared to events already defined in the
 *         library (stm32f10x_i2c.h) or to custom values defined by user.
 *       - This function is suitable when multiple flags are monitored at the same time.
 *       - At the opposite of I2C_CheckEvent() function, this function allows user to
 *         choose when an event is accepted (when all events flags are set and no
 *         other flags are set or just when the needed flags are set like
 *         I2C_CheckEvent() function).
 *     - Limitations:
 *       - User may need to define his own events.
 *       - Same remark concerning the error management is applicable for this
 *         function if user decides to check only regular communication flags (and
 *         ignores error flags).
 *
 *
 *  3) Flag-based state monitoring:
 *     Using the function I2C_GetFlagStatus() which simply returns the status of
 *     one single flag (ie. I2C_FLAG_RXNE ...).
 *     - When to use:
 *        - This function could be used for specific applications or in debug phase.
 *        - It is suitable when only one flag checking is needed (most I2C events
 *          are monitored through multiple flags).
 *     - Limitations:
 *        - When calling this function, the Status register is accessed. Some flags are
 *          cleared when the status register is accessed. So checking the status
 *          of one Flag, may clear other ones.
 *        - Function may need to be called twice or more in order to monitor one
 *          single event.
 *
 *  For detailed description of Events, please refer to section I2C_Events in
 *  stm32f10x_i2c.h file.
 *
 */

/**
 *
 *  1) Basic state monitoring
 *******************************************************************************
 */

/**
 * @brief ?????? I2Cx ???????????
 * ?????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_EVENT??????????
 * ????????????
 * @arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED?EV1
 * @arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED?EV1
 * @arg I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED?EV1
 * @arg I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED?EV1
 * @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED?EV1
 * @arg I2C_EVENT_SLAVE_BYTE_RECEIVED?EV2
 * @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF) : EV2
 * @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL) : EV2
 * @arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED?EV3
 * @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF) : EV3
 * @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL) : EV3
 * @arg I2C_EVENT_SLAVE_ACK_FAILURE : EV3_2
 * @arg I2C_EVENT_SLAVE_STOP_DETECTED?EV4
 * @arg I2C_EVENT_MASTER_MODE_SELECT : EV5
 * @arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED?EV6
 * @arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED?EV6
 * @arg I2C_EVENT_MASTER_BYTE_RECEIVED?EV7
 * @arg I2C_EVENT_MASTER_BYTE_TRANSMITTING : EV8
 * @arg I2C_EVENT_MASTER_BYTE_TRANSMITTED?EV8_2
 * @arg I2C_EVENT_MASTER_MODE_ADDRESS10 : EV9
 *
 * @note: ????????????
 * stm32f10x_i2c.h ???? I2C_Events?
 *
 * @retval ?? ErrorStatus ????
 * - SUCCESS????????? I2C_EVENT
 * - ?????????? I2C_EVENT ??
 */
ErrorStatus I2C_CheckEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_EVENT(I2C_EVENT));

  /* Read the I2Cx status register */
  flag1 = I2Cx->SR1;
  flag2 = I2Cx->SR2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & FLAG_Mask;

  /* Check whether the last event contains the I2C_EVENT */
  if ((lastevent & I2C_EVENT) == I2C_EVENT)
  {
    /* SUCCESS: last event is equal to I2C_EVENT */
    status = SUCCESS;
  }
  else
  {
    /* ERROR: last event is different from I2C_EVENT */
    status = ERROR;
  }
  /* Return status */
  return status;
}

/**
 *
 *  2) Advanced state monitoring
 *******************************************************************************
 */

/**
 * @brief ?????? I2Cx ???
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 *
 * @note: ????????????
 * stm32f10x_i2c.h ???? I2C_Events?
 *
 * @retval ??????
 */
uint32_t I2C_GetLastEvent(I2C_TypeDef *I2Cx)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Read the I2Cx status register */
  flag1 = I2Cx->SR1;
  flag2 = I2Cx->SR2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & FLAG_Mask;

  /* Return status */
  return lastevent;
}

/**
 *
 *  3) Flag-based state monitoring
 *******************************************************************************
 */

/**
 * @brief ?????????? I2C ???
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_FLAG??????????
 * ????????????
 * @arg I2C_FLAG_DUALF?????????
 * @arg I2C_FLAG_SMBHOST?SMBus ????????
 * @arg I2C_FLAG_SMBDEFAULT?SMBus ?????????
 * @arg I2C_FLAG_GENCALL????????????
 * @arg I2C_FLAG_TRA????/?????
 * @arg I2C_FLAG_BUSY???????
 * @arg I2C_FLAG_MSL??/???
 * @arg I2C_FLAG_SMBALERT?SMBus ????
 * @arg I2C_FLAG_TIMEOUT???? Tlow ????
 * @arg I2C_FLAG_PECERR: ?????? PEC ??
 * @arg I2C_FLAG_OVR???/?????????
 * @arg I2C_FLAG_AF???????
 * @arg I2C_FLAG_ARLO????????????
 * @arg I2C_FLAG_BERR???????
 * @arg I2C_FLAG_TXE??????????????
 * @arg I2C_FLAG_RXNE????????????????
 * @arg I2C_FLAG_STOPF????????????
 * @arg I2C_FLAG_ADD10?10 ????????????
 * @arg I2C_FLAG_BTF?????????
 * @arg I2C_FLAG_ADDR????????????“ADSL”
 * ???????????“ENDA”
 * @arg I2C_FLAG_SB???????????
 * @retval I2C_FLAG ?????SET ? RESET??
 */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG)
{
  FlagStatus bitstatus = RESET;
  __IO uint32_t i2creg = 0, i2cxbase = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

  /* Get the I2Cx peripheral base address */
  i2cxbase = (uint32_t)I2Cx;

  /* Read flag register index */
  i2creg = I2C_FLAG >> 28;

  /* Get bit[23:0] of the flag */
  I2C_FLAG &= FLAG_Mask;

  if (i2creg != 0)
  {
    /* Get the I2Cx SR1 register address */
    i2cxbase += 0x14;
  }
  else
  {
    /* Flag in I2Cx SR2 Register */
    I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
    /* Get the I2Cx SR2 register address */
    i2cxbase += 0x18;
  }

  if (((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
  {
    /* I2C_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_FLAG is reset */
    bitstatus = RESET;
  }

  /* Return the I2C_FLAG status */
  return bitstatus;
}

/**
 * @brief ?? I2Cx ??????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_FLAG??????????
 * ???????????????
 * @arg I2C_FLAG_SMBALERT?SMBus ????
 * @arg I2C_FLAG_TIMEOUT???? Tlow ????
 * @arg I2C_FLAG_PECERR: ?????? PEC ??
 * @arg I2C_FLAG_OVR???/?????????
 * @arg I2C_FLAG_AF???????
 * @arg I2C_FLAG_ARLO????????????
 * @arg I2C_FLAG_BERR???????
 *
 * @??
 * - STOPF?????????????????
 * ? I2C_SR1 ??? (I2C_GetFlagStatus()) ?????
 * ? I2C_CR1 ????I2C_Cmd() ???? I2C ????
 * - ADD10???? 10 ??????????????
 * ? I2C_SR1 (I2C_GetFlagStatus()) ????????
 * DR ?????????????
 * - BTF??????????????????
 * ? I2C_SR1 ??? (I2C_GetFlagStatus()) ????????
 * ?/? I2C_DR ??? (I2C_SendData())?
 * - ADDR?????????????????
 * I2C_SR1 ??? (I2C_GetFlagStatus()) ???????
 * I2C_SR2 ??? ((void)(I2Cx->SR2))?
 * - SB????????????? I2C_SR1 ?????
 * ??? (I2C_GetFlagStatus()) ??? I2C_DR ????
 * ??? (I2C_SendData())?
 * @retval ?
 */
void I2C_ClearFlag(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG)
{
  uint32_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));
  /* Get the I2C flag position */
  flagpos = I2C_FLAG & FLAG_Mask;
  /* Clear the selected I2C flag */
  I2Cx->SR1 = (uint16_t)~flagpos;
}

/**
 * @brief ?????????? I2C ???
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_IT???????????
 * ????????????
 * @arg I2C_IT_SMBALERT?SMBus ????
 * @arg I2C_IT_TIMEOUT???? Tlow ????
 * @arg I2C_IT_PECERR: ?????? PEC ??
 * @arg I2C_IT_OVR???/?????????
 * @arg I2C_IT_AF???????
 * @arg I2C_IT_ARLO????????????
 * @arg I2C_IT_BERR???????
 * @arg I2C_IT_TXE??????????????
 * @arg I2C_IT_RXNE????????????????
 * @arg I2C_IT_STOPF????????????
 * @arg I2C_IT_ADD10?10 ????????????
 * @arg I2C_IT_BTF?????????
 * @arg I2C_IT_ADDR????????????“ADSL”
 * ???????????“ENDAD”
 * @arg I2C_IT_SB???????????
 * @retval I2C_IT ?????SET ? RESET??
 */
ITStatus I2C_GetITStatus(I2C_TypeDef *I2Cx, uint32_t I2C_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_IT(I2C_IT));

  /* Check if the interrupt source is enabled or not */
  enablestatus = (uint32_t)(((I2C_IT & ITEN_Mask) >> 16) & (I2Cx->CR2));

  /* Get bit[23:0] of the flag */
  I2C_IT &= FLAG_Mask;

  /* Check the status of the specified I2C flag */
  if (((I2Cx->SR1 & I2C_IT) != (uint32_t)RESET) && enablestatus)
  {
    /* I2C_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_IT is reset */
    bitstatus = RESET;
  }
  /* Return the I2C_IT status */
  return bitstatus;
}

/**
 * @brief ?? I2Cx ???????
 * @param I2Cx??? x ??? 1 ? 2 ??? I2C ???
 * @param I2C_IT?????????????
 * ???????????????
 * @arg I2C_IT_SMBALERT?SMBus ????
 * @arg I2C_IT_TIMEOUT???? Tlow ????
 * @arg I2C_IT_PECERR??????? PEC ??
 * @arg I2C_IT_OVR???/?????????
 * @arg I2C_IT_AF???????
 * @arg I2C_IT_ARLO????????????
 * @arg I2C_IT_BERR???????
 *
 * @??
 * - STOPF?????????????????
 * ? I2C_SR1 ??? (I2C_GetITStatus())???????
 * I2C_CR1 ????I2C_Cmd() ???? I2C ????
 * - ADD10???? 10 ??????????????
 * ? I2C_SR1 (I2C_GetITStatus()) ???????????
 * I2C_DR ??????????
 * - BTF??????????????????
 * ? I2C_SR1 ??? (I2C_GetITStatus()) ??????
 * ?/? I2C_DR ??? (I2C_SendData())?
 * - ADDR?????????????????
 * I2C_SR1 ??? (I2C_GetITStatus()) ???????
 * I2C_SR2 ??? ((void)(I2Cx->SR2))?
 * - SB??????????????????
 * I2C_SR1 ??? (I2C_GetITStatus()) ??????
 * I2C_DR ??? (I2C_SendData())?
 * @retval ?
 */
void I2C_ClearITPendingBit(I2C_TypeDef *I2Cx, uint32_t I2C_IT)
{
  uint32_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_IT(I2C_IT));
  /* Get the I2C flag position */
  flagpos = I2C_IT & FLAG_Mask;
  /* Clear the selected I2C flag */
  I2Cx->SR1 = (uint16_t)~flagpos;
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
