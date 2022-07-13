/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_flash.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup FLASH
 * @brief FLASH driver modules
 * @{
 */

/** @defgroup FLASH_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup FLASH_Private_Defines
 * @{
 */

/* Flash Access Control Register bits */
#define ACR_LATENCY_Mask ((uint32_t)0x00000038)
#define ACR_HLFCYA_Mask ((uint32_t)0xFFFFFFF7)
#define ACR_PRFTBE_Mask ((uint32_t)0xFFFFFFEF)

/* Flash Access Control Register bits */
#define ACR_PRFTBS_Mask ((uint32_t)0x00000020)

/* Flash Control Register bits */
#define CR_PG_Set ((uint32_t)0x00000001)
#define CR_PG_Reset ((uint32_t)0x00001FFE)
#define CR_PER_Set ((uint32_t)0x00000002)
#define CR_PER_Reset ((uint32_t)0x00001FFD)
#define CR_MER_Set ((uint32_t)0x00000004)
#define CR_MER_Reset ((uint32_t)0x00001FFB)
#define CR_OPTPG_Set ((uint32_t)0x00000010)
#define CR_OPTPG_Reset ((uint32_t)0x00001FEF)
#define CR_OPTER_Set ((uint32_t)0x00000020)
#define CR_OPTER_Reset ((uint32_t)0x00001FDF)
#define CR_STRT_Set ((uint32_t)0x00000040)
#define CR_LOCK_Set ((uint32_t)0x00000080)

/* FLASH Mask */
#define RDPRT_Mask ((uint32_t)0x00000002)
#define WRP0_Mask ((uint32_t)0x000000FF)
#define WRP1_Mask ((uint32_t)0x0000FF00)
#define WRP2_Mask ((uint32_t)0x00FF0000)
#define WRP3_Mask ((uint32_t)0xFF000000)
#define OB_USER_BFB2 ((uint16_t)0x0008)

/* FLASH Keys */
#define RDP_Key ((uint16_t)0x00A5)
#define FLASH_KEY1 ((uint32_t)0x45670123)
#define FLASH_KEY2 ((uint32_t)0xCDEF89AB)

/* FLASH BANK address */
#define FLASH_BANK1_END_ADDRESS ((uint32_t)0x807FFFF)

/* Delay definition */
#define EraseTimeout ((uint32_t)0x000B0000)
#define ProgramTimeout ((uint32_t)0x00002000)
/**
 * @}
 */

/** @defgroup FLASH_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup FLASH_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup FLASH_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup FLASH_Private_Functions
 * @{
 */

/**
@??

 ??????????? STM32F10x ????????????????
 ????? STM32F10x_XL ?????

 STM32F10x_XL ?????? 1 MB ?????????????????? (RWW) ???
    - bank1?????? 512 KB?256 ???? 2KB?
    - bank2??? 512 KB??? 256 ???? 2KB?
 ??? STM32F10x ?????????? 512 KB ??? bank?

 V3.3.0?????????????????
 STM32F10x_XL ?????????????????????????????
 ??? XL ???

 ????????????????????? STM32F10x ???

   ****************************************************** *
   * ???? STM32F10x ?????? *
   ****************************************************** *
   +-------------------------------------------------- -------------------------------------------------- -----------------------------------------------+
   |????|STM32F10x_XL|??STM32F10x|?? |
   | |?? |?? | |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_SetLatency |? |? |???? |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_HalfCycleAccessCmd |? |? |???? |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_PrefetchBufferCmd |? |? |???? |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_?? |? |? | - ?? STM32F10X_XL ????? Bank1 ? Bank2? |
   | | | | - ????????? Bank1 ?????? |
   | | | |? FLASH_UnlockBank1 ??? |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_Lock |? |? | - ?? STM32F10X_XL ????? Bank1 ? Bank2? |
   | | | | - ????????? Bank1 ?????? |
   | | | |? FLASH_LockBank1 ??? |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_ErasePage |? |? | - ?? STM32F10x_XL ????? Bank1 ? Bank2 ?????? |
   | | | | - ????????? Bank1 ???? |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_EraseAllPages |? |? | - ?? STM32F10x_XL ????? Bank1 ? Bank2 ?????? |
   | | | | - ????????? Bank1 ?????? |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_EraseOptionBytes |? |? |???? |
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_ProgramWord |? |? |????? 1MByte ?????????????|
   |------------------------------------------------- -------------------------------------------------- -------------------------------------------|
   |FLASH_ProgramHalfWord |? |? |????? 1MByte ?????????????|
   |------------------------------------------------- -------------------------------------------------- --


/**
   * @brief ????????
   * @note ???????? STM32F10x ???
   * @param FLASH_Latency??? FLASH ????
   * ????????????
   * @arg FLASH_Latency_0?FLASH ?????
   * @arg FLASH_Latency_1: FLASH ??????
   * @arg FLASH_Latency_2: FLASH ??????
   * @retval ?
   */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_LATENCY(FLASH_Latency));

  /* Read the ACR register */
  tmpreg = FLASH->ACR;

  /* Sets the Latency value */
  tmpreg &= ACR_LATENCY_Mask;
  tmpreg |= FLASH_Latency;

  /* Write the ACR register */
  FLASH->ACR = tmpreg;
}

/**
 * @brief ?????????????
 * @note ???????? STM32F10x ???
 * @param FLASH_HalfCycleAccess??? FLASH ????????
 * ????????????
 * @arg FLASH_HalfCycleAccess_Enable?FLASH ?????
 * @arg FLASH_HalfCycleAccess_Disable?FLASH ?????
 * @retval ?
 */
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess)
{
  /* Check the parameters */
  assert_param(IS_FLASH_HALFCYCLEACCESS_STATE(FLASH_HalfCycleAccess));

  /* Enable or disable the Half cycle access */
  FLASH->ACR &= ACR_HLFCYA_Mask;
  FLASH->ACR |= FLASH_HalfCycleAccess;
}

/**
 * @brief ???????????
 * @note ???????? STM32F10x ???
 * @param FLASH_PrefetchBuffer???????????
 * ????????????
 * @arg FLASH_PrefetchBuffer_Enable?FLASH ???????
 * @arg FLASH_PrefetchBuffer_Disable?FLASH ???????
 * @retval ?
 */
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer)
{
  /* Check the parameters */
  assert_param(IS_FLASH_PREFETCHBUFFER_STATE(FLASH_PrefetchBuffer));

  /* Enable or disable the Prefetch Buffer */
  FLASH->ACR &= ACR_PRFTBE_Mask;
  FLASH->ACR |= FLASH_PrefetchBuffer;
}

/**
 * @brief ????????????
 * @note ???????? STM32F10x ???
 * - ?? STM32F10X_XL ???????? Bank1 ? Bank2?
 * - ???????????? Bank1 ???????
 * ? FLASH_UnlockBank1 ??..
 * @param ?
 * @retval ?
 */
void FLASH_Unlock(void)
{
  /* Authorize the FPEC of Bank1 Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;

#ifdef STM32F10X_XL
  /* Authorize the FPEC of Bank2 Access */
  FLASH->KEYR2 = FLASH_KEY1;
  FLASH->KEYR2 = FLASH_KEY2;
#endif /* STM32F10X_XL */
}
/**
 * @brief ?? FLASH Bank1 ????????
 * @note ???????? STM32F10x ???
 * - ?? STM32F10X_XL ???????? Bank1?
 * - ????????????? Bank1???
 * ??? FLASH_Unlock ???
 * @param ?
 * @retval ?
 */
void FLASH_UnlockBank1(void)
{
  /* Authorize the FPEC of Bank1 Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
}

#ifdef STM32F10X_XL
/**
 * @brief ?? FLASH Bank2 ????????
 * @note ??????? STM32F10X_XL ?????
 * @param ?
 * @retval ?
 */
void FLASH_UnlockBank2(void)
{
  /* Authorize the FPEC of Bank2 Access */
  FLASH->KEYR2 = FLASH_KEY1;
  FLASH->KEYR2 = FLASH_KEY2;
}
#endif /* STM32F10X_XL */

/**
 * @brief ????????????
 * @note ???????? STM32F10x ???
 * - ?? STM32F10X_XL ???????? Bank1 ? Bank2?
 * - ???????????? Bank1??????
 * ? FLASH_LockBank1 ???
 * @param ?
 * @retval ?
 */
void FLASH_Lock(void)
{
  /* Set the Lock Bit to lock the FPEC and the CR of  Bank1 */
  FLASH->CR |= CR_LOCK_Set;

#ifdef STM32F10X_XL
  /* Set the Lock Bit to lock the FPEC and the CR of  Bank2 */
  FLASH->CR2 |= CR_LOCK_Set;
#endif /* STM32F10X_XL */
}

/**
 * @brief ?? FLASH Bank1 ????????
 * @note ???????? STM32F10x ???
 * - ?? STM32F10X_XL ???????? Bank1?
 * - ???????????? Bank1??????
 * ? FLASH_Lock ???
 * @param ?
 * @retval ?
 */
void FLASH_LockBank1(void)
{
  /* Set the Lock Bit to lock the FPEC and the CR of  Bank1 */
  FLASH->CR |= CR_LOCK_Set;
}

#ifdef STM32F10X_XL
/**
 * @brief ?? FLASH Bank2 ????????
 * @note ??????? STM32F10X_XL ?????
 * @param ?
 * @retval ?
 */
void FLASH_LockBank2(void)
{
  /* Set the Lock Bit to lock the FPEC and the CR of  Bank2 */
  FLASH->CR2 |= CR_LOCK_Set;
}
#endif /* STM32F10X_XL */

/**
 * @brief ????? FLASH ??
 * @note ???????? STM32F10x ???
 * @param Page_Address??????????
 * @retval FLASH??????????FLASH_BUSY?FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Page_Address));

#ifdef STM32F10X_XL
  if (Page_Address < FLASH_BANK1_END_ADDRESS)
  {
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank1Operation(EraseTimeout);
    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to erase the page */
      FLASH->CR |= CR_PER_Set;
      FLASH->AR = Page_Address;
      FLASH->CR |= CR_STRT_Set;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastBank1Operation(EraseTimeout);

      /* Disable the PER Bit */
      FLASH->CR &= CR_PER_Reset;
    }
  }
  else
  {
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank2Operation(EraseTimeout);
    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to erase the page */
      FLASH->CR2 |= CR_PER_Set;
      FLASH->AR2 = Page_Address;
      FLASH->CR2 |= CR_STRT_Set;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastBank2Operation(EraseTimeout);

      /* Disable the PER Bit */
      FLASH->CR2 &= CR_PER_Reset;
    }
  }
#else
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase the page */
    FLASH->CR |= CR_PER_Set;
    FLASH->AR = Page_Address;
    FLASH->CR |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    /* Disable the PER Bit */
    FLASH->CR &= CR_PER_Reset;
  }
#endif /* STM32F10X_XL */

  /* Return the Erase Status */
  return status;
}

/**
 * @brief ???? FLASH ???
 * @note ???????? STM32F10x ???
 * @param ?
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_COMPLETE;

#ifdef STM32F10X_XL
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastBank1Operation(EraseTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
    FLASH->CR |= CR_MER_Set;
    FLASH->CR |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank1Operation(EraseTimeout);

    /* Disable the MER Bit */
    FLASH->CR &= CR_MER_Reset;
  }
  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
    FLASH->CR2 |= CR_MER_Set;
    FLASH->CR2 |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank2Operation(EraseTimeout);

    /* Disable the MER Bit */
    FLASH->CR2 &= CR_MER_Reset;
  }
#else
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
    FLASH->CR |= CR_MER_Set;
    FLASH->CR |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    /* Disable the MER Bit */
    FLASH->CR &= CR_MER_Reset;
  }
#endif /* STM32F10X_XL */

  /* Return the Erase Status */
  return status;
}

/**
 * @brief ???? Bank1 FLASH ???
 * @note ???????? STM32F10x ???
 * - ?? STM32F10X_XL ?????????? Bank1 ??
 * - ??????????????? Bank1 ????????
 * ? FLASH_EraseAllPages ???
 * @param ?
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_EraseAllBank1Pages(void)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastBank1Operation(EraseTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
    FLASH->CR |= CR_MER_Set;
    FLASH->CR |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank1Operation(EraseTimeout);

    /* Disable the MER Bit */
    FLASH->CR &= CR_MER_Reset;
  }
  /* Return the Erase Status */
  return status;
}

#ifdef STM32F10X_XL
/**
 * @brief  Erases all Bank2 FLASH pages.
 * @note   This function can be used only for STM32F10x_XL density devices.
 * @param  None
 * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_EraseAllBank2Pages(void)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastBank2Operation(EraseTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
    FLASH->CR2 |= CR_MER_Set;
    FLASH->CR2 |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank2Operation(EraseTimeout);

    /* Disable the MER Bit */
    FLASH->CR2 &= CR_MER_Reset;
  }
  /* Return the Erase Status */
  return status;
}
#endif /* STM32F10X_XL */

/**
 * @brief ?? FLASH ?????
 * @note ????????? (RDP) ??????????
 * @note ???????? STM32F10x ???
 * @param ?
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_EraseOptionBytes(void)
{
  uint16_t rdptmp = RDP_Key;

  FLASH_Status status = FLASH_COMPLETE;

  /* Get the actual read protection Option Byte value */
  if (FLASH_GetReadOutProtectionStatus() != RESET)
  {
    rdptmp = 0x00;
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if (status == FLASH_COMPLETE)
  {
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;

    /* if the previous operation is completed, proceed to erase the option bytes */
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if (status == FLASH_COMPLETE)
    {
      /* if the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= CR_OPTER_Reset;

      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= CR_OPTPG_Set;
      /* Restore the last read protection Option Byte value */
      OB->RDP = (uint16_t)rdptmp;
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);

      if (status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
  }
  /* Return the erase status */
  return status;
}

/**
 * @brief ???????????
 * @note ???????? STM32F10x ???
 * @param Address??????????
 * @param Data??????????
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

#ifdef STM32F10X_XL
  if (Address < FLASH_BANK1_END_ADDRESS - 2)
  {
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank1Operation(ProgramTimeout);
    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new first
        half word */
      FLASH->CR |= CR_PG_Set;

      *(__IO uint16_t *)Address = (uint16_t)Data;
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);

      if (status == FLASH_COMPLETE)
      {
        /* if the previous operation is completed, proceed to program the new second
        half word */
        tmp = Address + 2;

        *(__IO uint16_t *)tmp = Data >> 16;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        /* Disable the PG Bit */
        FLASH->CR &= CR_PG_Reset;
      }
      else
      {
        /* Disable the PG Bit */
        FLASH->CR &= CR_PG_Reset;
      }
    }
  }
  else if (Address == (FLASH_BANK1_END_ADDRESS - 1))
  {
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank1Operation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new first
        half word */
      FLASH->CR |= CR_PG_Set;

      *(__IO uint16_t *)Address = (uint16_t)Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastBank1Operation(ProgramTimeout);

      /* Disable the PG Bit */
      FLASH->CR &= CR_PG_Reset;
    }
    else
    {
      /* Disable the PG Bit */
      FLASH->CR &= CR_PG_Reset;
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank2Operation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new second
      half word */
      FLASH->CR2 |= CR_PG_Set;
      tmp = Address + 2;

      *(__IO uint16_t *)tmp = Data >> 16;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastBank2Operation(ProgramTimeout);

      /* Disable the PG Bit */
      FLASH->CR2 &= CR_PG_Reset;
    }
    else
    {
      /* Disable the PG Bit */
      FLASH->CR2 &= CR_PG_Reset;
    }
  }
  else
  {
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastBank2Operation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new first
        half word */
      FLASH->CR2 |= CR_PG_Set;

      *(__IO uint16_t *)Address = (uint16_t)Data;
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastBank2Operation(ProgramTimeout);

      if (status == FLASH_COMPLETE)
      {
        /* if the previous operation is completed, proceed to program the new second
        half word */
        tmp = Address + 2;

        *(__IO uint16_t *)tmp = Data >> 16;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastBank2Operation(ProgramTimeout);

        /* Disable the PG Bit */
        FLASH->CR2 &= CR_PG_Reset;
      }
      else
      {
        /* Disable the PG Bit */
        FLASH->CR2 &= CR_PG_Reset;
      }
    }
  }
#else
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new first
    half word */
    FLASH->CR |= CR_PG_Set;

    *(__IO uint16_t *)Address = (uint16_t)Data;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new second
      half word */
      tmp = Address + 2;

      *(__IO uint16_t *)tmp = Data >> 16;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);

      /* Disable the PG Bit */
      FLASH->CR &= CR_PG_Reset;
    }
    else
    {
      /* Disable the PG Bit */
      FLASH->CR &= CR_PG_Reset;
    }
  }
#endif /* STM32F10X_XL */

  /* Return the Program Status */
  return status;
}

/**
 * @brief ??????????
 * @note ???????? STM32F10x ???
 * @param Address??????????
 * @param Data??????????
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

#ifdef STM32F10X_XL
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if (Address < FLASH_BANK1_END_ADDRESS)
  {
    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new data */
      FLASH->CR |= CR_PG_Set;

      *(__IO uint16_t *)Address = Data;
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastBank1Operation(ProgramTimeout);

      /* Disable the PG Bit */
      FLASH->CR &= CR_PG_Reset;
    }
  }
  else
  {
    if (status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new data */
      FLASH->CR2 |= CR_PG_Set;

      *(__IO uint16_t *)Address = Data;
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastBank2Operation(ProgramTimeout);

      /* Disable the PG Bit */
      FLASH->CR2 &= CR_PG_Reset;
    }
  }
#else
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new data */
    FLASH->CR |= CR_PG_Set;

    *(__IO uint16_t *)Address = Data;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    /* Disable the PG Bit */
    FLASH->CR &= CR_PG_Reset;
  }
#endif /* STM32F10X_XL */

  /* Return the Program Status */
  return status;
}

/**
 * @brief ?????????????????
 * @note ???????? STM32F10x ???
 * @param Address??????????
 * ?????? 0x1FFFF804 ? 0x1FFFF806?
 * @param Data??????????
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  assert_param(IS_OB_DATA_ADDRESS(Address));
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* Enables the Option Bytes Programming operation */
    FLASH->CR |= CR_OPTPG_Set;
    *(__IO uint16_t *)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if (status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }
  /* Return the Option Byte Data Program Status */
  return status;
}

/**
 * @brief Write ???????
 * @note ???????? STM32F10x ???
 * @param FLASH_Pages?????????????
 * ???????
 * @arg For @b STM32_Low-density_devices?FLASH_WRProt_Pages0to3 ? FLASH_WRProt_Pages28to31 ????
 * @arg For @b STM32_Medium-density_devices?FLASH_WRProt_Pages0to3 ????
 * ? FLASH_WRProt_Pages124 ? 127
 * @arg For @b STM32_High-density_devices?FLASH_WRProt_Pages0to1 ?
 * FLASH_WRProt_Pages60to61 ? FLASH_WRProt_Pages62to255
 * @arg For @b STM32_Connectivity_line_devices?FLASH_WRProt_Pages0to1 ?
 * FLASH_WRProt_Pages60to61 ? FLASH_WRProt_Pages62to127
 * @arg For @b STM32_XL-density_devices?FLASH_WRProt_Pages0to1 ?
 * FLASH_WRProt_Pages60to61 ? FLASH_WRProt_Pages62to511
 * @arg FLASH_WRProt_AllPages
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages)
{
  uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;

  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_WRPROT_PAGE(FLASH_Pages));

  FLASH_Pages = (uint32_t)(~FLASH_Pages);
  WRP0_Data = (uint16_t)(FLASH_Pages & WRP0_Mask);
  WRP1_Data = (uint16_t)((FLASH_Pages & WRP1_Mask) >> 8);
  WRP2_Data = (uint16_t)((FLASH_Pages & WRP2_Mask) >> 16);
  WRP3_Data = (uint16_t)((FLASH_Pages & WRP3_Mask) >> 24);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* Authorizes the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTPG_Set;
    if (WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if ((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if ((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 = WRP2_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }

    if ((status == FLASH_COMPLETE) && (WRP3_Data != 0xFF))
    {
      OB->WRP3 = WRP3_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }

    if (status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }
  /* Return the write protection operation Status */
  return status;
}

/**
 * @brief ??????????
 * @note ????????????????????
 * ?????????????????????????????
 * @note ???????? STM32F10x ???
 * @param Newstate??????????
 * ???????ENABLE ? DISABLE?
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if (status == FLASH_COMPLETE)
  {
    /* Authorizes the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if (status == FLASH_COMPLETE)
    {
      /* if the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= CR_OPTER_Reset;
      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= CR_OPTPG_Set;
      if (NewState != DISABLE)
      {
        OB->RDP = 0x00;
      }
      else
      {
        OB->RDP = RDP_Key;
      }
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(EraseTimeout);

      if (status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the OPTER Bit */
        FLASH->CR &= CR_OPTER_Reset;
      }
    }
  }
  /* Return the protection operation Status */
  return status;
}

/**
 * @brief ? FLASH ???????????IWDG_SW / RST_STOP / RST_STDBY?
 * @note ???????? STM32F10x ???
 * @param OB_IWDG: ?? IWDG ??
 * ????????????
 * @arg OB_IWDG_SW????? IWDG
 * @arg OB_IWDG_HW????? IWDG
 * @param OB_STOP??? STOP ?????????
 * ????????????
 * @arg OB_STOP_NoRST: ?? STOP ??????
 * @arg OB_STOP_RST: ?? STOP ?????
 * @param OB_STDBY??????????????
 * ????????????
 * @arg OB_STDBY_NoRST: ?? STANDBY ??????
 * @arg OB_STDBY_RST: ?? STANDBY ?????
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= CR_OPTPG_Set;

    OB->USER = OB_IWDG | (uint16_t)(OB_STOP | (uint16_t)(OB_STDBY | ((uint16_t)0xF8)));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if (status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

#ifdef STM32F10X_XL
/**
 * @brief ???? Bank1 ? Bank2 ???
 * @note ??????? STM32F10x_XL ?????
 * @param FLASH_BOOT????????? FLASH Bank?
 * ????????????
 * @arg FLASH_BOOT_Bank1???????????????????????
 * ????????????? Bank1???????
 * @arg FLASH_BOOT_Bank2???????????????????????
 * ????????????? Bank2 ? Bank1 ???
 * ???????????????????
 * ?????Bank2???? Bank1?
 * ?????????????
 * ????????????????
 * ?????????
 * ?????????? www.st.com ? AN2606?
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_BootConfig(uint16_t FLASH_BOOT)
{
  FLASH_Status status = FLASH_COMPLETE;
  assert_param(IS_FLASH_BOOT(FLASH_BOOT));
  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if (status == FLASH_COMPLETE)
  {
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= CR_OPTPG_Set;

    if (FLASH_BOOT == FLASH_BOOT_Bank1)
    {
      OB->USER |= OB_USER_BFB2;
    }
    else
    {
      OB->USER &= (uint16_t)(~(uint16_t)(OB_USER_BFB2));
    }
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if (status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}
#endif /* STM32F10X_XL */

/**
 * @brief ?? FLASH ????????
 * @note ???????? STM32F10x ???
 * @param ?
 * @retval FLASH ????????IWDG_SW(Bit0), RST_STOP(Bit1)
 * ? RST_STDBY(Bit2)?
 */
uint32_t FLASH_GetUserOptionByte(void)
{
  /* Return the User Option Byte */
  return (uint32_t)(FLASH->OBR >> 2);
}

/**
 * @brief ????????????????
 * @note ???????? STM32F10x ???
 * @param ?
 * @retval FLASH ???????????
 */
uint32_t FLASH_GetWriteProtectionOptionByte(void)
{
  /* Return the Flash write protection Register value */
  return (uint32_t)(FLASH->WRPR);
}

/**
 * @brief ??????? FLASH ???????
 * @note ???????? STM32F10x ???
 * @param ?
 * @retval FLASH ???????SET ? RESET?
 */
FlagStatus FLASH_GetReadOutProtectionStatus(void)
{
  FlagStatus readoutstatus = RESET;
  if ((FLASH->OBR & RDPRT_Mask) != (uint32_t)RESET)
  {
    readoutstatus = SET;
  }
  else
  {
    readoutstatus = RESET;
  }
  return readoutstatus;
}

/**
 * @brief ??????? FLASH Prefetch Buffer ???
 * @note ???????? STM32F10x ???
 * @param ?
 * @retval FLASH ????????SET ? RESET??
 */
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((FLASH->ACR & ACR_PRFTBS_Mask) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
  return bitstatus;
}

/**
 * @brief ???????? FLASH ???
 * @note ???????? STM32F10x ???
 * - ?? STM32F10X_XL ??????????? FLASH ??? Bank1 ? Bank2?
 * - ????????????? Bank1 ??? FLASH ???
 * @param FLASH_IT?????????? FLASH ????
 * ???????????????
 * @arg FLASH_IT_ERROR: FLASH ????
 * @arg FLASH_IT_EOP: FLASH ??????
 * @param NewState??? Flash ???????
 * ???????ENABLE ? DISABLE?
 * @retval ?
 */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
#ifdef STM32F10X_XL
  /* Check the parameters */
  assert_param(IS_FLASH_IT(FLASH_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if ((FLASH_IT & 0x80000000) != 0x0)
  {
    if (NewState != DISABLE)
    {
      /* Enable the interrupt sources */
      FLASH->CR2 |= (FLASH_IT & 0x7FFFFFFF);
    }
    else
    {
      /* Disable the interrupt sources */
      FLASH->CR2 &= ~(uint32_t)(FLASH_IT & 0x7FFFFFFF);
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Enable the interrupt sources */
      FLASH->CR |= FLASH_IT;
    }
    else
    {
      /* Disable the interrupt sources */
      FLASH->CR &= ~(uint32_t)FLASH_IT;
    }
  }
#else
  /* Check the parameters */
  assert_param(IS_FLASH_IT(FLASH_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->CR &= ~(uint32_t)FLASH_IT;
  }
#endif /* STM32F10X_XL */
}

/**
 * @brief ?????????? FLASH ???
 * @note ???????? STM32F10x ???
 * - ?? STM32F10X_XL ???????????
 * Bank1 ? Bank2 ???????
 * - ????????????? Bank1 ????
 * ?????
 * @param FLASH_FLAG??????? FLASH ???
 * ????????????
 * @arg FLASH_FLAG_BSY: ?????
 * @arg FLASH_FLAG_PGERR?FLASH ??????
 * @arg FLASH_FLAG_WRPRTERR: FLASH ???????
 * @arg FLASH_FLAG_EOP?FLASH ??????
 * @arg FLASH_FLAG_OPTERR?FLASH ????????
 * @retval FLASH_FLAG ?????SET ? RESET??
 */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;

#ifdef STM32F10X_XL
  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));
  if (FLASH_FLAG == FLASH_FLAG_OPTERR)
  {
    if ((FLASH->OBR & FLASH_FLAG_OPTERR) != (uint32_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if ((FLASH_FLAG & 0x80000000) != 0x0)
    {
      if ((FLASH->SR2 & FLASH_FLAG) != (uint32_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
    }
    else
    {
      if ((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
    }
  }
#else
  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));
  if (FLASH_FLAG == FLASH_FLAG_OPTERR)
  {
    if ((FLASH->OBR & FLASH_FLAG_OPTERR) != (uint32_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if ((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
#endif /* STM32F10X_XL */

  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus;
}

/**
 * @brief ?? FLASH ??????
 * @note ???????? STM32F10x ???
 * - ?? STM32F10X_XL ???????? Bank1 ? Bank2 ?????
 * - ?????????? Bank1 ??????
 * @param FLASH_FLAG??????? FLASH ???
 * ???????????????
 * @arg FLASH_FLAG_PGERR?FLASH ??????
 * @arg FLASH_FLAG_WRPRTERR: FLASH ???????
 * @arg FLASH_FLAG_EOP?FLASH ??????
 * @retval ?
 */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
#ifdef STM32F10X_XL
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

  if ((FLASH_FLAG & 0x80000000) != 0x0)
  {
    /* Clear the flags */
    FLASH->SR2 = FLASH_FLAG;
  }
  else
  {
    /* Clear the flags */
    FLASH->SR = FLASH_FLAG;
  }

#else
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

  /* Clear the flags */
  FLASH->SR = FLASH_FLAG;
#endif /* STM32F10X_XL */
}

/**
 * @brief ???????
 * @note ???????? STM32F10x ?????
 * ? FLASH_GetBank1Status ???
 * @param ?
 * @retval FLASH??????????FLASH_BUSY?FLASH_ERROR_PG?
 * FLASH_ERROR_WRP ? FLASH_COMPLETE
 */
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  if ((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
  {
    flashstatus = FLASH_BUSY;
  }
  else
  {
    if ((FLASH->SR & FLASH_FLAG_PGERR) != 0)
    {
      flashstatus = FLASH_ERROR_PG;
    }
    else
    {
      if ((FLASH->SR & FLASH_FLAG_WRPRTERR) != 0)
      {
        flashstatus = FLASH_ERROR_WRP;
      }
      else
      {
        flashstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the Flash Status */
  return flashstatus;
}

/**
 * @brief ?? FLASH Bank1 ???
 * @note ???????? STM32F10x ?????
 * ? FLASH_GetStatus ???
 * @param ?
 * @retval FLASH??????????FLASH_BUSY?FLASH_ERROR_PG?
 * FLASH_ERROR_WRP ? FLASH_COMPLETE
 */
FLASH_Status FLASH_GetBank1Status(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  if ((FLASH->SR & FLASH_FLAG_BANK1_BSY) == FLASH_FLAG_BSY)
  {
    flashstatus = FLASH_BUSY;
  }
  else
  {
    if ((FLASH->SR & FLASH_FLAG_BANK1_PGERR) != 0)
    {
      flashstatus = FLASH_ERROR_PG;
    }
    else
    {
      if ((FLASH->SR & FLASH_FLAG_BANK1_WRPRTERR) != 0)
      {
        flashstatus = FLASH_ERROR_WRP;
      }
      else
      {
        flashstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the Flash Status */
  return flashstatus;
}

#ifdef STM32F10X_XL
/**
 * @brief  Returns the FLASH Bank2 Status.
 * @note   This function can be used for STM32F10x_XL density devices.
 * @param  None
 * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *        FLASH_ERROR_WRP or FLASH_COMPLETE
 */
FLASH_Status FLASH_GetBank2Status(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  if ((FLASH->SR2 & (FLASH_FLAG_BANK2_BSY & 0x7FFFFFFF)) == (FLASH_FLAG_BANK2_BSY & 0x7FFFFFFF))
  {
    flashstatus = FLASH_BUSY;
  }
  else
  {
    if ((FLASH->SR2 & (FLASH_FLAG_BANK2_PGERR & 0x7FFFFFFF)) != 0)
    {
      flashstatus = FLASH_ERROR_PG;
    }
    else
    {
      if ((FLASH->SR2 & (FLASH_FLAG_BANK2_WRPRTERR & 0x7FFFFFFF)) != 0)
      {
        flashstatus = FLASH_ERROR_WRP;
      }
      else
      {
        flashstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the Flash Status */
  return flashstatus;
}
#endif /* STM32F10X_XL */
/**
 * @brief ?? Flash ????? TIMEOUT ???
 * @note ???????? STM32F10x ???
 * ??? FLASH_WaitForLastBank1Operation?
 * - ?? STM32F10X_XL ???????? Bank1 Flash ??
 * ????????
 * - ????????????? Flash ????
 * ? TIMEOUT ???
 * @param Timeout: FLASH ????
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check for the Flash Status */
  status = FLASH_GetBank1Status();
  /* Wait for a Flash operation to complete or a TIMEOUT to occur */
  while ((status == FLASH_BUSY) && (Timeout != 0x00))
  {
    status = FLASH_GetBank1Status();
    Timeout--;
  }
  if (Timeout == 0x00)
  {
    status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
}

/**
 * @brief ?? Bank1 ?? Flash ??????? TIMEOUT?
 * @note ???????? STM32F10x ???
 * ??? FLASH_WaitForLastOperation?
 * @param Timeout: FLASH ????
 * @retval FLASH??????????FLASH_ERROR_PG?
 * FLASH_ERROR_WRP?FLASH_COMPLETE ? FLASH_TIMEOUT?
 */
FLASH_Status FLASH_WaitForLastBank1Operation(uint32_t Timeout)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check for the Flash Status */
  status = FLASH_GetBank1Status();
  /* Wait for a Flash operation to complete or a TIMEOUT to occur */
  while ((status == FLASH_FLAG_BANK1_BSY) && (Timeout != 0x00))
  {
    status = FLASH_GetBank1Status();
    Timeout--;
  }
  if (Timeout == 0x00)
  {
    status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
}

#ifdef STM32F10X_XL
/**
 * @brief  Waits for a Flash operation on Bank2 to complete or a TIMEOUT to occur.
 * @note   This function can be used only for STM32F10x_XL density devices.
 * @param  Timeout: FLASH programming Timeout
 * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_WaitForLastBank2Operation(uint32_t Timeout)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check for the Flash Status */
  status = FLASH_GetBank2Status();
  /* Wait for a Flash operation to complete or a TIMEOUT to occur */
  while ((status == (FLASH_FLAG_BANK2_BSY & 0x7FFFFFFF)) && (Timeout != 0x00))
  {
    status = FLASH_GetBank2Status();
    Timeout--;
  }
  if (Timeout == 0x00)
  {
    status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
}
#endif /* STM32F10X_XL */

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
