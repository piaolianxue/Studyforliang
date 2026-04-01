#include "stm32f4xx.h"
#include "delay.h"
#include "myiic.h"
#include "oled.h"
#include "Timer.h"

volatile uint16_t Num = 0;

int main(void)
{
    delay_init(168);  
    OLED_Init(); 
		Timer_Init();
		OLED_Clear();
  
	OLED_ShowString(0, 0,  (uint8_t *)"Num:", 16);  
	
                  
                                   
    OLED_Refresh();
    
    while(1)
    {
       OLED_ShowNum(40,0,Num,5,16);
			 OLED_Refresh();
			 delay_ms(100);
			
    }
}
