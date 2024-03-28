#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"

#include "board.h"


static void enable_clocks(void);
static void setup_gpio(void);
static void setup_gpio_leds(void);


/**
 * @brief Initialise all used peripherals
 */
void board_init(void)
{
    enable_clocks();
    setup_gpio();
}


/**
 * @brief Enabled clocks for all used peripherals
 */
static void enable_clocks(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
}


/**
 * @brief Set up all used GPIO pins
 */
static void setup_gpio(void)
{
    setup_gpio_leds();
}


/**
 * @brief Set up the GPIO pins used for LEDs
 */
static void setup_gpio_leds(void)
{
    LL_GPIO_InitTypeDef gpioInitData;
    GPIO_TypeDef * port;
    uint32_t pins;

    /* All LEDs are on port B */
    port = GPIOB;
    pins = PIN_LED1 | PIN_LED2 | PIN_LED3;

    /* Set LED pins to logic low before configuring as output */
    LL_GPIO_ResetOutputPin(port, PIN_LED1);
    LL_GPIO_ResetOutputPin(port, PIN_LED2);
    LL_GPIO_ResetOutputPin(port, PIN_LED3);

    /* Configure LED pins as output */
    gpioInitData.Pin = pins;
    gpioInitData.Mode = LL_GPIO_MODE_OUTPUT;
    gpioInitData.Speed = LL_GPIO_SPEED_FREQ_LOW;
    gpioInitData.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpioInitData.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(port, &gpioInitData);
}