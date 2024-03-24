#ifndef BOARD_H
#define BOARD_H

#include "stm32f4xx.h"

// GPIO ports
#define PORT_LED1   GPIOB
#define PORT_LED2   GPIOB
#define PORT_LED3   GPIOB

// GPIO pins
#define PIN_LED1     LL_GPIO_PIN_0
#define PIN_LED2     LL_GPIO_PIN_7
#define PIN_LED3     LL_GPIO_PIN_14

void board_init(void);

#endif