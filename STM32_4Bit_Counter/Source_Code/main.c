#include "binary_count.h"
#include <stdint.h>

#define MAX_4BIT 16
int main(void)
{

	uint32_t count = 0, status = 0;
	uint32_t LED[4] = {0,1,2,3};

	led_init(LED, 4);

	button_init(5);

	while(1){
		status = (GPIOA->IDR & (1<<5));
		if(status){
			count++;
			if(count >= 16) count = 0; // count should not exceed 15 (0 to 15 = 16)

			GPIOA->ODR = (GPIOA->ODR & ~0x0F) | (count & 0x0F); // Only update lower 4 bits (PA0–PA3)

			for(volatile int i=0; i<100000; i++); // wait for some time to avoid de-bounce

			while(GPIOA->IDR & (1 << 5)); // Wait until button released
		}
	}

	return 0;
}
