#include "board.h"
#include "LED_LedDriver.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include <string.h>
#include "app_main.h"



void app_main(void)
{
	board_init();

	UART_HandleTypeDef UartHandle;
	memset(&UartHandle, 0, sizeof(UartHandle));
	UartHandle.Instance = USART3;
	UartHandle.Init.BaudRate = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UartHandle);

	while (1)
	{
		LED_Toggle(ledRed);

		const char * message = "hello world\n";
		HAL_UART_Transmit(&UartHandle, (const uint8_t *)message, (uint16_t)strlen(message), UINT32_MAX);

		HAL_Delay(1000);
	}
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
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
