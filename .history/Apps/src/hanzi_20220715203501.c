#include "sys.h"
#include "lcd.h"
#include "hanzi.h"
#inc

//在指定位置显示一个字符
// x,y:起始坐标
// num:要显示的字符:" "--->"~"
// size:字体大小 12/16/24
// mode:叠加方式(1)还是非叠加方式(0)
void ShowCn(u16 x, u16 y, u8 size, u8 num, u8 mode)
{
    u8 temp, t1, t;
    u16 y0 = y;
    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * size; //得到字体一个字符对应点阵集所占的字节数

    for (t = 0; t < csize; t++)
    {
        if (size == 16 || size == 24 || size == 32)
            temp = hanzi[num][t];

        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80)
                LCD_Fast_DrawPoint(x, y, POINT_COLOR);
            else if (mode == 0)
                LCD_Fast_DrawPoint(x, y, BACK_COLOR);

            temp <<= 1;
            y++;

            if (y >= lcddev.height)
                return; //超区域了

            if ((y - y0) == size)
            {
                y = y0;
                x++;

                if (x >= lcddev.width)
                    return; //超区域了

                break;
            }
        }
    }
}