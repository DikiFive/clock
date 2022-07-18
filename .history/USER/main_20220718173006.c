#include "sys.h"	//系统头文件（库函数）
#include "delay.h"	//延时
#include "led.h"	//LED灯
#include "lcd.h"	//TFT——LCD
#include "beep.h"	//蜂鸣器
#include "usart.h"	//串口
#include "clock.h"	//时钟相关函数
#include "gui.h"	//gui用户图层
#include "24cxx.h"	//24CXX驱动函数
#include "w25qxx.h" //W25QXX芯片
#include "touch.h"	//触摸屏
#include "key.h"	//独立按键
#include "colors.h" //颜色
#include "remote.h" //红外
#include "tpad.h"	//触摸按键
#include "tim1.h"	//定时器1
//声明函数
void Time_set();
//主函数入口
int main(void)
{
	//中断、定时、串口初始化
	TIM_UserConfig(10000 - 1, 7200 - 1);			//定时器TIM1初始化
	// TIM3_Int_Init(10 - 1, 7200 - 1);				//定时器TIM3初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);								//串口初始化为9600

	//相关函数初始化
	delay_init();  //延时函数初始化
	Beep_int();	   //蜂鸣器初始化
	LED_Init();	   // LED端口初始化
	LCD_Init();	   // LCD初始化
	KEY_Init();	   // KEY按键初始化
	Remote_Init(); //红外接收初始化
	TPAD_Init(6);  //触摸按键初始化
	tp_dev.init(); //触摸屏初始化

	//时钟表盘
	LCD_Clear(PINK);									   //粉色背景清屏
	BACK_COLOR = PINK;									   //粉色背景色
	clock_draw_panel(120, 100, 80 * 2, 16);				   //显示指针时钟表盘
	clock_draw_frame(240, 320, Chocolates, Mint_Cream);	   //显示时钟边框
	gui_flower(95, 183, 144, 209, 8, Fresh_meat, scarlet); //花框
	LCD_ShowString(104, 190, 96, 16, 16, "DKFV");		   //作者信息
	ShowCn(80, 235, 16, 0, 1);							   //显示汉字“时”
	ShowCn(110, 235, 16, 3, 1);							   //显示汉字“分”
	ShowCn(140, 235, 16, 5, 1);							   //显示汉字“秒”

	//按钮图标
	gui_draw_arcrectangle(10, 290, 80, 20, 10, 1, scarlet, scarlet); //减少位图标
	// LCD_ShowChar(46, 290, '-', 16, 1);										   //减少位图标
	gui_draw_arcrectangle(90, 290, 60, 20, 10, 1, Dark_emerald, Dark_emerald); //选择位图标
	// LCD_ShowChar(116, 290, '*', 16, 1);										   //选择位图标
	gui_draw_arcrectangle(150, 290, 80, 20, 10, 1, scarlet, scarlet); //增加位图标
	// LCD_ShowChar(186, 290, '+', 16, 1);										   //增加位图标
	while (1)
	{
		//触屏特征码
		static u8 TC_flag = 1;
		//获取键码位
		kn.Num = KEY_Scan(0);  //获取按键码
		kn.IR = Remote_Scan(); //获取红外键码
		kn.wk_up = KUP_Scan(); //获取wk——up键码状态
							   // wk_up按键功能
		if (kn.wk_up == LONG_PRES)
		{
			clock.hour++;
		}
		if (kn.wk_up == DOUBLE_PRES)
		{
			clock.min++;
		}
		if (kn.wk_up == KUP_PRES)
		{
			clock.hour--;
		}
		//返回功能
		if (TPAD_Scan(0) || kn.IR == POWER) //按下触摸按钮或者红外POWER键位相当于返回
		{
			TC_flag = 0;
			RmtSta = 0;
			clock.time_select = 0;
			clock.time_flag = !clock.time_flag;
		}
		//触摸屏相关操作函数
		tp_dev.scan(0);				   //扫描触摸屏
		if (tp_dev.sta & TP_PRES_DOWN) //触摸屏被按下
		{
			if (((tp_dev.x[0] < 90) && (tp_dev.x[0] > 10)) && ((tp_dev.y[0] < 310) && (tp_dev.y[0] > 290)) && TC_flag == 1)
			{
				TC_flag = 0;											   //置零特征码
				gui_draw_arcrectangle(10, 290, 80, 20, 10, 1, BLUE, BLUE); //减少位图标
				switch (clock.time_select)								   //对选择位进行判断
				{
				case 1:
					clock.hour--;
					break;
				case 2:
					clock.min--;
					break;
				case 3:
					clock.sec--;
					break;
				}
			}
			if (((tp_dev.x[0] < 150) && (tp_dev.x[0] > 90)) && ((tp_dev.y[0] < 310) && (tp_dev.y[0] > 290)) && TC_flag == 1)
			{
				TC_flag = 0;											 //置零特征码
				gui_draw_arcrectangle(90, 290, 60, 20, 10, 1, RED, RED); //选择位图标
				clock.time_select++;
				clock.time_select %= 4; //防止越界
			}
			if (((tp_dev.x[0] < 230) && (tp_dev.x[0] > 150)) && ((tp_dev.y[0] < 310) && (tp_dev.y[0] > 290)) && TC_flag == 1)
			{
				TC_flag = 0;												//置零特征码
				gui_draw_arcrectangle(150, 290, 80, 20, 10, 1, BLUE, BLUE); //增加位图标
				switch (clock.time_select)									//对选择位进行判断
				{
				case 1:
					clock.hour++;
					break;
				case 2:
					clock.min++;
					break;
				case 3:
					clock.sec++;
					break;
				}
			}
		}
		else
		{
			TC_flag = 1;
			gui_draw_arcrectangle(10, 290, 80, 20, 10, 1, scarlet, scarlet);		   //减少位图标
			gui_draw_arcrectangle(90, 290, 60, 20, 10, 1, Dark_emerald, Dark_emerald); //选择位图标
			gui_draw_arcrectangle(150, 290, 80, 20, 10, 1, scarlet, scarlet);		   //增加位图标									   //增加位图标
		}
		//红外修改时间123加456减
		if (kn.IR == One)
		{
			RmtSta = 0;
			clock.hour++;
		}
		if (kn.IR == Four)
		{
			RmtSta = 0;
			if (clock.hour != 0)
			{
				clock.hour--;
			}
			else
			{
				clock.hour = 23;
			}
		}
		if (kn.IR == Two)
		{
			RmtSta = 0;
			clock.min++;
		}
		if (kn.IR == Five)
		{
			RmtSta = 0;
			if (clock.min != 0)
			{
				clock.min--;
			}
			else
			{
				clock.min = 59;
			}
		}
		if (kn.IR == Three)
		{
			RmtSta = 0;
			clock.sec++;
		}
		if (kn.IR == Six)
		{
			RmtSta = 0;
			if (clock.sec != 0)
			{
				clock.sec--;
			}
			else
			{
				clock.sec = 59;
			}
		}
		//判断按键修改时间模式
		switch (clock.time_flag)
		{
		case 0:
			break;
		case 1:
			Time_set();
			gui_fill_circle(120, 100, 16 / 2, PINK); //画中心圈
			break;
		}
		//倒计时一分钟功能判断
		if (kn.Num == KEY0_PRES || kn.IR == RPT) //当key0按下||红外按下RPT
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
		//时间显示
		clock_play(120, 100, 80, 16);									 //时钟表盘显示
		clock_NumShow(clock.hour, clock.min, clock.sec, GRAY, 120, 214); //数显时间
	}
}

/**
 * @brief 时间设置
 */
void Time_set()
{
	if (kn.wk_up == 0)
	{
		gui_fill_circle(120, 100, 16 / 2, PINK); //画中心圈
		clock.time_select++;
		clock.time_select %= 4;
	}

	if (kn.wk_up == VOLA)
	{
		switch (clock.time_select)
		{
		case 1:
			clock.hour++;
			clock_set();
			break;
		case 2:
			clock.min++;
			clock_set();
			break;
		case 3:
			clock.sec++;
			clock_set();
			break;
		}
	}

	if (kn.wk_up == VOLD)
	{
		switch (clock.time_select)
		{
		case 1:
			clock.hour++;
			clock_set();
			break;
		case 2:
			clock.min++;
			clock_set();
			break;
		case 3:
			clock.sec++;
			clock_set();
			break;
		}
	}
	//更新显示，根据clock.time_select和clock.time_FlashFlag判断可完成闪烁功能
	if (clock.time_select == 1 && clock.time_FlashFlag == 1)
	{
		gui_draw_bline1(80, 230, 100, 230, 1, BLACK);
	}
	else
	{
		gui_draw_bline1(80, 230, 100, 230, 1, PINK);
	}
	if (clock.time_select == 2 && clock.time_FlashFlag == 1)
	{
		gui_draw_bline1(110, 230, 130, 230, 1, BLACK);
	}
	else
	{
		gui_draw_bline1(110, 230, 130, 230, 1, PINK);
	}
	if (clock.time_select == 3 && clock.time_FlashFlag == 1)
	{
		gui_draw_bline1(140, 230, 160, 230, 1, BLACK);
	}
	else
	{
		gui_draw_bline1(140, 230, 160, 230, 1, PINK);
	}
}