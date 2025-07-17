#include "stm32f4xx.h"
#include "stm32f401xe.h"

#ifndef BINARY_COUNT_H_
#define BINARY_COUNT_H_

#define GPIOAEN			(1U<<0)
void led_init(uint32_t LED_OUT[4], int totalLED);
void button_init(int pinNumber);


#endif /* BINARY_COUNT_H_ */
