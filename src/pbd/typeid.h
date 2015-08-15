/* 
 * File:   typeid.h
 * Author: Jose Abelardo Gutierrez
 *
 * Created on August 8, 2015, 10:16 PM
 */

#ifndef PBD_TYPEID_H
#define	PBD_TYPEID_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <pbd/pbd.h>

#ifdef	__cplusplus
extern "C" {
#endif

pbd_type_id pbd_type_to_write(pbd_type_id type, size_t size);

pbd_type_id pbd_type_from_read(pbd_type_id type);

pbd_type_id pbd_type_best_integer(int64_t value);

pbd_type_id pbd_type_best_integer_array(int64_t min, int64_t max);

pbd_type_id pbd_type_best_real(double value);

pbd_type_id pbd_type_best_real_array(double min, double max);

size_t pbd_sizeof_integer_value(pbd_type_id type_id);

size_t pbd_sizeof_integer_array_value(pbd_type_id type_id);

size_t pbd_sizeof_real_value(pbd_type_id type_id);

size_t pbd_sizeof_real_array_value(pbd_type_id type_id);

bool pbd_is_unsigned(pbd_type_id type_id);

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_TYPEID_H */

