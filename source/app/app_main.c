#include "board.h"
#include "LED_LedDriver.h"
#include "stm32f4xx_ll_utils.h"
#include "app_main.h"

void app_main(void)
{
	board_init();

	while (1)
	{
		LED_Toggle(ledRed);

		LL_mDelay(1000);
	}
}
