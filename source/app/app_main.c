#include "board.h"
#include "LED_LedDriver.h"
#include "stm32f4xx_hal.h"
#include "app_main.h"

void app_main(void)
{
	board_init();

	while (1)
	{
		LED_Toggle(ledRed);

		HAL_Delay(1000);
	}
}
