#include "flash_map_backend/flash_map_backend.h"
#include "mcuboot_config/mcuboot_logging.h"
#include "mcuboot_config/mcuboot_config.h"
#include "sysflash/sysflash.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_flash_ex.h"
#include <string.h>

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
 *  32k bootloader (sector 0 - 1)
 *  96k unused (sector 2 - 4)
 *  128k slot 0 (sector 5)
 *  128k slot 1 (sector 6)
 *  128k scratch (sector 7)
 */

#define BOOTLOADER_START_ADDR               0x08000000
#define BOOTLOADER_SIZE                     (32 * 1024)
#define APPLICATION_PRIMARY_START_ADDRESS   0x08020000
#define APPLICATION_PRIMARY_SIZE            (128 * 1024)
#define APPLICATION_SECONDARY_START_ADDRESS 0x08040000
#define APPLICATION_SECONDARY_SIZE          (128 * 1024)
#define SCRATCH_START_ADDRESS               0x08060000
#define SCRATCH_SIZE                        (128 * 1024)

_Static_assert(BOOTLOADER_START_ADDR + BOOTLOADER_SIZE <= APPLICATION_PRIMARY_START_ADDRESS,
    "Bootloader and application overlap");
_Static_assert(APPLICATION_PRIMARY_START_ADDRESS + APPLICATION_PRIMARY_SIZE <= APPLICATION_SECONDARY_START_ADDRESS,
    "Application primary and secondary overlap");
_Static_assert(APPLICATION_SECONDARY_START_ADDRESS + APPLICATION_SECONDARY_SIZE <= SCRATCH_START_ADDRESS,
    "Application secondary and scratch overlap");

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

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

static const struct flash_area fa_scratch = {
    .fa_id = FLASH_AREA_IMAGE_SCRATCH,
    .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
    .fa_off = SCRATCH_START_ADDRESS,
    .fa_size = SCRATCH_SIZE
};

static const struct flash_area *flash_areas[] = {
    &fa_bootloader,
    &fa_app_primary,
    &fa_app_secondary,
    &fa_scratch,
};

const struct flash_sector flash_sectors[] = {
    /* Four 16k sectors */
    { .fs_off = 0x08000000, .fs_size = (16 * 1024) },
    { .fs_off = 0x08004000, .fs_size = (16 * 1024) },
    { .fs_off = 0x08008000, .fs_size = (16 * 1024) },
    { .fs_off = 0x0800C000, .fs_size = (16 * 1024) },
    /* One 64k sector */
    { .fs_off = 0x08010000, .fs_size = (64 * 1024) },
    /* Three 128k sectors */
    { .fs_off = 0x08020000, .fs_size = (128 * 1024) },
    { .fs_off = 0x08040000, .fs_size = (128 * 1024) },
    { .fs_off = 0x08060000, .fs_size = (128 * 1024) },
};

#define FLASH_SECTOR_COUNT ARRAY_SIZE(flash_sectors)
_Static_assert(FLASH_SECTOR_COUNT <= MCUBOOT_MAX_IMG_SECTORS, "Too many flash sectors");

static const struct flash_area * lookup_flash_area(uint8_t id)
{
    for (uint32_t i = 0; i < ARRAY_SIZE(flash_areas); i++) {
        if (flash_areas[i]->fa_id == id) {
            return flash_areas[i];
        }
    }

    return NULL;
}

int flash_area_open(uint8_t id, const struct flash_area **area_outp)
{
    MCUBOOT_LOG_DBG("flash_area_open: %u", id);

    if (NULL == area_outp) {
        MCUBOOT_LOG_ERR("NULL area_outp");
        return -1;
    }

    *area_outp = lookup_flash_area(id);

    if (*area_outp == NULL) {
        MCUBOOT_LOG_ERR("Flash area not found");
        return -1;
    }

    return 0;
}

void flash_area_close(const struct flash_area *fa)
{
    MCUBOOT_LOG_DBG("flash_area_close: %d", fa->fa_id);
    
    /* No cleanup required */
}

int flash_area_read(const struct flash_area *fa, uint32_t off,
                    void *dst, uint32_t len)
{
    if (NULL == fa || NULL == dst) {
        MCUBOOT_LOG_ERR("Invalid parameter");
        return -1;
    }

    if (FLASH_DEVICE_INTERNAL_FLASH != fa->fa_device_id) {
        MCUBOOT_LOG_ERR("Invalid flash device");
        return -1;
    }

    /* Offset is relative to the flash area offset */
    void * addr = (void *)(fa->fa_off + off);
    memcpy(dst, addr, len);

    return 0;
}

int flash_area_write(const struct flash_area *fa, uint32_t off,
                     const void *src, uint32_t len)
{
    (void)fa;
    (void)off;
    (void)src;
    (void)len;
    MCUBOOT_LOG_DBG("flash_area_write");
    return -1;
}

int flash_area_erase(const struct flash_area *fa,
                     uint32_t off, uint32_t len)
{
    MCUBOOT_LOG_DBG("flash_area_erase");

    /* Validate parameters and get sector information */
    if (NULL == fa) {
        return -1;
    }

    if (FLASH_DEVICE_INTERNAL_FLASH != fa->fa_device_id) {
        return -1;
    }

    FLASH_EraseInitTypeDef erase_init = {
        .TypeErase = FLASH_TYPEERASE_SECTORS,
        .Sector = UINT32_MAX,
        .NbSectors = 0,
        .VoltageRange = FLASH_VOLTAGE_RANGE_3,
    };

    uint32_t erase_start = fa->fa_off + off;
    for (uint32_t i = 0; i < FLASH_SECTOR_COUNT; i++) {
        if (flash_sectors[i].fs_off == erase_start) {
            erase_init.Sector = i;
            break;
        }
    }

    if (UINT32_MAX == erase_init.Sector) {
        MCUBOOT_LOG_ERR("Erase does not start on a sector boundary");
        return -1;
    }

    uint32_t erase_end = fa->fa_off + off + len;
    for (uint32_t i = 0; i < FLASH_SECTOR_COUNT; i++) {
        if (erase_end == flash_sectors[i].fs_off + flash_sectors[i].fs_size) {
            erase_init.NbSectors = (i + 1) - erase_init.Sector;
        }
    }

    if (erase_init.NbSectors > FLASH_SECTOR_COUNT) {
        MCUBOOT_LOG_ERR("Erase does not end on a sector boundary");
        return -1;
    }

    /* Unlock flash register access */
    HAL_FLASH_Unlock();

    uint32_t sector_error;
    int ret = HAL_FLASHEx_Erase(&erase_init, &sector_error);
    if (0 != ret) {
        MCUBOOT_LOG_ERR("Failed to erase flash, err %d", ret);
        return -1;
    }

    /* Lock flash register access */
    HAL_FLASH_Lock();

    return 0;
}

uint32_t flash_area_align(const struct flash_area *area)
{
    (void)area;
    return 1;
}

uint8_t flash_area_erased_val(const struct flash_area *area)
{
    (void)area;
    return 0xFF;
}

int flash_area_get_sectors(int fa_id, uint32_t *count,
                           struct flash_sector *sectors)
{
    MCUBOOT_LOG_DBG("flash_area_get_sectors, fa_id %d", fa_id);

    if (NULL == count || NULL == sectors) {
        MCUBOOT_LOG_ERR("Invalid parameter");
        return -1;
    }

    const struct flash_area * fa = lookup_flash_area(fa_id);

    if (NULL == fa) {
        MCUBOOT_LOG_ERR("Flash area not found");
        return -1;
    }

    if (FLASH_DEVICE_INTERNAL_FLASH != fa->fa_device_id) {
        MCUBOOT_LOG_ERR("Invalid flash device");
        return -1;
    }

    const uint32_t fa_start = fa->fa_off;
    const uint32_t fa_end = fa_start + fa->fa_size;

    *count = 0;

    for (uint32_t i = 0; i < FLASH_SECTOR_COUNT; i++) {
        const struct flash_sector * fs = &flash_sectors[i];
        
        /* If the flash sector falls within the flash area, add it to the list */
        if (fs->fs_off >= fa_start && fs->fs_off < fa_end) {
            sectors[*count].fs_off = fs->fs_off;
            sectors[*count].fs_size = fs->fs_size;
            (*count)++;

            MCUBOOT_LOG_DBG("Sector 0x%x (0x%x) is in flash area %d", fs->fs_off, fs->fs_size, fa->fa_id);
        }
    }

    return 0;
}

int flash_area_id_from_multi_image_slot(int image_index, int slot)
{
    if (0 != image_index) {
        MCUBOOT_LOG_ERR("Multi images not supported");
        return -1;
    }

    if (0 == slot) {
        return FLASH_AREA_IMAGE_PRIMARY(0);
    } else if (1 == slot) {
        return FLASH_AREA_IMAGE_SECONDARY(0);
    }

    MCUBOOT_LOG_ERR("Unsupported slot %d", slot);
    return -1;
}

int flash_area_id_from_image_slot(int slot)
{
    return flash_area_id_from_multi_image_slot(0, slot);
}

int flash_area_get_sector(const struct flash_area *area, uint32_t off,
                          struct flash_sector *sector)
{
    MCUBOOT_LOG_DBG("flash_area_get_sector, area %p off %u sector %p", area, off, sector);
    return -1;
}
