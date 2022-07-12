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
	u8 lcd_id[12];
	TIM_UserConfig(u16 Period, u16 Prescaler)		//存放LCD ID字符串
		delay_init();								//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);								//串口初始化为115200
	LED_Init();										// LED端口初始化
	LCD_Init();
	usmart_dev.init(SystemCoreClock / 10000000);
	LCD_Clear(BLACK);
	sprintf((char *)lcd_id, "LCD ID:%04X", lcddev.id); //将LCD ID打印到lcd_id数组。
	while (1)
	{
		clock_play();
	}
}
