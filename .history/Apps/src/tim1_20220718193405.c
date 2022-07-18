#include "tim1.h"
#include "clock.h"
#include "key.h"
#include "lcd.h"

/**
 * @brief  定时器用户设置
 * @param  Period 分频值
 * @param  Prescaler 预分频值
 * @retval 无
 */
void TIM_UserConfig(u16 Period, u16 Prescaler)
{
    TIM_TimeBaseInitTypeDef TIM_InitStructure; //定时器参数结构体
    NVIC_InitTypeDef NVIC_InitStructure;       //中断优先级结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    TIM_InitStructure.TIM_Period = Period;
    TIM_InitStructure.TIM_Prescaler = Prescaler;
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_InitStructure);

    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    TIM_ITConfig(TIM1, TIM_IT_Update | TIM_IT_Trigger, ENABLE);
    TIM_Cmd(TIM1, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  定时器中断
 * @retval 无
 */
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        clock.temp++;
        if (clock.temp % 2 == 0)
        {
            clock.temp = 0;
            clock.sec++;
            clock_set();
            if (clock.count == 1)
            {
                clock.down++;
            }
        }
        clock.time_FlashFlag = !clock.time_FlashFlag;
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}
