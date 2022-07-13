/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_fsmc.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup FSMC
 * @brief FSMC driver modules
 * @{
 */

/** @defgroup FSMC_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @defgroup FSMC_Private_Defines
 * @{
 */

/* --------------------- FSMC registers bit mask ---------------------------- */

/* FSMC BCRx Mask */
#define BCR_MBKEN_Set ((uint32_t)0x00000001)
#define BCR_MBKEN_Reset ((uint32_t)0x000FFFFE)
#define BCR_FACCEN_Set ((uint32_t)0x00000040)

/* FSMC PCRx Mask */
#define PCR_PBKEN_Set ((uint32_t)0x00000004)
#define PCR_PBKEN_Reset ((uint32_t)0x000FFFFB)
#define PCR_ECCEN_Set ((uint32_t)0x00000040)
#define PCR_ECCEN_Reset ((uint32_t)0x000FFFBF)
#define PCR_MemoryType_NAND ((uint32_t)0x00000008)
/**
 * @}
 */

/** @defgroup FSMC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup FSMC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup FSMC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup FSMC_Private_Functions
 * @{
 */

/**
 * @brief 将 FSMC NOR/SRAM 组寄存器取消初始化为默认值
 * 重置值。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank1_NORSRAM1：FSMC Bank1 NOR/SRAM1
 * @arg FSMC_Bank1_NORSRAM2：FSMC Bank1 NOR/SRAM2
 * @arg FSMC_Bank1_NORSRAM3：FSMC Bank1 NOR/SRAM3
 * @arg FSMC_Bank1_NORSRAM4：FSMC Bank1 NOR/SRAM4
 * @retval 无
 */
void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank)
{
  /* Check the parameter */
  assert_param(IS_FSMC_NORSRAM_BANK(FSMC_Bank));

  /* FSMC_Bank1_NORSRAM1 */
  if (FSMC_Bank == FSMC_Bank1_NORSRAM1)
  {
    FSMC_Bank1->BTCR[FSMC_Bank] = 0x000030DB;
  }
  /* FSMC_Bank1_NORSRAM2,  FSMC_Bank1_NORSRAM3 or FSMC_Bank1_NORSRAM4 */
  else
  {
    FSMC_Bank1->BTCR[FSMC_Bank] = 0x000030D2;
  }
  FSMC_Bank1->BTCR[FSMC_Bank + 1] = 0x0FFFFFFF;
  FSMC_Bank1E->BWTR[FSMC_Bank] = 0x0FFFFFFF;
}

/**
 * @brief 将 FSMC NAND 组寄存器取消初始化为其默认重置值。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @retval 无
 */
void FSMC_NANDDeInit(uint32_t FSMC_Bank)
{
  /* Check the parameter */
  assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));

  if (FSMC_Bank == FSMC_Bank2_NAND)
  {
    /* Set the FSMC_Bank2 registers to their reset values */
    FSMC_Bank2->PCR2 = 0x00000018;
    FSMC_Bank2->SR2 = 0x00000040;
    FSMC_Bank2->PMEM2 = 0xFCFCFCFC;
    FSMC_Bank2->PATT2 = 0xFCFCFCFC;
  }
  /* FSMC_Bank3_NAND */
  else
  {
    /* Set the FSMC_Bank3 registers to their reset values */
    FSMC_Bank3->PCR3 = 0x00000018;
    FSMC_Bank3->SR3 = 0x00000040;
    FSMC_Bank3->PMEM3 = 0xFCFCFCFC;
    FSMC_Bank3->PATT3 = 0xFCFCFCFC;
  }
}
/**
 * @brief 将 FSMC PCCARD 银行寄存器取消初始化为其默认复位值。
 * @param 无
 * @retval 无
 */
void FSMC_PCCARDDeInit(void)
{
  /* Set the FSMC_Bank4 registers to their reset values */
  FSMC_Bank4->PCR4 = 0x00000018;
  FSMC_Bank4->SR4 = 0x00000000;
  FSMC_Bank4->PMEM4 = 0xFCFCFCFC;
  FSMC_Bank4->PATT4 = 0xFCFCFCFC;
  FSMC_Bank4->PIO4 = 0xFCFCFCFC;
}

/**
 * @brief 根据指定初始化 FSMC NOR/SRAM Bank
 * FSMC_NORSRAMInitStruct 中的参数。
 * @param FSMC_NORSRAMInitStruct : 指向 FSMC_NORSRAMInitTypeDef 的指针
 * 包含配置信息的结构
 * FSMC NOR/SRAM 指定的 Banks。
 * @retval 无
 */
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef *FSMC_NORSRAMInitStruct)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_BANK(FSMC_NORSRAMInitStruct->FSMC_Bank));
  assert_param(IS_FSMC_MUX(FSMC_NORSRAMInitStruct->FSMC_DataAddressMux));
  assert_param(IS_FSMC_MEMORY(FSMC_NORSRAMInitStruct->FSMC_MemoryType));
  assert_param(IS_FSMC_MEMORY_WIDTH(FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth));
  assert_param(IS_FSMC_BURSTMODE(FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode));
  assert_param(IS_FSMC_ASYNWAIT(FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait));
  assert_param(IS_FSMC_WAIT_POLARITY(FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity));
  assert_param(IS_FSMC_WRAP_MODE(FSMC_NORSRAMInitStruct->FSMC_WrapMode));
  assert_param(IS_FSMC_WAIT_SIGNAL_ACTIVE(FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive));
  assert_param(IS_FSMC_WRITE_OPERATION(FSMC_NORSRAMInitStruct->FSMC_WriteOperation));
  assert_param(IS_FSMC_WAITE_SIGNAL(FSMC_NORSRAMInitStruct->FSMC_WaitSignal));
  assert_param(IS_FSMC_EXTENDED_MODE(FSMC_NORSRAMInitStruct->FSMC_ExtendedMode));
  assert_param(IS_FSMC_WRITE_BURST(FSMC_NORSRAMInitStruct->FSMC_WriteBurst));
  assert_param(IS_FSMC_ADDRESS_SETUP_TIME(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime));
  assert_param(IS_FSMC_ADDRESS_HOLD_TIME(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime));
  assert_param(IS_FSMC_DATASETUP_TIME(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime));
  assert_param(IS_FSMC_TURNAROUND_TIME(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration));
  assert_param(IS_FSMC_CLK_DIV(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision));
  assert_param(IS_FSMC_DATA_LATENCY(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency));
  assert_param(IS_FSMC_ACCESS_MODE(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode));

  /* Bank1 NOR/SRAM control register configuration */
  FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] =
      (uint32_t)FSMC_NORSRAMInitStruct->FSMC_DataAddressMux |
      FSMC_NORSRAMInitStruct->FSMC_MemoryType |
      FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth |
      FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode |
      FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait |
      FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity |
      FSMC_NORSRAMInitStruct->FSMC_WrapMode |
      FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive |
      FSMC_NORSRAMInitStruct->FSMC_WriteOperation |
      FSMC_NORSRAMInitStruct->FSMC_WaitSignal |
      FSMC_NORSRAMInitStruct->FSMC_ExtendedMode |
      FSMC_NORSRAMInitStruct->FSMC_WriteBurst;

  if (FSMC_NORSRAMInitStruct->FSMC_MemoryType == FSMC_MemoryType_NOR)
  {
    FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] |= (uint32_t)BCR_FACCEN_Set;
  }

  /* Bank1 NOR/SRAM timing register configuration */
  FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank + 1] =
      (uint32_t)FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime |
      (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime << 4) |
      (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime << 8) |
      (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
      (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision << 20) |
      (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency << 24) |
      FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode;

  /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
  if (FSMC_NORSRAMInitStruct->FSMC_ExtendedMode == FSMC_ExtendedMode_Enable)
  {
    assert_param(IS_FSMC_ADDRESS_SETUP_TIME(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime));
    assert_param(IS_FSMC_ADDRESS_HOLD_TIME(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime));
    assert_param(IS_FSMC_DATASETUP_TIME(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime));
    assert_param(IS_FSMC_CLK_DIV(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision));
    assert_param(IS_FSMC_DATA_LATENCY(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency));
    assert_param(IS_FSMC_ACCESS_MODE(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode));
    FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] =
        (uint32_t)FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime |
        (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime << 4) |
        (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime << 8) |
        (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision << 20) |
        (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency << 24) |
        FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode;
  }
  else
  {
    FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 0x0FFFFFFF;
  }
}

/**
 * @brief 根据指定初始化 FSMC NAND Bank
 * FSMC_NANDInitStruct 中的参数。
 * @param FSMC_NANDInitStruct : 指向 FSMC_NANDInitTypeDef 的指针
 * 包含 FSMC 配置信息的结构
 * NAND 指定的银行。
 * @retval 无
 */
void FSMC_NANDInit(FSMC_NANDInitTypeDef *FSMC_NANDInitStruct)
{
  uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

  /* Check the parameters */
  assert_param(IS_FSMC_NAND_BANK(FSMC_NANDInitStruct->FSMC_Bank));
  assert_param(IS_FSMC_WAIT_FEATURE(FSMC_NANDInitStruct->FSMC_Waitfeature));
  assert_param(IS_FSMC_MEMORY_WIDTH(FSMC_NANDInitStruct->FSMC_MemoryDataWidth));
  assert_param(IS_FSMC_ECC_STATE(FSMC_NANDInitStruct->FSMC_ECC));
  assert_param(IS_FSMC_ECCPAGE_SIZE(FSMC_NANDInitStruct->FSMC_ECCPageSize));
  assert_param(IS_FSMC_TCLR_TIME(FSMC_NANDInitStruct->FSMC_TCLRSetupTime));
  assert_param(IS_FSMC_TAR_TIME(FSMC_NANDInitStruct->FSMC_TARSetupTime));
  assert_param(IS_FSMC_SETUP_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime));
  assert_param(IS_FSMC_SETUP_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime));

  /* Set the tmppcr value according to FSMC_NANDInitStruct parameters */
  tmppcr = (uint32_t)FSMC_NANDInitStruct->FSMC_Waitfeature |
           PCR_MemoryType_NAND |
           FSMC_NANDInitStruct->FSMC_MemoryDataWidth |
           FSMC_NANDInitStruct->FSMC_ECC |
           FSMC_NANDInitStruct->FSMC_ECCPageSize |
           (FSMC_NANDInitStruct->FSMC_TCLRSetupTime << 9) |
           (FSMC_NANDInitStruct->FSMC_TARSetupTime << 13);

  /* Set tmppmem value according to FSMC_CommonSpaceTimingStructure parameters */
  tmppmem = (uint32_t)FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24);

  /* Set tmppatt value according to FSMC_AttributeSpaceTimingStructure parameters */
  tmppatt = (uint32_t)FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24);

  if (FSMC_NANDInitStruct->FSMC_Bank == FSMC_Bank2_NAND)
  {
    /* FSMC_Bank2_NAND registers configuration */
    FSMC_Bank2->PCR2 = tmppcr;
    FSMC_Bank2->PMEM2 = tmppmem;
    FSMC_Bank2->PATT2 = tmppatt;
  }
  else
  {
    /* FSMC_Bank3_NAND registers configuration */
    FSMC_Bank3->PCR3 = tmppcr;
    FSMC_Bank3->PMEM3 = tmppmem;
    FSMC_Bank3->PATT3 = tmppatt;
  }
}

/**
 * @brief 根据指定初始化 FSMC PCCARD Bank
 * FSMC_PCCARDInitStruct 中的参数。
 * @param FSMC_PCCARDInitStruct : 指向 FSMC_PCCARDInitTypeDef 的指针
 * 包含 FSMC 配置信息的结构
 * PCCARD 银行。
 * @retval 无
 */
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef *FSMC_PCCARDInitStruct)
{
  /* Check the parameters */
  assert_param(IS_FSMC_WAIT_FEATURE(FSMC_PCCARDInitStruct->FSMC_Waitfeature));
  assert_param(IS_FSMC_TCLR_TIME(FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime));
  assert_param(IS_FSMC_TAR_TIME(FSMC_PCCARDInitStruct->FSMC_TARSetupTime));

  assert_param(IS_FSMC_SETUP_TIME(FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime));

  assert_param(IS_FSMC_SETUP_TIME(FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime));
  assert_param(IS_FSMC_SETUP_TIME(FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime));

  /* Set the PCR4 register value according to FSMC_PCCARDInitStruct parameters */
  FSMC_Bank4->PCR4 = (uint32_t)FSMC_PCCARDInitStruct->FSMC_Waitfeature |
                     FSMC_MemoryDataWidth_16b |
                     (FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime << 9) |
                     (FSMC_PCCARDInitStruct->FSMC_TARSetupTime << 13);

  /* Set PMEM4 register value according to FSMC_CommonSpaceTimingStructure parameters */
  FSMC_Bank4->PMEM4 = (uint32_t)FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
                      (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
                      (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
                      (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24);

  /* Set PATT4 register value according to FSMC_AttributeSpaceTimingStructure parameters */
  FSMC_Bank4->PATT4 = (uint32_t)FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
                      (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
                      (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
                      (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24);

  /* Set PIO4 register value according to FSMC_IOSpaceTimingStructure parameters */
  FSMC_Bank4->PIO4 = (uint32_t)FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime |
                     (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
                     (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
                     (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime << 24);
}

/**
 * @brief 用默认值填充每个 FSMC_NORSRAMInitStruct 成员。
 * @param FSMC_NORSRAMInitStruct：指向 FSMC_NORSRAMInitTypeDef 的指针
 * 将被初始化的结构。
 * @retval 无
 */
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef *FSMC_NORSRAMInitStruct)
{
  /* Reset NOR/SRAM Init structure parameters values */
  FSMC_NORSRAMInitStruct->FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStruct->FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
  FSMC_NORSRAMInitStruct->FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
  FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStruct->FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStruct->FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStruct->FSMC_WaitSignal = FSMC_WaitSignal_Enable;
  FSMC_NORSRAMInitStruct->FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStruct->FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime = 0xFF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode = FSMC_AccessMode_A;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime = 0xFF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode = FSMC_AccessMode_A;
}

/**
 * @brief 用默认值填充每个 FSMC_NANDInitStruct 成员。
 * @param FSMC_NANDInitStruct：指向 FSMC_NANDInitTypeDef 的指针
 * 将被初始化的结构。
 * @retval 无
 */
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef *FSMC_NANDInitStruct)
{
  /* Reset NAND Init structure parameters values */
  FSMC_NANDInitStruct->FSMC_Bank = FSMC_Bank2_NAND;
  FSMC_NANDInitStruct->FSMC_Waitfeature = FSMC_Waitfeature_Disable;
  FSMC_NANDInitStruct->FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
  FSMC_NANDInitStruct->FSMC_ECC = FSMC_ECC_Disable;
  FSMC_NANDInitStruct->FSMC_ECCPageSize = FSMC_ECCPageSize_256Bytes;
  FSMC_NANDInitStruct->FSMC_TCLRSetupTime = 0x0;
  FSMC_NANDInitStruct->FSMC_TARSetupTime = 0x0;
  FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
}

/**
 * @brief 用默认值填充每个 FSMC_PCCARDInitStruct 成员。
 * @param FSMC_PCCARDInitStruct：指向 FSMC_PCCARDInitTypeDef 的指针
 * 将被初始化的结构。
 * @retval 无
 */
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef *FSMC_PCCARDInitStruct)
{
  /* Reset PCCARD Init structure parameters values */
  FSMC_PCCARDInitStruct->FSMC_Waitfeature = FSMC_Waitfeature_Disable;
  FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime = 0x0;
  FSMC_PCCARDInitStruct->FSMC_TARSetupTime = 0x0;
  FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
}

/**
 * @brief 启用或禁用指定的 NOR/SRAM 内存库。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank1_NORSRAM1：FSMC Bank1 NOR/SRAM1
 * @arg FSMC_Bank1_NORSRAM2：FSMC Bank1 NOR/SRAM2
 * @arg FSMC_Bank1_NORSRAM3：FSMC Bank1 NOR/SRAM3
 * @arg FSMC_Bank1_NORSRAM4：FSMC Bank1 NOR/SRAM4
 * @param NewState：FSMC_Bank 的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState)
{
  assert_param(IS_FSMC_NORSRAM_BANK(FSMC_Bank));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register */
    FSMC_Bank1->BTCR[FSMC_Bank] |= BCR_MBKEN_Set;
  }
  else
  {
    /* Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register */
    FSMC_Bank1->BTCR[FSMC_Bank] &= BCR_MBKEN_Reset;
  }
}

/**
 * @brief 启用或禁用指定的 NAND 内存库。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @param NewState：FSMC_Bank 的新状态。 该参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState)
{
  assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected NAND Bank by setting the PBKEN bit in the PCRx register */
    if (FSMC_Bank == FSMC_Bank2_NAND)
    {
      FSMC_Bank2->PCR2 |= PCR_PBKEN_Set;
    }
    else
    {
      FSMC_Bank3->PCR3 |= PCR_PBKEN_Set;
    }
  }
  else
  {
    /* Disable the selected NAND Bank by clearing the PBKEN bit in the PCRx register */
    if (FSMC_Bank == FSMC_Bank2_NAND)
    {
      FSMC_Bank2->PCR2 &= PCR_PBKEN_Reset;
    }
    else
    {
      FSMC_Bank3->PCR3 &= PCR_PBKEN_Reset;
    }
  }
}

/**
 * @brief 启用或禁用 PCCARD 内存库。
 * @param NewState：PCCARD 内存库的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void FSMC_PCCARDCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the PCCARD Bank by setting the PBKEN bit in the PCR4 register */
    FSMC_Bank4->PCR4 |= PCR_PBKEN_Set;
  }
  else
  {
    /* Disable the PCCARD Bank by clearing the PBKEN bit in the PCR4 register */
    FSMC_Bank4->PCR4 &= PCR_PBKEN_Reset;
  }
}

/**
 * @brief 启用或禁用 FSMC NAND ECC 功能。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @param NewState：FSMC NAND ECC 功能的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState)
{
  assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected NAND Bank ECC function by setting the ECCEN bit in the PCRx register */
    if (FSMC_Bank == FSMC_Bank2_NAND)
    {
      FSMC_Bank2->PCR2 |= PCR_ECCEN_Set;
    }
    else
    {
      FSMC_Bank3->PCR3 |= PCR_ECCEN_Set;
    }
  }
  else
  {
    /* Disable the selected NAND Bank ECC function by clearing the ECCEN bit in the PCRx register */
    if (FSMC_Bank == FSMC_Bank2_NAND)
    {
      FSMC_Bank2->PCR2 &= PCR_ECCEN_Reset;
    }
    else
    {
      FSMC_Bank3->PCR3 &= PCR_ECCEN_Reset;
    }
  }
}

/**
 * @brief 返回纠错码寄存器值。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @retval 纠错码 (ECC) 值。
 */
uint32_t FSMC_GetECC(uint32_t FSMC_Bank)
{
  uint32_t eccval = 0x00000000;

  if (FSMC_Bank == FSMC_Bank2_NAND)
  {
    /* Get the ECCR2 register value */
    eccval = FSMC_Bank2->ECCR2;
  }
  else
  {
    /* Get the ECCR3 register value */
    eccval = FSMC_Bank3->ECCR3;
  }
  /* Return the error correction code value */
  return (eccval);
}

/**
 * @brief 启用或禁用指定的 FSMC 中断。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @arg FSMC_Bank4_PCCARD：FSMC Bank4 PCCARD
 * @param FSMC_IT：指定要启用或禁用的 FSMC 中断源。
 * 该参数可以是以下值的任意组合：
 * @arg FSMC_IT_RisingEdge：上升沿检测中断。
 * @arg FSMC_IT_Level：电平边缘检测中断。
 * @arg FSMC_IT_FallingEdge：下降沿检测中断。
 * @param NewState：指定 FSMC 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void FSMC_ITConfig(uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState)
{
  assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
  assert_param(IS_FSMC_IT(FSMC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected FSMC_Bank2 interrupts */
    if (FSMC_Bank == FSMC_Bank2_NAND)
    {
      FSMC_Bank2->SR2 |= FSMC_IT;
    }
    /* Enable the selected FSMC_Bank3 interrupts */
    else if (FSMC_Bank == FSMC_Bank3_NAND)
    {
      FSMC_Bank3->SR3 |= FSMC_IT;
    }
    /* Enable the selected FSMC_Bank4 interrupts */
    else
    {
      FSMC_Bank4->SR4 |= FSMC_IT;
    }
  }
  else
  {
    /* Disable the selected FSMC_Bank2 interrupts */
    if (FSMC_Bank == FSMC_Bank2_NAND)
    {

      FSMC_Bank2->SR2 &= (uint32_t)~FSMC_IT;
    }
    /* Disable the selected FSMC_Bank3 interrupts */
    else if (FSMC_Bank == FSMC_Bank3_NAND)
    {
      FSMC_Bank3->SR3 &= (uint32_t)~FSMC_IT;
    }
    /* Disable the selected FSMC_Bank4 interrupts */
    else
    {
      FSMC_Bank4->SR4 &= (uint32_t)~FSMC_IT;
    }
  }
}

/**
 * @brief 检查是否设置了指定的 FSMC 标志。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @arg FSMC_Bank4_PCCARD：FSMC Bank4 PCCARD
 * @param FSMC_FLAG：指定要检查的标志。
 * 此参数可以是以下值之一：
 * @arg FSMC_FLAG_RisingEdge：上升egde检测标志。
 * @arg FSMC_FLAG_Level：电平检测标志。
 * @arg FSMC_FLAG_FallingEdge：下降 egde 检测标志。
 * @arg FSMC_FLAG_FEMPT：先进先出空标志。
 * @retval FSMC_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpsr = 0x00000000;

  /* Check the parameters */
  assert_param(IS_FSMC_GETFLAG_BANK(FSMC_Bank));
  assert_param(IS_FSMC_GET_FLAG(FSMC_FLAG));

  if (FSMC_Bank == FSMC_Bank2_NAND)
  {
    tmpsr = FSMC_Bank2->SR2;
  }
  else if (FSMC_Bank == FSMC_Bank3_NAND)
  {
    tmpsr = FSMC_Bank3->SR3;
  }
  /* FSMC_Bank4_PCCARD*/
  else
  {
    tmpsr = FSMC_Bank4->SR4;
  }

  /* Get the flag status */
  if ((tmpsr & FSMC_FLAG) != (uint16_t)RESET)
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
 * @brief 清除 FSMC 的挂起标志。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @arg FSMC_Bank4_PCCARD：FSMC Bank4 PCCARD
 * @param FSMC_FLAG：指定要清除的标志。
 * 该参数可以是以下值的任意组合：
 * @arg FSMC_FLAG_RisingEdge：上升egde检测标志。
 * @arg FSMC_FLAG_Level：电平检测标志。
 * @arg FSMC_FLAG_FallingEdge：下降 egde 检测标志。
 * @retval 无
 */
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_FSMC_GETFLAG_BANK(FSMC_Bank));
  assert_param(IS_FSMC_CLEAR_FLAG(FSMC_FLAG));

  if (FSMC_Bank == FSMC_Bank2_NAND)
  {
    FSMC_Bank2->SR2 &= ~FSMC_FLAG;
  }
  else if (FSMC_Bank == FSMC_Bank3_NAND)
  {
    FSMC_Bank3->SR3 &= ~FSMC_FLAG;
  }
  /* FSMC_Bank4_PCCARD*/
  else
  {
    FSMC_Bank4->SR4 &= ~FSMC_FLAG;
  }
}

/**
 * @brief 检查是否发生了指定的 FSMC 中断。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @arg FSMC_Bank4_PCCARD：FSMC Bank4 PCCARD
 * @param FSMC_IT：指定要检查的 FSMC 中断源。
 * 此参数可以是以下值之一：
 * @arg FSMC_IT_RisingEdge：上升沿检测中断。
 * @arg FSMC_IT_Level：电平边缘检测中断。
 * @arg FSMC_IT_FallingEdge：下降沿检测中断。
 * @retval FSMC_IT 的新状态（SET 或 RESET）。
 */
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpsr = 0x0, itstatus = 0x0, itenable = 0x0;

  /* Check the parameters */
  assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
  assert_param(IS_FSMC_GET_IT(FSMC_IT));

  if (FSMC_Bank == FSMC_Bank2_NAND)
  {
    tmpsr = FSMC_Bank2->SR2;
  }
  else if (FSMC_Bank == FSMC_Bank3_NAND)
  {
    tmpsr = FSMC_Bank3->SR3;
  }
  /* FSMC_Bank4_PCCARD*/
  else
  {
    tmpsr = FSMC_Bank4->SR4;
  }

  itstatus = tmpsr & FSMC_IT;

  itenable = tmpsr & (FSMC_IT >> 3);
  if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
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
 * @brief 清除 FSMC 的中断挂起位。
 * @param FSMC_Bank：指定要使用的 FSMC 银行
 * 此参数可以是以下值之一：
 * @arg FSMC_Bank2_NAND：FSMC Bank2 NAND
 * @arg FSMC_Bank3_NAND：FSMC Bank3 NAND
 * @arg FSMC_Bank4_PCCARD：FSMC Bank4 PCCARD
 * @param FSMC_IT：指定要清除的中断挂起位。
 * 该参数可以是以下值的任意组合：
 * @arg FSMC_IT_RisingEdge：上升沿检测中断。
 * @arg FSMC_IT_Level：电平边缘检测中断。
 * @arg FSMC_IT_FallingEdge：下降沿检测中断。
 * @retval 无
 */
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT)
{
  /* Check the parameters */
  assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
  assert_param(IS_FSMC_IT(FSMC_IT));

  if (FSMC_Bank == FSMC_Bank2_NAND)
  {
    FSMC_Bank2->SR2 &= ~(FSMC_IT >> 3);
  }
  else if (FSMC_Bank == FSMC_Bank3_NAND)
  {
    FSMC_Bank3->SR3 &= ~(FSMC_IT >> 3);
  }
  /* FSMC_Bank4_PCCARD*/
  else
  {
    FSMC_Bank4->SR4 &= ~(FSMC_IT >> 3);
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
