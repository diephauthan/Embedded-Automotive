#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "delay.h"

#define SCL_PIN GPIO_Pin_6
#define SDA_PIN GPIO_Pin_7
#define I2C_GPIO GPIOB
#define WRITE_SDA_0   GPIO_ResetBits(I2C_GPIO, SDA_PIN)
#define WRITE_SDA_1   GPIO_SetBits(I2C_GPIO, SDA_PIN)
#define WRITE_SCL_0   GPIO_ResetBits(I2C_GPIO, SCL_PIN)
#define WRITE_SCL_1   GPIO_SetBits(I2C_GPIO, SCL_PIN)
#define READ_SDA_VAL  GPIO_ReadInputDataBit(I2C_GPIO, SDA_PIN)

typedef enum{
    NOT_OK = 0,
    OK
} status;

void RCC_Config(void);
void Tim_Config(void);
void delay_us(uint32_t timedelay);
void GPIO_Config(void);
void I2C_Start(void);
void I2C_Stop(void);
status I2C_Write(uint8_t u8Data);
status I2C_Read(uint8_t* u8Data, uint8_t ack);
void I2C_WriteArray(uint8_t* arr, uint8_t length);

void RCC_Config(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

//void Tim_Config(void){
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1; // Assuming 72 MHz clock
//    TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF;
//    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
//    TIM_Cmd(TIM2, ENABLE);
//}

//void delay_us(uint32_t timedelay){
//    TIM_SetCounter(TIM2, 0);
//    while(TIM_GetCounter(TIM2) < timedelay){}
//}

void GPIO_Config(void){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = SCL_PIN | SDA_PIN;
    GPIO_Init(I2C_GPIO, &GPIO_InitStruct);
}

void I2C_Start(void) {
		WRITE_SDA_1; //ensure SDA and SCL are High
		WRITE_SCL_1;
		delay_ms(2);
    WRITE_SDA_1;
    delay_us(3);
    WRITE_SCL_1; 
    delay_us(3);
    WRITE_SDA_0;
    delay_us(3);
	  WRITE_SCL_0;
    delay_us(3);
}



void I2C_Stop(void){
    WRITE_SDA_0;
    delay_us(3);
    WRITE_SCL_1;  // SCL set to 1 before SDA.
    delay_us(3);
    WRITE_SDA_1;
    delay_us(3);
}

status I2C_Write(uint8_t u8Data){
    uint8_t i;
    status stRet;
    for(i=0; i< 8; i++){
        if (u8Data & 0x80) {
            WRITE_SDA_1;
        } else {
            WRITE_SDA_0;
        }
        delay_us(3);
				
        WRITE_SCL_1;
        delay_us(3); //5
        WRITE_SCL_0;
        delay_us(3); //2
        u8Data <<= 1;
    }
    WRITE_SDA_1;                    
    delay_us(3);
    WRITE_SCL_1;                
    delay_us(3);
    
    if (READ_SDA_VAL) {    
        stRet = NOT_OK;                
    } else {
        stRet = OK;                    
    }

    delay_us(3); //2
    WRITE_SCL_0;
    delay_us(3); //5
    
    return stRet;
}

status I2C_Read(uint8_t* u8Data, uint8_t ack){
    uint8_t i;
    *u8Data = 0;
    for(i = 0; i < 8; i++){
        WRITE_SCL_1;
        delay_us(3);
        *u8Data = (*u8Data << 1) | READ_SDA_VAL;
        WRITE_SCL_0;
        delay_us(3);
    }
    if(ack){
        WRITE_SDA_0;
    }else{
        WRITE_SDA_1;
    }
    delay_us(3);
    WRITE_SCL_1;
    delay_us(3);
    WRITE_SCL_0;
    delay_us(3);
    WRITE_SDA_1;
    return OK;
}

void I2C_WriteArray(uint8_t* arr, uint8_t length){
    I2C_Start(); // B?t d?u giao ti?p I2C
    I2C_Write(0x08 << 1); // G?i d?a ch? slave v?i bit ghi (write)
    for(uint8_t i = 0; i < length; i++){
        I2C_Write(arr[i]); // G?i t?ng ph?n t? c?a m?ng
    }
    I2C_Stop(); // K?t thúc giao ti?p I2C
}

int main(){
    RCC_Config(); // C?u hình RCC
    Tim_Config(); // C?u hình Timer
    GPIO_Config(); // C?u hình GPIO

    uint8_t arr[] = {128, 1,2,90,15};
    
    while(1){
        I2C_WriteArray(arr, sizeof(arr)); // G?i m?ng d? li?u d?n Arduino
        delay_us(1000000); // Delay 1 giây
    }
}

