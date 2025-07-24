#include "stm32f4xx.h"
#include "stm32f401xe.h"

#ifndef LEDCONTROL_H_
#define LEDCONTROL_H_

#define GPIOAEN					(1U<<0)
#define GPIOBEN					(1U<<1)

void led_init(uint32_t LED_OUT[16], int totalLED);

void pattern1(void);
void pattern2(void);
void pattern3(void);

#endif
