#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include <string.h>
#include "button.h"

#define BTN_PORT GPIOC
#define BTN_PIN  GPIO_PIN_13

int button_init(void)
{
    if (__HAL_RCC_GPIOC_IS_CLK_DISABLED()) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

    GPIO_InitTypeDef GPIO_InitStruct;
    memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
    GPIO_InitStruct.Pin = BTN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(BTN_PORT, &GPIO_InitStruct);

    return 0;
}

int button_read(void)
{
    return HAL_GPIO_ReadPin(BTN_PORT, BTN_PIN);
}
