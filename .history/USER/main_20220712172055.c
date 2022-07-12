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
	Beep_int();
	u8 x = 0;
	u8 lcd_id[12]; //存放LCD ID字符串
	TIM_UserConfig(10000 - 1, 7200 - 1);
	delay_init();									//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);								//串口初始化为115200
	LED_Init();										// LED端口初始化
	LCD_Init();
	usmart_dev.init(SystemCoreClock / 10000000);
	LCD_Clear(BLACK);
	sprintf((char *)lcd_id, "LCD ID:%04X", lcddev.id); //将LCD ID打印到lcd_id数组。
	clock_draw_panel(120, 80, 80 * 2, 8);			   //显示指针时钟表盘
	while (1)
	{
		clock_play();
	}
}
