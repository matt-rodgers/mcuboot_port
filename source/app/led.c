#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include <string.h>
#include "led.h"

#define LED_PORT GPIOB
#define LED_PIN  GPIO_PIN_0

void led_init(void)
{
    if (__HAL_RCC_GPIOB_IS_CLK_DISABLED()) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }

    GPIO_InitTypeDef GPIO_InitStruct;
    memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

void led_on(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, 1);
}

void led_off(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, 0);
}

void led_toggle(void)
{
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}

void led_deinit(void)
{
    if (__HAL_RCC_GPIOB_IS_CLK_ENABLED()) {
        HAL_GPIO_DeInit(LED_PORT, LED_PIN);
        __HAL_RCC_GPIOB_CLK_DISABLE();
    }
}
