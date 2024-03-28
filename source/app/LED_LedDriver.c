#include "stm32f4xx_ll_gpio.h"

#include "board.h"
#include "LED_LedDriver.h"


/* List of pins to initialise. The index of each LED in the following tables must correspond
   to the tLedColour enumerated value of the relevant LED. */
static GPIO_TypeDef * const mLedPortList[] = {PORT_LED1, PORT_LED2, PORT_LED3};
static const uint32_t mLedPinList[] = {PIN_LED1, PIN_LED2, PIN_LED3};


void LED_On(tLedColour ledColour)
{
    GPIO_TypeDef * pGpioPort = mLedPortList[ledColour];
    uint32_t gpioPin = mLedPinList[ledColour];

    LL_GPIO_SetOutputPin(pGpioPort, gpioPin);
}


void LED_Off(tLedColour ledColour)
{
    GPIO_TypeDef * pGpioPort = mLedPortList[ledColour];
    uint32_t gpioPin = mLedPinList[ledColour];
    
    LL_GPIO_ResetOutputPin(pGpioPort, gpioPin);
}


void LED_Toggle(tLedColour ledColour)
{
    GPIO_TypeDef * pGpioPort = mLedPortList[ledColour];
    uint32_t gpioPin = mLedPinList[ledColour];

    LL_GPIO_TogglePin(pGpioPort, gpioPin);
}