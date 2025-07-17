#include "stm32f4xx.h"
#include "stm32f401xe.h"
#include "binary_count.h"
#include <stdint.h>

#define pinBit0(pin)	pin*2   // Get a 0th bit of Corresponding PinX

void led_init(uint32_t LED_OUT[4], int totalLED){
	RCC->AHB1ENR |= GPIOAEN; // Enable Clock Access to Port A

	for(uint16_t i=0; i < totalLED; i++){

		/* Configure Pins as a Output Mode */
		GPIOA->MODER |= (1U << pinBit0(LED_OUT[i])); //Set '1' to PinX[0]
		GPIOA->MODER &= ~(1U << (pinBit0(LED_OUT[i]) + 1)); //Set '0' to PinX[1]
	}
}

void button_init(int pinNumber){
	RCC->AHB1ENR |= GPIOAEN; // Enable Clock Access to Port A

	/*Configure as PAX as Input Mode */
	GPIOA->MODER &= ~(1 << pinBit0(pinNumber));
	GPIOA->MODER &= ~(1 << (pinBit0(pinNumber)+1));

	/* Enable Pull-Down configure */
	GPIOA->PUPDR |= (1U << (pinBit0(pinNumber) + 1));
	GPIOA->PUPDR &= ~(1U << pinBit0(pinNumber));
}
