#include <string.h>
#include "stm32f4xx_hal.h"
#include "serial.h"
#include "led.h"
#include "log.h"
#include "bootutil/bootutil.h"
#include "app_main.h"

void app_main(void)
{
	uint32_t delay_period = 1000;

	led_init();
	serial_init();

	led_off();

	LOG("Starting MCUboot\n");

	struct boot_rsp br;
	int ret = boot_go(&br);
	if (ret) {
		LOG("No bootable image\n");

		/* Set a fast LED flash to indicate error */
		delay_period = 100;
	}

	/* Boot the specified image */
	

	while (1)
	{
		led_toggle();
		LOG("toggle\n");

		const char * message = "hello world\n";
		serial_write((const uint8_t *)message, (uint16_t)strlen(message));

		HAL_Delay(delay_period);
	}
}
