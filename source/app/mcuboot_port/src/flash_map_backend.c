#include "flash_map_backend/flash_map_backend.h"
#include "mcuboot_config/mcuboot_logging.h"
#include "sysflash/sysflash.h"

/* STM32F446 flash layout:
 *
 * Sector 0 0x0800 0000 - 0x0800 3FFF 16 Kbytes
 * Sector 1 0x0800 4000 - 0x0800 7FFF 16 Kbytes
 * Sector 2 0x0800 8000 - 0x0800 BFFF 16 Kbytes
 * Sector 3 0x0800 C000 - 0x0800 FFFF 16 Kbytes
 * Sector 4 0x0801 0000 - 0x0801 FFFF 64 Kbytes
 * Sector 5 0x0802 0000 - 0x0803 FFFF 128 Kbytes
 * Sector 6 0x0804 0000 - 0x0805 FFFF 128 Kbytes
 * Sector 7 0x0806 0000 - 0x0807 FFFF 128 Kbytes
 * 
 * Assignments:
 *  32k bootloader (sector 0 and 2)
 *  224k slot 1 (sector 2 - 5)
 *  256k slot 0 (sector 6 - 7)
 * 
 * We want the primary slot to be larger than the secondary slot, hence swapping 0 and 1
 */

#define BOOTLOADER_START_ADDR               0x08000000
#define BOOTLOADER_SIZE                     (32 * 1024)
#define APPLICATION_PRIMARY_START_ADDRESS   0x08040000
#define APPLICATION_PRIMARY_SIZE            (256 * 1024)
#define APPLICATION_SECONDARY_START_ADDRESS 0x08008000
#define APPLICATION_SECONDARY_SIZE          (224 * 1024)

_Static_assert(BOOTLOADER_START_ADDR + BOOTLOADER_SIZE <= APPLICATION_SECONDARY_START_ADDRESS,
    "Bootloader and application overlap");
_Static_assert(APPLICATION_SECONDARY_START_ADDRESS + APPLICATION_SECONDARY_SIZE <= APPLICATION_PRIMARY_START_ADDRESS,
    "Application primary and secondary overlap");

static const struct flash_area fa_bootloader = {
    .fa_id = FLASH_AREA_BOOTLOADER,
    .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
    .fa_off = BOOTLOADER_START_ADDR,
    .fa_size = BOOTLOADER_SIZE
};

static const struct flash_area fa_app_primary = {
    .fa_id = FLASH_AREA_IMAGE_PRIMARY(0),
    .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
    .fa_off = APPLICATION_PRIMARY_START_ADDRESS,
    .fa_size = APPLICATION_PRIMARY_SIZE
};

static const struct flash_area fa_app_secondary = {
    .fa_id = FLASH_AREA_IMAGE_SECONDARY(0),
    .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
    .fa_off = APPLICATION_SECONDARY_START_ADDRESS,
    .fa_size = APPLICATION_SECONDARY_SIZE
};

static const struct flash_area *flash_areas[] = {
    &fa_bootloader,
    &fa_app_primary,
    &fa_app_secondary
};

int flash_area_open(uint8_t id, const struct flash_area **area_outp)
{
    MCUBOOT_LOG_DBG("flash_area_open: %u\n", id);

    if (NULL == area_outp) {
        MCUBOOT_LOG_ERR("NULL area_outp\n");
        return -1;
    }

    *area_outp = NULL;
    for (uint32_t i = 0; i < sizeof(flash_areas) / sizeof(flash_areas[0]); i++) {
        if (flash_areas[i]->fa_id == id) {
            *area_outp = flash_areas[i];
            break;
        }
    }

    if (*area_outp == NULL) {
        MCUBOOT_LOG_ERR("Flash area not found\n");
        return -1;
    }

    return 0;
}

void flash_area_close(const struct flash_area *fa)
{
    MCUBOOT_LOG_DBG("flash_area_close: %u\n", fa);
    
    /* No cleanup required */
}

int flash_area_read(const struct flash_area *fa, uint32_t off,
                    void *dst, uint32_t len)
{
    (void)fa;
    (void)off;
    (void)dst;
    (void)len;
    MCUBOOT_LOG_DBG("flash_area_read\n");
    return -1;
}

int flash_area_write(const struct flash_area *fa, uint32_t off,
                     const void *src, uint32_t len)
{
    (void)fa;
    (void)off;
    (void)src;
    (void)len;
    MCUBOOT_LOG_DBG("flash_area_write\n");
    return -1;
}

int flash_area_erase(const struct flash_area *fa,
                     uint32_t off, uint32_t len)
{
    (void)fa;
    (void)off;
    (void)len;
    MCUBOOT_LOG_DBG("flash_area_erase\n");
    return -1;
}

uint32_t flash_area_align(const struct flash_area *area)
{
    (void)area;
    MCUBOOT_LOG_DBG("flash_area_align\n");
    return UINT32_MAX;
}

uint8_t flash_area_erased_val(const struct flash_area *area)
{
    (void)area;
    return 0xFF;
}

int flash_area_get_sectors(int fa_id, uint32_t *count,
                           struct flash_sector *sectors)
{
    (void)fa_id;
    (void)count;
    (void)sectors;
    MCUBOOT_LOG_DBG("flash_area_get_sectors\n");
    return -1;
}

int flash_area_id_from_multi_image_slot(int image_index, int slot)
{
    MCUBOOT_LOG_DBG("flash_area_id_from_multi_image_slot, img %d slot %d\n", image_index, slot);
    
    if (0 != image_index) {
        MCUBOOT_LOG_ERR("Multi images not supported\n");
        return -1;
    }

    if (0 == slot) {
        return FLASH_AREA_IMAGE_PRIMARY(0);
    } else if (1 == slot) {
        return FLASH_AREA_IMAGE_SECONDARY(0);
    }

    MCUBOOT_LOG_ERR("Unsupported slot %d\n", slot);
    return -1;
}

int flash_area_get_sector(const struct flash_area *area, uint32_t off,
                          struct flash_sector *sector)
{
    MCUBOOT_LOG_DBG("flash_area_get_sector, area %p off %u sector %p\n", area, off, sector);
    return -1;
}