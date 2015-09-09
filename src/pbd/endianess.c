#if defined(__APPLE__)
    #include <libkern/OSByteOrder.h>
    #define bswap_16 OSSwapInt16
    #define bswap_32 OSSwapInt32
    #define bswap_64 OSSwapInt64
#elif defined(__linux__)
    #include <byteswap.h>
#elif defined(__OpenBSD__)
    #include <sys/endian.h>
    #define bswap_16 __swap16
    #define bswap_32 __swap32
    #define bswap_64 __swap64
#endif

#include "endianess.h"

bool pbd_is_little_endian() { 
    int n = 1; 
    return (*(char *) & n == 1);
}

size_t pbd_get_size_from_uint16(bool little_endian, uint16_t value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_16(value);
    }
}

uint32_t pbd_get_uint32_from_uint16(bool little_endian, uint16_t value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_16(value);
    }
}

uint16_t pbd_get_uint16(bool little_endian, uint16_t value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_16(value);
    }
}

size_t pbd_get_size_from_uint32(bool little_endian, uint32_t value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_32(value);
    }
}

uint32_t pbd_get_uint32(bool little_endian, uint32_t value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_32(value);
    }
}

size_t pbd_get_size_from_uint64(bool little_endian, uint64_t value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_64(value);
    }
}

uint64_t pbd_get_uint64(bool little_endian, uint64_t value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_64(value);
    }
}

float pbd_get_float(bool little_endian, float value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_32(value);
    }
    
}

double pbd_get_double(bool little_endian, double value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
        return bswap_64(value);
    }
}
