/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_crc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup CRC
 * @brief CRC driver modules
 * @{
 */

/** @defgroup CRC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup CRC_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @defgroup CRC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup CRC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup CRC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup CRC_Private_Functions
 * @{
 */

/**
 * @brief 重置 CRC 数据寄存器 (DR)。
 * @param 无
 * @retval 无
 */
void CRC_ResetDR(void)
{
  /* Reset CRC generator */
  CRC->CR = CRC_CR_RESET;
}

/**
 * @brief 计算给定数据字（32 位）的 32 位 CRC。
 * @param Data：数据字（32 位）来计算它的 CRC
 * @retval 32 位 CRC
 */
uint32_t CRC_CalcCRC(uint32_t Data)
{
  CRC->DR = Data;

  return (CRC->DR);
}

/**
 * @brief 计算给定数据字（32 位）缓冲区的 32 位 CRC。
 * @param pBuffer：指向包含要计算的数据的缓冲区的指针
 * @param BufferLength：要计算的缓冲区长度
 * @retval 32 位 CRC
 */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;

  for (index = 0; index < BufferLength; index++)
  {
    CRC->DR = pBuffer[index];
  }
  return (CRC->DR);
}

/**
 * @brief 返回当前的 CRC 值。
 * @param 无
 * @retval 32 位 CRC
 */
uint32_t CRC_GetCRC(void)
{
  return (CRC->DR);
}

/**
 * @brief 在独立数据（ID）寄存器中存储一个 8 位数据。
 * @param IDValue：要存储在 ID 寄存器中的 8 位值
 * @retval 无
 */
void CRC_SetIDRegister(uint8_t IDValue)
{
  CRC->IDR = IDValue;
}

/**
 * @brief 返回存储在独立数据（ID）寄存器中的 8 位数据
 * @param 无
 * @retval ID 寄存器的 8 位值
 */
uint8_t CRC_GetIDRegister(void)
{
  return (CRC->IDR);
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
