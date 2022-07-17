#ifndef __RED_H
#define __RED_H
#include "sys.h"

#define RDATA PBin(9) //红外数据输入脚

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0

#define POWER 162
#define Mode 98
#define NoVoice 226
#define Stop 34
#define Mback 2
#define Mforward 194
#define EQ 224
#define VOLD 168
#define VOLA 144
#define zero 104
#define RPT 152
#define USD 176
#define One 48
#define Two 24
#define Three 122
#define Four 16
#define Five 56
#define Six 90
#define Seven 66
#define Eight 74
#define Nine 82

extern u8 RmtCnt;  //按键按下的次数
extern u32 RmtRec; //红外接收到的数据

void Remote_Init(void); //红外传感器接收头引脚初始化
u8 Remote_Scan(void);   //红外接受解码
#endif
