#include <string.h>
#include "stm32f4xx_hal.h"
#include "serial.h"
#include "led.h"
#include "button.h"
#include "log.h"
#include "bootutil/bootutil.h"
#include "sysflash/sysflash.h"
#include "boot_serial/boot_serial.h"
#include "core_cm4.h"
#include "app_main.h"

#define BTN_CHECK_INTV_MS   10
#define BTN_PRESS_TOTAL_MS  500

static struct boot_uart_funcs uart_funcs = {
	.read = NULL,
	.write = NULL
};

typedef void (*app_entry_t)(void);

static void start_app(struct boot_rsp *br)
{
	ASSERT(FLASH_DEVICE_INTERNAL_FLASH == br->br_flash_dev_id);
	uint32_t vector_table_addr = FLASH_DEVICE_INTERNAL_FLASH_BASE + br->br_image_off + br->br_hdr->ih_hdr_size;
	uint32_t *vector_table = (uint32_t *)vector_table_addr;
	uint32_t app_sp = vector_table[0];
	app_entry_t app_entry = (app_entry_t)vector_table[1];

	LOG("Got bootable image with sp 0x%x, pc 0x%x\n", app_sp, app_entry);

	/* De-initialise peripherals */
	button_deinit();
	led_deinit();
	serial_deinit();

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

void app_main(void)
{
	LOG("Starting MCUboot\n");

	/* Init peripherals */
	button_init();
	led_init();
	serial_init();

	/* Turn on indicator LED */
	led_on();

	bool serial_recovery_mode = true;
	for (uint32_t i = 0; i < (BTN_PRESS_TOTAL_MS / BTN_CHECK_INTV_MS); i++) {
		if (!button_read()) {
			serial_recovery_mode = false;
			break;
		}

		HAL_Delay(BTN_CHECK_INTV_MS);
	}

	if (!serial_recovery_mode) {
		struct boot_rsp br = {0};
		int ret = boot_go(&br);
		if (0 == ret) {
			start_app(&br);
			/* start_app should not return */
		}
	}

	/* Enter serial recovery mode */
	boot_serial_start(&uart_funcs);
}
