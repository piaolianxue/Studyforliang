#include "stm32f4xx.h"
#include "delay.h"
#include "myiic.h"
#include "oled.h"
#include "LED.h"
#include "Key_ctr.h"


uint32_t count = 0;

int main(void)
{
    
		delay_init(168);  
		LED_Init();
    OLED_Init();      
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
		
		
		Keyctr_Init();
	
		OLED_ShowString(0, 0, (uint8_t *)"Count:", 16);
		OLED_ShowNum(48, 0, count, 5, 16);
		OLED_Refresh();
	
		
		
		
    
    while(1)
    {
        delay_ms(500);
    }
}

