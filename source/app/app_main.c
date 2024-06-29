#include <string.h>
#include "stm32f4xx_hal.h"
#include "serial.h"
#include "led.h"
#include "button.h"
#include "log.h"
#include "bootutil/bootutil.h"
#include "sysflash/sysflash.h"
#include "core_cm4.h"
#include "app_main.h"

typedef void (*app_entry_t)(void);

void app_main(void)
{
	LOG("Starting MCUboot\n");

	button_init();

	if (button_read()) {
		LOG("Button state is 1\n");
	} else {
		LOG("Button state is 0\n");
	}

	HAL_Delay(5000);

	struct boot_rsp br;
	int ret = boot_go(&br);
	if (ret) {
		LOG("No bootable image\n");

		/* Fast flash LED to indicate issue */
		led_init();

		while (1) {
			led_toggle();
			HAL_Delay(100);
		}
	}

	/* We have a bootable image, start it */
	ASSERT(FLASH_DEVICE_INTERNAL_FLASH == br.br_flash_dev_id);
	uint32_t vector_table_addr = FLASH_DEVICE_INTERNAL_FLASH_BASE + br.br_image_off + br.br_hdr->ih_hdr_size;
	uint32_t *vector_table = (uint32_t *)vector_table_addr;
	uint32_t app_sp = vector_table[0];
	app_entry_t app_entry = (app_entry_t)vector_table[1];

	LOG("Got bootable image with sp 0x%x, pc 0x%x\n", app_sp, app_entry);

	/* TODO de-initialise peripherals */

	/* Disable interrupts */
	__disable_irq();

	/* Update vector table offset */
	SCB->VTOR = vector_table_addr;
	__DSB();

	/* Set stack pointer */
	__set_MSP(app_sp);

	/* Jump to application */
	app_entry();

	/* Should not get here! */
	ASSERT(0);
}
