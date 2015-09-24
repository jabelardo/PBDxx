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
#elif defined(_WIN32)
	#include <stdlib.h>
    #define bswap_16 _byteswap_ushort
	#define bswap_32 _byteswap_ulong 
	#define bswap_64 _byteswap_uint64
#endif

#include <string.h>
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
        return (size_t) value;
    } else {
        return (size_t) bswap_64(value);
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
		uint32_t in_raw_value;
		memcpy(&in_raw_value, &value, sizeof(in_raw_value));
		uint32_t swap_raw_value = bswap_32(in_raw_value);
		float result = *(float*)swap_raw_value;
        return result;
    }
    
}

double pbd_get_double(bool little_endian, double value) {
    if (pbd_is_little_endian() == little_endian) {
        return value;
    } else {
		uint64_t in_raw_value;
		memcpy(&in_raw_value, &value, sizeof(in_raw_value));
		uint64_t swap_raw_value = bswap_64(in_raw_value);
		double result = *(double*) swap_raw_value;
		return result;
    }
}
