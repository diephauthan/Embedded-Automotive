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
    GPIO_ConfigPin(GPIOA, GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
		GPIO_ConfigPin(GPIOA, GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_IPU);
}


		void ChaseLEDs() {
    uint16_t LEDPins[] = {GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15, GPIO_Pin_0};
    GPIO_TypeDef* Ports[] = {GPIOC, GPIOC, GPIOC, GPIOA};

        for (uint8_t i = 0; i < 4; i++) {
            // Turn off LED
            for (uint8_t k = 0; k < 4; k++) {	
							GPIO_SetBits(Ports[k], LEDPins[k]);
            }
            // Turn on LED
						GPIO_ResetBits(Ports[i], LEDPins[i]);
            Delay_ms(500);
						// Turn off whole LED to prevent the last LED will be turn on
						for (uint8_t k = 0; k < 4; k++) {
							GPIO_SetBits(Ports[k], LEDPins[k]);
						}	
        }
    }
		
int main() {
    RCC_Config();
    GPIO_Config();

     while(1) {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == Bit_RESET) {
            Delay_ms(50);  
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == Bit_RESET) {
                while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == Bit_RESET);
                ChaseLEDs();
            }
        }
    }
}
