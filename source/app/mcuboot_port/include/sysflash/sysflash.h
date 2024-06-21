#ifndef _SYSFLASH_H
#define _SYSFLASH_H

#define FLASH_DEVICE_INTERNAL_FLASH      0
#define FLASH_DEVICE_INTERNAL_FLASH_BASE 0x0

#define FLASH_SLOT_DOES_NOT_EXIST 255

#define FLASH_AREA_BOOTLOADER 0
#define FLASH_AREA_IMAGE_SCRATCH 3

#define FLASH_AREA_IMAGE_PRIMARY(i) ((i == 0) ? 1 : 255)
#define FLASH_AREA_IMAGE_SECONDARY(i) ((i == 0) ? 2 : 255)

#endif /* _SYSFLASH_H */
