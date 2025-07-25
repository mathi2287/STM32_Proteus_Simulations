#include "exti.h"

#define GPIOBEN			(1U << 1)
#define SYSCFGEN		(1U << 14)

#define EXTI_PB0		(1U << 0)
#define EXTI_PB1		(1U << 4)
#define EXTI_PB9		(1U << 4)
#define EXTI_PB10		(1U << 8)


void port_b_exti_init(void){
	/* Disable Global Interrupts */
	__disable_irq();

	/* Enable clock access to SYSCFG */
	RCC->APB2ENR |= SYSCFGEN;

	/*Select PB[0], PB[1], PB[9], PB[10] as EXTI0, EXTI1, EXTI9, EXTI10*/
	SYSCFG->EXTICR[0] |= EXTI_PB0 | EXTI_PB1;
	SYSCFG->EXTICR[2] |= EXTI_PB9 | EXTI_PB10;

	/*Un-mask Interrupts*/
	EXTI->IMR |= (1U << 0) | (1U << 1) | (1U << 9) | (1U << 10); //0110 0000 0011 EXTI10, EXTI9, EXTI1 and EXTI0

	/*Enable Interrupt on Rising Edge*/
	EXTI->RTSR |= (1U << 0) | (1U << 1) | (1U << 9) | (1U << 10);

	/*Enable Interrupts in NVIC*/
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/* Enable Global Interrupts*/
	__enable_irq();
}
