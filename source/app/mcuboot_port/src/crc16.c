#include "crc/crc16.h"

/* Implementation from Zephyr */
uint16_t crc16_ccitt(uint16_t initial, void * data, uint16_t len)
{
    uint8_t * src = (uint8_t *)data;

	for (; len > 0; len--) {
		initial = (initial >> 8U) | (initial << 8U);
		initial ^= *src;
		++src;
		initial ^= (initial & 0xffU) >> 4U;
		initial ^= initial << 12U;
		initial ^= (initial & 0xffU) << 5U;
	}

	return initial;
}
