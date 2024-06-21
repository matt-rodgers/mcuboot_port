#include "flash_map_backend/flash_map_backend.h"
#include "mcuboot_config/mcuboot_logging.h"

int flash_area_open(uint8_t id, const struct flash_area **area_outp)
{
    (void)id;
    (void)area_outp;
    MCUBOOT_LOG_DBG("flash_area_open\n");
    return -1;
}

void flash_area_close(const struct flash_area *fa)
{
    (void)fa;
    MCUBOOT_LOG_DBG("flash_area_close\n");
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
    (void)image_index;
    (void)slot;
    MCUBOOT_LOG_DBG("flash_area_id_from_multi_image_slot\n");
    return -1;
}
