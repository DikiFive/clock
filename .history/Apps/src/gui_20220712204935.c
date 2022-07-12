#include "gui.h"
#include "lcd.h"

/**
 * @brief  画实心圆
 * @param  x0 坐标
 * @param  y0 坐标
 * @param  r 半径
 * @param  color 颜色
 * @retval 无
 */
void gui_fill_circle(u16 x0, u16 y0, u16 r, u16 color)
{
    u32 i;
    u32 imax = ((u32)r * 707) / 1000 + 1;
    u32 sqmax = (u32)r * (u32)r + (u32)r / 2;
    u32 x = r;
    gui_draw_hline(x0 - r, y0, 2 * r, color);
    for (i = 1; i <= imax; i++)
    {
        if ((i * i + x * x) > sqmax)
        {
            // 在外圈画线
            if (x > imax)
            {
                gui_draw_hline(x0 - i + 1, y0 + x, 2 * (i - 1), color);
                gui_draw_hline(x0 - i + 1, y0 - x, 2 * (i - 1), color);
            }
            x--;
        }
        //在中心画线
        gui_draw_hline(x0 - x, y0 + i, 2 * x, color);
        gui_draw_hline(x0 - x, y0 - i, 2 * x, color);
    }
}

/**
 * @brief  画空心圆
 * @param  x0 坐标
 * @param  y0 坐标
 * @param  r 半径
 * @param  color 颜色
 * @retval 无
 */
void gui_hollow_circle(u16 x0, u16 y0, u16 r, u16 color)
{
    POINT_COLOR(color);
    LCD_Draw_Circle(x0, y0, r);
}

/**
 * @brief  画水平线
 * @param  x0 坐标
 * @param  y0 坐标
 * @param  len 线长度
 * @param  color 颜色
 * @retval 无
 */
void gui_draw_hline(u16 x0, u16 y0, u16 len, u16 color)
{
    if ((len == 0) || (x0 > lcddev.width) || (y0 > lcddev.height))
    {
        return;
    }
    LCD_Fill(x0, y0, x0 + len - 1, y0, color);
}

/**
 * @brief  画垂直线
 * @param  x0 坐标
 * @param  y0 坐标
 * @param  len 花边直径
 * @param  color 颜色
 * @retval 无
 */
void gui_draw_vline(u16 x0, u16 y0, u16 len, u16 color)
{
    if ((len == 0) || (x0 > lcddev.width) || (y0 > lcddev.height))
    {
        return;
    }
    LCD_Fill(x0, y0, x0, y0 + len - 1, color);
}

/**
 * @brief  画一条粗线(方法1)
 * @param  x0 坐标
 * @param  y0 坐标
 * @param  x1 终点
 * @param  y1 终点
 * @param  size 线粗细,仅支持:0~2.
 * @param  color 颜色
 * @retval 无
 */
void gui_draw_bline1(u16 x0, u16 y0, u16 x1, u16 y1, u8 size, u16 color)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;

    delta_x = x1 - x0; //计算坐标增量
    delta_y = y1 - y0;
    uRow = x0;
    uCol = y0;
    if (delta_x > 0)
        incx = 1; //设置单步方向
    else if (delta_x == 0)
        incx = 0; //垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; //水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; //选取基本增量坐标轴
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++) //画线输出
    {
        if (size == 0)
            LCD_Fast_DrawPoint(uRow, uCol, color); //画点
        if (size == 1)
        {
            LCD_Fast_DrawPoint(uRow, uCol, color);         //画点
            LCD_Fast_DrawPoint(uRow + 1, uCol, color);     //画点
            LCD_Fast_DrawPoint(uRow, uCol + 1, color);     //画点
            LCD_Fast_DrawPoint(uRow + 1, uCol + 1, color); //画点
        }
        if (size == 2)
        {
            LCD_Fast_DrawPoint(uRow, uCol, color);         //画点
            LCD_Fast_DrawPoint(uRow + 1, uCol, color);     //画点
            LCD_Fast_DrawPoint(uRow, uCol + 1, color);     //画点
            LCD_Fast_DrawPoint(uRow + 1, uCol + 1, color); //画点
            LCD_Fast_DrawPoint(uRow - 1, uCol + 1, color); //画点
            LCD_Fast_DrawPoint(uRow + 1, uCol - 1, color); //画点
            LCD_Fast_DrawPoint(uRow - 1, uCol - 1, color); //画点
            LCD_Fast_DrawPoint(uRow - 1, uCol, color);     //画点
            LCD_Fast_DrawPoint(uRow, uCol - 1, color);     //画点
        }
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/**
 * @brief  画一条花边框
 * @param  x0 对角点
 * @param  y0 对角点
 * @param  x1 对角点
 * @param  y1 对角点
 * @param  size 花边直径
 * @param  color 颜色
 * @retval 无
 */
void gui_flower(u16 x0, u16 y0, u16 x1, u16 y1, u8 size, u16 color)
{

    gui_fill_circle(x0, y0, size / 2, color);
}

//画矩形
// x0,y0:矩形的左上角坐标
// width,height:矩形的尺寸
// color:颜色
/**
 * @brief  画矩形
 * @param  x0 对角点
 * @param  y0 对角点
 * @param  x1 对角点
 * @param  y1 对角点
 * @param  size 花边直径
 * @param  color 颜色
 * @retval 无
 */
void gui_draw_rectangle(u16 x0, u16 y0, u16 width, u16 height, u16 color)
{
    gui_draw_hline(x0, y0, width, color);
    gui_draw_hline(x0, y0 + height - 1, width, color);
    gui_draw_vline(x0, y0, height, color);
    gui_draw_vline(x0 + width - 1, y0, height, color);
}