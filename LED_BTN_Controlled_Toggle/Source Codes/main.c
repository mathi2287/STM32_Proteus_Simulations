#include "ledControl.h"
#include <stdint.h>

int main(void)
{
	uint32_t LED[] = {0,1,2,3};
	led_init(LED, 4);

	uint32_t BTN[] = {0,1,2,3};
	button_init(BTN, 4);

	uint32_t Status = 0;
	while(1){
		Status = GPIOB->IDR;
		if(Status & (1UL << 0))	GPIOA->ODR ^= (1 << LED[0]);
		else if(Status & (1UL << 1))	GPIOA->ODR ^= (1 << LED[1]);
		else if(Status & (1UL << 2))	GPIOA->ODR ^= (1 << LED[2]);
		else if(Status & (1UL << 3))	GPIOA->ODR ^= (1 << LED[3]);
	}

	return 0;
}
