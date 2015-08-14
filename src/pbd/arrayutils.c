#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "arrayutils.h"
#include "element.h"

pbd_array_size_bytes pbd_sizeof_array_size_by_value(size_t size) {
    if (size > 65535) {
        return pbd_four_bytes;
    } else if (size > 255) {
        return pbd_two_bytes;
    } else {
        return pbd_one_byte;
    }
}

pbd_array_size_bytes pbd_sizeof_array_size_by_type(pbd_type_id type_id) {
    assert(type_id != pbd_type_unknown);
    switch (type_id) {
        case pbd_type_int8_array_four_bytes:
        case pbd_type_uint8_array_four_bytes:
        case pbd_type_int16_array_four_bytes:
        case pbd_type_uint16_array_four_bytes:
        case pbd_type_int32_array_four_bytes:
        case pbd_type_uint32_array_four_bytes:
        case pbd_type_int64_array_four_bytes:
        case pbd_type_float_array_four_bytes:
        case pbd_type_double_array_four_bytes:
        case pbd_type_bool_array_four_bytes:
        case pbd_type_element_array_four_bytes:
        case pbd_type_string_four_bytes:
            return pbd_four_bytes;
            
        case pbd_type_int8_array_two_bytes:
        case pbd_type_uint8_array_two_bytes:
        case pbd_type_int16_array_two_bytes:
        case pbd_type_uint16_array_two_bytes:
        case pbd_type_int32_array_two_bytes:
        case pbd_type_uint32_array_two_bytes:
        case pbd_type_int64_array_two_bytes:
        case pbd_type_float_array_two_bytes:
        case pbd_type_double_array_two_bytes:
        case pbd_type_bool_array_two_bytes:
        case pbd_type_element_array_two_bytes:
        case pbd_type_string_two_bytes:
            return pbd_two_bytes;
            
        default:
            return pbd_one_byte;
    }
}

uint32_t pbd_read_array_size(const char* buffer, pbd_array_size_bytes sizeof_array_size) {
    assert(buffer != NULL);
    uint32_t size;
    if (sizeof_array_size == pbd_one_byte) {
        uint8_t tmp_size;
        memcpy(&tmp_size, buffer + SIZEOF_TYPE_ID, sizeof_array_size);
        size = tmp_size;
    } else if (sizeof_array_size == pbd_two_bytes) {
        uint16_t tmp_size;
        memcpy(&tmp_size, buffer + SIZEOF_TYPE_ID, sizeof_array_size);
        size = tmp_size;
    } else {
        memcpy(&size, buffer + SIZEOF_TYPE_ID, sizeof_array_size);
    }
    return size;
}

void pbd_write_array_size(char* buffer, size_t size, pbd_array_size_bytes sizeof_array_size) {
    assert(buffer != NULL);
    if (sizeof_array_size == pbd_one_byte) {
        uint8_t array_size = size;
        memcpy(buffer + SIZEOF_TYPE_ID, &array_size, pbd_one_byte);   
        
    } else if (sizeof_array_size == pbd_two_bytes) {
        uint16_t array_size = size;
        memcpy(buffer + SIZEOF_TYPE_ID, &array_size, pbd_two_bytes);
        
    } else {
        uint32_t array_size = size;
        memcpy(buffer + SIZEOF_TYPE_ID, &array_size, pbd_four_bytes);
        
    }
}