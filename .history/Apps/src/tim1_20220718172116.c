#include "tim1.h"
#include "clock.h"
#include "key.h"
#include "lcd.h"
#include "led.h"
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
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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
        clock.sec++;
        clock_set();
        skey.u32time1++;
        skey.u32time2++;
        if (clock.count == 1)
        {
            clock.down++;
        }
        clock.time_FlashFlag = !clock.time_FlashFlag;
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}
void TIM3_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //Ê±ÖÓÊ¹ÄÜ

    //¶¨Ê±Æ÷TIM3³õÊ¼»¯
    TIM_TimeBaseStructure.TIM_Period = arr;                     //ÉèÖÃÔÚÏÂÒ»¸ö¸üÐÂÊÂ¼þ×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ýÊýµÄÔ¤·ÖÆµÖµ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIMÏòÉÏ¼ÆÊýÄ£Ê½
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊýµ¥Î»

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //Ê¹ÄÜÖ¸¶¨µÄTIM3ÖÐ¶Ï,ÔÊÐí¸üÐÂÖÐ¶Ï

    //ÖÐ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           // TIM3ÖÐ¶Ï
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //´ÓÓÅÏÈ¼¶3¼¶
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQÍ¨µÀ±»Ê¹ÄÜ
    NVIC_Init(&NVIC_InitStructure);                           //³õÊ¼»¯NVIC¼Ä´æÆ÷

    TIM_Cmd(TIM3, ENABLE); //Ê¹ÄÜTIMx
}
//TIM3中断
void TIM3_IRQHandler(void) 
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //¼ì²éTIM3¸üÐÂÖÐ¶Ï·¢ÉúÓë·ñ
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //Çå³ýTIMx¸üÐÂÖÐ¶Ï±êÖ¾
        LED1 = !LED1;
    }
}
