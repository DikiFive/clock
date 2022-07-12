#include "gui.h"
#include "lcd.h"

/**
 * @brief  在区域内画点
 * @param  sx 设定的显示范围
 * @param  sy 设定的显示范围
 * @param  ex 设定的显示范围
 * @param  ey 设定的显示范围
 * @param  x 点坐标
 * @param  y 点坐标
 * @param  color 颜色
 * @retval 无
 */
void gui_draw_expoint(u16 sx, u16 sy, u16 ex, u16 ey, u16 x, u16 y, u16 color)
{
    u16 tempcolor;
    if (x <= ex && x >= sx && y <= ey && y >= sy)
    {
        tempcolor = POINT_COLOR;
        POINT_COLOR = color;
        LCD_DrawPoint(x, y);
        POINT_COLOR = tempcolor;
    }
}

/**
 * @brief  画8点(Bresenham算法)
 * @param  sx 设定的显示范围
 * @param  sy 设定的显示范围
 * @param  ex 设定的显示范围
 * @param  ey 设定的显示范围
 * @param  rx 参数
 * @param  ry 参数
 * @param  a 参数
 * @param  b 参数
 * @param  r 半径
 * @param  color 颜色
 * @retval 无
 */
void gui_draw_circle8(u16 sx, u16 sy, u16 ex, u16 ey, u16 rx, u16 ry, int a, int b, u16 color)
{
    gui_draw_expoint(sx, sy, ex, ey, rx + a, ry - b, color);
    gui_draw_expoint(sx, sy, ex, ey, rx + b, ry - a, color);
    gui_draw_expoint(sx, sy, ex, ey, rx + b, ry + a, color);
    gui_draw_expoint(sx, sy, ex, ey, rx + a, ry + b, color);
    gui_draw_expoint(sx, sy, ex, ey, rx - a, ry + b, color);
    gui_draw_expoint(sx, sy, ex, ey, rx - b, ry + a, color);
    gui_draw_expoint(sx, sy, ex, ey, rx - b, ry - a, color);
    gui_draw_expoint(sx, sy, ex, ey, rx - a, ry - b, color);
}

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
 * @brief  在指定位置画一个指定大小的圆
 * @param  rx 坐标
 * @param  ry 坐标
 * @param  sx 设定的显示范围
 * @param  sy 设定的显示范围
 * @param  ex 设定的显示范围
 * @param  ey 设定的显示范围
 * @param  r 半径
 * @param  color 颜色
 * @param mode 0,不填充;1,填充
 * @retval 无
 */
void gui_draw_arc(u16 sx, u16 sy, u16 ex, u16 ey, u16 rx, u16 ry, u16 r, u16 color, u8 mode)
{
    int a, b, c;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1); //判断下个点位置的标志
    while (a <= b)
    {
        if (mode)
            for (c = a; c <= b; c++)
                gui_draw_circle8(sx, sy, ex, ey, rx, ry, a, c, color); //画实心圆
        else
            gui_draw_circle8(sx, sy, ex, ey, rx, ry, a, b, color); //画空心圆
        a++;
        //使用Bresenham算法画圆
        if (di < 0)
            di += 4 * a + 6;
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

/**
 * @brief  画椭圆
 * @param  x0 坐标
 * @param  y0 坐标
 * @param  rx 方向半径
 * @param  ry 方向半径
 * @param  color 颜色
 * @retval 无
 */
void gui_draw_ellipse(u16 x0, u16 y0, u16 rx, u16 ry, u16 color)
{
    u32 OutConst, Sum, SumY;
    u16 x, y;
    u16 xOld;
    u32 _rx = rx;
    u32 _ry = ry;
    if (rx > x0 || ry > y0)
        return;                                                //非法.
    OutConst = _rx * _rx * _ry * _ry + (_rx * _rx * _ry >> 1); // 常数如上所述
    //补偿舍入
    xOld = x = rx;
    for (y = 0; y <= ry; y++)
    {
        if (y == ry)
            x = 0;
        else
        {
            SumY = ((u32)(rx * rx)) * ((u32)(y * y)); //循环中不改变
            while (Sum = SumY + ((u32)(ry * ry)) * ((u32)(x * x)), (x > 0) && (Sum > OutConst))
                x--;
        }
        // 因为我们画线，所以不能在第一次迭代中绘制
        if (y)
        {
            gui_draw_line(x0 - xOld, y0 - y + 1, x0 - x, y0 - y, color);
            gui_draw_line(x0 - xOld, y0 + y - 1, x0 - x, y0 + y, color);
            gui_draw_line(x0 + xOld, y0 - y + 1, x0 + x, y0 - y, color);
            gui_draw_line(x0 + xOld, y0 + y - 1, x0 + x, y0 + y, color);
        }
        xOld = x;
    }
}

/**
 * @brief  填充椭圆
 * @param  x0 坐标
 * @param  y0 坐标
 * @param  rx 方向半径
 * @param  ry 方向半径
 * @param  color 颜色
 * @retval 无
 */
void gui_fill_ellipse(u16 x0, u16 y0, u16 rx, u16 ry, u16 color)
{
    u32 OutConst, Sum, SumY;
    u16 x, y;
    u32 _rx = rx;
    u32 _ry = ry;
    OutConst = _rx * _rx * _ry * _ry + (_rx * _rx * _ry >> 1); // Constant as explaint above
    // To compensate for rounding
    x = rx;
    for (y = 0; y <= ry; y++)
    {
        SumY = ((u32)(rx * rx)) * ((u32)(y * y)); // Does not change in loop
        while (Sum = SumY + ((u32)(ry * ry)) * ((u32)(x * x)), (x > 0) && (Sum > OutConst))
            x--;
        gui_draw_hline(x0 - x, y0 + y, 2 * x, color);
        if (y)
            gui_draw_hline(x0 - x, y0 - y, 2 * x, color);
    }
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
 * @brief  画一条粗线
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
    gui_draw_arcrectangle
}

/**
 * @brief  填充矩形
 * @param  x0 矩形的左上角坐标
 * @param  y0 矩形的左上角坐标
 * @param  width 矩形的尺寸
 * @param  height 矩形的尺寸
 * @param  color 颜色
 * @retval 无
 */
void gui_fill_rectangle(u16 x0, u16 y0, u16 width, u16 height, u16 color)
{
    if (width == 0 || height == 0)
        return; //非法.
    LCD_Fill(x0, y0, x0 + width - 1, y0 + height - 1, color);
}

/**
 * @brief  画矩形
 * @param  x0 矩形的左上角坐标
 * @param  y0 矩形的左上角坐标
 * @param  width 矩形的尺寸
 * @param  height 矩形的尺寸
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

/**
 * @brief  画圆角矩形/填充圆角矩形
 * @param  x 圆角矩形的位置
 * @param  y 圆角矩形的位置
 * @param  width 矩形的尺寸
 * @param  height 矩形的尺寸
 * @param  mode 0,画矩形框;1,填充矩形
 * @param  upcolor 上半部分颜色
 * @param  downcolor 下半部分颜色
 * @retval 无
 */
void gui_draw_arcrectangle(u16 x, u16 y, u16 width, u16 height, u8 r, u8 mode, u16 upcolor, u16 downcolor)
{
    u16 btnxh = 0;
    if (height % 2)
        btnxh = height + 1; //基偶数处理
    else
        btnxh = height;
    if (mode) //填充
    {
        gui_fill_rectangle(x + r, y, width - 2 * r, btnxh / 2, upcolor);               //中上
        gui_fill_rectangle(x + r, y + btnxh / 2, width - 2 * r, btnxh / 2, downcolor); //中下
        gui_fill_rectangle(x, y + r, r, btnxh / 2 - r, upcolor);                       //左上
        gui_fill_rectangle(x, y + btnxh / 2, r, btnxh / 2 - r, downcolor);             //左下
        gui_fill_rectangle(x + width - r, y + r, r, btnxh / 2 - r, upcolor);           //右上
        gui_fill_rectangle(x + width - r, y + btnxh / 2, r, btnxh / 2 - r, downcolor); //右下
    }
    else
    {
        gui_draw_hline(x + r, y, width - 2 * r, upcolor);                       //上
        gui_draw_hline(x + r, y + btnxh - 1, width - 2 * r, downcolor);         //下
        gui_draw_vline(x, y + r, btnxh / 2 - r, upcolor);                       //左上
        gui_draw_vline(x, y + btnxh / 2, btnxh / 2 - r, downcolor);             //左下
        gui_draw_vline(x + width - 1, y + r, btnxh / 2 - r, upcolor);           //右上
        gui_draw_vline(x + width - 1, y + btnxh / 2, btnxh / 2 - r, downcolor); //右下
    }
    gui_draw_arc(x, y, x + r, y + r, x + r, y + r, r, upcolor, mode);                                                               //左上
    gui_draw_arc(x, y + btnxh - r, x + r, y + btnxh - 1, x + r, y + btnxh - r - 1, r, downcolor, mode);                             //左下
    gui_draw_arc(x + width - r, y, x + width, y + r, x + width - r - 1, y + r, r, upcolor, mode);                                   //右上
    gui_draw_arc(x + width - r, y + btnxh - r, x + width, y + btnxh - 1, x + width - r - 1, y + btnxh - r - 1, r, downcolor, mode); //右下
}
