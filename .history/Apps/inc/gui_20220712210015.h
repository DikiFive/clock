#ifndef __gui_h
#define __gui_h

#include "sys.h"

void gui_draw_expoint(u16 sx, u16 sy, u16 ex, u16 ey, u16 x, u16 y, u16 color) void gui_draw_circle8(u16 sx, u16 sy, u16 ex, u16 ey, u16 rx, u16 ry, int a, int b, u16 color);
void gui_fill_circle(u16 x0, u16 y0, u16 r, u16 color); //画实心圆
void gui_draw_arc(u16 sx, u16 sy, u16 ex, u16 ey, u16 rx, u16 ry, u16 r, u16 color, u8 mode);
void gui_draw_hline(u16 x0, u16 y0, u16 len, u16 color); //画水平线
void gui_draw_vline(u16 x0, u16 y0, u16 len, u16 color);
void gui_draw_bline1(u16 x0, u16 y0, u16 x1, u16 y1, u8 size, u16 color); //画粗线
void gui_flower(u16 x0, u16 y0, u8 size, u16 color);                      //画花边框
void gui_draw_rectangle(u16 x0, u16 y0, u16 width, u16 height, u16 color);
void gui_draw_arcrectangle(u16 x, u16 y, u16 width, u16 height, u8 r, u8 mode, u16 upcolor, u16 downcolor);

#endif
