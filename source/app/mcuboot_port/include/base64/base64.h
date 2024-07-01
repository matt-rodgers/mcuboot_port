#ifndef _BASE64_H
#define _BASE64_H

/* From Zephyr and Espressif ports */
#define BASE64_ENCODE_SIZE(in_size) ((((((in_size) - 1) / 3) * 4) + 4) + 1)

/**
 * @brief Base64 encode data
 * 
 * @param buf_in Input buffer
 * @param in_len Length of data to encode
 * @param buf_out Output buffer
 * @param param Unused, needed to match required function signature
 * 
 * @note It is assumed that buf_out is large enough to hold the encoded data. The buffer can be
 *       sized using BASE64_ENCODE_SIZE macro.
 * 
 * @return The length of the encoded data, not including NULL termination (if any)
 */
uint16_t base64_encode(char * buf_in, uint16_t in_len, char * buf_out, int param);

/**
 * @brief Base64 decode data
 * 
 * @param buf_in Input buffer (NULL terminated string)
 * @param buf_out Output buffer
 * 
 * @return Length of decoded data, or negative error code
 */
int base64_decode(char * buf_in, char * buf_out);

/**
 * @brief Get required length of buffer for base64 decode, given an encoded input buffer
 * 
 * @param buf_in Encoded input buffer
 * 
 * @note Encoded input buffer should be NULL terminated if all is well. But the function must
 *       handle the case where it is not NULL terminated (returning an error).
 * 
 * @return Decoded length, or a number larger than MCUBOOT_SERIAL_MAX_RECEIVE_SIZE on error
*/
int base64_decode_len(char * buf_in);

#endif /* _BASE64_H */
