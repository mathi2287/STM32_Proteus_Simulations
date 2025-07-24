#include "exti.h"

#define GPIOBEN			(1U << 1)
#define SYSCFGEN		(1U << 14)


void pb0_exti_init(void){
	/* Disable Global Interrupts */
	__disable_irq();

	/* Enable clock access to PB0 and set as input mode */
	RCC->AHB1ENR |= GPIOBEN;

	GPIOB->MODER &= ~(1U << 0);
	GPIOB->MODER &= ~(1U << 1);

	GPIOB->PUPDR |= (1U << 1);
	GPIOB->PUPDR &= ~(1U << 0);

	/* Enable clock access to SYSCFG */
	RCC->APB2ENR |= SYSCFGEN;

	/*Select PB[0] as EXTI0 */
	SYSCFG->EXTICR[0] |= (1U << 0);

	/* Un-mask EXTI0 */
	EXTI->IMR |= (1U << 0);

	/* Select Falling edge trigger */
	EXTI->RTSR |= (1U << 0);

	/* Enable EXTI0 line in NVIC */
	NVIC_EnableIRQ(EXTI0_IRQn);

	/* Enable global interrupt */
	__enable_irq();
}
