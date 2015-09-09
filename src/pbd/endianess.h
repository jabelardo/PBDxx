/* 
 * File:   endianess.h
 * Author: jabelardo
 *
 * Created on September 8, 2015, 8:53 PM
 */

#ifndef PBD_ENDIANESS_H
#define	PBD_ENDIANESS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

bool pbd_is_little_endian();

size_t pbd_get_size_from_uint16(bool little_endian, uint16_t value);

uint32_t pbd_get_uint32_from_uint16(bool little_endian, uint16_t value);

uint16_t pbd_get_uint16(bool little_endian, uint16_t value);

size_t pbd_get_size_from_uint32(bool little_endian, uint32_t value);

uint32_t pbd_get_uint32(bool little_endian, uint32_t value);

size_t pbd_get_size_from_uint64(bool little_endian, uint64_t value);

uint64_t pbd_get_uint64(bool little_endian, uint64_t value);

float pbd_get_float(bool little_endian, float value);

double pbd_get_double(bool little_endian, double value);

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_ENDIANESS_H */

