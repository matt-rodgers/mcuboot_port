#ifndef LED_LED_DRIVER_H
#define LED_LED_DRIVER_H

/* Standard library includes */
#include <stdint.h>

/* ST includes */
#include "stm32f4xx.h"

/* Type definitions */
typedef enum
{
    ledGreen = 0,
    ledBlue = 1,
    ledRed = 2
} tLedColour;

/* Function prototypes */
void LED_Init(void);
void LED_On(tLedColour ledColour);
void LED_Off(tLedColour ledColour);
void LED_Toggle(tLedColour ledColour);

#endif