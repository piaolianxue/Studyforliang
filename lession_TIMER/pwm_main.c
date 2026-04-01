#include "stm32f4xx.h"
#include "delay.h"
#include "myiic.h"
#include "led.h"
#include "PWM.h"

volatile uint16_t Num = 0;

uint16_t i;

int main(void)
{
		delay_init(168);
 
		PWM_Init();
	
	
    while(1)
		{
			for(i = 0; i < 500; i++)
			{
				PWM_SetComparel(i);
				delay_ms(2);
			}
			for(i = 0; i < 500; i++)
			{
				PWM_SetComparel(600-i);
				delay_ms(2);
			}
			
		}
}
