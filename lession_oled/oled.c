#include "oled.h"
#include "myiic.h"
#include "delay.h"
#include "oledfont.h" 

uint8_t OLED_GRAM[128][8];

void OLED_WR_Byte(uint8_t dat, uint8_t cmd)
{
    IIC_Start();
    IIC_Send_Byte(0x78);
    IIC_Wait_Ack();
    if (cmd)
    {
        IIC_Send_Byte(0x40);
    }
    else
    {
        IIC_Send_Byte(0x00);
    }
    IIC_Wait_Ack();
    IIC_Send_Byte(dat);
    IIC_Wait_Ack();
    IIC_Stop();
    
}

void OLED_Refresh(void)
{
    uint8_t i,n;
    for(i = 0; i < 8; i++)
    {
        OLED_WR_Byte(0xb0 + i, OLED_CMD);
        OLED_WR_Byte(0x00, OLED_CMD);
        OLED_WR_Byte(0x10,OLED_CMD);
        for(n = 0; n < 128; n++)
        {
            OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
        }
    }
}

void OLED_Clear(void) {  
    uint8_t i, n;
    for(i = 0; i < 8; i++) {
        for(n = 0; n < 128; n++) OLED_GRAM[n][i] = 0;
    }
    OLED_Refresh();
}

void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t)
{
    if (x > 127 || y > 63)
    {
        /* code */return;
    }
    if(t)
    {
        OLED_GRAM[x][y/8] |= (1 << (y % 8));
    }
    else 
    {
        OLED_GRAM[x][y / 8] &= ~(1 << (y % 8));
    }
    
}

void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size)
{
    uint8_t temp, t1;
    uint8_t y0 = y;
    uint8_t csize = ((size / 8 + ((size % 8) ? 1 : 0))) * (size / 2);//size/2按照字库，宽应该是高的一半
    chr chr - '';

    for(uint8_t t = 0; t < csize; t++)
    {
        if(size == 12) temp = asc2_1206[chr][t];
        else if(size == 16) temp = asc2_1608[chr][t];
        else return;

        for(t1 = 0; t1 < 8; t1++)
        {
            if(temp & 0x80) OLED_DrawPoint(x, y, 1);
            else OLED_DrawPoint(x, y, 0);
            temp << 1;
            y++;
            if((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

uint32_t oled_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while(n--) result *= m;
    return result;
}

void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size)
{
    uint8_t t, temp;
    uint8_t enshow = 0;                           
    for(t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10; //数字筛选器
        if(enshow == 0 && t < (len - 1))
        {
            if(temp == 0)
            {
                OLED_ShowChar(x + (size / 2) * t, y, '', size);
                continue;
            }
            else enshow = 1;
        }
        OLED_ShowChar(x + (size / 2) * t, y, temp + '0', size); 
    }
}

void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *p, uint8_t Char_Size)
{
    while(*p != '\0')
    {
        if(x > 128 - (Char_Size/2))
        {
            x = 0;
            y += Char_Size;
        }
        OLED_ShowChar(x, y, *p, Char_Size);
        x += Char_Size / 2;
        p++;
    }
}

void OLED_Init(void) 
{
    IIC_Init();
    delay_ms(200); 
    
    OLED_WR_Byte(0xAE, OLED_CMD); // 关闭显示
    OLED_WR_Byte(0x00, OLED_CMD); // 设置低列地址
    OLED_WR_Byte(0x10, OLED_CMD); // 设置高列地址
    OLED_WR_Byte(0x40, OLED_CMD); // 设置起始行地址
    OLED_WR_Byte(0x81, OLED_CMD); // 对比度设置
    OLED_WR_Byte(0xCF, OLED_CMD); // 对比度值
    OLED_WR_Byte(0xA1, OLED_CMD); // 段重定向设置
    OLED_WR_Byte(0xC8, OLED_CMD); // COM扫描方向
    OLED_WR_Byte(0xA6, OLED_CMD); // 正常显示
    OLED_WR_Byte(0xA8, OLED_CMD); // 多路复用率
    OLED_WR_Byte(0x3f, OLED_CMD); // 1/64 duty
    OLED_WR_Byte(0xD3, OLED_CMD); // 显示偏移
    OLED_WR_Byte(0x00, OLED_CMD); 
    OLED_WR_Byte(0xd5, OLED_CMD); // 时钟分频
    OLED_WR_Byte(0x80, OLED_CMD); 
    OLED_WR_Byte(0xD9, OLED_CMD); // 预充电周期
    OLED_WR_Byte(0xF1, OLED_CMD); 
    OLED_WR_Byte(0xDA, OLED_CMD); // COM硬件配置
    OLED_WR_Byte(0x12, OLED_CMD); 
    OLED_WR_Byte(0xDB, OLED_CMD); // VCOMH
    OLED_WR_Byte(0x40, OLED_CMD); 
    OLED_WR_Byte(0x20, OLED_CMD); // 内存寻址模式
    OLED_WR_Byte(0x02, OLED_CMD); // 页寻址模式
    OLED_WR_Byte(0x8D, OLED_CMD); // 电荷泵
    OLED_WR_Byte(0x14, OLED_CMD); 
    OLED_WR_Byte(0xAF, OLED_CMD); // 开启显示
    OLED_Clear();
}