#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>

void serial_init(void);

void serial_write(const char * data, int len);

int serial_read(char * data, int cnt, int *newline);

void serial_deinit(void);

#endif /* _SERIAL_H */