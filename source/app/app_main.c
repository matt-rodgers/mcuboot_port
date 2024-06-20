#include <string.h>
#include "stm32f4xx_hal.h"
#include "serial.h"
#include "led.h"
#include "log.h"
#include "app_main.h"

void app_main(void)
{
	led_init();
	serial_init();

	led_off();

	LOG("hello world\n");

	while (1)
	{
		led_toggle();
		LOG("toggle\n");

		const char * message = "hello world\n";
		serial_write((const uint8_t *)message, (uint16_t)strlen(message));

		HAL_Delay(1000);
	}
}
