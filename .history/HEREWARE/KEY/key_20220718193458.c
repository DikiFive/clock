#include "stm32f10x.h"
#include "key.h"
#include "sys.h"
#include "delay.h"

Key_Tag skey;

/**
 * @brief 按键初始化函数
 */
void KEY_Init(void) // IO初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE); //使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3; // KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		   //设置成上拉输入
	GPIO_Init(GPIOE, &GPIO_InitStructure);				   //初始化GPIOE4,3

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // PA0设置成输入，默认下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);		  //初始化GPIOA.0
}

/**
 * @brief 按键处理函数
// 0，没有任何按键按下
// 1，wk_up单击
// 2，wk_up长按
// 3，WK_UP双击
 */
u8 KUP_Scan()
{
	static u8 press = 0;

	if (WK_UP == 1) //按键按下
	{
		delay_ms(10);	//消抖
		if (WK_UP == 1) //按下按键
		{
			if (skey.u8key_flag == 0)
			{
				skey.u8key_flag = 1; //第一次按下，标志位置1。同时计数值归零
				skey.u32time1 = 0;
			}
			else if (skey.u8key_flag == 1)
			{
				if (!press && skey.u32time1 > 6) //如果第一次按下且时间超过3S，视为长按
				{
					press = 1;
					return LONG_PRES; //返回长按键值
				}
			}
		}
	}
	else if (WK_UP == 0) //按键松开
	{
		if (skey.u8key_flag == 1) //第一次按键松开
		{
			skey.u8key_flag = 0;
			if (skey.u32time1 > ) //按下后超过3秒才松开，已经返回了键值，松手后把标志位都归零
			{
				press = 0;
				skey.u32time1 = 0;
				skey.u32time2 = 0;
				skey.u8key_flag = 0;
				skey.u8key_double_flag = 0;
			}
			else if (skey.u8key_double_flag == 0)
			{
				skey.u8key_double_flag = 1; //第一次松开之后标志位置1开始等待第二次按键松开
				skey.u32time2 = 0;
			}
			else if (skey.u8key_double_flag == 1)
			{
				if (skey.u32time2 < 500) //如果第二次松开时间间隔小于0.5S，视为双击
				{
					skey.u8key_double_flag = 0;
					return DOUBLE_PRES;
				}
			}
		}
		else if (skey.u8key_double_flag == 1)
		{
			if (skey.u32time2 >= 500)
			{
				skey.u8key_double_flag = 0;

				return KUP_PRES; //如果第一次松开之后0.5s没有第二次按键操作，视为短按
			}
		}
	}
	return 0; //没有按键按下返回0
}

/**
 * @brief 按键处理函数
 * @param mode:0,不支持连续按;1,支持连续按;
// 0，没有任何按键按下
// 1，KEY0按下
// 2，KEY1按下
// 3，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY_UP!!
 */
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1; //按键按松开标志
	if (mode)
		key_up = 1; //支持连按
	if (key_up && (KEY0 == 0 || KEY1 == 0 || WK_UP == 1))
	{
		delay_ms(10); //去抖动
		key_up = 0;
		if (KEY0 == 0)
			return KEY0_PRES;
		else if (KEY1 == 0)
			return KEY1_PRES;
		else if (WK_UP == 1)
			return WKUP_PRES;
	}
	else if (KEY0 == 1 && KEY1 == 1 && WK_UP == 0)
		key_up = 1;
	return 0; // 无按键按下
}
