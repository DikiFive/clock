#ifndef __tim1_h
#define __tim1_h

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
extern time clock; //日历结构体

void TIM_UserConfig(u16 Period, u16 Prescaler);


#endif
