#include "ledControl.h"
#include "exti.h"
#include <stdint.h>

#define LINE0			(1U << 0)
#define LINE1			(1U << 1)
#define LINE9			(1U << 9)
#define LINE10			(1U << 10)

#define LED1			(1U << 0)
#define LED2			(1U << 1)
#define LED3			(1U << 2)
#define LED4			(1U << 3)


int main(void)
{
	uint32_t LED[] = {0,1,2,3};
	led_init(LED, 4);

	uint32_t BTN[] = {0,1,9,10};
	button_init(BTN, 4);

	port_b_exti_init();

	while(1){
		;
	}

	return 0;
}

void EXTI0_IRQHandler(void){
	if(EXTI->PR & LINE0){
		/*Clear PR0*/
		EXTI->PR |= LINE0;

		/*Software De-bounce*/
		for(int i = 0; i < 100000; i++);

		if(GPIOB->IDR & LINE0){
			GPIOA->ODR ^= LED1;
		}
	}
}

void EXTI1_IRQHandler(void){
	if(EXTI->PR & LINE1){
		/*Clear PR0*/
		EXTI->PR = LINE1;

		/*Software De-bounce*/
		for(int i = 0; i < 10000; i++);

		if(GPIOB->IDR & LINE1){
			GPIOA->ODR ^= LED2;
		}
	}
}

void EXTI9_5_IRQHandler(void){
	if(EXTI->PR & LINE9){
		/*Clear PR0*/
		EXTI->PR = LINE9;

		/*Software De-bounce*/
		for(int i = 0; i < 10000; i++);

		if(GPIOB->IDR & LINE9){
			GPIOA->ODR ^= LED3;
		}
	}

}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & LINE10){
		/*Clear PR0*/
		EXTI->PR = LINE10;

		/*Software De-bounce*/
		for(int i = 0; i < 10000; i++);

		if(GPIOB->IDR & LINE10){
			GPIOA->ODR ^= LED4;
		}
	}

}
