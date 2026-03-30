#include "stm32f4xx.h"
#include "delay.h"
#include "myiic.h"
#include "oled.h"

int main(void)
{
    delay_init(168);  
    OLED_Init();      
    OLED_Clear();     
    
    // 注意 Y 坐标的变化：0, 16, 32
    OLED_ShowString(0, 0,  (uint8_t *)"Have a good day", 16);  
    OLED_ShowString(0, 16, (uint8_t *)"STM32F407 Test", 16); 
    
    OLED_ShowString(0, 32, (uint8_t *)"Code:", 16);          
    OLED_ShowNum(40, 32, 2026, 4, 16);                       
                                   
    OLED_Refresh();
    
    while(1)
    {
        delay_ms(500);
    }
}
