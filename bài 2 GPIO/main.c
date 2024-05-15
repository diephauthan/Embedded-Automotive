#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Delay_ms(uint32_t ms) {
    for(uint32_t i = 0; i < ms; i++) {
        for(volatile uint32_t j = 0; j < 7200; j++);
    }
}

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

void GPIO_ConfigPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode) {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
    GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void GPIO_Config() {
    GPIO_ConfigPin(GPIOC, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    GPIO_ConfigPin(GPIOA, GPIO_Pin_0 | GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
}

void ChaseLEDs(uint8_t loops) {
    uint16_t LEDPins[] = {GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15, GPIO_Pin_0, GPIO_Pin_1};
    GPIO_TypeDef* Ports[] = {GPIOC, GPIOC, GPIOC, GPIOA, GPIOA};

    for (uint8_t j = 0; j < loops; j++) {
        for (uint8_t i = 0; i < 5; i++) {
            for (uint8_t k = 0; k < 5; k++) {
                GPIO_ResetBits(Ports[k], LEDPins[k]);
            }
            GPIO_SetBits(Ports[i], LEDPins[i]);
            Delay_ms(500);
        }
    }
}

int main() {
    RCC_Config();
    GPIO_Config();

    while(1) {
        ChaseLEDs(3);
        Delay_ms(1000);
    }
}
