#include "sys.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"
#include "beep.h"
#include "usmart.h"
#include "usart.h"
#include "clock.h"

int main(void)
{
	Beep_int();										//蜂鸣器初始化
	TIM_UserConfig(10000 - 1, 7200 - 1);			//定时器TIM1初始化
	delay_init();									//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);								//串口初始化为115200
	LED_Init();										// LED端口初始化
	LCD_Init();										// LCD初始化
	usmart_dev.init(SystemCoreClock / 10000000);
	LCD_Clear(WHITE);						 //黑色背景清屏
	clock_draw_panel(120, 100, 80 * 2, 16);	 //显示指针时钟表盘
	clock_draw_frame(240, 320, RED, YELLOW); //显示时钟边框
	gui_flower(99, 185, 141, 206, 5, RED, BLACK);
	LCD_ShowString(104, 190, 96, 16, 16, "DKFV");
	// LCD_ShowString(104, 210, 96, 16, 16, "中国制造");
	while (1)
	{
		clock_play(120, 100, 80, 16);
	}
}
