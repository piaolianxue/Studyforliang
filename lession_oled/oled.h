#ifndef __OLED_H
#define __OLED_H
#include "stm32f4xx.h"

#define OLED_CMD 0 //写命令
#define OLED_DATA 1 // 写数据

void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
void OLED_Display_On(void);
void OLED_Displau_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
//void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_ShowChar(uint8_t x, uint8_t y,uint8_t chr, uint8_t Char_Size);
void OLED_ShowNum(uint8_t x, uint8_t y, uint8_t num, uint8_t len, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *p, uint8_t Char_Size);
void OLED_Refresh(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);

#endif