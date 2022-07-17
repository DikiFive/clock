#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

typedef struct
{
    u32 u32time1;         //第一次按下后开始计时，主要用于判断长按，放在定时器中自加
    u32 u32time2;         //第一次松手后开始计时，用于判断双击或单击，放在定时器中自加
    u8 u8key_flag;        //第一次按下标志
    u8 u8key_double_flag; //第二次标志
} Key_Tag;

#define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)  //读取按键0
#define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)  //读取按键1
#define WK_UP GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) //读取按键3(WK_UP)

#define KEY0_PRES 1 // KEY0按下
#define KEY1_PRES 2 // KEY1按下
#define WKUP_PRES 3 // KEY_UP按下(即WK_UP/KEY_UP)

extern Key_Tag skey;

#define KUP_PRES 1    //单击
#define LONG_PRES 2   //长按
#define DOUBLE_PRES 3 //双击

void KEY_Init(void); // IO初始化
u8 KEY_Scan(u8);     //按键扫描函数
u8 KUP_Scan();       // keyup多功能识别
#endif
