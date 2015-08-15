#include <float.h>
#include <errno.h>

#include "typeid.h"
#include "arrayutils.h"

pbd_type_id pbd_type_from_read(pbd_type_id type_id) {
    switch (type_id) {
        case pbd_type_int8_array_one_byte:
        case pbd_type_int8_array_two_bytes:
        case pbd_type_int8_array_four_bytes:
            return pbd_type_int8_array;

        case pbd_type_uint8_array_one_byte:
        case pbd_type_uint8_array_two_bytes:
        case pbd_type_uint8_array_four_bytes:
            return pbd_type_uint8_array;

        case pbd_type_int16_array_one_byte:
        case pbd_type_int16_array_two_bytes:
        case pbd_type_int16_array_four_bytes:
            return pbd_type_int16_array;

        case pbd_type_uint16_array_one_byte:
        case pbd_type_uint16_array_two_bytes:
        case pbd_type_uint16_array_four_bytes:
            return pbd_type_uint16_array;

        case pbd_type_int32_array_one_byte:
        case pbd_type_int32_array_two_bytes:
        case pbd_type_int32_array_four_bytes:
            return pbd_type_int32_array;

        case pbd_type_uint32_array_one_byte:
        case pbd_type_uint32_array_two_bytes:
        case pbd_type_uint32_array_four_bytes:
            return pbd_type_uint32_array;

        case pbd_type_int64_array_one_byte:
        case pbd_type_int64_array_two_bytes:
        case pbd_type_int64_array_four_bytes:
            return pbd_type_int64_array;

        case pbd_type_float_array_one_byte:
        case pbd_type_float_array_two_bytes:
        case pbd_type_float_array_four_bytes:
            return pbd_type_float_array;

        case pbd_type_double_array_one_byte:
        case pbd_type_double_array_two_bytes:
        case pbd_type_double_array_four_bytes:
            return pbd_type_double_array;

        case pbd_type_bool_array_one_byte:
        case pbd_type_bool_array_two_bytes:
        case pbd_type_bool_array_four_bytes:
            return pbd_type_bool_array;

        case pbd_type_element_array_one_byte:
        case pbd_type_element_array_two_bytes:
        case pbd_type_element_array_four_bytes:
            return pbd_type_element_array;

        case pbd_type_string_one_byte:
        case pbd_type_string_two_bytes:
        case pbd_type_string_four_bytes:
            return pbd_type_string;

        default:
            return type_id;
    }
}

pbd_type_id pbd_type_to_write(pbd_type_id type_id, size_t size) {
    switch (type_id) {
        case pbd_type_int8_array:
        case pbd_type_uint8_array:
        case pbd_type_int16_array:
        case pbd_type_uint16_array:
        case pbd_type_int32_array:
        case pbd_type_uint32_array:
        case pbd_type_int64_array:
        case pbd_type_float_array:
        case pbd_type_double_array:
        case pbd_type_bool_array:
        case pbd_type_element_array:
        case pbd_type_string:
            if (size > UINT16_MAX) {
                return type_id + 2;
            } else if (size > UINT8_MAX) {
                return type_id + 1;
            }
        default: break;
    }
    return type_id;
}

pbd_type_id pbd_type_best_real(double val) {
    return pbd_type_best_real_array(val, val) - pbd_type_scalar_delta;
}

pbd_type_id pbd_type_best_real_array(double min, double max) {
    if (min >= FLT_MIN && max <= FLT_MAX) {
        return pbd_type_float_array;
    }
    return pbd_type_double_array;
}

pbd_type_id pbd_type_best_integer(int64_t val) {
    return pbd_type_best_integer_array(val, val) - pbd_type_scalar_delta;
}

pbd_type_id pbd_type_best_integer_array(int64_t min, int64_t max) {
    if (min >= 0) { // unsigned
        if (max <= UINT8_MAX) {
            return pbd_type_uint8_array;
        }
        if (max <= UINT16_MAX) {
            return pbd_type_uint16_array;
        }
        if (max <= UINT32_MAX) {
            return pbd_type_uint32_array;
        }
    } else { // signed
        if (min >= INT8_MIN) {
            if (max <= INT8_MAX) {
                return pbd_type_int8_array;
            }
            if (max <= INT16_MAX) {
                return pbd_type_int16_array;
            }
            if (max <= INT32_MAX) {
                return pbd_type_int32_array;
            }
        } else if (min >= INT16_MIN) {
            if (max <= INT16_MAX) {
                return pbd_type_int16_array;
            }
            if (max <= INT32_MAX) {
                return pbd_type_int32_array;
            }
        } else if (min >= INT32_MIN) {
            if (max <= INT32_MAX) {
                return pbd_type_int32_array;
            }
        }
    }
    return pbd_type_int64_array;
}

size_t pbd_sizeof_integer_value(pbd_type_id type_id) {
    switch(type_id) {
        case pbd_type_int8_scalar:
        case pbd_type_uint8_scalar:
            return sizeof(int8_t);
            
        case pbd_type_int16_scalar:
        case pbd_type_uint16_scalar:
            return sizeof(int16_t);
            
        case pbd_type_int32_scalar:
        case pbd_type_uint32_scalar:
            return sizeof(int32_t);
            
        case pbd_type_int64_scalar:
            return sizeof(int64_t);
            
        default:
            errno = EINVAL;
            return 0;
    }
}

size_t pbd_sizeof_real_value(pbd_type_id type_id) {
    switch(type_id) {
        case pbd_type_float_scalar:
            return sizeof(float);
            
        case pbd_type_double_scalar:
            return sizeof(double);
            
        default:
            errno = EINVAL;
            return 0;
    }
}

size_t pbd_sizeof_real_array_value(pbd_type_id type_id) {
    switch(type_id) {
        case pbd_type_float_array_one_byte:
        case pbd_type_float_array_two_bytes:
        case pbd_type_float_array_four_bytes:
            return sizeof(float);
            
        case pbd_type_double_array_one_byte:
        case pbd_type_double_array_two_bytes:
        case pbd_type_double_array_four_bytes:
            return sizeof(double);
            
        default:
            errno = EINVAL;
            return 0;
    }
}

size_t pbd_sizeof_integer_array_value(pbd_type_id type_id) {
    switch(type_id) {
        case pbd_type_int8_array_one_byte:
        case pbd_type_uint8_array_one_byte:
        case pbd_type_int8_array_two_bytes:
        case pbd_type_uint8_array_two_bytes:
        case pbd_type_int8_array_four_bytes:
        case pbd_type_uint8_array_four_bytes:
            return sizeof(int8_t);
            
        case pbd_type_int16_array_one_byte:
        case pbd_type_uint16_array_one_byte:
        case pbd_type_int16_array_two_bytes:
        case pbd_type_uint16_array_two_bytes:
        case pbd_type_int16_array_four_bytes:
        case pbd_type_uint16_array_four_bytes:
            return sizeof(int16_t);
            
        case pbd_type_int32_array_one_byte:
        case pbd_type_uint32_array_one_byte:
        case pbd_type_int32_array_two_bytes:
        case pbd_type_uint32_array_two_bytes:
        case pbd_type_int32_array_four_bytes:
        case pbd_type_uint32_array_four_bytes:
            return sizeof(int32_t);
            
        case pbd_type_int64_array_one_byte:
        case pbd_type_int64_array_two_bytes:
        case pbd_type_int64_array_four_bytes:
            return sizeof(int64_t);
                        
        default:
            errno = EINVAL;
            return 0;
    }
}

bool pbd_is_unsigned(pbd_type_id type_id) {
    switch (type_id) {
        case pbd_type_uint8_scalar:
        case pbd_type_uint16_scalar:
        case pbd_type_uint32_scalar:
        case pbd_type_uint8_array_one_byte:
        case pbd_type_uint8_array_two_bytes:
        case pbd_type_uint8_array_four_bytes:
        case pbd_type_uint16_array_one_byte:
        case pbd_type_uint16_array_two_bytes:
        case pbd_type_uint16_array_four_bytes:
        case pbd_type_uint32_array_one_byte:
        case pbd_type_uint32_array_two_bytes:
        case pbd_type_uint32_array_four_bytes:
            return true;
        
        default:
            return false;
    }
}