#include "stm32f4xx.h"

#define GPIOAEN  (1U<<0)
#define GPIOCEN  (1U<<2)

#define PIN5     (1U<<5)
#define PIN13    (1U<<13)

#define LED_PIN  PIN5
#define BTN_PIN  PIN13

int main(){
	//Enable RCC to GPIOA and GPIOC
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	//Set GPIOA to OUT and GPIOC to IN
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	GPIOC->MODER &= ~(1U<<26);     // for input set to 00
	GPIOC->MODER &= ~(1U<<27);


	while(1){
		if(GPIOC->IDR & BTN_PIN){
			/*Turn On LED if button pressed*/
			GPIOA->BSRRL = LED_PIN;
		}else{
			/*Turn OFF LED*/
			GPIOA->BSRRH = LED_PIN;
		}

	}
	return 0;
}



