#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>

void serial_init(void);

void serial_write(const uint8_t * msg, uint16_t len);

#endif /* _SERIAL_H */