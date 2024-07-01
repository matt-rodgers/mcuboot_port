#include <string.h>
#include "mcuboot_config/mcuboot_config.h"
#include "mcuboot_config/mcuboot_assert.h"
#include "mbedtls/base64.h"
#include "base64/base64.h"

uint16_t base64_encode(char * buf_in, uint16_t in_len, char * buf_out, int param)
{
    size_t out_len = 0;

    int rc = mbedtls_base64_encode((unsigned char *)buf_out, BASE64_ENCODE_SIZE(in_len), &out_len,
                                   (const unsigned char *)buf_in, in_len);
    ASSERT(0 == rc);

    return (uint16_t)out_len;
}

int base64_decode(char * buf_in, char * buf_out)
{
    /* Make the assumption that the output buffer is large enough - it should already have been
       size-checked using base64_decode_len */
    size_t dest_len = MCUBOOT_SERIAL_MAX_RECEIVE_SIZE;
    size_t in_len = strnlen(buf_in, MCUBOOT_SERIAL_MAX_RECEIVE_SIZE);
    size_t out_len = 0;

    int rc = mbedtls_base64_decode((unsigned char *)buf_out, dest_len, &out_len,
                                   (const unsigned char *)buf_in, in_len);
    if (0 == rc) {
        return (int)out_len;
    }

    return rc;
}

int base64_decode_len(char * buf_in)
{
    size_t out_len = MCUBOOT_SERIAL_MAX_RECEIVE_SIZE;
    size_t in_len = strnlen(buf_in, MCUBOOT_SERIAL_MAX_RECEIVE_SIZE);

    (void)mbedtls_base64_decode(NULL, 0, &out_len, (const unsigned char *)buf_in, in_len);
    return (int)out_len;
}
