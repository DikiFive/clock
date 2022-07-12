#include "clock.h"
#include "beep.h"
#include "lcd.h"
#include "math.h"
#include "gui.h"
#include "delay.h"
#include "tim1.h"

time clock; //时间表盘结构体
SHOW STime; //时间数显结构体

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
    gui_fill_circle(x, y, r, WHITE);     //画外圈
    gui_fill_circle(x, y, r - 4, BLACK); //画内圈
    for (i = 0; i < 60; i++)             //画秒钟格
    {
        px0 = sx + r + (r - 4) * sin((PI / 30) * i);
        py0 = sy + r - (r - 4) * cos((PI / 30) * i);
        px1 = sx + r + (r - d) * sin((PI / 30) * i);
        py1 = sy + r - (r - d) * cos((PI / 30) * i);
        gui_draw_bline1(px0, py0, px1, py1, 0, GBLUE);
    }
    for (i = 0; i < 12; i++) //画小时格
    {
        px0 = sx + r + (r - 5) * sin((PI / 6) * i);
        py0 = sy + r - (r - 5) * cos((PI / 6) * i);
        px1 = sx + r + (r - d) * sin((PI / 6) * i);
        py1 = sy + r - (r - d) * cos((PI / 6) * i);
        gui_draw_bline1(px0, py0, px1, py1, 2, YELLOW);
    }
    for (i = 0; i < 4; i++) //画3小时格
    {
        px0 = sx + r + (r - 5) * sin((PI / 2) * i);
        py0 = sy + r - (r - 5) * cos((PI / 2) * i);
        px1 = sx + r + (r - d - 3) * sin((PI / 2) * i);
        py1 = sy + r - (r - d - 3) * cos((PI / 2) * i);
        gui_draw_bline1(px0, py0, px1, py1, 2, BRED);
    }
    gui_fill_circle(x, y, d / 2, CYAN); //画中心圈
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
    if (hour > 11)
    {
        hour -= 12; //清除小时
    }
    r1 = d / 2 + 4;
    //清除上一次的数据
    temp = (float)oldmin / 60;
    temp += oldhour;
    px0 = sx + r + (r - 3 * d - 7) * sin((PI / 6) * temp);
    py0 = sy + r - (r - 3 * d - 7) * cos((PI / 6) * temp);
    px1 = sx + r + r1 * sin((PI / 6) * temp);
    py1 = sy + r - r1 * cos((PI / 6) * temp);
    gui_draw_bline1(px0, py0, px1, py1, 2, BLACK);
    //清除分钟
    r1 = d / 2 + 3;
    temp = (float)oldsec / 60;
    temp += oldmin;
    //清除上一次的数据
    px0 = sx + r + (r - 2 * d - 7) * sin((PI / 30) * temp);
    py0 = sy + r - (r - 2 * d - 7) * cos((PI / 30) * temp);
    px1 = sx + r + r1 * sin((PI / 30) * temp);
    py1 = sy + r - r1 * cos((PI / 30) * temp);
    gui_draw_bline1(px0, py0, px1, py1, 1, BLACK);
    //清除秒钟
    r1 = d / 2 + 3;
    //清除上一次的数据
    px0 = sx + r + (r - d - 7) * sin((PI / 30) * oldsec);
    py0 = sy + r - (r - d - 7) * cos((PI / 30) * oldsec);
    px1 = sx + r + r1 * sin((PI / 30) * oldsec);
    py1 = sy + r - r1 * cos((PI / 30) * oldsec);
    gui_draw_bline1(px0, py0, px1, py1, 0, BLACK);
    ///////////////////////////////////////////////
    //显示小时
    r1 = d / 2 + 4;
    //显示新的时钟
    temp = (float)min / 60;
    temp += hour;
    px0 = sx + r + (r - 3 * d - 7) * sin((PI / 6) * temp);
    py0 = sy + r - (r - 3 * d - 7) * cos((PI / 6) * temp);
    px1 = sx + r + r1 * sin((PI / 6) * temp);
    py1 = sy + r - r1 * cos((PI / 6) * temp);
    gui_draw_bline1(px0, py0, px1, py1, 2, BRRED);
    //显示分钟
    r1 = d / 2 + 3;
    temp = (float)sec / 60;
    temp += min;
    //显示新的分钟
    px0 = sx + r + (r - 2 * d - 7) * sin((PI / 30) * temp);
    py0 = sy + r - (r - 2 * d - 7) * cos((PI / 30) * temp);
    px1 = sx + r + r1 * sin((PI / 30) * temp);
    py1 = sy + r - r1 * cos((PI / 30) * temp);
    gui_draw_bline1(px0, py0, px1, py1, 1, LIGHTGREEN);
    //显示秒钟
    r1 = d / 2 + 3;
    //显示新的秒钟
    px0 = sx + r + (r - d - 7) * sin((PI / 30) * sec);
    py0 = sy + r - (r - d - 7) * cos((PI / 30) * sec);
    px1 = sx + r + r1 * sin((PI / 30) * sec);
    py1 = sy + r - r1 * cos((PI / 30) * sec);
    gui_draw_bline1(px0, py0, px1, py1, 0, MAGENTA);
    oldhour = hour; //保存时
    oldmin = min;   //保存分
    oldsec = sec;   //保存秒
    //零点置零
    if (clock.sec == 86400)
    {
        clock.sec = 0;
    }
}

/**
 * @brief 时钟显示
 * @param r 半径
 * @param d 秒钟高度
 */
u8 clock_play(u16 r, u8 d)
{
    clock_showtime(120, 80, r * 2, d, clock.hour, clock.min, clock.sec); //指针时钟显示时间
}
