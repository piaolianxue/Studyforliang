#include "stm32f4xx.h"                  // Device header


void PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 1. 开启时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

    // 2. 引脚复用映射 
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);

    // 3. GPIO配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    
    // 4. 定时器基础配置
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;     // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 840 - 1;  // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    // 放在赋值的后面
    TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStructure); 
    
    // 5. 定时器 PWM 通道配置
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_Pulse = 0;                       // 初始占空比
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; // 注意：使用 OCPolarity，低电平点亮
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    // 放在赋值的后面
    TIM_OC1Init(TIM14, &TIM_OCInitStruct);
    
    // 6. 启动定时器
    TIM_Cmd(TIM14, ENABLE);
}

void PWM_SetComparel(uint16_t Compare)
{
    TIM_SetCompare1(TIM14, Compare);
}
