#include "sys.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"
#include "beep.h"
#include "usart.h"
#include "clock.h"
#include "gui.h"
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"
#include "key.h"
#include "colors.h"
#include "remote.h"
#include "tpad.h"
#include "hanzi.h"

void Time_set();

int main(void)
{
	TIM_UserConfig(1000 - 1, 7200 - 1);				//定时器TIM1初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);								//串口初始化为9600

	delay_init();  //延时函数初始化
	Beep_int();	   //蜂鸣器初始化
	LED_Init();	   // LED端口初始化
	LCD_Init();	   // LCD初始化
	KEY_Init();	   // KEY按键初始化
	Remote_Init(); //红外接收初始化
	TPAD_Init(6);  //初始化触摸按键

	LCD_Clear(PINK);									   //粉色背景清屏
	BACK_COLOR = PINK;									   //粉色背景色
	clock_draw_panel(120, 100, 80 * 2, 16);				   //显示指针时钟表盘
	clock_draw_frame(240, 320, Chocolates, Mint_Cream);	   //显示时钟边框
	gui_flower(95, 183, 144, 209, 8, Fresh_meat, scarlet); //花框
	LCD_ShowString(104, 190, 96, 16, 16, "DKFV");		   //作者信息
	// LCD_ShowString(104, 210, 96, 16, 16, "中国制造");//中文显示
	while (1)
	{
		kn.Num = KEY_Scan(0); //获取按键码
		kn.IR = Remote_Scan();
		RmtRec = 0;
		kn.wk_up = KUP_Scan(); //获取wk——up键码状态

		if (kn.IR == zero)
		{
			gui_fill_circle(120, 100, 16 / 2, PINK);
		}

		if (kn.wk_up == DOUBLE_PRES || kn.IR == POWER || kn.Num == KEY1_PRES)
		{
			if (clock.time_flag == 0)
			{
				gui_fill_circle(120, 100, 16 / 2, PINK);
				clock.time_flag = 1;
				clock.time_select = 0;
			}
			else if (clock.time_flag == 1)
			{
				clock.time_flag = 0;
				gui_fill_circle(120, 100, 16 / 2, BLUE); //画中心圈
			}
		}

		switch (clock.time_flag)
		{
		case 0:
			break;
		case 1:
			Time_set();
			break;
		}

		if (kn.Num == KEY0_PRES || kn.IR == RPT || TPAD_Scan(0)) //当key0按下||红外按下RPT||成功捕获到了一次上升沿(此函数执行时间至少15ms)
		{
			clock.count++; //特征码自增
			if (clock.count > 1)
			{
				clock.count = 0; //特征码置零
			}
		}
		if (clock.count == 1)
		{
			clock_countdown(3, 1);
			gui_fill_circle(120, 100, 16 / 2, RED); //画中心圈
		}
		else
		{
			LED0 = 1;
			LED1 = 1;
			clock.down = 0;							 //计时器置零
			gui_fill_circle(120, 100, 16 / 2, BLUE); //画中心圈
		}
		clock_play(120, 100, 80, 16);									 //时钟表盘显示
		clock_NumShow(clock.hour, clock.min, clock.sec, GRAY, 120, 214); //数显时间

		// ShowCn(120, 250, 16, 1, 1);
	}
}

/**
 * @brief 时间设置
 */
void Time_set()
{
	if (kn.IR == Mforward)
	{
		gui_fill_circle(120, 100, 16 / 2, PINK); //画中心圈
		clock.time_select++;
		clock.time_select %= 3;
	}
	if (kn.wk_up == KUP_PRES || kn.IR == VOLA)
	{
		switch (clock.time_select)
		{
		case 0:
			clock.hour++;
			clock_set();
			break;
		case 1:
			clock.min++;
			clock_set();
			break;
		case 2:
			clock.sec++;
			clock_set();
			break;
		}
	}
	//更新显示，根据clock.time_select和clock.time_FlashFlag判断可完成闪烁功能
	if (clock.time_select == 0 && clock.time_FlashFlag == 1)
	{
		gui_draw_arcrectangle(120, 214, 32, 16, 5, 1, PINK, PINK);
	}
	else
	{
		clock_NumShow(clock.hour, clock.min, clock.sec, GRAY, 120, 214); //数显时间
	}
	if (clock.time_select == 1 && clock.time_FlashFlag == 1)
	{
		gui_draw_arcrectangle(152, 214, 32, 16, 5, 1, PINK, PINK);
	}
	else
	{
		clock_NumShow(clock.hour, clock.min, clock.sec, GRAY, 120, 214); //数显时间
	}
	if (clock.time_select == 2 && clock.time_FlashFlag == 1)
	{
		gui_draw_arcrectangle(184, 214, 32, 16, 5, 1, PINK, PINK);
	}
	else
	{
		clock_NumShow(clock.hour, clock.min, clock.sec, GRAY, 120, 214); //数显时间
	}
}