GPIO_ResetBits函数实际上在操作GPIOx_BSRR register
对于GPIOx_BSRR register 有32位
高16位为清除位                                            低16位为设置位
写入1对应IO口输出置0，写入0无动作。                 写入1将对应IO口输出置1，写入0无动作。
优点：单条指令修改，中断或者任务不会破坏数据完整性，不需要操作GPIOX_ODR执行“读取-修改-回写”。



GPIO_Struture中结构体的顺序为 MODE TYPE SPEED PUPD 

模拟了信号从内核->引脚物理处理顺序


LED.c

#include "led.h"
#include "stm32f4xx.h"

void LED_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF ,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOF,GPIO_Pin_10);

}


main.c


#include "stm32f4xx.h"
#include "LED.h"
#include "delay.h"


int main(void)
{
	delay_init(168);
	
	LED_Init();
	
	while(1)
	{
		GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		GPIO_SetBits(GPIOF,GPIO_Pin_10);
		
		delay_ms(500);
		
		GPIO_SetBits(GPIOF,GPIO_Pin_9);
		GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		
		delay_ms(500);
	
	}
	
}



