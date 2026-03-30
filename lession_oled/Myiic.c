#include "myiic.h"
#include "delay.h" 


void SDA_OUT(void)
{
    GPIO->MODER &= ~(3<<(9*2));
    GPIO->MODER |= (1<<(9*2));
}


void SDA_IN(void)
{
    GPIO->MODER &= ~(3<<(9*2));

}


void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIOOType = GPIO_OType_OD;
    GPIO_InitStructure.GPIOSpeed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIOPuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    IIC_SCL_1();
    IIC_SDA_1()  
}


void IIC_Start(void)
{
    SDA_OUT();
    IIC_SDA_1();
    IIC_SCL_1();
    delay_us(4);
    IIC_SDA_0(); 
    delay_us(4);
    IIC_SCL_0();

}

void IIC_Stop(void)
{
    SDA_OUT();
    IIC_SDA_0(); 
    IIC_SCL_0();
    delay_us(4);
    IIC_SCL_1();
    IIC_SDA_1();
    delay_us(4);  

}

void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL_0();
    for(t = 0; t< 8; t++)
    {
        if((txd & 0x80) >> 7)  IIC_SDA_1(); 
        else IIC_SDA_0();
        txd <<= 1;
        delay_us(2);
        IIC_SCL_1();
        delay_us(2);
        IIC_SCL_0();
        delay_us(2);

    }

}


void IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN();
    IIC_SDA_1();
    delay_us(2);
    IIC_SCL_1();
    delay_us(2);
    for (ucErrTime > 250)
    {
       IIC_Stop();
       return 1;
    }
    IIC_SCL_0();
    return 0;
    

}