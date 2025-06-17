#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN (1U<<0)
#define UART2EN (1U<<17)

#define SYS_FREQ 16000000
#define APB1_CLK  SYS_FREQ

#define UART_BAUDRATE 9600

#define UART2_CR1_TE (1U<<3)
#define UART2_CR1_UE (1U<<13)
#define SR_TXE (1U<<7)

void uart2_tx_init(void);
void uart2_write(int ch);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate );
static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_tx_init(void){
	//------Configure UART2 GPIO pins-----
	/* 1.Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* 2.Configure PA2 Mode as Alternate Function */
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<4);

	/* 3.Configure PA2 as Alternate type UART2_TX (AF07) in Alternating Function register*/
	GPIOA->AFR[0] |= (7U<<8);
	GPIOA->AFR[0] &= ~(1U<<11);

	//------Configure UART2 Module------
	/* 1.Enable Clock access to UART2 */
	RCC->APB1ENR |= UART2EN;

	/* 2.Configure Baud Rate */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/* 3.Enable Transmitter Direction (control registser1 in USART2*/
	USART2->CR1 = UART2_CR1_TE;

	/* 4.Enable USART Mode */
	USART2->CR1 |= UART2_CR1_UE;

}

void uart2_write(int ch){
	/* Make sure empty the data register*/
	//USART2->DR = (ch & 0xFF);
	while(!(USART2->SR & SR_TXE)){}
	/*Write to transmit data register (using Status Register)*/
	USART2->DR = (ch & 0xFF);

}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate ){
	USARTx->BRR = compute_uart_div(PeriphClk, BaudRate);
}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate){
	/* Compute clock ticks b/w 2 symbols divides PeriphClk */
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

int main(){
	uart2_tx_init();
	while(1){
		uart2_write('T');
	}
	return 0;
}


