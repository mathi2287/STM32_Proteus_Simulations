#include "stm32f4xx.h"
#include "stm32f401xe.h"
#include "ledControl.h"
#include <stdint.h>

void led_init(uint32_t LED_OUT[16], int totalLED){
	RCC->AHB1ENR |= GPIOAEN; // Enable Clock Access to Port A
	uint16_t pinBit0;
	for(uint16_t i=0; i < totalLED; i++){
		pinBit0 = LED_OUT[i]*2; // Get a 0th bit of Corresponding PinX

		/* Configure Pins as a Output Mode */
		GPIOA->MODER |= (1U << pinBit0); //Set '1' to PinX[0]
		GPIOA->MODER &= ~(1U << (pinBit0 + 1)); //Set '0' to PinX[1]
	}
}

void button_init(uint32_t BTN_IN[16], int totalBTN){
	RCC->AHB1ENR |= GPIOBEN; // Enable Clock Access to Port B
	uint16_t pinBit0;
	for(uint16_t i=0; i < totalBTN; i++){
		pinBit0 = BTN_IN[i]*2; // Get a 0th bit of Corresponding PinX

		/* Configure Pins as a Output Mode */
		GPIOB->MODER &= ~(1U << pinBit0);
		GPIOB->MODER &= ~(1U << (pinBit0 + 1));

		/* Set PinX as Open Drain config.*/
		GPIOB->OTYPER |= (1U << (pinBit0/2));

		/* Enable PULL-DOWN config. to PinX*/
		GPIOB->PUPDR &= ~(1U << pinBit0);
		GPIOB->PUPDR |= (1U << (pinBit0 + 1));
	}


}
