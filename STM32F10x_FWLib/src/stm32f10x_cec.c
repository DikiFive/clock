/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_cec.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup CEC
 * @brief CEC driver modules
 * @{
 */

/** @defgroup CEC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup CEC_Private_Defines
 * @{
 */

/* ------------ CEC registers bit address in the alias region ----------- */
#define CEC_OFFSET (CEC_BASE - PERIPH_BASE)

/* --- CFGR Register ---*/

/* Alias word address of PE bit */
#define CFGR_OFFSET (CEC_OFFSET + 0x00)
#define PE_BitNumber 0x00
#define CFGR_PE_BB (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (PE_BitNumber * 4))

/* Alias word address of IE bit */
#define IE_BitNumber 0x01
#define CFGR_IE_BB (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (IE_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of TSOM bit */
#define CSR_OFFSET (CEC_OFFSET + 0x10)
#define TSOM_BitNumber 0x00
#define CSR_TSOM_BB (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TSOM_BitNumber * 4))

/* Alias word address of TEOM bit */
#define TEOM_BitNumber 0x01
#define CSR_TEOM_BB (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TEOM_BitNumber * 4))

#define CFGR_CLEAR_Mask (uint8_t)(0xF3)  /* CFGR register Mask */
#define FLAG_Mask ((uint32_t)0x00FFFFFF) /* CEC FLAG mask */

/**
 * @}
 */

/** @defgroup CEC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup CEC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup CEC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup CEC_Private_Functions
 * @{
 */

/**
 * @brief 将 CEC 外设寄存器初始化为默认复位
 * 值。
 * @param 无
 * @retval 无
 */
void CEC_DeInit(void)
{
  /* Enable CEC reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, ENABLE);
  /* Release CEC from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, DISABLE);
}

/**
 * @brief 根据指定初始化 CEC 外设
 * CEC_InitStruct 中的参数。
 * @param CEC_InitStruct：指向 CEC_InitTypeDef 结构的指针
 * 包含指定的配置信息
 * CEC 外围设备。
 * @retval 无
 */
void CEC_Init(CEC_InitTypeDef *CEC_InitStruct)
{
  uint16_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_CEC_BIT_TIMING_ERROR_MODE(CEC_InitStruct->CEC_BitTimingMode));
  assert_param(IS_CEC_BIT_PERIOD_ERROR_MODE(CEC_InitStruct->CEC_BitPeriodMode));

  /*---------------------------- CEC CFGR Configuration -----------------*/
  /* Get the CEC CFGR value */
  tmpreg = CEC->CFGR;

  /* Clear BTEM and BPEM bits */
  tmpreg &= CFGR_CLEAR_Mask;

  /* Configure CEC: Bit Timing Error and Bit Period Error */
  tmpreg |= (uint16_t)(CEC_InitStruct->CEC_BitTimingMode | CEC_InitStruct->CEC_BitPeriodMode);

  /* Write to CEC CFGR  register*/
  CEC->CFGR = tmpreg;
}

/**
 * @brief 启用或禁用指定的 CEC 外围设备。
 * @param NewState：CEC 外围设备的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void CEC_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *)CFGR_PE_BB = (uint32_t)NewState;

  if (NewState == DISABLE)
  {
    /* Wait until the PE bit is cleared by hardware (Idle Line detected) */
    while ((CEC->CFGR & CEC_CFGR_PE) != (uint32_t)RESET)
    {
    }
  }
}

/**
 * @brief 启用或禁用 CEC 中断。
 * @param NewState：CEC 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void CEC_ITConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *)CFGR_IE_BB = (uint32_t)NewState;
}

/**
 * @brief 定义 CEC 设备的自有地址。
 * @param CEC_OwnAddress：CEC自己的地址
 * @retval 无
 */
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress)
{
  /* Check the parameters */
  assert_param(IS_CEC_ADDRESS(CEC_OwnAddress));

  /* Set the CEC own address */
  CEC->OAR = CEC_OwnAddress;
}

/**
 * @brief 设置 CEC 预分频器值。
 * @param CEC_Prescaler：CEC 预分频器新值
 * @retval 无
 */
void CEC_SetPrescaler(uint16_t CEC_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_CEC_PRESCALER(CEC_Prescaler));

  /* Set the  Prescaler value*/
  CEC->PRES = CEC_Prescaler;
}

/**
 * @brief 通过 CEC 外设传输单个数据。
 * @param Data：要传输的数据。
 * @retval 无
 */
void CEC_SendDataByte(uint8_t Data)
{
  /* Transmit Data */
  CEC->TXD = Data;
}

/**
 * @brief 返回 CEC 外围设备最近接收到的数据。
 * @param 无
 * @retval 接收到的数据。
 */
uint8_t CEC_ReceiveDataByte(void)
{
  /* Receive Data */
  return (uint8_t)(CEC->RXD);
}

/**
 * @brief 开始一条新消息。
 * @param 无
 * @retval 无
 */
void CEC_StartOfMessage(void)
{
  /* Starts of new message */
  *(__IO uint32_t *)CSR_TSOM_BB = (uint32_t)0x1;
}

/**
 * @brief 传输带有或不带有 EOM 位的消息。
 * @param NewState：CEC Tx 消息结束的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void CEC_EndOfMessageCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* The data byte will be transmitted with or without an EOM bit*/
  *(__IO uint32_t *)CSR_TEOM_BB = (uint32_t)NewState;
}

/**
 * @brief 获取 CEC 标志状态
 * @param CEC_FLAG：指定要检查的 CEC 标志。
 * 此参数可以是以下值之一：
 * @arg CEC_FLAG_BTE：位时序错误
 * @arg CEC_FLAG_BPE: 位周期错误
 * @arg CEC_FLAG_RBTFE: Rx 块传输完成错误
 * @arg CEC_FLAG_SBE: 起始位错误
 * @arg CEC_FLAG_ACKE：块确认错误
 * @arg CEC_FLAG_LINE: 线路错误
 * @arg CEC_FLAG_TBTFE: Tx 块传输完成错误
 * @arg CEC_FLAG_TEOM: Tx 消息结束
 * @arg CEC_FLAG_TERR：发送错误
 * @arg CEC_FLAG_TBTRF：Tx 字节传输请求或块传输完成
 * @arg CEC_FLAG_RSOM: Rx 消息开始
 * @arg CEC_FLAG_REOM: Rx 消息结束
 * @arg CEC_FLAG_RERR：接收错误
 * @arg CEC_FLAG_RBTF: Rx 字节/块传输完成
 * @retval CEC_FLAG 的新状态（SET 或 RESET）
 */
FlagStatus CEC_GetFlagStatus(uint32_t CEC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t cecreg = 0, cecbase = 0;

  /* Check the parameters */
  assert_param(IS_CEC_GET_FLAG(CEC_FLAG));

  /* Get the CEC peripheral base address */
  cecbase = (uint32_t)(CEC_BASE);

  /* Read flag register index */
  cecreg = CEC_FLAG >> 28;

  /* Get bit[23:0] of the flag */
  CEC_FLAG &= FLAG_Mask;

  if (cecreg != 0)
  {
    /* Flag in CEC ESR Register */
    CEC_FLAG = (uint32_t)(CEC_FLAG >> 16);

    /* Get the CEC ESR register address */
    cecbase += 0xC;
  }
  else
  {
    /* Get the CEC CSR register address */
    cecbase += 0x10;
  }

  if (((*(__IO uint32_t *)cecbase) & CEC_FLAG) != (uint32_t)RESET)
  {
    /* CEC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC_FLAG is reset */
    bitstatus = RESET;
  }

  /* Return the CEC_FLAG status */
  return bitstatus;
}

/**
 * @brief 清除 CEC 的挂起标志。
 * @param CEC_FLAG：指定要清除的标志。
 * 该参数可以是以下值的任意组合：
 * @arg CEC_FLAG_TERR：发送错误
 * @arg CEC_FLAG_TBTRF：Tx 字节传输请求或块传输完成
 * @arg CEC_FLAG_RSOM: Rx 消息开始
 * @arg CEC_FLAG_REOM: Rx 消息结束
 * @arg CEC_FLAG_RERR：接收错误
 * @arg CEC_FLAG_RBTF: Rx 字节/块传输完成
 * @retval 无
 */
void CEC_ClearFlag(uint32_t CEC_FLAG)
{
  uint32_t tmp = 0x0;

  /* Check the parameters */
  assert_param(IS_CEC_CLEAR_FLAG(CEC_FLAG));

  tmp = CEC->CSR & 0x2;

  /* Clear the selected CEC flags */
  CEC->CSR &= (uint32_t)(((~(uint32_t)CEC_FLAG) & 0xFFFFFFFC) | tmp);
}

/**
  * @brief 检查指定的 CEC 中断是否发生。
  * @param CEC_IT：指定要检查的 CEC 中断源。
  * 此参数可以是以下值之一：
  * @arg CEC_IT_TERR：发送错误
  * @arg CEC_IT_TBTF: Tx 块传输完成
  * @arg CEC_IT_RERR：接收错误
  * @arg CEC_IT_RBTF: Rx 块传输完成
  * @retval CEC_IT 的新状态（SET 或 RESET）。
  */
ITStatus CEC_GetITStatus(uint8_t CEC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_CEC_GET_IT(CEC_IT));

  /* Get the CEC IT enable bit status */
  enablestatus = (CEC->CFGR & (uint8_t)CEC_CFGR_IE);

  /* Check the status of the specified CEC interrupt */
  if (((CEC->CSR & CEC_IT) != (uint32_t)RESET) && enablestatus)
  {
    /* CEC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the CEC_IT status */
  return bitstatus;
}

/**
 * @brief 清除 CEC 的中断挂起位。
 * @param CEC_IT：指定要清除的 CEC 中断挂起位。
 * 该参数可以是以下值的任意组合：
 * @arg CEC_IT_TERR：发送错误
 * @arg CEC_IT_TBTF: Tx 块传输完成
 * @arg CEC_IT_RERR：接收错误
 * @arg CEC_IT_RBTF: Rx 块传输完成
 * @retval 无
 */
void CEC_ClearITPendingBit(uint16_t CEC_IT)
{
  uint32_t tmp = 0x0;

  /* Check the parameters */
  assert_param(IS_CEC_GET_IT(CEC_IT));

  tmp = CEC->CSR & 0x2;

  /* Clear the selected CEC interrupt pending bits */
  CEC->CSR &= (uint32_t)(((~(uint32_t)CEC_IT) & 0xFFFFFFFC) | tmp);
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
