#ifndef _ENDIAN_H
#define _ENDIAN_H

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

static inline uint16_t ntohs(uint16_t netshort)
{
    return netshort;
}

static inline uint16_t htons(uint16_t hostshort)
{
    return hostshort;
}

#elif defined (__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

#define SWAP_ENDIAN_16(in) ((((in) & 0x00FF) << 8) | (((in) & 0xFF00) >> 8))

static inline uint16_t ntohs(uint16_t netshort)
{
    return SWAP_ENDIAN_16(netshort);
}

static inline uint16_t htons(uint16_t hostshort)
{
    return SWAP_ENDIAN_16(hostshort);
}

#else
#error "Unknown endianness"
#endif

#endif /* _ENDIAN_H */
