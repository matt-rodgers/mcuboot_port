#ifndef _CRC_16_H
#define _CRC_16_H

/* Seed for CRC16 */
#define CRC16_INITIAL_CRC       0

/**
 * @brief Calculate CCITT CRC16 for a block of data
 * 
 * @param initial Initial value of CRC
 * @param data Data to calculate CRC for
 * @param len Length of data
*/
uint16_t crc16_ccitt(uint16_t initial, void * data, uint16_t len);

#endif /* _CRC_16_H */
