/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
 * @{
 */

/** @defgroup TIM
 * @brief TIM driver modules
 * @{
 */

/** @defgroup TIM_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup TIM_Private_Defines
 * @{
 */

/* ---------------------- TIM registers bit mask ------------------------ */
#define SMCR_ETR_Mask ((uint16_t)0x00FF)
#define CCMR_Offset ((uint16_t)0x0018)
#define CCER_CCE_Set ((uint16_t)0x0001)
#define CCER_CCNE_Set ((uint16_t)0x0004)

/**
 * @}
 */

/** @defgroup TIM_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup TIM_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup TIM_Private_FunctionPrototypes
 * @{
 */

static void TI1_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI2_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI3_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI4_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
/**
 * @}
 */

/** @defgroup TIM_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup TIM_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup TIM_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup TIM_Private_Functions
 * @{
 */

/**
 * @brief 将 TIMx 外设寄存器取消初始化为其默认复位值。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @retval 无
 */
void TIM_DeInit(TIM_TypeDef *TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  if (TIMx == TIM1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);
  }
  else if (TIMx == TIM2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
  }
  else if (TIMx == TIM3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
  }
  else if (TIMx == TIM4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
  }
  else if (TIMx == TIM5)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, DISABLE);
  }
  else if (TIMx == TIM6)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
  }
  else if (TIMx == TIM7)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
  }
  else if (TIMx == TIM8)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, DISABLE);
  }
  else if (TIMx == TIM9)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, DISABLE);
  }
  else if (TIMx == TIM10)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, DISABLE);
  }
  else if (TIMx == TIM11)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, DISABLE);
  }
  else if (TIMx == TIM12)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, DISABLE);
  }
  else if (TIMx == TIM13)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, DISABLE);
  }
  else if (TIMx == TIM14)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, DISABLE);
  }
  else if (TIMx == TIM15)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, DISABLE);
  }
  else if (TIMx == TIM16)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, DISABLE);
  }
  else
  {
    if (TIMx == TIM17)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, DISABLE);
    }
  }
}

/**
 * @brief 根据以下内容初始化 TIMx 时基单元外设
 * TIM_TimeBaseInitStruct 中的指定参数。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param TIM_TimeBaseInitStruct：指向 TIM_TimeBaseInitTypeDef 的指针
 * 包含配置信息的结构
 * 指定的 TIM 外设。
 * @retval 无
 */
void TIM_TimeBaseInit(TIM_TypeDef *TIMx, TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct)
{
  uint16_t tmpcr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
  assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));

  tmpcr1 = TIMx->CR1;

  if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) ||
      (TIMx == TIM4) || (TIMx == TIM5))
  {
    /* Select the Counter Mode */
    tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_CR1_DIR | TIM_CR1_CMS)));
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_CounterMode;
  }

  if ((TIMx != TIM6) && (TIMx != TIM7))
  {
    /* Set the clock division */
    tmpcr1 &= (uint16_t)(~((uint16_t)TIM_CR1_CKD));
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision;
  }

  TIMx->CR1 = tmpcr1;

  /* Set the Autoreload value */
  TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period;

  /* Set the Prescaler value */
  TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;

  if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM15) || (TIMx == TIM16) || (TIMx == TIM17))
  {
    /* Set the Repetition Counter value */
    TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
  }

  /* Generate an update event to reload the Prescaler and the Repetition counter
     values immediately */
  TIMx->EGR = TIM_PSCReloadMode_Immediate;
}

/**
 * @brief 根据指定初始化 TIMx Channel1
 * TIM_OCInitStruct 中的参数。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_OCInitStruct: 指向 TIM_OCInitTypeDef 结构的指针
 * 包含指定 TIM 外设的配置信息。
 * @retval 无
 */
void TIM_OC1Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
  /* Disable the Channel 1: Reset the CC1E Bit */
  TIMx->CCER &= (uint16_t)(~(uint16_t)TIM_CCER_CC1E);
  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;
  /* Get the TIMx CR2 register value */
  tmpcr2 = TIMx->CR2;

  /* Get the TIMx CCMR1 register value */
  tmpccmrx = TIMx->CCMR1;

  /* Reset the Output Compare Mode Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR1_OC1M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR1_CC1S));

  /* Select the Output Compare Mode */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC1P));
  /* Set the Output Compare Polarity */
  tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;

  /* Set the Output State */
  tmpccer |= TIM_OCInitStruct->TIM_OutputState;

  if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM15) ||
      (TIMx == TIM16) || (TIMx == TIM17))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC1NP));
    /* Set the Output N Polarity */
    tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;

    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC1NE));
    /* Set the Output N State */
    tmpccer |= TIM_OCInitStruct->TIM_OutputNState;

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS1));
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS1N));

    /* Set the Output Idle state */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
    /* Set the Output N Idle state */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;

  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;

  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 根据指定初始化 TIMx Channel2
 * TIM_OCInitStruct 中的参数。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以供选择
 * TIM 外围设备。
 * @param TIM_OCInitStruct: 指向 TIM_OCInitTypeDef 结构的指针
 * 包含指定 TIM 外设的配置信息。
 * @retval 无
 */
void TIM_OC2Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CCER_CC2E));

  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;
  /* Get the TIMx CR2 register value */
  tmpcr2 = TIMx->CR2;

  /* Get the TIMx CCMR1 register value */
  tmpccmrx = TIMx->CCMR1;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR1_OC2M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR1_CC2S));

  /* Select the Output Compare Mode */
  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC2P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 4);

  if ((TIMx == TIM1) || (TIMx == TIM8))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC2NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 4);

    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC2NE));
    /* Set the Output N State */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 4);

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS2));
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS2N));

    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 2);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;

  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;

  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 根据指定初始化 TIMx Channel3
 * TIM_OCInitStruct 中的参数。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCInitStruct: 指向 TIM_OCInitTypeDef 结构的指针
 * 包含指定 TIM 外设的配置信息。
 * @retval 无
 */
void TIM_OC3Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CCER_CC3E));

  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;
  /* Get the TIMx CR2 register value */
  tmpcr2 = TIMx->CR2;

  /* Get the TIMx CCMR2 register value */
  tmpccmrx = TIMx->CCMR2;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR2_OC3M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR2_CC3S));
  /* Select the Output Compare Mode */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC3P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 8);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 8);

  if ((TIMx == TIM1) || (TIMx == TIM8))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC3NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 8);
    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC3NE));

    /* Set the Output N State */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 8);
    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS3));
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS3N));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 4);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;

  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;

  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 根据指定初始化 TIMx Channel4
 * TIM_OCInitStruct 中的参数。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCInitStruct: 指向 TIM_OCInitTypeDef 结构的指针
 * 包含指定 TIM 外设的配置信息。
 * @retval 无
 */
void TIM_OC4Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
  /* Disable the Channel 2: Reset the CC4E Bit */
  TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CCER_CC4E));

  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;
  /* Get the TIMx CR2 register value */
  tmpcr2 = TIMx->CR2;

  /* Get the TIMx CCMR2 register value */
  tmpccmrx = TIMx->CCMR2;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR2_OC4M));
  tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CCMR2_CC4S));

  /* Select the Output Compare Mode */
  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TIM_CCER_CC4P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 12);

  if ((TIMx == TIM1) || (TIMx == TIM8))
  {
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    /* Reset the Output Compare IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TIM_CR2_OIS4));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;

  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;

  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 根据指定初始化 TIM 外设
 * TIM_ICInitStruct 中的参数。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_ICInitStruct：指向 TIM_ICInitTypeDef 结构的指针
 * 包含指定 TIM 外设的配置信息。
 * @retval 无
 */
void TIM_ICInit(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_CHANNEL(TIM_ICInitStruct->TIM_Channel));
  assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
  assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));

  if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) ||
      (TIMx == TIM4) || (TIMx == TIM5))
  {
    assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));
  }
  else
  {
    assert_param(IS_TIM_IC_POLARITY_LITE(TIM_ICInitStruct->TIM_ICPolarity));
  }
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    assert_param(IS_TIM_LIST8_PERIPH(TIMx));
    /* TI1 Configuration */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
  {
    assert_param(IS_TIM_LIST6_PERIPH(TIMx));
    /* TI2 Configuration */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
  {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    /* TI3 Configuration */
    TI3_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    /* TI4 Configuration */
    TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/**
 * @brief 根据指定配置 TIM 外设
 * TIM_ICInitStruct 中的参数用于测量外部 PWM 信号。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_ICInitStruct：指向 TIM_ICInitTypeDef 结构的指针
 * 包含指定 TIM 外设的配置信息。
 * @retval 无
 */
void TIM_PWMIConfig(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct)
{
  uint16_t icoppositepolarity = TIM_ICPolarity_Rising;
  uint16_t icoppositeselection = TIM_ICSelection_DirectTI;
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  /* Select the Opposite Input Polarity */
  if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
  {
    icoppositepolarity = TIM_ICPolarity_Falling;
  }
  else
  {
    icoppositepolarity = TIM_ICPolarity_Rising;
  }
  /* Select the Opposite Input */
  if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
  {
    icoppositeselection = TIM_ICSelection_IndirectTI;
  }
  else
  {
    icoppositeselection = TIM_ICSelection_DirectTI;
  }
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    /* TI2 Configuration */
    TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  {
    /* TI2 Configuration */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    /* TI1 Configuration */
    TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/**
 * @brief 配置：中断功能、死区时间、锁定级别、OSSI、
 * OSSR 状态和 AOE（自动输出使能）。
 * @param TIMx: 其中 x 可以是 1 或 8 来选择 TIM
 * @param TIM_BDTRInitStruct：指向 TIM_BDTRInitTypeDef 结构的指针
 * 包含 TIM 外设的 BDTR 寄存器配置信息。
 * @retval 无
 */
void TIM_BDTRConfig(TIM_TypeDef *TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
  assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
  assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
  assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
  assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
  assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));
  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSR State,
     the OSSI State, the dead time value and the Automatic Output Enable Bit */
  TIMx->BDTR = (uint32_t)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
               TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
               TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
               TIM_BDTRInitStruct->TIM_AutomaticOutput;
}

/**
 * @brief 用默认值填充每个 TIM_TimeBaseInitStruct 成员。
 * @param TIM_TimeBaseInitStruct : 指向 TIM_TimeBaseInitTypeDef 的指针
 * 将被初始化的结构。
 * @retval 无
 */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct)
{
  /* Set the default configuration */
  TIM_TimeBaseInitStruct->TIM_Period = 0xFFFF;
  TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
  TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

/**
 * @brief 用默认值填充每个 TIM_OCInitStruct 成员。
 * @param TIM_OCInitStruct : 指向 TIM_OCInitTypeDef 结构的指针，它将
 * 被初始化。
 * @retval 无
 */
void TIM_OCStructInit(TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  /* Set the default configuration */
  TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct->TIM_Pulse = 0x0000;
  TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/**
 * @brief 用默认值填充每个 TIM_ICInitStruct 成员。
 * @param TIM_ICInitStruct：指向 TIM_ICInitTypeDef 结构的指针，该结构将
 * 被初始化。
 * @retval 无
 */
void TIM_ICStructInit(TIM_ICInitTypeDef *TIM_ICInitStruct)
{
  /* Set the default configuration */
  TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
  TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

/**
 * @brief 用默认值填充每个 TIM_BDTRInitStruct 成员。
 * @param TIM_BDTRInitStruct：指向 TIM_BDTRInitTypeDef 结构的指针
 * 将被初始化。
 * @retval 无
 */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* Set the default configuration */
  TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/**
 * @brief 启用或禁用指定的 TIM 外设。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIMx 外设。
 * @param NewState：TIMx 外设的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TIM Counter */
    TIMx->CR1 |= TIM_CR1_CEN;
  }
  else
  {
    /* Disable the TIM Counter */
    TIMx->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
  }
}

/**
 * @brief 启用或禁用 TIM 外设主输出。
 * @param TIMx：其中 x 可以是 1、8、15、16 或 17 以选择 TIMx 外设。
 * @param NewState：TIM 外设主输出的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_CtrlPWMOutputs(TIM_TypeDef *TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the TIM Main Output */
    TIMx->BDTR |= TIM_BDTR_MOE;
  }
  else
  {
    /* Disable the TIM Main Output */
    TIMx->BDTR &= (uint16_t)(~((uint16_t)TIM_BDTR_MOE));
  }
}

/**
 * @brief 启用或禁用指定的 TIM 中断。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIMx 外设。
 * @param TIM_IT：指定要启用或禁用的 TIM 中断源。
 * 该参数可以是以下值的任意组合：
 * @arg TIM_IT_Update：TIM 更新中断源
 * @arg TIM_IT_CC1：TIM 捕捉比较 1 中断源
 * @arg TIM_IT_CC2：TIM 捕捉比较 2 中断源
 * @arg TIM_IT_CC3：TIM 捕捉比较 3 中断源
 * @arg TIM_IT_CC4：TIM 捕捉比较 4 中断源
 * @arg TIM_IT_COM：TIM 换向中断源
 * @arg TIM_IT_Trigger：TIM 触发中断源
 * @arg TIM_IT_Break：TIM 中断中断源
 * @笔记
 * - TIM6 和 TIM7 只能产生更新中断。
 * - TIM9、TIM12 和 TIM15 只能有 TIM_IT_Update、TIM_IT_CC1、
 * TIM_IT_CC2 或 TIM_IT_Trigger。
 * - TIM10、TIM11、TIM13、TIM14、TIM16 和 TIM17 可以具有 TIM_IT_Update 或 TIM_IT_CC1。
 * - TIM_IT_Break 仅用于 TIM1、TIM8 和 TIM15。
 * - TIM_IT_COM 仅用于 TIM1、TIM8、TIM15、TIM16 和 TIM17。
 * @param NewState：TIM 中断的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_ITConfig(TIM_TypeDef *TIMx, uint16_t TIM_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIMx->DIER |= TIM_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIMx->DIER &= (uint16_t)~TIM_IT;
  }
}

/**
 * @brief 配置由软件生成的 TIMx 事件。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param TIM_EventSource：指定事件源。
 * 该参数可以是以下一个或多个值：
 * @arg TIM_EventSource_Update：定时器更新事件源
 * @arg TIM_EventSource_CC1：定时器捕获比较 1 事件源
 * @arg TIM_EventSource_CC2：定时器捕获比较 2 事件源
 * @arg TIM_EventSource_CC3：定时器捕获比较 3 事件源
 * @arg TIM_EventSource_CC4：定时器捕获比较 4 事件源
 * @arg TIM_EventSource_COM：定时器 COM 事件源
 * @arg TIM_EventSource_Trigger：定时器触发事件源
 * @arg TIM_EventSource_Break：定时器中断事件源
 * @笔记
 * - TIM6 和 TIM7 只能生成更新事件。
 * - TIM_EventSource_COM 和 TIM_EventSource_Break 仅用于 TIM1 和 TIM8。
 * @retval 无
 */
void TIM_GenerateEvent(TIM_TypeDef *TIMx, uint16_t TIM_EventSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource));

  /* Set the event sources */
  TIMx->EGR = TIM_EventSource;
}

/**
 * @brief 配置 TIMx 的 DMA 接口。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、15、16 或 17 以供选择
 * TIM 外围设备。
 * @param TIM_DMABase：DMA 基地址。
 * 此参数可以是以下值之一：
 * @arg TIM_DMABase_CR, TIM_DMABase_CR2, TIM_DMABase_SMCR,
 * TIM_DMABase_DIER、TIM1_DMABase_SR、TIM_DMABase_EGR、
 * TIM_DMABase_CCMR1、TIM_DMABase_CCMR2、TIM_DMABase_CCER、
 * TIM_DMABase_CNT、TIM_DMABase_PSC、TIM_DMABase_ARR、
 * TIM_DMABase_RCR、TIM_DMABase_CCR1、TIM_DMABase_CCR2、
 * TIM_DMABase_CCR3、TIM_DMABase_CCR4、TIM_DMABase_BDTR、
 * TIM_DMABase_DCR。
 * @param TIM_DMABurstLength：DMA 突发长度。
 * 此参数可以是以下值之间的一个值：
 * TIM_DMABurstLength_1Transfer 和 TIM_DMABurstLength_18Transfers。
 * @retval 无
 */
void TIM_DMAConfig(TIM_TypeDef *TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_BASE(TIM_DMABase));
  assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));
  /* Set the DMA Base and the DMA Burst Length */
  TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}

/**
 * @brief 启用或禁用 TIMx 的 DMA 请求。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、6、7、8、15、16 或 17
 * 选择 TIM 外设。
 * @param TIM_DMASource：指定 DMA 请求源。
 * 该参数可以是以下值的任意组合：
 * @arg TIM_DMA_Update：TIM 更新中断源
 * @arg TIM_DMA_CC1：TIM 捕捉比较 1 DMA 源
 * @arg TIM_DMA_CC2：TIM 捕捉比较 2 DMA 源
 * @arg TIM_DMA_CC3：TIM 捕捉比较 3 DMA 源
 * @arg TIM_DMA_CC4：TIM 捕捉比较 4 DMA 源
 * @arg TIM_DMA_COM：TIM 换向 DMA 源
 * @arg TIM_DMA_Trigger：TIM 触发 DMA 源
 * @param NewState：DMA 请求源的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_DMACmd(TIM_TypeDef *TIMx, uint16_t TIM_DMASource, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST9_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the DMA sources */
    TIMx->DIER |= TIM_DMASource;
  }
  else
  {
    /* Disable the DMA sources */
    TIMx->DIER &= (uint16_t)~TIM_DMASource;
  }
}

/**
 * @brief 配置 TIMx 内部时钟
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15
 * 选择 TIM 外设。
 * @retval 无
 */
void TIM_InternalClockConfig(TIM_TypeDef *TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TIMx->SMCR &= (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
}

/**
 * @brief 将 TIMx 内部触发配置为外部时钟
 * @param TIMx：其中 x 可以是 1、2、3、4、5、9、12 或 15 以选择 TIM 外设。
 * @param TIM_ITRSource：触发源。
 * 此参数可以是以下值之一：
 * @param TIM_TS_ITR0: 内部触发器 0
 * @param TIM_TS_ITR1：内部触发器 1
 * @param TIM_TS_ITR2：内部触发器 2
 * @param TIM_TS_ITR3：内部触发器 3
 * @retval 无
 */
void TIM_ITRxExternalClockConfig(TIM_TypeDef *TIMx, uint16_t TIM_InputTriggerSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));
  /* Select the Internal Trigger */
  TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);
  /* Select the External clock mode1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
 * @brief 将 TIMx 触发器配置为外部时钟
 * @param TIMx：其中 x 可以是 1、2、3、4、5、9、12 或 15 以选择 TIM 外设。
 * @param TIM_TIxExternalCLKSource：触发源。
 * 此参数可以是以下值之一：
 * @arg TIM_TIxExternalCLK1Source_TI1ED：TI1 边沿检测器
 * @arg TIM_TIxExternalCLK1Source_TI1：过滤定时器输入 1
 * @arg TIM_TIxExternalCLK1Source_TI2：过滤定时器输入 2
 * @param TIM_ICPolarity：指定 TIx 极性。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPolarity_Rising
 * @arg TIM_ICPolarity_Falling
 * @param ICFilter : 指定过滤器值。
 * 此参数必须是介于 0x0 和 0xF 之间的值。
 * @retval 无
 */
void TIM_TIxExternalClockConfig(TIM_TypeDef *TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_TIXCLK_SOURCE(TIM_TIxExternalCLKSource));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
  assert_param(IS_TIM_IC_FILTER(ICFilter));
  /* Configure the Timer Input Clock Source */
  if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  /* Select the Trigger source */
  TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
  /* Select the External clock mode1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
 * @brief 配置外部时钟模式 1
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ExtTRGPrescaler：外部触发预分频器。
 * 此参数可以是以下值之一：
 * @arg TIM_ExtTRGPSC_OFF：ETRP 预分频器关闭。
 * @arg TIM_ExtTRGPSC_DIV2：ETRP 频率除以 2。
 * @arg TIM_ExtTRGPSC_DIV4：ETRP 频率除以 4。
 * @arg TIM_ExtTRGPSC_DIV8：ETRP 频率除以 8。
 * @param TIM_ExtTRGPolarity：外部触发极性。
 * 此参数可以是以下值之一：
 * @arg TIM_ExtTRGPolarity_Inverted：低电平有效或下降沿有效。
 * @arg TIM_ExtTRGPolarity_NonInverted：高电平有效或上升沿有效。
 * @param ExtTRGFilter：外部触发滤波器。
 * 此参数必须是介于 0x00 和 0x0F 之间的值
 * @retval 无
 */
void TIM_ETRClockMode1Config(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  /* Configure the ETR Clock source */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);

  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;
  /* Reset the SMS Bits */
  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
  /* Select the External clock mode1 */
  tmpsmcr |= TIM_SlaveMode_External1;
  /* Select the Trigger selection : ETRF */
  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_TS));
  tmpsmcr |= TIM_TS_ETRF;
  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
 * @brief 配置外部时钟模式 2
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ExtTRGPrescaler：外部触发预分频器。
 * 此参数可以是以下值之一：
 * @arg TIM_ExtTRGPSC_OFF：ETRP 预分频器关闭。
 * @arg TIM_ExtTRGPSC_DIV2：ETRP 频率除以 2。
 * @arg TIM_ExtTRGPSC_DIV4：ETRP 频率除以 4。
 * @arg TIM_ExtTRGPSC_DIV8：ETRP 频率除以 8。
 * @param TIM_ExtTRGPolarity：外部触发极性。
 * 此参数可以是以下值之一：
 * @arg TIM_ExtTRGPolarity_Inverted：低电平有效或下降沿有效。
 * @arg TIM_ExtTRGPolarity_NonInverted：高电平有效或上升沿有效。
 * @param ExtTRGFilter：外部触发滤波器。
 * 此参数必须是介于 0x00 和 0x0F 之间的值
 * @retval 无
 */
void TIM_ETRClockMode2Config(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler,
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  /* Configure the ETR Clock source */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  /* Enable the External clock mode2 */
  TIMx->SMCR |= TIM_SMCR_ECE;
}

/**
 * @brief 配置 TIMx 外部触发 (ETR)。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ExtTRGPrescaler：外部触发预分频器。
 * 此参数可以是以下值之一：
 * @arg TIM_ExtTRGPSC_OFF：ETRP 预分频器关闭。
 * @arg TIM_ExtTRGPSC_DIV2：ETRP 频率除以 2。
 * @arg TIM_ExtTRGPSC_DIV4：ETRP 频率除以 4。
 * @arg TIM_ExtTRGPSC_DIV8：ETRP 频率除以 8。
 * @param TIM_ExtTRGPolarity：外部触发极性。
 * 此参数可以是以下值之一：
 * @arg TIM_ExtTRGPolarity_Inverted：低电平有效或下降沿有效。
 * @arg TIM_ExtTRGPolarity_NonInverted：高电平有效或上升沿有效。
 * @param ExtTRGFilter：外部触发滤波器。
 * 此参数必须是介于 0x00 和 0x0F 之间的值
 * @retval 无
 */
void TIM_ETRConfig(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  tmpsmcr = TIMx->SMCR;
  /* Reset the ETR Bits */
  tmpsmcr &= SMCR_ETR_Mask;
  /* Set the Prescaler, the Filter value and the Polarity */
  tmpsmcr |= (uint16_t)(TIM_ExtTRGPrescaler | (uint16_t)(TIM_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
 * @brief 配置 TIMx 预分频器。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param Prescaler：指定预分频器寄存器值
 * @param TIM_PSCReloadMode：指定 TIM 预分频器重载模式
 * 此参数可以是以下值之一：
 * @arg TIM_PSCReloadMode_Update：预分频器在更新事件中加载。
 * @arg TIM_PSCReloadMode_Immediate：预分频器立即加载。
 * @retval 无
 */
void TIM_PrescalerConfig(TIM_TypeDef *TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));
  /* Set the Prescaler value */
  TIMx->PSC = Prescaler;
  /* Set or reset the UG Bit */
  TIMx->EGR = TIM_PSCReloadMode;
}

/**
 * @brief 指定要使用的 TIMx 计数器模式。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_CounterMode：指定要使用的计数器模式
 * 此参数可以是以下值之一：
 * @arg TIM_CounterMode_Up：TIM 向上计数模式
 * @arg TIM_CounterMode_Down：TIM 向下计数模式
 * @arg TIM_CounterMode_CenterAligned1：TIM 中心对齐模式 1
 * @arg TIM_CounterMode_CenterAligned2：TIM 中心对齐模式 2
 * @arg TIM_CounterMode_CenterAligned3：TIM 中心对齐模式 3
 * @retval 无
 */
void TIM_CounterModeConfig(TIM_TypeDef *TIMx, uint16_t TIM_CounterMode)
{
  uint16_t tmpcr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));
  tmpcr1 = TIMx->CR1;
  /* Reset the CMS and DIR Bits */
  tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_CR1_DIR | TIM_CR1_CMS)));
  /* Set the Counter Mode */
  tmpcr1 |= TIM_CounterMode;
  /* Write to TIMx CR1 register */
  TIMx->CR1 = tmpcr1;
}

/**
 * @brief 选择输入触发源
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_InputTriggerSource：输入触发源。
 * 此参数可以是以下值之一：
 * @arg TIM_TS_ITR0：内部触发器 0
 * @arg TIM_TS_ITR1：内部触发器 1
 * @arg TIM_TS_ITR2：内部触发器 2
 * @arg TIM_TS_ITR3：内部触发器 3
 * @arg TIM_TS_TI1F_ED：TI1 边缘检测器
 * @arg TIM_TS_TI1FP1：过滤定时器输入 1
 * @arg TIM_TS_TI2FP2：过滤定时器输入 2
 * @arg TIM_TS_ETRF：外部触发输入
 * @retval 无
 */
void TIM_SelectInputTrigger(TIM_TypeDef *TIMx, uint16_t TIM_InputTriggerSource)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));
  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;
  /* Reset the TS Bits */
  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_TS));
  /* Set the Input Trigger source */
  tmpsmcr |= TIM_InputTriggerSource;
  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
 * @brief 配置 TIMx 编码器接口。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_EncoderMode：指定 TIMx 编码器模式。
 * 此参数可以是以下值之一：
 * @arg TIM_EncoderMode_TI1：计数器在 TI1FP1 边沿计数，具体取决于 TI2FP2 电平。
 * @arg TIM_EncoderMode_TI2：计数器在 TI2FP2 边沿计数，具体取决于 TI1FP1 电平。
 * @arg TIM_EncoderMode_TI12：TI1FP1 和 TI2FP2 边沿上的计数器计数取决于
 * 在其他输入的级别上。
 * @param TIM_IC1Polarity：指定 IC1 极性
 * 此参数可以是以下值之一：
 * @arg TIM_ICPolarity_Falling：IC 下降沿。
 * @arg TIM_ICPolarity_Rising：IC 上升沿。
 * @param TIM_IC2Polarity：指定 IC2 极性
 * 此参数可以是以下值之一：
 * @arg TIM_ICPolarity_Falling：IC 下降沿。
 * @arg TIM_ICPolarity_Rising：IC 上升沿。
 * @retval 无
 */
void TIM_EncoderInterfaceConfig(TIM_TypeDef *TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity)
{
  uint16_t tmpsmcr = 0;
  uint16_t tmpccmr1 = 0;
  uint16_t tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST5_PERIPH(TIMx));
  assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));

  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;

  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;

  /* Set the encoder Mode */
  tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMCR_SMS));
  tmpsmcr |= TIM_EncoderMode;

  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
  tmpccmr1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CCMR1_CC1S)) & (uint16_t)(~((uint16_t)TIM_CCMR1_CC2S)));
  tmpccmr1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;

  /* Set the TI1 and the TI2 Polarities */
  tmpccer &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CCER_CC1P)) & ((uint16_t) ~((uint16_t)TIM_CCER_CC2P)));
  tmpccer |= (uint16_t)(TIM_IC1Polarity | (uint16_t)(TIM_IC2Polarity << (uint16_t)4));

  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 强制 TIMx 输出 1 波形为活动或非活动电平。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_ForcedAction：指定要设置为输出波形的强制动作。
 * 此参数可以是以下值之一：
 * @arg TIM_ForcedAction_Active：在 OC1REF 上强制激活电平
 * @arg TIM_ForcedAction_InActive：在 OC1REF 上强制非活动级别。
 * @retval 无
 */
void TIM_ForcedOC1Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC1M Bits */
  tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_OC1M);
  /* Configure The Forced output Mode */
  tmpccmr1 |= TIM_ForcedAction;
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
 * @brief 强制 TIMx 输出 2 波形为活动或非活动电平。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_ForcedAction：指定要设置为输出波形的强制动作。
 * 此参数可以是以下值之一：
 * @arg TIM_ForcedAction_Active：在 OC2REF 上强制激活级别
 * @arg TIM_ForcedAction_InActive：强制 OC2REF 上的非活动级别。
 * @retval 无
 */
void TIM_ForcedOC2Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2M Bits */
  tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_OC2M);
  /* Configure The Forced output Mode */
  tmpccmr1 |= (uint16_t)(TIM_ForcedAction << 8);
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
 * @brief 强制 TIMx 输出 3 波形为活动或非活动电平。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ForcedAction：指定要设置为输出波形的强制动作。
 * 此参数可以是以下值之一：
 * @arg TIM_ForcedAction_Active：在 OC3REF 上强制激活级别
 * @arg TIM_ForcedAction_InActive：在 OC3REF 上强制非活动级别。
 * @retval 无
 */
void TIM_ForcedOC3Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC1M Bits */
  tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_OC3M);
  /* Configure The Forced output Mode */
  tmpccmr2 |= TIM_ForcedAction;
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
 * @brief 强制 TIMx 输出 4 波形为活动或非活动电平。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ForcedAction：指定要设置为输出波形的强制动作。
 * 此参数可以是以下值之一：
 * @arg TIM_ForcedAction_Active：在 OC4REF 上强制激活级别
 * @arg TIM_ForcedAction_InActive：强制 OC4REF 上的非活动级别。
 * @retval 无
 */
void TIM_ForcedOC4Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC2M Bits */
  tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_OC4M);
  /* Configure The Forced output Mode */
  tmpccmr2 |= (uint16_t)(TIM_ForcedAction << 8);
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
 * @brief 启用或禁用 ARR 上的 TIMx 外设预加载寄存器。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param NewState：TIMx 外设预加载寄存器的新状态
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_ARRPreloadConfig(TIM_TypeDef *TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the ARR Preload Bit */
    TIMx->CR1 |= TIM_CR1_ARPE;
  }
  else
  {
    /* Reset the ARR Preload Bit */
    TIMx->CR1 &= (uint16_t) ~((uint16_t)TIM_CR1_ARPE);
  }
}

/**
 * @brief 选择 TIM 外设换向事件。
 * @param TIMx：其中 x 可以是 1、8、15、16 或 17 以选择 TIMx 外设
 * @param NewState：Commutation 事件的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_SelectCOM(TIM_TypeDef *TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the COM Bit */
    TIMx->CR2 |= TIM_CR2_CCUS;
  }
  else
  {
    /* Reset the COM Bit */
    TIMx->CR2 &= (uint16_t) ~((uint16_t)TIM_CR2_CCUS);
  }
}

/**
 * @brief 选择 TIMx 外设捕捉比较 DMA 源。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、15、16 或 17 以供选择
 * TIM 外围设备。
 * @param NewState：捕获比较 DMA 源的新状态
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_SelectCCDMA(TIM_TypeDef *TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST4_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the CCDS Bit */
    TIMx->CR2 |= TIM_CR2_CCDS;
  }
  else
  {
    /* Reset the CCDS Bit */
    TIMx->CR2 &= (uint16_t) ~((uint16_t)TIM_CR2_CCDS);
  }
}

/**
 * @brief 设置或复位 TIM 外设捕捉比较预加载控制位。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8 或 15
 * 选择 TIMx 外设
 * @param NewState：捕获比较预加载控制位的新状态
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_CCPreloadControl(TIM_TypeDef *TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST5_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the CCPC Bit */
    TIMx->CR2 |= TIM_CR2_CCPC;
  }
  else
  {
    /* Reset the CCPC Bit */
    TIMx->CR2 &= (uint16_t) ~((uint16_t)TIM_CR2_CCPC);
  }
}

/**
 * @brief 启用或禁用 CCR1 上的 TIMx 外设预加载寄存器。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_OCPreload：TIMx 外设预加载寄存器的新状态
 * 此参数可以是以下值之一：
 * @arg TIM_OCPreload_Enable
 * @arg TIM_OCPreload_Disable
 * @retval 无
 */
void TIM_OC1PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC1PE Bit */
  tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_OC1PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= TIM_OCPreload;
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
 * @brief 启用或禁用 CCR2 上的 TIMx 外设预加载寄存器。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以供选择
 * TIM 外围设备。
 * @param TIM_OCPreload：TIMx 外设预加载寄存器的新状态
 * 此参数可以是以下值之一：
 * @arg TIM_OCPreload_Enable
 * @arg TIM_OCPreload_Disable
 * @retval 无
 */
void TIM_OC2PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2PE Bit */
  tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_OC2PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= (uint16_t)(TIM_OCPreload << 8);
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
 * @brief 启用或禁用 CCR3 上的 TIMx 外设预加载寄存器。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCPreload：TIMx 外设预加载寄存器的新状态
 * 此参数可以是以下值之一：
 * @arg TIM_OCPreload_Enable
 * @arg TIM_OCPreload_Disable
 * @retval 无
 */
void TIM_OC3PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC3PE Bit */
  tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_OC3PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= TIM_OCPreload;
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
 * @brief 启用或禁用 CCR4 上的 TIMx 外设预加载寄存器。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCPreload：TIMx 外设预加载寄存器的新状态
 * 此参数可以是以下值之一：
 * @arg TIM_OCPreload_Enable
 * @arg TIM_OCPreload_Disable
 * @retval 无
 */
void TIM_OC4PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC4PE Bit */
  tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_OC4PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= (uint16_t)(TIM_OCPreload << 8);
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
 * @brief 配置 TIMx 输出比较 1 快速功能。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_OCFast：输出比较快速启用位的新状态。
 * 此参数可以是以下值之一：
 * @arg TIM_OCFast_Enable：TIM 输出比较快速启用
 * @arg TIM_OCFast_Disable：TIM 输出比较快速禁用
 * @retval 无
 */
void TIM_OC1FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC1FE Bit */
  tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_OC1FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= TIM_OCFast;
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
 * @brief 配置 TIMx 输出比较 2 快速功能。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以供选择
 * TIM 外围设备。
 * @param TIM_OCFast：输出比较快速启用位的新状态。
 * 此参数可以是以下值之一：
 * @arg TIM_OCFast_Enable：TIM 输出比较快速启用
 * @arg TIM_OCFast_Disable：TIM 输出比较快速禁用
 * @retval 无
 */
void TIM_OC2FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2FE Bit */
  tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_OC2FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= (uint16_t)(TIM_OCFast << 8);
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
 * @brief 配置 TIMx 输出比较 3 快速功能。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCFast：输出比较快速启用位的新状态。
 * 此参数可以是以下值之一：
 * @arg TIM_OCFast_Enable：TIM 输出比较快速启用
 * @arg TIM_OCFast_Disable：TIM 输出比较快速禁用
 * @retval 无
 */
void TIM_OC3FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC3FE Bit */
  tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_OC3FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= TIM_OCFast;
  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
 * @brief 配置 TIMx 输出比较 4 快速功能。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCFast：输出比较快速启用位的新状态。
 * 此参数可以是以下值之一：
 * @arg TIM_OCFast_Enable：TIM 输出比较快速启用
 * @arg TIM_OCFast_Disable：TIM 输出比较快速禁用
 * @retval 无
 */
void TIM_OC4FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC4FE Bit */
  tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_OC4FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= (uint16_t)(TIM_OCFast << 8);
  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
 * @brief 清除或保护外部事件上的 OCREF1 信号
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCClear：输出比较清除使能位的新状态。
 * 此参数可以是以下值之一：
 * @arg TIM_OCClear_Enable：TIM 输出清除启用
 * @arg TIM_OCClear_Disable：TIM 输出清除禁用
 * @retval 无
 */
void TIM_ClearOC1Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC1CE Bit */
  tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_OC1CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= TIM_OCClear;
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
 * @brief 清除或保护外部事件的 OCREF2 信号
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCClear：输出比较清除使能位的新状态。
 * 此参数可以是以下值之一：
 * @arg TIM_OCClear_Enable：TIM 输出清除启用
 * @arg TIM_OCClear_Disable：TIM 输出清除禁用
 * @retval 无
 */
void TIM_ClearOC2Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr1 = TIMx->CCMR1;
  /* Reset the OC2CE Bit */
  tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_OC2CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= (uint16_t)(TIM_OCClear << 8);
  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/**
 * @brief 清除或保护外部事件的 OCREF3 信号
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCClear：输出比较清除使能位的新状态。
 * 此参数可以是以下值之一：
 * @arg TIM_OCClear_Enable：TIM 输出清除启用
 * @arg TIM_OCClear_Disable：TIM 输出清除禁用
 * @retval 无
 */
void TIM_ClearOC3Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC3CE Bit */
  tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_OC3CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= TIM_OCClear;
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
 * @brief 清除或保护外部事件的 OCREF4 信号
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCClear：输出比较清除使能位的新状态。
 * 此参数可以是以下值之一：
 * @arg TIM_OCClear_Enable：TIM 输出清除启用
 * @arg TIM_OCClear_Disable：TIM 输出清除禁用
 * @retval 无
 */
void TIM_ClearOC4Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr2 = TIMx->CCMR2;
  /* Reset the OC4CE Bit */
  tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_OC4CE);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= (uint16_t)(TIM_OCClear << 8);
  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/**
 * @brief 配置 TIMx 通道 1 极性。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_OCPolarity：指定 OC1 极性
 * 此参数可以是以下值之一：
 * @arg TIM_OCPolarity_High：输出比较高电平有效
 * @arg TIM_OCPolarity_Low：输出比较低电平有效
 * @retval 无
 */
void TIM_OC1PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC1P Bit */
  tmpccer &= (uint16_t) ~((uint16_t)TIM_CCER_CC1P);
  tmpccer |= TIM_OCPolarity;
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}
/**
 * @brief 配置 TIMx 通道 1N 极性。
 * @param TIMx：其中 x 可以是 1、8、15、16 或 17 以选择 TIM 外设。
 * @param TIM_OCNPolarity：指定 OC1N 极性
 * 此参数可以是以下值之一：
 * @arg TIM_OCNPolarity_High：输出比较高电平有效
 * @arg TIM_OCNPolarity_Low：输出比较低电平有效
 * @retval 无
 */
void TIM_OC1NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

  tmpccer = TIMx->CCER;
  /* Set or Reset the CC1NP Bit */
  tmpccer &= (uint16_t) ~((uint16_t)TIM_CCER_CC1NP);
  tmpccer |= TIM_OCNPolarity;
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 配置 TIMx 通道 2 极性。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_OCPolarity：指定 OC2 极性
 * 此参数可以是以下值之一：
 * @arg TIM_OCPolarity_High：输出比较高电平有效
 * @arg TIM_OCPolarity_Low：输出比较低电平有效
 * @retval 无
 */
void TIM_OC2PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC2P Bit */
  tmpccer &= (uint16_t) ~((uint16_t)TIM_CCER_CC2P);
  tmpccer |= (uint16_t)(TIM_OCPolarity << 4);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 配置 TIMx 通道 2N 极性。
 * @param TIMx：其中 x 可以是 1 或 8 以选择 TIM 外设。
 * @param TIM_OCNPolarity：指定 OC2N 极性
 * 此参数可以是以下值之一：
 * @arg TIM_OCNPolarity_High：输出比较高电平有效
 * @arg TIM_OCNPolarity_Low：输出比较低电平有效
 * @retval 无
 */
void TIM_OC2NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST1_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

  tmpccer = TIMx->CCER;
  /* Set or Reset the CC2NP Bit */
  tmpccer &= (uint16_t) ~((uint16_t)TIM_CCER_CC2NP);
  tmpccer |= (uint16_t)(TIM_OCNPolarity << 4);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 配置 TIMx 通道 3 极性。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCPolarity：指定 OC3 极性
 * 此参数可以是以下值之一：
 * @arg TIM_OCPolarity_High：输出比较高电平有效
 * @arg TIM_OCPolarity_Low：输出比较低电平有效
 * @retval 无
 */
void TIM_OC3PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC3P Bit */
  tmpccer &= (uint16_t) ~((uint16_t)TIM_CCER_CC3P);
  tmpccer |= (uint16_t)(TIM_OCPolarity << 8);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 配置 TIMx 通道 3N 极性。
 * @param TIMx：其中 x 可以是 1 或 8 以选择 TIM 外设。
 * @param TIM_OCNPolarity：指定 OC3N 极性
 * 此参数可以是以下值之一：
 * @arg TIM_OCNPolarity_High：输出比较高电平有效
 * @arg TIM_OCNPolarity_Low：输出比较低电平有效
 * @retval 无
 */
void TIM_OC3NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST1_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

  tmpccer = TIMx->CCER;
  /* Set or Reset the CC3NP Bit */
  tmpccer &= (uint16_t) ~((uint16_t)TIM_CCER_CC3NP);
  tmpccer |= (uint16_t)(TIM_OCNPolarity << 8);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 配置 TIMx 通道 4 极性。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_OCPolarity：指定 OC4 极性
 * 此参数可以是以下值之一：
 * @arg TIM_OCPolarity_High：输出比较高电平有效
 * @arg TIM_OCPolarity_Low：输出比较低电平有效
 * @retval 无
 */
void TIM_OC4PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* Set or Reset the CC4P Bit */
  tmpccer &= (uint16_t) ~((uint16_t)TIM_CCER_CC4P);
  tmpccer |= (uint16_t)(TIM_OCPolarity << 12);
  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/**
 * @brief 启用或禁用 TIM 捕获比较通道 x。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_Channel：指定 TIM 通道
 * 此参数可以是以下值之一：
 * @arg TIM_Channel_1: TIM 通道 1
 * @arg TIM_Channel_2：TIM 通道 2
 * @arg TIM_Channel_3：TIM 通道 3
 * @arg TIM_Channel_4：TIM 通道 4
 * @param TIM_CCx：指定 TIM 通道 CCxE 位的新状态。
 * 此参数可以是：TIM_CCx_Enable 或 TIM_CCx_Disable。
 * @retval 无
 */
void TIM_CCxCmd(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx)
{
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCX(TIM_CCx));

  tmp = CCER_CCE_Set << TIM_Channel;

  /* Reset the CCxE Bit */
  TIMx->CCER &= (uint16_t)~tmp;

  /* Set or reset the CCxE Bit */
  TIMx->CCER |= (uint16_t)(TIM_CCx << TIM_Channel);
}

/**
 * @brief 启用或禁用 TIM 捕获比较通道 xN。
 * @param TIMx：其中 x 可以是 1、8、15、16 或 17 以选择 TIM 外设。
 * @param TIM_Channel：指定 TIM 通道
 * 此参数可以是以下值之一：
 * @arg TIM_Channel_1: TIM 通道 1
 * @arg TIM_Channel_2：TIM 通道 2
 * @arg TIM_Channel_3：TIM 通道 3
 * @param TIM_CCxN：指定 TIM 通道 CCxNE 位的新状态。
 * 此参数可以是：TIM_CCxN_Enable 或 TIM_CCxN_Disable。
 * @retval 无
 */
void TIM_CCxNCmd(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN)
{
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_TIM_COMPLEMENTARY_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCXN(TIM_CCxN));

  tmp = CCER_CCNE_Set << TIM_Channel;

  /* Reset the CCxNE Bit */
  TIMx->CCER &= (uint16_t)~tmp;

  /* Set or reset the CCxNE Bit */
  TIMx->CCER |= (uint16_t)(TIM_CCxN << TIM_Channel);
}

/**
 * @brief 选择 TIM 输出比较模式。
 * @note 此函数在更改输出之前禁用所选通道
 *比较模式。
 * 用户必须使用 TIM_CCxCmd 和 TIM_CCxNCmd 函数启用此通道。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_Channel：指定 TIM 通道
 * 此参数可以是以下值之一：
 * @arg TIM_Channel_1: TIM 通道 1
 * @arg TIM_Channel_2：TIM 通道 2
 * @arg TIM_Channel_3：TIM 通道 3
 * @arg TIM_Channel_4：TIM 通道 4
 * @param TIM_OCMode：指定 TIM 输出比较模式。
 * 此参数可以是以下值之一：
 * @arg TIM_OCMode_Timing
 * @arg TIM_OCMode_Active
 * @arg TIM_OCMode_Toggle
 * @arg TIM_OCMode_PWM1
 * @arg TIM_OCMode_PWM2
 * @arg TIM_ForcedAction_Active
 * @arg TIM_ForcedAction_InActive
 * @retval 无
 */
void TIM_SelectOCxM(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode)
{
  uint32_t tmp = 0;
  uint16_t tmp1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_OCM(TIM_OCMode));

  tmp = (uint32_t)TIMx;
  tmp += CCMR_Offset;

  tmp1 = CCER_CCE_Set << (uint16_t)TIM_Channel;

  /* Disable the Channel: Reset the CCxE Bit */
  TIMx->CCER &= (uint16_t)~tmp1;

  if ((TIM_Channel == TIM_Channel_1) || (TIM_Channel == TIM_Channel_3))
  {
    tmp += (TIM_Channel >> 1);

    /* Reset the OCxM bits in the CCMRx register */
    *(__IO uint32_t *)tmp &= (uint32_t) ~((uint32_t)TIM_CCMR1_OC1M);

    /* Configure the OCxM bits in the CCMRx register */
    *(__IO uint32_t *)tmp |= TIM_OCMode;
  }
  else
  {
    tmp += (uint16_t)(TIM_Channel - (uint16_t)4) >> (uint16_t)1;

    /* Reset the OCxM bits in the CCMRx register */
    *(__IO uint32_t *)tmp &= (uint32_t) ~((uint32_t)TIM_CCMR1_OC2M);

    /* Configure the OCxM bits in the CCMRx register */
    *(__IO uint32_t *)tmp |= (uint16_t)(TIM_OCMode << 8);
  }
}

/**
 * @brief 启用或禁用 TIMx 更新事件。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param NewState：TIMx UDIS 位的新状态
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_UpdateDisableConfig(TIM_TypeDef *TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the Update Disable Bit */
    TIMx->CR1 |= TIM_CR1_UDIS;
  }
  else
  {
    /* Reset the Update Disable Bit */
    TIMx->CR1 &= (uint16_t) ~((uint16_t)TIM_CR1_UDIS);
  }
}

/**
   * @brief 配置 TIMx 更新请求中断源。
   * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
   * @param TIM_UpdateSource：指定更新源。
   * 此参数可以是以下值之一：
   * @arg TIM_UpdateSource_Regular：更新源是计数器上溢/下溢
                                        或UG位的设置，或更新生成
                                        通过从模式控制器。
   * @arg TIM_UpdateSource_Global：更新源是计数器上溢/下溢。
   * @retval 无
   */
void TIM_UpdateRequestConfig(TIM_TypeDef *TIMx, uint16_t TIM_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));
  if (TIM_UpdateSource != TIM_UpdateSource_Global)
  {
    /* Set the URS Bit */
    TIMx->CR1 |= TIM_CR1_URS;
  }
  else
  {
    /* Reset the URS Bit */
    TIMx->CR1 &= (uint16_t) ~((uint16_t)TIM_CR1_URS);
  }
}

/**
 * @brief 启用或禁用 TIMx 的霍尔传感器接口。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param NewState：TIMx 霍尔传感器接口的新状态。
 * 此参数可以是：ENABLE 或 DISABLE。
 * @retval 无
 */
void TIM_SelectHallSensor(TIM_TypeDef *TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Set the TI1S Bit */
    TIMx->CR2 |= TIM_CR2_TI1S;
  }
  else
  {
    /* Reset the TI1S Bit */
    TIMx->CR2 &= (uint16_t) ~((uint16_t)TIM_CR2_TI1S);
  }
}

/**
 * @brief 选择 TIMx 的单脉冲模式。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param TIM_OPMode：指定要使用的 OPM 模式。
 * 此参数可以是以下值之一：
 * @arg TIM_OPMode_Single
 * @arg TIM_OPMode_Repetitive
 * @retval 无
 */
void TIM_SelectOnePulseMode(TIM_TypeDef *TIMx, uint16_t TIM_OPMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_OPM_MODE(TIM_OPMode));
  /* Reset the OPM Bit */
  TIMx->CR1 &= (uint16_t) ~((uint16_t)TIM_CR1_OPM);
  /* Configure the OPM Mode */
  TIMx->CR1 |= TIM_OPMode;
}

/**
 * @brief 选择 TIMx 触发输出模式。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、6、7、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_TRGOSource：指定触发输出源。
 * 此参数可以是以下值之一：
 *
 * - 对于所有 TIMx
 * @arg TIM_TRGOSource_Reset：TIM_EGR 寄存器中的 UG 位用作触发输出 (TRGO)。
 * @arg TIM_TRGOSource_Enable：计数器启用 CEN 用作触发输出 (TRGO)。
 * @arg TIM_TRGOSource_Update：更新事件被选为触发输出（TRGO）。
 *
 * - 对于除 TIM6 和 TIM7 之外的所有 TIMx
 * @arg TIM_TRGOSource_OC1：当CC1IF标志位触发输出发送一个正脉冲
 * 将在发生捕获或比较匹配 (TRGO) 时设置。
 * @arg TIM_TRGOSource_OC1Ref：OC1REF 信号用作触发输出 (TRGO)。
 * @arg TIM_TRGOSource_OC2Ref：OC2REF 信号用作触发输出 (TRGO)。
 * @arg TIM_TRGOSource_OC3Ref：OC3REF 信号用作触发输出 (TRGO)。
 * @arg TIM_TRGOSource_OC4Ref：OC4REF 信号用作触发输出 (TRGO)。
 *
 * @retval 无
 */
void TIM_SelectOutputTrigger(TIM_TypeDef *TIMx, uint16_t TIM_TRGOSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST7_PERIPH(TIMx));
  assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));
  /* Reset the MMS Bits */
  TIMx->CR2 &= (uint16_t) ~((uint16_t)TIM_CR2_MMS);
  /* Select the TRGO source */
  TIMx->CR2 |= TIM_TRGOSource;
}

/**
 * @brief 选择 TIMx 从模式。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_SlaveMode：指定定时器从模式。
 * 此参数可以是以下值之一：
 * @arg TIM_SlaveMode_Reset：所选触发信号 (TRGI) 的上升沿重新初始化
 * 计数器并触发寄存器的更新。
 * @arg TIM_SlaveMode_Gated：当触发信号 (TRGI) 为高电平时，计数器时钟被启用。
 * @arg TIM_SlaveMode_Trigger：计数器在触发器 TRGI 的上升沿开始。
 * @arg TIM_SlaveMode_External1：选定触发器 (TRGI) 的上升沿为计数器提供时钟。
 * @retval 无
 */
void TIM_SelectSlaveMode(TIM_TypeDef *TIMx, uint16_t TIM_SlaveMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));
  /* Reset the SMS Bits */
  TIMx->SMCR &= (uint16_t) ~((uint16_t)TIM_SMCR_SMS);
  /* Select the Slave Mode */
  TIMx->SMCR |= TIM_SlaveMode;
}

/**
 * @brief 设置或重置 TIMx 主/从模式。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_MasterSlaveMode：指定定时器主从模式。
 * 此参数可以是以下值之一：
 * @arg TIM_MasterSlaveMode_Enable：当前定时器之间的同步
 * 及其从属设备（通过 TRGO）。
 * @arg TIM_MasterSlaveMode_Disable：无操作
 * @retval 无
 */
void TIM_SelectMasterSlaveMode(TIM_TypeDef *TIMx, uint16_t TIM_MasterSlaveMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_MSM_STATE(TIM_MasterSlaveMode));
  /* Reset the MSM Bit */
  TIMx->SMCR &= (uint16_t) ~((uint16_t)TIM_SMCR_MSM);

  /* Set or Reset the MSM Bit */
  TIMx->SMCR |= TIM_MasterSlaveMode;
}

/**
 * @brief 设置 TIMx 计数器寄存器值
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param Counter：指定计数器寄存器的新值。
 * @retval 无
 */
void TIM_SetCounter(TIM_TypeDef *TIMx, uint16_t Counter)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* Set the Counter Register value */
  TIMx->CNT = Counter;
}

/**
 * @brief 设置 TIMx 自动重载寄存器值
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param Autoreload：指定 Autoreload 寄存器的新值。
 * @retval 无
 */
void TIM_SetAutoreload(TIM_TypeDef *TIMx, uint16_t Autoreload)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* Set the Autoreload Register value */
  TIMx->ARR = Autoreload;
}

/**
 * @brief 设置 TIMx Capture Compare1 寄存器值
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param Compare1：指定 Capture Compare1 寄存器的新值。
 * @retval 无
 */
void TIM_SetCompare1(TIM_TypeDef *TIMx, uint16_t Compare1)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  /* Set the Capture Compare1 Register value */
  TIMx->CCR1 = Compare1;
}

/**
 * @brief 设置 TIMx Capture Compare2 寄存器值
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param Compare2：指定 Capture Compare2 寄存器的新值。
 * @retval 无
 */
void TIM_SetCompare2(TIM_TypeDef *TIMx, uint16_t Compare2)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  /* Set the Capture Compare2 Register value */
  TIMx->CCR2 = Compare2;
}

/**
 * @brief 设置 TIMx Capture Compare3 寄存器值
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param Compare3：指定 Capture Compare3 寄存器的新值。
 * @retval 无
 */
void TIM_SetCompare3(TIM_TypeDef *TIMx, uint16_t Compare3)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  /* Set the Capture Compare3 Register value */
  TIMx->CCR3 = Compare3;
}

/**
 * @brief 设置 TIMx Capture Compare4 寄存器值
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param Compare4：指定 Capture Compare4 寄存器的新值。
 * @retval 无
 */
void TIM_SetCompare4(TIM_TypeDef *TIMx, uint16_t Compare4)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  /* Set the Capture Compare4 Register value */
  TIMx->CCR4 = Compare4;
}

/**
 * @brief 设置 TIMx 输入捕捉 1 预分频器。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_ICPSC：指定输入 Capture1 预分频器新值。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPSC_DIV1：没有预分频器
 * @arg TIM_ICPSC_DIV2：每 2 个事件捕获一次
 * @arg TIM_ICPSC_DIV4：每 4 个事件捕获一次
 * @arg TIM_ICPSC_DIV8：每 8 个事件捕获一次
 * @retval 无
 */
void TIM_SetIC1Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* Reset the IC1PSC Bits */
  TIMx->CCMR1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_IC1PSC);
  /* Set the IC1PSC value */
  TIMx->CCMR1 |= TIM_ICPSC;
}

/**
 * @brief 设置 TIMx 输入捕捉 2 预分频器。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_ICPSC：指定输入 Capture2 预分频器新值。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPSC_DIV1：没有预分频器
 * @arg TIM_ICPSC_DIV2：每 2 个事件捕获一次
 * @arg TIM_ICPSC_DIV4：每 4 个事件捕获一次
 * @arg TIM_ICPSC_DIV8：每 8 个事件捕获一次
 * @retval 无
 */
void TIM_SetIC2Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* Reset the IC2PSC Bits */
  TIMx->CCMR1 &= (uint16_t) ~((uint16_t)TIM_CCMR1_IC2PSC);
  /* Set the IC2PSC value */
  TIMx->CCMR1 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
 * @brief 设置 TIMx 输入捕捉 3 预分频器。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ICPSC：指定输入 Capture3 预分频器新值。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPSC_DIV1：没有预分频器
 * @arg TIM_ICPSC_DIV2：每 2 个事件捕获一次
 * @arg TIM_ICPSC_DIV4：每 4 个事件捕获一次
 * @arg TIM_ICPSC_DIV8：每 8 个事件捕获一次
 * @retval 无
 */
void TIM_SetIC3Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* Reset the IC3PSC Bits */
  TIMx->CCMR2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_IC3PSC);
  /* Set the IC3PSC value */
  TIMx->CCMR2 |= TIM_ICPSC;
}

/**
 * @brief 设置 TIMx 输入捕捉 4 预分频器。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ICPSC：指定输入 Capture4 预分频器新值。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPSC_DIV1：没有预分频器
 * @arg TIM_ICPSC_DIV2：每 2 个事件捕获一次
 * @arg TIM_ICPSC_DIV4：每 4 个事件捕获一次
 * @arg TIM_ICPSC_DIV8：每 8 个事件捕获一次
 * @retval 无
 */
void TIM_SetIC4Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* Reset the IC4PSC Bits */
  TIMx->CCMR2 &= (uint16_t) ~((uint16_t)TIM_CCMR2_IC4PSC);
  /* Set the IC4PSC value */
  TIMx->CCMR2 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
 * @brief 设置 TIMx 时钟分频值。
 * @param TIMx：其中 x 可以是 1 到 17，但要选择的 6 和 7 除外
 * TIM 外围设备。
 * @param TIM_CKD：指定时钟分频值。
 * 此参数可以是以下值之一：
 * @arg TIM_CKD_DIV1: TDTS = Tck_tim
 * @arg TIM_CKD_DIV2: TDTS = 2*Tck_tim
 * @arg TIM_CKD_DIV4: TDTS = 4*Tck_tim
 * @retval 无
 */
void TIM_SetClockDivision(TIM_TypeDef *TIMx, uint16_t TIM_CKD)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  assert_param(IS_TIM_CKD_DIV(TIM_CKD));
  /* Reset the CKD Bits */
  TIMx->CR1 &= (uint16_t) ~((uint16_t)TIM_CR1_CKD);
  /* Set the CKD value */
  TIMx->CR1 |= TIM_CKD;
}

/**
 * @brief 获取 TIMx 输入捕获 1 值。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @retval 捕获比较 1 个寄存器值。
 */
uint16_t TIM_GetCapture1(TIM_TypeDef *TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIMx));
  /* Get the Capture 1 Register value */
  return TIMx->CCR1;
}

/**
 * @brief 获取 TIMx 输入捕获 2 值。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @retval 捕获比较 2 寄存器值。
 */
uint16_t TIM_GetCapture2(TIM_TypeDef *TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST6_PERIPH(TIMx));
  /* Get the Capture 2 Register value */
  return TIMx->CCR2;
}

/**
 * @brief 获取 TIMx 输入捕获 3 值。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @retval 捕获比较 3 寄存器值。
 */
uint16_t TIM_GetCapture3(TIM_TypeDef *TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  /* Get the Capture 3 Register value */
  return TIMx->CCR3;
}

/**
 * @brief 获取 TIMx 输入捕获 4 值。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @retval 捕获比较 4 寄存器值。
 */
uint16_t TIM_GetCapture4(TIM_TypeDef *TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  /* Get the Capture 4 Register value */
  return TIMx->CCR4;
}

/**
 * @brief 获取 TIMx 计数器值。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @retval 计数器寄存器值。
 */
uint16_t TIM_GetCounter(TIM_TypeDef *TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* Get the Counter Register value */
  return TIMx->CNT;
}

/**
 * @brief 获取 TIMx 预分频器值。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @retval 预分频器寄存器值。
 */
uint16_t TIM_GetPrescaler(TIM_TypeDef *TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* Get the Prescaler Register value */
  return TIMx->PSC;
}

/**
 * @brief 检查是否设置了指定的 TIM 标志。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param TIM_FLAG：指定要检查的标志。
 * 此参数可以是以下值之一：
 * @arg TIM_FLAG_Update：TIM 更新标志
 * @arg TIM_FLAG_CC1：TIM 捕获比较 1 标志
 * @arg TIM_FLAG_CC2：TIM 捕获比较 2 标志
 * @arg TIM_FLAG_CC3：TIM 捕获比较 3 标志
 * @arg TIM_FLAG_CC4：TIM 捕获比较 4 标志
 * @arg TIM_FLAG_COM: TIM 换向标志
 * @arg TIM_FLAG_Trigger: TIM 触发标志
 * @arg TIM_FLAG_Break: TIM 中断标志
 * @arg TIM_FLAG_CC1OF：TIM 捕获比较 1 过捕获标志
 * @arg TIM_FLAG_CC2OF：TIM 捕获比较 2 过捕获标志
 * @arg TIM_FLAG_CC3OF：TIM 捕获比较 3 过捕获标志
 * @arg TIM_FLAG_CC4OF：TIM 捕获比较 4 过捕获标志
 * @笔记
 * - TIM6 和 TIM7 只能有一个更新标志。
 * - TIM9、TIM12 和 TIM15 只能有 TIM_FLAG_Update、TIM_FLAG_CC1、
 * TIM_FLAG_CC2 或 TIM_FLAG_Trigger。
 * - TIM10、TIM11、TIM13、TIM14、TIM16 和 TIM17 可以有 TIM_FLAG_Update 或 TIM_FLAG_CC1。
 * - TIM_FLAG_Break 仅用于 TIM1、TIM8 和 TIM15。
 * - TIM_FLAG_COM 仅用于 TIM1、TIM8、TIM15、TIM16 和 TIM17。
 * @retval TIM_FLAG 的新状态（SET 或 RESET）。
 */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef *TIMx, uint16_t TIM_FLAG)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_FLAG(TIM_FLAG));

  if ((TIMx->SR & TIM_FLAG) != (uint16_t)RESET)
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
 * @brief 清除 TIMx 的挂起标志。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param TIM_FLAG：指定要清除的标志位。
 * 该参数可以是以下值的任意组合：
 * @arg TIM_FLAG_Update：TIM 更新标志
 * @arg TIM_FLAG_CC1：TIM 捕获比较 1 标志
 * @arg TIM_FLAG_CC2：TIM 捕获比较 2 标志
 * @arg TIM_FLAG_CC3：TIM 捕获比较 3 标志
 * @arg TIM_FLAG_CC4：TIM 捕获比较 4 标志
 * @arg TIM_FLAG_COM: TIM 换向标志
 * @arg TIM_FLAG_Trigger: TIM 触发标志
 * @arg TIM_FLAG_Break: TIM 中断标志
 * @arg TIM_FLAG_CC1OF：TIM 捕获比较 1 过捕获标志
 * @arg TIM_FLAG_CC2OF：TIM 捕获比较 2 过捕获标志
 * @arg TIM_FLAG_CC3OF：TIM 捕获比较 3 过捕获标志
 * @arg TIM_FLAG_CC4OF：TIM 捕获比较 4 过捕获标志
 * @笔记
 * - TIM6 和 TIM7 只能有一个更新标志。
 * - TIM9、TIM12 和 TIM15 只能有 TIM_FLAG_Update、TIM_FLAG_CC1、
 * TIM_FLAG_CC2 或 TIM_FLAG_Trigger。
 * - TIM10、TIM11、TIM13、TIM14、TIM16 和 TIM17 可以有 TIM_FLAG_Update 或 TIM_FLAG_CC1。
 * - TIM_FLAG_Break 仅用于 TIM1、TIM8 和 TIM15。
 * - TIM_FLAG_COM 仅用于 TIM1、TIM8、TIM15、TIM16 和 TIM17。
 * @retval 无
 */
void TIM_ClearFlag(TIM_TypeDef *TIMx, uint16_t TIM_FLAG)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_CLEAR_FLAG(TIM_FLAG));

  /* Clear the flags */
  TIMx->SR = (uint16_t)~TIM_FLAG;
}

/**
 * @brief 检查 TIM 中断是否发生。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param TIM_IT：指定要检查的 TIM 中断源。
 * 此参数可以是以下值之一：
 * @arg TIM_IT_Update：TIM 更新中断源
 * @arg TIM_IT_CC1：TIM 捕捉比较 1 中断源
 * @arg TIM_IT_CC2：TIM 捕捉比较 2 中断源
 * @arg TIM_IT_CC3：TIM 捕捉比较 3 中断源
 * @arg TIM_IT_CC4：TIM 捕捉比较 4 中断源
 * @arg TIM_IT_COM：TIM 换向中断源
 * @arg TIM_IT_Trigger：TIM 触发中断源
 * @arg TIM_IT_Break：TIM 中断中断源
 * @笔记
 * - TIM6 和 TIM7 只能产生更新中断。
 * - TIM9、TIM12 和 TIM15 只能有 TIM_IT_Update、TIM_IT_CC1、
 * TIM_IT_CC2 或 TIM_IT_Trigger。
 * - TIM10、TIM11、TIM13、TIM14、TIM16 和 TIM17 可以具有 TIM_IT_Update 或 TIM_IT_CC1。
 * - TIM_IT_Break 仅用于 TIM1、TIM8 和 TIM15。
 * - TIM_IT_COM 仅用于 TIM1、TIM8、TIM15、TIM16 和 TIM17。
 * @retval TIM_IT 的新状态（SET 或 RESET）。
 */
ITStatus TIM_GetITStatus(TIM_TypeDef *TIMx, uint16_t TIM_IT)
{
  ITStatus bitstatus = RESET;
  uint16_t itstatus = 0x0, itenable = 0x0;
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_IT(TIM_IT));

  itstatus = TIMx->SR & TIM_IT;

  itenable = TIMx->DIER & TIM_IT;
  if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
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
 * @brief 清除 TIMx 的中断挂起位。
 * @param TIMx：其中 x 可以是 1 到 17 以选择 TIM 外设。
 * @param TIM_IT：指定要清除的挂起位。
 * 该参数可以是以下值的任意组合：
 * @arg TIM_IT_Update：TIM1 更新中断源
 * @arg TIM_IT_CC1：TIM 捕捉比较 1 中断源
 * @arg TIM_IT_CC2：TIM 捕捉比较 2 中断源
 * @arg TIM_IT_CC3：TIM 捕捉比较 3 中断源
 * @arg TIM_IT_CC4：TIM 捕捉比较 4 中断源
 * @arg TIM_IT_COM：TIM 换向中断源
 * @arg TIM_IT_Trigger：TIM 触发中断源
 * @arg TIM_IT_Break：TIM 中断中断源
 * @笔记
 * - TIM6 和 TIM7 只能产生更新中断。
 * - TIM9、TIM12 和 TIM15 只能有 TIM_IT_Update、TIM_IT_CC1、
 * TIM_IT_CC2 或 TIM_IT_Trigger。
 * - TIM10、TIM11、TIM13、TIM14、TIM16 和 TIM17 可以具有 TIM_IT_Update 或 TIM_IT_CC1。
 * - TIM_IT_Break 仅用于 TIM1、TIM8 和 TIM15。
 * - TIM_IT_COM 仅用于 TIM1、TIM8、TIM15、TIM16 和 TIM17。
 * @retval 无
 */
void TIM_ClearITPendingBit(TIM_TypeDef *TIMx, uint16_t TIM_IT)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
  /* Clear the IT pending Bit */
  TIMx->SR = (uint16_t)~TIM_IT;
}

/**
 * @brief 将 TI1 配置为输入。
 * @param TIMx：其中 x 可以是 1 到 17，除了 6 和 7 来选择 TIM 外设。
 * @param TIM_ICPolarity ：输入极性。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPolarity_Rising
 * @arg TIM_ICPolarity_Falling
 * @param TIM_ICSelection：指定要使用的输入。
 * 此参数可以是以下值之一：
 * @arg TIM_ICSelection_DirectTI：选择 TIM 输入 1 连接到 IC1。
 * @arg TIM_ICSelection_IndirectTI：选择 TIM 输入 1 连接到 IC2。
 * @arg TIM_ICSelection_TRC：选择 TIM 输入 1 以连接到 TRC。
 * @param TIM_ICFilter：指定输入捕获过滤器。
 * 此参数必须是介于 0x00 和 0x0F 之间的值。
 * @retval 无
 */
static void TI1_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0;
  /* Disable the Channel 1: Reset the CC1E Bit */
  TIMx->CCER &= (uint16_t) ~((uint16_t)TIM_CCER_CC1E);
  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  /* Select the Input and set the filter */
  tmpccmr1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CCMR1_CC1S)) & ((uint16_t) ~((uint16_t)TIM_CCMR1_IC1F)));
  tmpccmr1 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));

  if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) ||
      (TIMx == TIM4) || (TIMx == TIM5))
  {
    /* Select the Polarity and set the CC1E Bit */
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CCER_CC1P));
    tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CCER_CC1E);
  }
  else
  {
    /* Select the Polarity and set the CC1E Bit */
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CCER_CC1P | TIM_CCER_CC1NP));
    tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CCER_CC1E);
  }

  /* Write to TIMx CCMR1 and CCER registers */
  TIMx->CCMR1 = tmpccmr1;
  TIMx->CCER = tmpccer;
}

/**
 * @brief 将 TI2 配置为输入。
 * @param TIMx：其中 x 可以是 1、2、3、4、5、8、9、12 或 15 以选择 TIM 外设。
 * @param TIM_ICPolarity ：输入极性。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPolarity_Rising
 * @arg TIM_ICPolarity_Falling
 * @param TIM_ICSelection：指定要使用的输入。
 * 此参数可以是以下值之一：
 * @arg TIM_ICSelection_DirectTI：选择 TIM 输入 2 连接到 IC2。
 * @arg TIM_ICSelection_IndirectTI：选择 TIM 输入 2 连接到 IC1。
 * @arg TIM_ICSelection_TRC：选择 TIM 输入 2 以连接到 TRC。
 * @param TIM_ICFilter：指定输入捕获过滤器。
 * 此参数必须是介于 0x00 和 0x0F 之间的值。
 * @retval 无
 */
static void TI2_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;
  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= (uint16_t) ~((uint16_t)TIM_CCER_CC2E);
  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 4);
  /* Select the Input and set the filter */
  tmpccmr1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CCMR1_CC2S)) & ((uint16_t) ~((uint16_t)TIM_CCMR1_IC2F)));
  tmpccmr1 |= (uint16_t)(TIM_ICFilter << 12);
  tmpccmr1 |= (uint16_t)(TIM_ICSelection << 8);

  if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) ||
      (TIMx == TIM4) || (TIMx == TIM5))
  {
    /* Select the Polarity and set the CC2E Bit */
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CCER_CC2P));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CCER_CC2E);
  }
  else
  {
    /* Select the Polarity and set the CC2E Bit */
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CCER_CC2P | TIM_CCER_CC2NP));
    tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CCER_CC2E);
  }

  /* Write to TIMx CCMR1 and CCER registers */
  TIMx->CCMR1 = tmpccmr1;
  TIMx->CCER = tmpccer;
}

/**
 * @brief 将 TI3 配置为输入。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ICPolarity ：输入极性。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPolarity_Rising
 * @arg TIM_ICPolarity_Falling
 * @param TIM_ICSelection：指定要使用的输入。
 * 此参数可以是以下值之一：
 * @arg TIM_ICSelection_DirectTI：选择 TIM 输入 3 连接到 IC3。
 * @arg TIM_ICSelection_IndirectTI：选择 TIM 输入 3 连接到 IC4。
 * @arg TIM_ICSelection_TRC：选择 TIM 输入 3 以连接到 TRC。
 * @param TIM_ICFilter：指定输入捕获过滤器。
 * 此参数必须是介于 0x00 和 0x0F 之间的值。
 * @retval 无
 */
static void TI3_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;
  /* Disable the Channel 3: Reset the CC3E Bit */
  TIMx->CCER &= (uint16_t) ~((uint16_t)TIM_CCER_CC3E);
  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 8);
  /* Select the Input and set the filter */
  tmpccmr2 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CCMR2_CC3S)) & ((uint16_t) ~((uint16_t)TIM_CCMR2_IC3F)));
  tmpccmr2 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));

  if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) ||
      (TIMx == TIM4) || (TIMx == TIM5))
  {
    /* Select the Polarity and set the CC3E Bit */
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CCER_CC3P));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CCER_CC3E);
  }
  else
  {
    /* Select the Polarity and set the CC3E Bit */
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CCER_CC3P | TIM_CCER_CC3NP));
    tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CCER_CC3E);
  }

  /* Write to TIMx CCMR2 and CCER registers */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer;
}

/**
 * @brief 将 TI4 配置为输入。
 * @param TIMx：其中 x 可以是 1、2、3、4、5 或 8 以选择 TIM 外设。
 * @param TIM_ICPolarity ：输入极性。
 * 此参数可以是以下值之一：
 * @arg TIM_ICPolarity_Rising
 * @arg TIM_ICPolarity_Falling
 * @param TIM_ICSelection：指定要使用的输入。
 * 此参数可以是以下值之一：
 * @arg TIM_ICSelection_DirectTI：选择 TIM 输入 4 以连接到 IC4。
 * @arg TIM_ICSelection_IndirectTI：选择 TIM 输入 4 连接到 IC3。
 * @arg TIM_ICSelection_TRC：选择 TIM 输入 4 以连接到 TRC。
 * @param TIM_ICFilter：指定输入捕获过滤器。
 * 此参数必须是介于 0x00 和 0x0F 之间的值。
 * @retval 无
 */
static void TI4_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

  /* Disable the Channel 4: Reset the CC4E Bit */
  TIMx->CCER &= (uint16_t) ~((uint16_t)TIM_CCER_CC4E);
  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 12);
  /* Select the Input and set the filter */
  tmpccmr2 &= (uint16_t)((uint16_t)(~(uint16_t)TIM_CCMR2_CC4S) & ((uint16_t) ~((uint16_t)TIM_CCMR2_IC4F)));
  tmpccmr2 |= (uint16_t)(TIM_ICSelection << 8);
  tmpccmr2 |= (uint16_t)(TIM_ICFilter << 12);

  if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) ||
      (TIMx == TIM4) || (TIMx == TIM5))
  {
    /* Select the Polarity and set the CC4E Bit */
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CCER_CC4P));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CCER_CC4E);
  }
  else
  {
    /* Select the Polarity and set the CC4E Bit */
    tmpccer &= (uint16_t) ~((uint16_t)(TIM_CCER_CC3P | TIM_CCER_CC4NP));
    tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CCER_CC4E);
  }
  /* Write to TIMx CCMR2 and CCER registers */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer;
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
