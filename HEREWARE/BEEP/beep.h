#ifndef __BEEP_H
#define __BEEP_H

#include "sys.h"

#define BEEP PBout(8) // BEEP，蜂鸣器端口

void Beep_int(void); //初始化BEEP函數

#endif
