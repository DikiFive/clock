#ifndef __clock_h
#define __clock_h

#include "sys.h"

typedef struct time
{
    u8 year;
    u8 mon;
    u8 day;
    u8 hour;
    u8 min;
    u8 sec;
    u8 week;
    u8 save_flag;
} time;

#define PI 3.1415

extern time clock;

void clock_alarm_ring(u8 type);
void clock_draw_panel(u16 x, u16 y, u16 size, u16 d);
u8 clock_play(u16 r, u8 d);void clock_showtime(u16 x, u16 y, u16 size, u16 d, u8 hour, u8 min, u8 sec);

#endif
