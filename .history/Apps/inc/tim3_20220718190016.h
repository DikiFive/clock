#ifndef __tim3_h
#define __tim1_h

#include "sys.h"

void TIM_UserConfig(u16 Period, u16 Prescaler);
void TIM3_Int_Init(u16 arr, u16 psc);

#endif
