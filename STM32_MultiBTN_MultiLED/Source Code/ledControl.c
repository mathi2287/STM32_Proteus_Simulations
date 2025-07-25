#include "stm32f4xx.h"
#include "stm32f401xe.h"
#include "ledControl.h"
#include <stdint.h>


void led_init(uint32_t *LED_OUT, int totalLED){
	RCC->AHB1ENR |= GPIOAEN; // Enable Clock Access to Port A
	uint32_t pinBit0;
	for(uint16_t i=0; i < totalLED; i++){
		pinBit0 = LED_OUT[i]*2; // Get a 0th bit of Corresponding PinX

		/* Configure Pins as a Output Mode */
		GPIOA->MODER |= (1U << pinBit0); //Set '1' to PinX[0]
		GPIOA->MODER &= ~(1U << (pinBit0 + 1)); //Set '0' to PinX[1]
	}
}

void button_init(uint32_t *BTN_IN, int totalBTN){
	RCC->AHB1ENR |= GPIOBEN; // Enable Clock Access to Port B
	uint16_t pinBit0;
	for(uint16_t i=0; i < totalBTN; i++){
		pinBit0 = BTN_IN[i]*2; // Get a 0th bit of Corresponding PinX

		/* Configure Pins as a input Mode */
		GPIOB->MODER &= ~(1U << pinBit0);
		GPIOB->MODER &= ~(1U << (pinBit0 + 1));

		/* Enable PULL-DOWN config. to PinX*/
		GPIOB->PUPDR &= ~(1U << pinBit0);
		GPIOB->PUPDR |= (1U << (pinBit0 + 1));
	}
}
