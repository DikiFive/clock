#include "clock.h"
#include "beep.h"
#include "lcd.h"
#include "math.h"
#include "gui.h"
#include "delay.h"
#include "tim1.h"
#include "led.h"
#include "colors.h"
#include "usart.h"

time clock; //时间表盘结构体
KEY kn;
MOD mode;

/**
 * @brief  闹钟响铃
 * @param  type 响应次数
 * @retval 无
 */
void clock_alarm_ring(u8 type)
{
    u8 i;
    for (i = 0; i < (type + 1); i++)
    {
        BEEP = 1;
        delay_ms(50);
        BEEP = 0;
        delay_ms(70);
    }
}

/**
 * @brief  计时器响铃
 * @param  type 响应次数
 * @param  time 定时时间*分钟
 * @retval 无
 */
void clock_countdown(u8 type, u8 time)
{
    if (clock.down == (time * 60))
    {
        clock.down = 0;
        u8 i;
        for (i = 0; i < (type + 1); i++)
        {
            BEEP = 1;
            LED0 = 1;
            LED1 = 0;
            delay_ms(50);
            BEEP = 0;
            LED0 = 0;
            LED1 = 1;
            delay_ms(70);
        }
    }
}

/**
 * @brief  画圆形指针表盘
 * @param  x 坐标中心点
 * @param  y 坐标中心点
 * @param  size 直径（表盘大小）
 * @param  d 秒钟的高度，表盘分割
 * @retval 无
 */
void clock_draw_panel(u16 x, u16 y, u16 size, u16 d)
{
    u16 r = size / 2; //得到半径
    u16 sx = x - r;
    u16 sy = y - r;
    u16 px0, px1;
    u16 py0, py1;
    u16 i;
    gui_fill_circle(x, y, r, Chocolates);       //画外圈
    gui_fill_circle(x, y, r - 4, Light_yellow); //画内圈
    for (i = 0; i < 60; i++)                    //画秒钟格
    {
        px0 = sx + r + (r - 4) * sin((PI / 30) * i);
        py0 = sy + r - (r - 4) * cos((PI / 30) * i);
        px1 = sx + r + (r - d) * sin((PI / 30) * i);
        py1 = sy + r - (r - d) * cos((PI / 30) * i);
        gui_draw_bline1(px0, py0, px1, py1, 0, DARKBLUE);
    }
    for (i = 0; i < 12; i++) //画小时格
    {
        px0 = sx + r + (r - 5) * sin((PI / 6) * i);
        py0 = sy + r - (r - 5) * cos((PI / 6) * i);
        px1 = sx + r + (r - d) * sin((PI / 6) * i);
        py1 = sy + r - (r - d) * cos((PI / 6) * i);
        gui_draw_bline1(px0, py0, px1, py1, 2, BRRED);
    }
    for (i = 0; i < 4; i++) //画3小时格
    {
        px0 = sx + r + (r - 5) * sin((PI / 2) * i);
        py0 = sy + r - (r - 5) * cos((PI / 2) * i);
        px1 = sx + r + (r - d - 3) * sin((PI / 2) * i);
        py1 = sy + r - (r - d - 3) * cos((PI / 2) * i);
        gui_draw_bline1(px0, py0, px1, py1, 2, LIGHTBLUE);
    }
    gui_fill_circle(x, y, d / 2, BLUE); //画中心圈
}

/**
 * @brief  显示时间
 * @param  x 坐标中心点
 * @param  y 坐标中心点
 * @param  size 直径（表盘大小）
 * @param  d 秒钟的高度，表盘分割
 * @param  hour 时钟
 * @param  min 分钟
 * @param  sec 秒钟
 * @retval 无
 */
void clock_showtime(u16 x, u16 y, u16 size, u16 d, u8 hour, u8 min, u8 sec)
{
    static u8 oldhour = 0; //最近一次进入该函数的时分秒信息
    static u8 oldmin = 0;  //最近一次进入该函数的时分秒信息
    static u8 oldsec = 0;  //最近一次进入该函数的时分秒信息
    float temp;            //缓冲值
    u16 r = size / 2;      //得到半径
    u16 sx = x - r;        //相对坐标轴原点
    u16 sy = y - r;        //相对坐标轴原点
    u16 px0, px1;          //起点，终点的x轴
    u16 py0, py1;          //起点，终点的y轴
    u8 r1;
    if (clock.sec != oldsec)
    {
        r1 = d / 2 + 3;
        //清除上一次的数据
        temp = (float)oldmin / 60;
        temp += oldhour;
        px0 = sx + r + (r - 3 * d - 7) * sin((PI / 6) * temp);
        py0 = sy + r - (r - 3 * d - 7) * cos((PI / 6) * temp);
        px1 = sx + r + r1 * sin((PI / 6) * temp);
        py1 = sy + r - r1 * cos((PI / 6) * temp);
        gui_draw_bline1(px0, py0, px1, py1, 2, Light_yellow);
        //清除分钟
        r1 = d / 2 + 3;
        temp = (float)oldsec / 60;
        temp += oldmin;
        //清除上一次的数据
        px0 = sx + r + (r - 2 * d - 7) * sin((PI / 30) * temp);
        py0 = sy + r - (r - 2 * d - 7) * cos((PI / 30) * temp);
        px1 = sx + r + r1 * sin((PI / 30) * temp);
        py1 = sy + r - r1 * cos((PI / 30) * temp);
        gui_draw_bline1(px0, py0, px1, py1, 1, Light_yellow);
        //清除秒钟
        r1 = d / 2 + 3;
        //清除上一次的数据
        px0 = sx + r + (r - d - 7) * sin((PI / 30) * oldsec);
        py0 = sy + r - (r - d - 7) * cos((PI / 30) * oldsec);
        px1 = sx + r + r1 * sin((PI / 30) * oldsec);
        py1 = sy + r - r1 * cos((PI / 30) * oldsec);
        gui_draw_bline1(px0, py0, px1, py1, 0, Light_yellow);
        ///////////////////////////////////////////////
        //显示小时
        r1 = d / 2 + 3;
        //显示新的时钟
        temp = (float)min / 60;
        temp += hour;
        px0 = sx + r + (r - 3 * d - 7) * sin((PI / 6) * temp);
        py0 = sy + r - (r - 3 * d - 7) * cos((PI / 6) * temp);
        px1 = sx + r + r1 * sin((PI / 6) * temp);
        py1 = sy + r - r1 * cos((PI / 6) * temp);
        gui_draw_bline1(px0, py0, px1, py1, 2, BROWN);
        //显示分钟
        r1 = d / 2 + 3;
        temp = (float)sec / 60;
        temp += min;
        //显示新的分钟
        px0 = sx + r + (r - 2 * d - 7) * sin((PI / 30) * temp);
        py0 = sy + r - (r - 2 * d - 7) * cos((PI / 30) * temp);
        px1 = sx + r + r1 * sin((PI / 30) * temp);
        py1 = sy + r - r1 * cos((PI / 30) * temp);
        gui_draw_bline1(px0, py0, px1, py1, 1, BLACK);
        //显示秒钟
        r1 = d / 2 + 3;
        //显示新的秒钟
        px0 = sx + r + (r - d - 7) * sin((PI / 30) * sec);
        py0 = sy + r - (r - d - 7) * cos((PI / 30) * sec);
        px1 = sx + r + r1 * sin((PI / 30) * sec);
        py1 = sy + r - r1 * cos((PI / 30) * sec);
        gui_draw_bline1(px0, py0, px1, py1, 0, RED);
        oldhour = hour; //保存时
        oldmin = min;   //保存分
        oldsec = sec;   //保存秒
    }
}

/**
 * @brief  摆钟
 * @param  x 坐标中心点
 * @param  y 坐标中心点
 * @param  size 直径（表盘大小）
 * @param  d 秒钟的高度，表盘分割
 * @param  sec 秒钟
 * @retval 无
 */
void clock_swing(u16 x, u16 y, u16 size, u16 d, u8 sec)
{
    static u8 oldsec = 0; //最近一次进入该函数的时分秒信息
    float temp;           //缓冲值
    u16 r = size / 2;     //得到半径
    u16 sx = x - r;       //相对坐标轴原点
    u16 sy = y - r;       //相对坐标轴原点
    u16 px0, px1;         //起点，终点的x轴
    u16 py0, py1;         //起点，终点的y轴
    u8 r1;
    if (clock.sec != oldsec)
    {
        //清除秒钟
        r1 = d / 2 + 3;
        //清除上一次的数据
        px0 = sx + r + (r - d - 7) * sin((PI / 30) * oldsec);
        py0 = sy + r - (r - d - 7) * cos((PI / 30) * oldsec);
        px1 = sx + r + r1 * sin((PI / 30) * oldsec);
        py1 = sy + r - r1 * cos((PI / 30) * oldsec);
        gui_draw_bline1(px0, py0, px1, py1, 0, WHITE);

        //显示秒钟
        r1 = d / 2 + 3;
        //显示新的秒钟
        px0 = sx + r + (r - d - 7) * sin((PI / 30) * sec);
        py0 = sy + r - (r - d - 7) * cos((PI / 30) * sec);
        px1 = sx + r + r1 * sin((PI / 30) * sec);
        py1 = sy + r - r1 * cos((PI / 30) * sec);
        gui_draw_bline1(px0, py0, px1, py1, 0, RED);
        oldsec = sec; //保存秒
    }
}

/**
 * @brief 时钟数显
 * @param hour 小时
 * @param min 分钟
 * @param sec 秒
 * @param color 颜色
 * @param x 左上角
 * @param y 左上角
 */
void clock_NumShow(u8 hour, u8 min, u8 sec, u16 color, u16 x, u16 y)
{
    POINT_COLOR = color;
    LCD_ShowxNum(x - 40, y, hour, 2, 16, 0x80);
    LCD_ShowString(x - 20, y, 16, 16, 16, ":");
    LCD_ShowxNum(x - 10, y, min, 2, 16, 0x80);
    LCD_ShowString(x + 10, y, 16, 16, 16, ":");
    LCD_ShowxNum(x + 20, y, sec, 2, 16, 0x80);
}

/**
 * @brief 时钟边框
 * @param width 宽
 * @param height 高
 * @param color1 颜色
 * @param color2 颜色
 */
void clock_draw_frame(u16 width, u16 height, u16 color1, u16 color2)
{
    gui_flower(0, 0, width, height, 10, color1, color2);
}

/**
 * @brief 表盘皮肤
 * @param x 坐标中心点
 * @param y 坐标中心点
 * @param color1 颜色
 * @param color2 颜色
 */
void clock_skin(u16 x, u16 y, u16 color1, u16 color2)
{
}

/**
 * @brief 时钟进制
 */
void clock_set()
{
    if (clock.sec >= 60)
    {
        clock.sec = 0;
        clock.min++;
    }
    if (clock.min >= 60)
    {
        clock.min = 0;
        clock.hour++;
    }
    if (clock.hour > 23)
    {
        clock.hour -= 24;
    }
}

/**
 * @brief 时钟显示
 * @param x 坐标中心点
 * @param y 坐标中心点
 * @param r 半径
 * @param d 秒钟高度
 */
u8 clock_play(u16 x, u16 y, u16 r, u8 d)
{
    clock_showtime(x, y, r * 2, d, clock.hour, clock.min, clock.sec); //指针时钟显示时间
    if (USART_RX_STA & 0x8000)
    {
        mode.len = USART_RX_STA & 0x3fff; //得到此次接收到的数据长度
        printf("\r\n修改的时间为:\r\n");
        if (USART_RX_BUF[2] == '-')
        {
            clock.hour = (USART_RX_BUF[1] - '0') + (USART_RX_BUF[0] - '0') * 10;
        }

        if (USART_RX_BUF[5] == '-')
        {
            clock.min = (USART_RX_BUF[4] - '0') + (USART_RX_BUF[3] - '0') * 10;
        }

        clock.sec = (USART_RX_BUF[7] - '0') + (USART_RX_BUF[6] - '0') * 10;

        if (USART_RX_BUF[2] != '-' || USART_RX_BUF[5] != '-')
        {
            mode.flag = 1;
        }
        while ((USART1->SR & 0X40) == 0)
            ; //等待发送结束
        if (mode.flag == 1)
        {
            printf("error");
            mode.flag = 0;
        }
        else
        {
            printf("\r\n\r\n"); //插入换行
            USART_RX_STA = 0;
        }
    }
}
