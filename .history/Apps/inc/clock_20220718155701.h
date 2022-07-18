#ifndef __clock_h
#define __clock_h

#include "sys.h"

typedef struct time
{
    u8 hour;
    u8 min;
    u8 sec;
    u8 count;
    u8 down;
    u8 time_select;
    u8 time_flag;
    u8 time_FlashFlag;
} time;

typedef struct mod
{
    u8 i;
    u8 len;
    u8 flag;
    u8 Rf;
} MOD;

typedef struct key
{
    u8 IR;
    u8 Num;
    u8 wk_up;
} KEY;

#define PI 3.1415

extern time clock;
extern MOD mode;
extern KEY kn;

void clock_alarm_ring(u8 type);
void clock_countdown(u8 type, u8 time);
void clock_draw_panel(u16 x, u16 y, u16 size, u16 d);
u8 clock_play(u16 x, u16 y, u16 r, u8 d);
void clock_showtime(u16 x, u16 y, u16 size, u16 d, u8 hour, u8 min, u8 sec);
void clock_set();
void clock_draw_frame(u16 width, u16 height, u16 color1, u16 color2);
void clock_NumShow(u8 hour, u8 min, u8 sec, u16 color, u16 x, u16 y);

#endif
