/* 
 * File:   arrayutils.h
 * Author: jabelardo
 *
 * Created on August 11, 2015, 9:18 PM
 */

#ifndef PBD_ARRAYUTILS_H
#define	PBD_ARRAYUTILS_H

#include "typeid.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum pbd_array_size_bytes {
        pbd_one_byte    = 1
    ,   pbd_two_bytes   = 2
    ,   pbd_four_bytes  = 4
} pbd_array_size_bytes;

pbd_array_size_bytes pbd_sizeof_array_size_by_value(size_t size);

pbd_array_size_bytes pbd_sizeof_array_size_by_type(pbd_type_id type_id);

uint32_t pbd_read_array_size(const char* buffer, pbd_array_size_bytes sizeof_array_size);

void pbd_write_array_size(char* buffer, size_t size, pbd_array_size_bytes sizeof_array_size);

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_ARRAYUTILS_H */

