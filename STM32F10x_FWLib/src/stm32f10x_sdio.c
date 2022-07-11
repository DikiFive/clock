/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_sdio.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup SDIO
  * @brief SDIO driver modules
  * @{
  */

/** @defgroup SDIO_Private_TypesDefinitions
  * @{
  */

/* ------------ SDIO registers bit address in the alias region ----------- */
#define SDIO_OFFSET                (SDIO_BASE - PERIPH_BASE)

/* --- CLKCR Register ---*/

/* Alias word address of CLKEN bit */
#define CLKCR_OFFSET              (SDIO_OFFSET + 0x04)
#define CLKEN_BitNumber           0x08
#define CLKCR_CLKEN_BB            (PERIPH_BB_BASE + (CLKCR_OFFSET * 32) + (CLKEN_BitNumber * 4))

/* --- CMD Register ---*/

/* Alias word address of SDIOSUSPEND bit */
#define CMD_OFFSET                (SDIO_OFFSET + 0x0C)
#define SDIOSUSPEND_BitNumber     0x0B
#define CMD_SDIOSUSPEND_BB        (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (SDIOSUSPEND_BitNumber * 4))

/* Alias word address of ENCMDCOMPL bit */
#define ENCMDCOMPL_BitNumber      0x0C
#define CMD_ENCMDCOMPL_BB         (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (ENCMDCOMPL_BitNumber * 4))

/* Alias word address of NIEN bit */
#define NIEN_BitNumber            0x0D
#define CMD_NIEN_BB               (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (NIEN_BitNumber * 4))

/* Alias word address of ATACMD bit */
#define ATACMD_BitNumber          0x0E
#define CMD_ATACMD_BB             (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (ATACMD_BitNumber * 4))

/* --- DCTRL Register ---*/

/* Alias word address of DMAEN bit */
#define DCTRL_OFFSET              (SDIO_OFFSET + 0x2C)
#define DMAEN_BitNumber           0x03
#define DCTRL_DMAEN_BB            (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (DMAEN_BitNumber * 4))

/* Alias word address of RWSTART bit */
#define RWSTART_BitNumber         0x08
#define DCTRL_RWSTART_BB          (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWSTART_BitNumber * 4))

/* Alias word address of RWSTOP bit */
#define RWSTOP_BitNumber          0x09
#define DCTRL_RWSTOP_BB           (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWSTOP_BitNumber * 4))

/* Alias word address of RWMOD bit */
#define RWMOD_BitNumber           0x0A
#define DCTRL_RWMOD_BB            (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWMOD_BitNumber * 4))

/* Alias word address of SDIOEN bit */
#define SDIOEN_BitNumber          0x0B
#define DCTRL_SDIOEN_BB           (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (SDIOEN_BitNumber * 4))

/* ---------------------- SDIO registers bit mask ------------------------ */

/* --- CLKCR Register ---*/

/* CLKCR register clear mask */
#define CLKCR_CLEAR_MASK         ((uint32_t)0xFFFF8100)

/* --- PWRCTRL Register ---*/

/* SDIO PWRCTRL Mask */
#define PWR_PWRCTRL_MASK         ((uint32_t)0xFFFFFFFC)

/* --- DCTRL Register ---*/

/* SDIO DCTRL Clear Mask */
#define DCTRL_CLEAR_MASK         ((uint32_t)0xFFFFFF08)

/* --- CMD Register ---*/

/* CMD Register clear mask */
#define CMD_CLEAR_MASK           ((uint32_t)0xFFFFF800)

/* SDIO RESP Registers Address */
#define SDIO_RESP_ADDR           ((uint32_t)(SDIO_BASE + 0x14))

/**
  * @}
  */

/** @defgroup SDIO_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Private_Functions
  * @{
  */

/**
 * @brief 将 SDIO 外设寄存器取消初始化为其默认复位值。
 * @param 无
 * @retval 无
 */
void SDIO_DeInit(void)
{
  SDIO->POWER = 0x00000000;
  SDIO->CLKCR = 0x00000000;
  SDIO->ARG = 0x00000000;
  SDIO->CMD = 0x00000000;
  SDIO->DTIMER = 0x00000000;
  SDIO->DLEN = 0x00000000;
  SDIO->DCTRL = 0x00000000;
  SDIO->ICR = 0x00C007FF;
  SDIO->MASK = 0x00000000;
}
/**
 * @brief 根据指定初始化 SDIO 外设
 * SDIO_InitStruct 中的参数。
 * @param SDIO_InitStruct : 指向 SDIO_InitTypeDef 结构的指针
 * 包含 SDIO 外设的配置信息。
 * @retval 无
 */
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_SDIO_CLOCK_EDGE(SDIO_InitStruct->SDIO_ClockEdge));
  assert_param(IS_SDIO_CLOCK_BYPASS(SDIO_InitStruct->SDIO_ClockBypass));
  assert_param(IS_SDIO_CLOCK_POWER_SAVE(SDIO_InitStruct->SDIO_ClockPowerSave));
  assert_param(IS_SDIO_BUS_WIDE(SDIO_InitStruct->SDIO_BusWide));
  assert_param(IS_SDIO_HARDWARE_FLOW_CONTROL(SDIO_InitStruct->SDIO_HardwareFlowControl));

/*---------------------------- SDIO CLKCR Configuration ------------------------*/
  /* Get the SDIO CLKCR value */
  tmpreg = SDIO->CLKCR;

  /* Clear CLKDIV, PWRSAV, BYPASS, WIDBUS, NEGEDGE, HWFC_EN bits */
  tmpreg &= CLKCR_CLEAR_MASK;

  /* Set CLKDIV bits according to SDIO_ClockDiv value */
  /* Set PWRSAV bit according to SDIO_ClockPowerSave value */
  /* Set BYPASS bit according to SDIO_ClockBypass value */
  /* Set WIDBUS bits according to SDIO_BusWide value */
  /* Set NEGEDGE bits according to SDIO_ClockEdge value */
  /* Set HWFC_EN bits according to SDIO_HardwareFlowControl value */
  tmpreg |= (SDIO_InitStruct->SDIO_ClockDiv  | SDIO_InitStruct->SDIO_ClockPowerSave |
             SDIO_InitStruct->SDIO_ClockBypass | SDIO_InitStruct->SDIO_BusWide |
             SDIO_InitStruct->SDIO_ClockEdge | SDIO_InitStruct->SDIO_HardwareFlowControl);

  /* Write to SDIO CLKCR */
  SDIO->CLKCR = tmpreg;
}

/**
 * @brief 用默认值填充每个 SDIO_InitStruct 成员。
 * @param SDIO_InitStruct：指向 SDIO_InitTypeDef 结构的指针，该结构
 * 将被初始化。
 * @retval 无
 */
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct)
{
  /* SDIO_InitStruct members default value */
  SDIO_InitStruct->SDIO_ClockDiv = 0x00;
  SDIO_InitStruct->SDIO_ClockEdge = SDIO_ClockEdge_Rising;
  SDIO_InitStruct->SDIO_ClockBypass = SDIO_ClockBypass_Disable;
  SDIO_InitStruct->SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
  SDIO_InitStruct->SDIO_BusWide = SDIO_BusWide_1b;
  SDIO_InitStruct->SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
}

/**
 * @brief 启用或禁用 SDIO 时钟。
 * @param NewState：SDIO 时钟的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_ClockCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CLKCR_CLKEN_BB = (uint32_t)NewState;
}

/**
 * @brief 设置控制器的电源状态。
 * @param SDIO_PowerState：电源状态的新状态。
 * 此参数可以是以下值之一：
 * @arg SDIO_PowerState_OFF
 * @arg SDIO_PowerState_ON
 * @retval 无
 */
void SDIO_SetPowerState(uint32_t SDIO_PowerState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_POWER_STATE(SDIO_PowerState));

  SDIO->POWER &= PWR_PWRCTRL_MASK;
  SDIO->POWER |= SDIO_PowerState;
}

/**
 * @brief 获取控制器的电源状态。
 * @param 无
 * @retval 控制器的电源状态。 返回值可以
 * 是以下之一：
 * - 0x00：电源关闭
 * - 0x02：上电
 * - 0x03: 开机
 */
uint32_t SDIO_GetPowerState(void)
{
  return (SDIO->POWER & (~PWR_PWRCTRL_MASK));
}

/**
 * @brief 启用或禁用 SDIO 中断。
 * @param SDIO_IT：指定要启用或禁用的 SDIO 中断源。
 * 此参数可以是以下值之一或组合：
 * @arg SDIO_IT_CCRCFAIL：收到命令响应（CRC校验失败）中断
 * @arg SDIO_IT_DCRCFAIL：数据块发送/接收（CRC校验失败）中断
 * @arg SDIO_IT_CTIMEOUT：命令响应超时中断
 * @arg SDIO_IT_DTIMEOUT：数据超时中断
 * @arg SDIO_IT_TXUNDERR：发送 FIFO 欠载错误中断
 * @arg SDIO_IT_RXOVERR: 接收到 FIFO 溢出错误中断
 * @arg SDIO_IT_CMDREND：收到命令响应（CRC 校验通过）中断
 * @arg SDIO_IT_CMDSENT：命令发送（无需响应）中断
 * @arg SDIO_IT_DATAEND：数据结束（数据计数器，SDIDCOUNT，为零）中断
 * @arg SDIO_IT_STBITERR：未在所有数据信号上检测到起始位
 * 总线模式中断
 * @arg SDIO_IT_DBCKEND：数据块发送/接收（CRC校验通过）中断
 * @arg SDIO_IT_CMDACT：命令传输正在进行中断
 * @arg SDIO_IT_TXACT：数据传输中中断
 * @arg SDIO_IT_RXACT：正在进行数据接收中断
 * @arg SDIO_IT_TXFIFOHE：发送 FIFO 半空中断
 * @arg SDIO_IT_RXFIFOHF：接收 FIFO 半满中断
 * @arg SDIO_IT_TXFIFOF：发送 FIFO 满中断
 * @arg SDIO_IT_RXFIFOF：接收 FIFO 满中断
 * @arg SDIO_IT_TXFIFOE：发送 FIFO 空中断
 * @arg SDIO_IT_RXFIFOE: 接收 FIFO 空中断
 * @arg SDIO_IT_TXDAVL：发送 FIFO 中断中可用的数据
 * @arg SDIO_IT_RXDAVL：数据在接收 FIFO 中断中可用
 * @arg SDIO_IT_SDIOIT: SD I/O 中断接收中断
 * @arg SDIO_IT_CEATAEND：收到 CMD61 中断的 CE-ATA 命令完成信号
 * @param NewState：指定 SDIO 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_IT(SDIO_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SDIO interrupts */
    SDIO->MASK |= SDIO_IT;
  }
  else
  {
    /* Disable the SDIO interrupts */
    SDIO->MASK &= ~SDIO_IT;
  }
}

/**
 * @brief 启用或禁用 SDIO DMA 请求。
 * @param NewState：所选 SDIO DMA 请求的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_DMACmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) DCTRL_DMAEN_BB = (uint32_t)NewState;
}

/**
 * @brief 根据指定初始化 SDIO 命令
 * SDIO_CmdInitStruct 中的参数并发送命令。
 * @param SDIO_CmdInitStruct : 指向 SDIO_CmdInitTypeDef 的指针
 * 包含 SDIO 命令配置信息的结构。
 * @retval 无
 */
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_SDIO_CMD_INDEX(SDIO_CmdInitStruct->SDIO_CmdIndex));
  assert_param(IS_SDIO_RESPONSE(SDIO_CmdInitStruct->SDIO_Response));
  assert_param(IS_SDIO_WAIT(SDIO_CmdInitStruct->SDIO_Wait));
  assert_param(IS_SDIO_CPSM(SDIO_CmdInitStruct->SDIO_CPSM));

/*---------------------------- SDIO ARG Configuration ------------------------*/
  /* Set the SDIO Argument value */
  SDIO->ARG = SDIO_CmdInitStruct->SDIO_Argument;

/*---------------------------- SDIO CMD Configuration ------------------------*/
  /* Get the SDIO CMD value */
  tmpreg = SDIO->CMD;
  /* Clear CMDINDEX, WAITRESP, WAITINT, WAITPEND, CPSMEN bits */
  tmpreg &= CMD_CLEAR_MASK;
  /* Set CMDINDEX bits according to SDIO_CmdIndex value */
  /* Set WAITRESP bits according to SDIO_Response value */
  /* Set WAITINT and WAITPEND bits according to SDIO_Wait value */
  /* Set CPSMEN bits according to SDIO_CPSM value */
  tmpreg |= (uint32_t)SDIO_CmdInitStruct->SDIO_CmdIndex | SDIO_CmdInitStruct->SDIO_Response
           | SDIO_CmdInitStruct->SDIO_Wait | SDIO_CmdInitStruct->SDIO_CPSM;

  /* Write to SDIO CMD */
  SDIO->CMD = tmpreg;
}

/**
 * @brief 用默认值填充每个 SDIO_CmdInitStruct 成员。
 * @param SDIO_CmdInitStruct：指向 SDIO_CmdInitTypeDef 的指针
 * 将被初始化的结构。
 * @retval 无
 */
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct)
{
  /* SDIO_CmdInitStruct members default value */
  SDIO_CmdInitStruct->SDIO_Argument = 0x00;
  SDIO_CmdInitStruct->SDIO_CmdIndex = 0x00;
  SDIO_CmdInitStruct->SDIO_Response = SDIO_Response_No;
  SDIO_CmdInitStruct->SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStruct->SDIO_CPSM = SDIO_CPSM_Disable;
}

/**
 * @brief 返回收到响应的最后一个命令的命令索引。
 * @param 无
 * @retval 返回最后收到的命令响应的命令索引。
 */
uint8_t SDIO_GetCommandResponse(void)
{
  return (uint8_t)(SDIO->RESPCMD);
}

/**
 * @brief 返回从卡收到的最后一个命令的响应。
 * @param SDIO_RESP：指定 SDIO 响应寄存器。
 * 此参数可以是以下值之一：
 * @arg SDIO_RESP1：响应寄存器 1
 * @arg SDIO_RESP2：响应寄存器 2
 * @arg SDIO_RESP3：响应寄存器 3
 * @arg SDIO_RESP4：响应寄存器 4
 * @retval 对应的响应寄存器值。
 */
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_SDIO_RESP(SDIO_RESP));

  tmp = SDIO_RESP_ADDR + SDIO_RESP;

  return (*(__IO uint32_t *) tmp);
}

/**
 * @brief 根据指定初始化SDIO数据路径
 * SDIO_DataInitStruct 中的参数。
 * @param SDIO_DataInitStruct : 指向 SDIO_DataInitTypeDef 结构的指针
 * 包含 SDIO 命令的配置信息。
 * @retval 无
 */
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_SDIO_DATA_LENGTH(SDIO_DataInitStruct->SDIO_DataLength));
  assert_param(IS_SDIO_BLOCK_SIZE(SDIO_DataInitStruct->SDIO_DataBlockSize));
  assert_param(IS_SDIO_TRANSFER_DIR(SDIO_DataInitStruct->SDIO_TransferDir));
  assert_param(IS_SDIO_TRANSFER_MODE(SDIO_DataInitStruct->SDIO_TransferMode));
  assert_param(IS_SDIO_DPSM(SDIO_DataInitStruct->SDIO_DPSM));

/*---------------------------- SDIO DTIMER Configuration ---------------------*/
  /* Set the SDIO Data TimeOut value */
  SDIO->DTIMER = SDIO_DataInitStruct->SDIO_DataTimeOut;

/*---------------------------- SDIO DLEN Configuration -----------------------*/
  /* Set the SDIO DataLength value */
  SDIO->DLEN = SDIO_DataInitStruct->SDIO_DataLength;

/*---------------------------- SDIO DCTRL Configuration ----------------------*/
  /* Get the SDIO DCTRL value */
  tmpreg = SDIO->DCTRL;
  /* Clear DEN, DTMODE, DTDIR and DBCKSIZE bits */
  tmpreg &= DCTRL_CLEAR_MASK;
  /* Set DEN bit according to SDIO_DPSM value */
  /* Set DTMODE bit according to SDIO_TransferMode value */
  /* Set DTDIR bit according to SDIO_TransferDir value */
  /* Set DBCKSIZE bits according to SDIO_DataBlockSize value */
  tmpreg |= (uint32_t)SDIO_DataInitStruct->SDIO_DataBlockSize | SDIO_DataInitStruct->SDIO_TransferDir
           | SDIO_DataInitStruct->SDIO_TransferMode | SDIO_DataInitStruct->SDIO_DPSM;

  /* Write to SDIO DCTRL */
  SDIO->DCTRL = tmpreg;
}

/**
 * @brief 用默认值填充每个 SDIO_DataInitStruct 成员。
 * @param SDIO_DataInitStruct：指向 SDIO_DataInitTypeDef 结构的指针，该结构
 * 将被初始化。
 * @retval 无
 */
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
  /* SDIO_DataInitStruct members default value */
  SDIO_DataInitStruct->SDIO_DataTimeOut = 0xFFFFFFFF;
  SDIO_DataInitStruct->SDIO_DataLength = 0x00;
  SDIO_DataInitStruct->SDIO_DataBlockSize = SDIO_DataBlockSize_1b;
  SDIO_DataInitStruct->SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStruct->SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStruct->SDIO_DPSM = SDIO_DPSM_Disable;
}

/**
 * @brief 返回要传输的剩余数据字节数。
 * @param 无
 * @retval 要传输的剩余数据字节数
 */
uint32_t SDIO_GetDataCounter(void)
{
  return SDIO->DCOUNT;
}

/**
 * @brief 从 Rx FIFO 中读取一个数据字。
 * @param 无
 * @retval 收到的数据
 */
uint32_t SDIO_ReadData(void)
{
  return SDIO->FIFO;
}

/**
 * @brief 将一个数据字写入 Tx FIFO。
 * @param Data：要写入的 32 位数据字。
 * @retval 无
 */
void SDIO_WriteData(uint32_t Data)
{
  SDIO->FIFO = Data;
}

/**
 * @brief 返回要写入 FIFO 或从 FIFO 读取的字数。
 * @param 无
 * @retval 剩余字数。
 */
uint32_t SDIO_GetFIFOCount(void)
{
  return SDIO->FIFOCNT;
}

/**
 * @brief 启动 SD I/O 读取等待操作。
 * @param NewState：开始 SDIO 读取等待操作的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_StartSDIOReadWait(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) DCTRL_RWSTART_BB = (uint32_t) NewState;
}

/**
 * @brief 停止 SD I/O 读取等待操作。
 * @param NewState：Stop SDIO Read Wait 操作的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_StopSDIOReadWait(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) DCTRL_RWSTOP_BB = (uint32_t) NewState;
}

/**
 * @brief 设置插入读取等待间隔的两个选项之一。
 * @param SDIO_ReadWaitMode：SD I/O 读取等待操作模式。
 * 该参数可以是：
 * @arg SDIO_ReadWaitMode_CLK：通过停止 SDIOCLK 进行读取等待控制
 * @arg SDIO_ReadWaitMode_DATA2：使用 SDIO_DATA2 进行读取等待控制
 * @retval 无
 */
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode)
{
  /* Check the parameters */
  assert_param(IS_SDIO_READWAIT_MODE(SDIO_ReadWaitMode));

  *(__IO uint32_t *) DCTRL_RWMOD_BB = SDIO_ReadWaitMode;
}

/**
 * @brief 启用或禁用 SD I/O 模式操作。
 * @param NewState：SDIO 特定操作的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_SetSDIOOperation(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) DCTRL_SDIOEN_BB = (uint32_t)NewState;
}

/**
 * @brief 启用或禁用 SD I/O 模式暂停命令发送。
 * @param NewState：SD I/O 模式挂起命令的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CMD_SDIOSUSPEND_BB = (uint32_t)NewState;
}

/**
 * @brief 启用或禁用命令完成信号。
 * @param NewState：命令完成信号的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_CommandCompletionCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CMD_ENCMDCOMPL_BB = (uint32_t)NewState;
}

/**
 * @brief 启用或禁用 CE-ATA 中断。
 * @param NewState：CE-ATA 中断的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_CEATAITCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CMD_NIEN_BB = (uint32_t)((~((uint32_t)NewState)) & ((uint32_t)0x1));
}

/**
 * @brief 发送 CE-ATA 命令 (CMD61)。
 * @param NewState：CE-ATA 命令的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void SDIO_SendCEATACmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CMD_ATACMD_BB = (uint32_t)NewState;
}

/**
 * @brief 检查是否设置了指定的 SDIO 标志。
 * @param SDIO_FLAG：指定要检查的标志。
 * 此参数可以是以下值之一：
 * @arg SDIO_FLAG_CCRCFAIL：收到命令响应（CRC校验失败）
 * @arg SDIO_FLAG_DCRCFAIL：数据块发送/接收（CRC校验失败）
 * @arg SDIO_FLAG_CTIMEOUT：命令响应超时
 * @arg SDIO_FLAG_DTIMEOUT：数据超时
 * @arg SDIO_FLAG_TXUNDERR：传输 FIFO 欠载错误
 * @arg SDIO_FLAG_RXOVERR: 接收到 FIFO 溢出错误
 * @arg SDIO_FLAG_CMDREND：收到命令响应（CRC 校验通过）
 * @arg SDIO_FLAG_CMDSENT：命令已发送（无需响应）
 * @arg SDIO_FLAG_DATAEND：数据结束（数据计数器，SDIDCOUNT，为零）
 * @arg SDIO_FLAG_STBITERR：未在所有数据信号上检测到起始位
 *总线模式。
 * @arg SDIO_FLAG_DBCKEND：数据块发送/接收（CRC校验通过）
 * @arg SDIO_FLAG_CMDACT：命令传输正在进行中
 * @arg SDIO_FLAG_TXACT：数据传输中
 * @arg SDIO_FLAG_RXACT：正在接收数据
 * @arg SDIO_FLAG_TXFIFOHE：发送 FIFO 半空
 * @arg SDIO_FLAG_RXFIFOHF：接收 FIFO 半满
 * @arg SDIO_FLAG_TXFIFOF：发送 FIFO 已满
 * @arg SDIO_FLAG_RXFIFOF：接收 FIFO 已满
 * @arg SDIO_FLAG_TXFIFOE：发送 FIFO 为空
 * @arg SDIO_FLAG_RXFIFOE：接收 FIFO 为空
 * @arg SDIO_FLAG_TXDAVL：发送 FIFO 中可用的数据
 * @arg SDIO_FLAG_RXDAVL：接收 FIFO 中可用的数据
 * @arg SDIO_FLAG_SDIOIT：收到 SD I/O 中断
 * @arg SDIO_FLAG_CEATAEND：收到 CMD61 的 CE-ATA 命令完成信号
 * @retval SDIO_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus SDIO_GetFlagStatus(uint32_t SDIO_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_SDIO_FLAG(SDIO_FLAG));

  if ((SDIO->STA & SDIO_FLAG) != (uint32_t)RESET)
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
 * @brief 清除 SDIO 的挂起标志。
 * @param SDIO_FLAG：指定要清除的标志。
 * 此参数可以是以下值之一或组合：
 * @arg SDIO_FLAG_CCRCFAIL：收到命令响应（CRC校验失败）
 * @arg SDIO_FLAG_DCRCFAIL：数据块发送/接收（CRC校验失败）
 * @arg SDIO_FLAG_CTIMEOUT：命令响应超时
 * @arg SDIO_FLAG_DTIMEOUT：数据超时
 * @arg SDIO_FLAG_TXUNDERR：传输 FIFO 欠载错误
 * @arg SDIO_FLAG_RXOVERR: 接收到 FIFO 溢出错误
 * @arg SDIO_FLAG_CMDREND：收到命令响应（CRC 校验通过）
 * @arg SDIO_FLAG_CMDSENT：命令已发送（无需响应）
 * @arg SDIO_FLAG_DATAEND：数据结束（数据计数器，SDIDCOUNT，为零）
 * @arg SDIO_FLAG_STBITERR：未在所有数据信号上检测到起始位
 * 总线模式
 * @arg SDIO_FLAG_DBCKEND：数据块发送/接收（CRC校验通过）
 * @arg SDIO_FLAG_SDIOIT：收到 SD I/O 中断
 * @arg SDIO_FLAG_CEATAEND：收到 CMD61 的 CE-ATA 命令完成信号
 * @retval 无
 */
void SDIO_ClearFlag(uint32_t SDIO_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SDIO_CLEAR_FLAG(SDIO_FLAG));

  SDIO->ICR = SDIO_FLAG;
}

/**
 * @brief 检查指定的 SDIO 中断是否发生。
 * @param SDIO_IT：指定要检查的 SDIO 中断源。
 * 此参数可以是以下值之一：
 * @arg SDIO_IT_CCRCFAIL：收到命令响应（CRC校验失败）中断
 * @arg SDIO_IT_DCRCFAIL：数据块发送/接收（CRC校验失败）中断
 * @arg SDIO_IT_CTIMEOUT：命令响应超时中断
 * @arg SDIO_IT_DTIMEOUT：数据超时中断
 * @arg SDIO_IT_TXUNDERR：发送 FIFO 欠载错误中断
 * @arg SDIO_IT_RXOVERR: 接收到 FIFO 溢出错误中断
 * @arg SDIO_IT_CMDREND：收到命令响应（CRC 校验通过）中断
 * @arg SDIO_IT_CMDSENT：命令发送（无需响应）中断
 * @arg SDIO_IT_DATAEND：数据结束（数据计数器，SDIDCOUNT，为零）中断
 * @arg SDIO_IT_STBITERR：未在所有数据信号上检测到起始位
 * 总线模式中断
 * @arg SDIO_IT_DBCKEND：数据块发送/接收（CRC校验通过）中断
 * @arg SDIO_IT_CMDACT：命令传输正在进行中断
 * @arg SDIO_IT_TXACT：数据传输中中断
 * @arg SDIO_IT_RXACT：正在进行数据接收中断
 * @arg SDIO_IT_TXFIFOHE：发送 FIFO 半空中断
 * @arg SDIO_IT_RXFIFOHF：接收 FIFO 半满中断
 * @arg SDIO_IT_TXFIFOF：发送 FIFO 满中断
 * @arg SDIO_IT_RXFIFOF：接收 FIFO 满中断
 * @arg SDIO_IT_TXFIFOE：发送 FIFO 空中断
 * @arg SDIO_IT_RXFIFOE: 接收 FIFO 空中断
 * @arg SDIO_IT_TXDAVL：发送 FIFO 中断中可用的数据
 * @arg SDIO_IT_RXDAVL：数据在接收 FIFO 中断中可用
 * @arg SDIO_IT_SDIOIT: SD I/O 中断接收中断
 * @arg SDIO_IT_CEATAEND：收到 CMD61 中断的 CE-ATA 命令完成信号
 * @retval SDIO_IT 的新状态（SET 或 RESET）。
 */
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_SDIO_GET_IT(SDIO_IT));
  if ((SDIO->STA & SDIO_IT) != (uint32_t)RESET)
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
 * @brief 清除 SDIO 的中断挂起位。
 * @param SDIO_IT：指定要清除的中断挂起位。
 * 此参数可以是以下值之一或组合：
 * @arg SDIO_IT_CCRCFAIL：收到命令响应（CRC校验失败）中断
 * @arg SDIO_IT_DCRCFAIL：数据块发送/接收（CRC校验失败）中断
 * @arg SDIO_IT_CTIMEOUT：命令响应超时中断
 * @arg SDIO_IT_DTIMEOUT：数据超时中断
 * @arg SDIO_IT_TXUNDERR：发送 FIFO 欠载错误中断
 * @arg SDIO_IT_RXOVERR: 接收到 FIFO 溢出错误中断
 * @arg SDIO_IT_CMDREND：收到命令响应（CRC 校验通过）中断
 * @arg SDIO_IT_CMDSENT：命令发送（无需响应）中断
 * @arg SDIO_IT_DATAEND：数据结束（数据计数器，SDIDCOUNT，为零）中断
 * @arg SDIO_IT_STBITERR：未在所有数据信号上检测到起始位
 * 总线模式中断
 * @arg SDIO_IT_SDIOIT: SD I/O 中断接收中断
 * @arg SDIO_IT_CEATAEND：收到 CMD61 的 CE-ATA 命令完成信号
 * @retval 无
 */
void SDIO_ClearITPendingBit(uint32_t SDIO_IT)
{
  /* Check the parameters */
  assert_param(IS_SDIO_CLEAR_IT(SDIO_IT));

  SDIO->ICR = SDIO_IT;
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
