#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define SPI_SCK_Pin GPIO_Pin_5
#define SPI_MISO_Pin GPIO_Pin_6
#define SPI_MOSI_Pin GPIO_Pin_7
#define SPI_CS_Pin GPIO_Pin_4
#define SPI_GPIO GPIOA
#define SPI_RCC RCC_APB2Periph_GPIOA

void SystemInit(void) {}

void RCC_Config() {
    RCC_APB2PeriphClockCmd(SPI_RCC, ENABLE);
}

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = SPI_SCK_Pin | SPI_MOSI_Pin | SPI_CS_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
}

void Clock() {
    GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_SET);
    delay(100);  // Adjust the delay as needed for your system
    GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
    delay(100);  // Adjust the delay as needed for your system
}

void My_SPI_Init() {
    GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
    GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
    GPIO_WriteBit(SPI_GPIO, SPI_MISO_Pin, Bit_RESET);
    GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
}

void SPI_Master_Transmit(volatile uint8_t u8Data) {
    uint8_t u8Mask = 0x80;
    GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);
    delay(100);
    for (int i = 0; i < 8; i++) {
        if (u8Data & u8Mask) {
            GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_SET);
        } else {
            GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
        }
        u8Data <<= 1;
        Clock();
    }
    GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
    delay(100);
}

uint8_t DataTrans[] = {1, 3, 9, 10, 15, 169, 90}; // Data

int main() {
    SystemInit();
    RCC_Config();
    GPIO_Config();
    My_SPI_Init();
    while (1) {
        for (int i = 0; i < 7; i++) {
            SPI_Master_Transmit(DataTrans[i]);
            delay(50000); // Delay to allow data to be processed
        }
    }
}
