#include "stm32f4xx.h"                  // Device header
#include "oled.h"
#include "delay.h"

extern uint32_t count;


void Keyctr_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	//PE4 连接到 EXTI4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	
	
	//配置下降沿触发
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	//配置NVIC
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_Init(&NVIC_InitStructure);

}

// 假设全局变量 count
 

void EXTI4_IRQHandler(void) 
{
    if (EXTI_GetITStatus(EXTI_Line4) != RESET) 
    {      
        delay_ms(10); 
        
        if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == Bit_RESET) 
        {            
          
            GPIO_SetBits(GPIOF, GPIO_Pin_9);                     
            
        
            count++;
            OLED_ShowNum(48, 0, count, 5, 16); 
            OLED_Refresh();
            
           
            while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == Bit_RESET)
            {
               
            }
            
            
            GPIO_ResetBits(GPIOF, GPIO_Pin_9);
        }
        
        
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}
