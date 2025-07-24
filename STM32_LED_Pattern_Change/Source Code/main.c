#include "ledControl.h"
#include "exti.h"
#include <stdint.h>

#define LINE0			(1U << 0)

volatile int pattern = 0;

int main(void)
{
	uint32_t LED[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	led_init(LED, 16);

	pb0_exti_init();

	while(1){
		if(pattern == 1)	pattern1();
		else if(pattern == 2)	pattern2();
		else if(pattern == 3)	pattern3();
	}

	return 0;
}

void EXTI0_IRQHandler(void){
	if(EXTI->PR & LINE0){
		/* Clear PR0 Flag */
		EXTI->PR |= LINE0;

		/* Pattern Change */
		for(int i=0; i<100000; i++);
		if(GPIOB->IDR & LINE0){
			if(pattern < 3)	pattern++;
			else	pattern = 1;
		}
	}
}
