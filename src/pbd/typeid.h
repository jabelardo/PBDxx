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

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum pbd_type_id {
        pbd_type_unknown	      =   0
    /**
     * IMPORT NOTE: the delta value between _scalar and _array types must use 
     * scalar_delta value, because both select_best_integer and select_best_real
     * implementation needs that to work properly.
     */
    ,   pbd_type_int8_scalar   =   1
    ,   pbd_type_uint8_scalar  =   4
    ,   pbd_type_int16_scalar  =   7
    ,   pbd_type_uint16_scalar =  10
    ,   pbd_type_int32_scalar  =  13
    ,   pbd_type_uint32_scalar =  16
    ,   pbd_type_int64_scalar  =  19
    ,   pbd_type_float_scalar  =  22
    ,   pbd_type_double_scalar =  25
        
    ,   pbd_type_scalar_delta  =  40
    ,   pbd_type_int8_array    =  41
    ,   pbd_type_uint8_array   =  44
    ,   pbd_type_int16_array   =  47
    ,   pbd_type_uint16_array  =  50
    ,   pbd_type_int32_array   =  53
    ,   pbd_type_uint32_array  =  56
    ,   pbd_type_int64_array   =  59
    ,   pbd_type_float_array   =  62
    ,   pbd_type_double_array  =  65

    ,   pbd_type_real          =  80
    ,   pbd_type_integer       =  81
    ,   pbd_type_bool          =  82
    ,   pbd_type_null          =  83
    
    ,   pbd_type_string        =  84
    ,   pbd_type_integer_array =  87
    ,   pbd_type_real_array    =  90
    ,   pbd_type_bool_array    =  93
    ,   pbd_type_element_array =  96
    
    ,   pbd_type_int8_array_one_byte       = pbd_type_int8_array
    ,   pbd_type_int8_array_two_bytes
    ,   pbd_type_int8_array_four_bytes
    
    ,   pbd_type_uint8_array_one_byte      = pbd_type_uint8_array
    ,   pbd_type_uint8_array_two_bytes
    ,   pbd_type_uint8_array_four_bytes
    
    ,   pbd_type_int16_array_one_byte      = pbd_type_int16_array
    ,   pbd_type_int16_array_two_bytes
    ,   pbd_type_int16_array_four_bytes
    
    ,   pbd_type_uint16_array_one_byte     = pbd_type_uint16_array
    ,   pbd_type_uint16_array_two_bytes
    ,   pbd_type_uint16_array_four_bytes
    
    ,   pbd_type_int32_array_one_byte      = pbd_type_int32_array
    ,   pbd_type_int32_array_two_bytes
    ,   pbd_type_int32_array_four_bytes
    
    ,   pbd_type_uint32_array_one_byte     = pbd_type_uint32_array
    ,   pbd_type_uint32_array_two_bytes
    ,   pbd_type_uint32_array_four_bytes
    
    ,   pbd_type_int64_array_one_byte      = pbd_type_int64_array
    ,   pbd_type_int64_array_two_bytes
    ,   pbd_type_int64_array_four_bytes
    
    ,   pbd_type_float_array_one_byte      = pbd_type_float_array
    ,   pbd_type_float_array_two_bytes
    ,   pbd_type_float_array_four_bytes
    
    ,   pbd_type_double_array_one_byte     = pbd_type_double_array
    ,   pbd_type_double_array_two_bytes
    ,   pbd_type_double_array_four_bytes
    
    ,   pbd_type_bool_array_one_byte    = pbd_type_bool_array
    ,   pbd_type_bool_array_two_bytes
    ,   pbd_type_bool_array_four_bytes
        
    ,   pbd_type_element_array_one_byte    = pbd_type_element_array
    ,   pbd_type_element_array_two_bytes
    ,   pbd_type_element_array_four_bytes
    
    ,   pbd_type_string_one_byte           = pbd_type_string
    ,   pbd_type_string_two_bytes
    ,   pbd_type_string_four_bytes
                
} pbd_type_id;

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

