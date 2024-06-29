#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32_assert.h"
#include <string.h>

#include "serial.h"

#define SERIAL_UART USART3

static UART_HandleTypeDef serial_uart_handle;

void serial_init(void)
{
	memset(&serial_uart_handle, 0, sizeof(serial_uart_handle));
	serial_uart_handle.Instance = SERIAL_UART;
	serial_uart_handle.Init.BaudRate = 115200;
	serial_uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	serial_uart_handle.Init.StopBits   = UART_STOPBITS_1;
	serial_uart_handle.Init.Parity     = UART_PARITY_NONE;
	serial_uart_handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	serial_uart_handle.Init.Mode       = UART_MODE_TX_RX;
	serial_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&serial_uart_handle);
}

void serial_write(const uint8_t * msg, uint16_t len)
{
    HAL_UART_Transmit(&serial_uart_handle, msg, len, UINT32_MAX);
}

void serial_deinit(void)
{
	HAL_UART_DeInit(&serial_uart_handle);
}

/**
 * @brief called by HAL driver to set up clocks and pinmux for UART
*/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	assert_param(SERIAL_UART == huart);
    (void)huart;

	GPIO_InitTypeDef  GPIO_InitStruct;

	/* Enable GPIO TX/RX clock */
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/* Enable USARTx clock */
	__HAL_RCC_USART3_CLK_ENABLE();

	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = GPIO_PIN_8;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/**
 * @brief called by HAL driver to deinit clocks and pinmux for UART
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	assert_param(SERIAL_UART == huart);
	(void)huart;

	HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8);
	HAL_GPIO_DeInit(GPIOD, GPIO_PIN_9);

	if (__HAL_RCC_GPIOD_IS_CLK_ENABLED()) {
		__HAL_RCC_GPIOD_CLK_DISABLE();
	}

	if (__HAL_RCC_USART3_IS_CLK_ENABLED()) {
		__HAL_RCC_USART3_CLK_DISABLE();
	}
}
