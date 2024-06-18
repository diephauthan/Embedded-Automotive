#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_usart.h"            // Device:StdPeriph Drivers:USART

#define UART_GPIO GPIOA
#define TX_Pin GPIO_Pin_9 //TX - trang
#define RX_Pin GPIO_Pin_10 // RX -Nau

void TIM_Config(void);
void RCC_Config(void);
void delay_us(uint64_t timedelay);
void GPIO_Config(void);
void UART_Config(void);
void UART_SendChar(USART_TypeDef *USARTx, uint16_t data);
char UART_ReceiveChar(USART_TypeDef *USARTx);
void UART_SendString(USART_TypeDef *USARTx, char *str);

void RCC_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_USART1, ENABLE);
}

void TIM_Config(void){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF;
	TIM_TimeBaseInitStruct.TIM_Prescaler =72-1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM2, ENABLE);
}

void delay_us(uint64_t timedelay){
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < timedelay){}
}

void GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = RX_Pin;
	GPIO_Init(UART_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = TX_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART_GPIO, &GPIO_InitStruct);
}

void UART_Config(void){
	USART_InitTypeDef USARTInitStruct;
	USARTInitStruct.USART_BaudRate = 9600;
	USARTInitStruct.USART_WordLength = USART_WordLength_8b;
	USARTInitStruct.USART_StopBits = USART_StopBits_1;
	USARTInitStruct.USART_Parity = USART_Parity_No;
	USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USARTInitStruct);
	USART_Cmd(USART1,ENABLE);
}

char UART_ReceiveChar(USART_TypeDef *USARTx){
	USARTx->DR = 0x00; //delete data register
	char tmp = 0x00;
	tmp = (char)USART_ReceiveData(USARTx);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)==RESET);
	
	return tmp;
}

void UART_SendString(USART_TypeDef *USARTx, char *str){
	while(*str)
		{
		UART_SendChar(USARTx, *str);
		str++;
		}
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
				delay_us(1000);
}

void UART_SendChar(USART_TypeDef *USARTx, uint16_t data){
	USARTx->DR = 0x00; //delete data register
	USART_SendData(USARTx, data);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
}

char data ='a';
char data1;
char mess[] = "Hello MCU ";

int main(){
	RCC_Config();
	GPIO_Config();
	UART_Config();
	while(1){
		//data1 = UART_ReceiveChar(USART1);
		//UART_SendChar(USART1, data);
		UART_SendString(USART1, mess);
	}
}
