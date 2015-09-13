/* 
 * File:   pbd.h
 * Author: jabelardo
 *
 * Created on August 10, 2015, 12:07 PM
 */

#ifndef PBD_H
#define	PBD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <pbd/pbdconf.h>

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
    
typedef struct pbd_element pbd_element;

/* element */
pbd_type_id pbd_element_type(const pbd_element* e);

int pbd_element_to_buffer(const pbd_element* e, char** buffer, size_t* size);

int pbd_element_to_buffer_custom(pbd_conf conf, const pbd_element* e, char** buffer, size_t* size);

pbd_element* pbd_element_from_buffer(const char* buffer, size_t* read_bytes);

pbd_element* pbd_element_from_buffer_custom(pbd_conf conf, const char* buffer, size_t* read_bytes);

pbd_element* pbd_element_create(const char* buffer);

pbd_element* pbd_element_create_custom(pbd_conf conf, const char* buffer);

void pbd_element_free(const pbd_element* e);

void pbd_element_free_custom(pbd_conf conf, const pbd_element* e);

pbd_element* pbd_element_new(pbd_type_id type);

pbd_element* pbd_element_new_custom(pbd_conf conf, pbd_type_id type);

/* null */
pbd_element* pbd_null_new();

pbd_element* pbd_null_new_custom(pbd_conf conf);

/* bool */
pbd_element* pbd_bool_new();

pbd_element* pbd_bool_new_custom(pbd_conf conf);

pbd_element* pbd_bool_create(bool value);

pbd_element* pbd_bool_create_custom(pbd_conf conf, bool value);

void pbd_bool_set(pbd_element* e, bool value);

bool pbd_bool_get(const pbd_element* e);

/* integer */
pbd_element* pbd_integer_new();

pbd_element* pbd_integer_new_custom(pbd_conf conf);

pbd_element* pbd_integer_create(int64_t value);

pbd_element* pbd_integer_create_custom(pbd_conf conf, int64_t value);

void pbd_integer_set(pbd_element* e, int64_t value);

int64_t pbd_integer_get(const pbd_element* e);

/* real */
pbd_element* pbd_real_new();

pbd_element* pbd_real_new_custom(pbd_conf conf);

pbd_element* pbd_real_create(double value);

pbd_element* pbd_real_create_custom(pbd_conf conf, double value);

void pbd_real_set(pbd_element* e, double value);

double pbd_real_get(const pbd_element* e);

/* string */
pbd_element* pbd_string_new();

pbd_element* pbd_string_new_custom(pbd_conf conf);

pbd_element* pbd_string_create(const char* value);

pbd_element* pbd_string_create_custom(pbd_conf conf, const char* value);

int pbd_string_set(pbd_element* e, const char* value);

int pbd_string_set_custom(pbd_conf conf, pbd_element* e, const char* value);

const char* pbd_string_get(const pbd_element* e);

/* bool_array */
pbd_element* pbd_bool_array_new();

pbd_element* pbd_bool_array_new_custom(pbd_conf conf);

int pbd_bool_array_add(pbd_element* s, bool value);

int pbd_bool_array_add_custom(pbd_conf conf, pbd_element* s, bool value);

size_t pbd_bool_array_size(const pbd_element* s);
    
const bool* pbd_bool_array_values(const pbd_element* s);

/* element_array */
pbd_element* pbd_element_array_new();

pbd_element* pbd_element_array_new_custom(pbd_conf conf);

int pbd_element_array_add(pbd_element* s, pbd_element* value);

int pbd_element_array_add_custom(pbd_conf conf, pbd_element* e, const pbd_element* value);

size_t pbd_element_array_size(const pbd_element* s);
    
const pbd_element** pbd_element_array_values(const pbd_element* s);

/* integer_array */
pbd_element* pbd_integer_array_new();

pbd_element* pbd_integer_array_new_custom(pbd_conf conf);

int pbd_integer_array_add(pbd_element* s, int64_t value);

int pbd_integer_array_add_custom(pbd_conf conf, pbd_element* s, int64_t value);

size_t pbd_integer_array_size(const pbd_element* s);
    
const int64_t* pbd_integer_array_values(const pbd_element* s);

/* real_array */
pbd_element* pbd_real_array_new();

pbd_element* pbd_real_array_new_custom(pbd_conf conf);

int pbd_real_array_add(pbd_element* s, double value);

int pbd_real_array_add_custom(pbd_conf conf, pbd_element* s, double value);

size_t pbd_real_array_size(const pbd_element* s);
    
const double* pbd_real_array_values(const pbd_element* s);

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_H */

