#ifndef __myiic_H
#define __myiic_H
#include "stm32f4xx.h"

#define IIC_SCL_1()  GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define IIC_SCL_0()  GPIO_ResetBits(GPIOB, GPIO_Pin_8)
#define co GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define IIC_SDA_0()  GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define READ_SDA() GPIO_ReadInputDataBit(PIOB, GPIO_Pin_9)

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Wait_Ack(void);


#endif