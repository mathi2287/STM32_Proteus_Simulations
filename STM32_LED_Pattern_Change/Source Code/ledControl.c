#include "stm32f4xx.h"
#include "stm32f401xe.h"
#include "ledControl.h"
#include <stdint.h>

uint32_t count = 0;
extern int pattern;

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

void pattern1(void){
	count = 0;
	while(pattern == 1){
		//Downward LED blowing
		GPIOA->ODR |= (1 << count);
		for(int i = 0; i < 50000; i++);
		count++;
		if(count == 16){
			//Upward LED blowing
			GPIOA->ODR = (GPIOA->ODR & ~(0xFFFF));
			while(count){
				count--;
				GPIOA->ODR |= (1 << count);
				for(int i = 0; i < 50000; i++);
			}
			count = 0;
			GPIOA->ODR = 0;
		}
	}
}

void pattern2(void){
	count = 0;
	while(pattern == 2){
		GPIOA->ODR |= (1 << count);
		count++;
		for(int i = 0; i < 50000; i++);
		if(count == 4){
			count--;
			while(count < 12){
				count += 3;
				GPIOA->ODR |= (1 << count);
				for(int i = 0; i < 50000; i++);
			}

			while(count < 15){
				count++;
				GPIOA->ODR |= (1 << count);
				for(int i = 0; i < 50000; i++);
			}

			while(count){
				count -= 5;
				GPIOA->ODR |= (1 << count);
				for(int i = 0; i < 50000; i++);
			}
			GPIOA->ODR = 0;
			for(int i = 0; i < 50000; i++);
			count = 0;
		}

	}
}

void pattern3(void){
	count = 0x1111; //0000 00  0001 0001 0001 0001
	while(pattern == 3){

		GPIOA->ODR |= (count << 0);
		for(int i = 0; i < 50000; i++);

		GPIOA->ODR &= ~(count << 0);
		for(int i = 0; i < 30000; i++);

		GPIOA->ODR |= (count << 1);
		for(int i = 0; i < 50000; i++);

		GPIOA->ODR &= ~(count << 1);
		for(int i = 0; i < 40000; i++);

		GPIOA->ODR |= (count << 2);
		for(int i = 0; i < 50000; i++);

		GPIOA->ODR &= ~(count << 2);
		for(int i = 0; i < 30000; i++);

		GPIOA->ODR |= (count << 3);
		for(int i = 0; i < 50000; i++);

		GPIOA->ODR &= ~(count << 3);
		for(int i = 0; i < 20000; i++);

	}

	GPIOA->ODR = 0;
	for(int i = 0; i < 100000; i++);
	count = 0;
}
