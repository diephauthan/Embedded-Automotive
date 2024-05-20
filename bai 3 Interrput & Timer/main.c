#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

void RCC_config(void);
void GPIO_Config(void);
void TIM_Config(void);
void TIM2_IRQHandler(void);

void RCC_config(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Ch?nh l?i dúng hàm
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void TIM_Config(void){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 3600 - 1;
    TIM_TimeBaseInitStruct.TIM_Period = 5000 - 1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void) {
    // Ki?m tra n?u ng?t c?p nh?t dã x?y ra
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        // Xóa c? ng?t c?p nh?t
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        // Ð?o tr?ng thái c?a LED (GPIOC Pin 13)
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));
    }
}

int main(void){
    RCC_config();
    GPIO_Config();
    TIM_Config();
    __enable_irq(); // Kích ho?t ng?t toàn c?c

    while(1){
        // Chuong trình chính không c?n làm gì ? dây
    }
}
