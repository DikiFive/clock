#ifndef __clock_h
#define __clock_h

#include "sys.h"

typedef struct time
{
    u8 hour;
    u8 min;
    u8 sec;
} time;

#define PI 3.1415

extern time clock;

void clock_alarm_ring(u8 type);
void clock_draw_panel(u16 x, u16 y, u16 size, u16 d);
u8 clock_play(u16 x, u16 y, u16 r, u8 d);
void clock_showtime(u16 x, u16 y, u16 size, u16 d, u8 hour, u8 min, u8 sec);
void clock_draw_frame(u16 width, u16 height, u16 color1, u16 color2);
void clock_set();
void clock_NumShow(u8 hour, u8 min, u8 sec, u16 color, u16 x, u16 y);

#endif
