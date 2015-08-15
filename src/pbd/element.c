#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include <pbd/pbd.h>

#include "element.h"
#include "typeid.h"
#include "arrayutils.h"

#include "string.h"
#include "boolarray.h"

void pbd_element_free(const pbd_element* e) {
    assert(e != NULL);
    if (e->vtable->free) {
        e->vtable->free(e);
    }
    free((pbd_element*) e);
}

pbd_type_id pbd_element_type(const pbd_element* e) {
    assert(e != NULL);
    return e->vtable->type;
}

int pbd_element_to_buffer(pbd_element* e, char** buffer, size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    return e->vtable->to_buffer(e, buffer, size);
}

pbd_element* pbd_element_new(pbd_type_id type) {
    switch (type) {
        case pbd_type_bool: 
            return pbd_bool_new();
            
        case pbd_type_bool_array:
            return pbd_bool_array_new();
            
        case pbd_type_element_array:
            return pbd_element_array_new();
            
        case pbd_type_integer:
            return pbd_integer_new();
            
        case pbd_type_integer_array:
            return pbd_integer_array_new();
            
        case pbd_type_null:
            return pbd_null_new();
            
        case pbd_type_real:
            return pbd_real_new();
            
        case pbd_type_real_array:
            return pbd_real_array_new();
            
        case pbd_type_string:
            return pbd_string_new();
            
        default:
            errno = EINVAL;
            return NULL;
    }
}

pbd_element* pbd_element_create(const char* buffer) {
    assert(buffer != NULL);
    size_t read_bytes = 0;
    return pbd_element_from_buffer(buffer, &read_bytes);
}


pbd_element* pbd_element_from_buffer(const char* buffer, size_t* read_bytes) {
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    uint8_t type_id;
    memcpy(&type_id, buffer + *read_bytes, SIZEOF_TYPE_ID);
    
    pbd_type_id adjusted_type_id = pbd_type_from_read(type_id);
    
    switch (adjusted_type_id) {
        
        case pbd_type_bool: {
            pbd_element* e = pbd_bool_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        case pbd_type_int8_scalar:
        case pbd_type_uint8_scalar:
        case pbd_type_int16_scalar:
        case pbd_type_uint16_scalar:
        case pbd_type_int32_scalar:
        case pbd_type_uint32_scalar:
        case pbd_type_int64_scalar: {
            pbd_element* e = pbd_integer_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        case pbd_type_float_scalar:
        case pbd_type_double_scalar: {
            pbd_element* e = pbd_real_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        case pbd_type_null: {
            pbd_element* e = pbd_null_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        case pbd_type_float_array:
        case pbd_type_double_array: {
            pbd_element* e = pbd_real_array_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        case pbd_type_int8_array:
        case pbd_type_uint8_array:
        case pbd_type_int16_array:
        case pbd_type_uint16_array:
        case pbd_type_int32_array:
        case pbd_type_uint32_array:
        case pbd_type_int64_array: {
            pbd_element* e = pbd_integer_array_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        case pbd_type_string: {
            pbd_element* e = pbd_string_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        case pbd_type_bool_array: {
            pbd_element* e = pbd_bool_array_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        case pbd_type_element_array: {
            pbd_element* e = pbd_element_array_new();
            e->vtable->from_buffer(e, buffer, type_id, read_bytes);
            return e;
        }
        default: 
            errno = EINVAL;
            return NULL;
    }
}