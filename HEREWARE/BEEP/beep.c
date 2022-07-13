#include "beep.h"

void Beep_int(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOB端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;         // BEEP-->PB.8 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据参数初始化GPIOB.8

    GPIO_ResetBits(GPIOB, GPIO_Pin_8); //初始化输出为0，关闭蜂鸣器
}
