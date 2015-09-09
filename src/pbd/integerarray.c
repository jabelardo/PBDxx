#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "typeid.h"
#include "integer.h"
#include "integerarray.h"
#include "arrayutils.h"
#include "endianess.h"

typedef struct pbd_int64_t_min_max {
    int64_t min;
    int64_t max;
} pbd_int64_t_min_max;
    
static pbd_int64_t_min_max get_min_max(const pbd_integer_array* s) {
    pbd_int64_t_min_max min_max;
    min_max.min = 0;
    min_max.max = 0;
    if (s->size) {
        min_max.min = INT64_MAX;
        min_max.max = INT64_MIN;
        for (int i = 0; i < s->size; ++i) {
            min_max.min = min_max.min < s->values[i] ? min_max.min : s->values[i];
            min_max.max = min_max.max > s->values[i] ? min_max.max : s->values[i];
        }
    }
    return min_max;
}

static struct pbd_element_vtable integer_array_vtable;
    
static int integer_array_to_buffer(const pbd_element* e, char** buffer, 
        size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == integer_array_vtable.type);
    pbd_integer_array* s = (pbd_integer_array*) &(*e);
    pbd_int64_t_min_max min_max = get_min_max(s);
    uint8_t type_id = pbd_type_to_write(
            pbd_type_best_integer_array(min_max.min, min_max.max), 
            s->size);
    size_t sizeof_array_size = pbd_sizeof_array_size_by_value(s->size);
    size_t sizeof_value = pbd_sizeof_integer_array_value(type_id);
    if (sizeof_value == 0) {
        return -1;
    }
    size_t full_size = SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * s->size;
    *buffer = malloc(full_size);
    if (*buffer == NULL) {
        return -1;
    }
    *size = full_size;
    memcpy(*buffer, &type_id, SIZEOF_TYPE_ID);
    pbd_write_array_size(*buffer, s->size, sizeof_array_size);
    for (size_t i = 0; i < s->size; ++i) {
        if (sizeof_value == sizeof(int8_t)) {
            int8_t value = s->values[i];  
            memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * i, 
                    &value, sizeof_value);
        } else if (sizeof_value == sizeof(int16_t)) {
            int16_t value = s->values[i];  
            memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * i, 
                    &value, sizeof_value);
        } else if (sizeof_value == sizeof(int32_t)) {
            int32_t value = s->values[i];  
            memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * i, 
                    &value, sizeof_value);
        } else {
            memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * i, 
                    &s->values[i], sizeof_value);
        }
    }
    return 0;
}

static int integer_array_from_buffer(struct pbd_element* e, const char* buffer, 
        pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == integer_array_vtable.type);
    size_t sizeof_value = pbd_sizeof_integer_array_value(type_id);
    if (sizeof_value == 0) {
        return -1;
    }
    buffer += *read_bytes;
    size_t sizeof_array_size = pbd_sizeof_array_size_by_type(type_id);
    uint32_t size = pbd_read_array_size(buffer, sizeof_array_size);
    bool little_endian = pbd_is_little_endian();
    for (int i = 0; i < size; ++i) {
        int64_t value;
        if (sizeof_value == 1) {
            int8_t tmp_val;
            memcpy(&tmp_val, buffer + SIZEOF_TYPE_ID + sizeof_array_size + 
                    sizeof_value * i, sizeof_value);
            value = pbd_is_unsigned(type_id) ? (uint8_t) tmp_val : tmp_val;
        } else if (sizeof_value == 2) {
            int16_t tmp_val;
            memcpy(&tmp_val, buffer + SIZEOF_TYPE_ID + sizeof_array_size + 
                    sizeof_value * i, sizeof_value);
            tmp_val = pbd_get_uint16(little_endian, tmp_val);
            value = pbd_is_unsigned(type_id) ? (uint16_t) tmp_val : tmp_val;
        } else if (sizeof_value == 4) {
            int32_t tmp_val;
            memcpy(&tmp_val, buffer + SIZEOF_TYPE_ID + sizeof_array_size + 
                    sizeof_value * i, sizeof_value);
            tmp_val = pbd_get_uint32(little_endian, tmp_val);
            value = pbd_is_unsigned(type_id) ? (uint32_t) tmp_val : tmp_val;
        } else {
            memcpy(&value, buffer + SIZEOF_TYPE_ID + sizeof_array_size + 
                    sizeof_value * i, sizeof_value);
            value = pbd_get_uint64(little_endian, value);
        }
        pbd_integer_array_add(e, value);
    }
    *read_bytes += SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * size;
    return 0;
}

static void integer_array_free(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == integer_array_vtable.type);
    pbd_integer_array* s = (pbd_integer_array*) &(*e);
    free(s->values);
    s->values = NULL;
    s->size = 0;
    s->capacity = 0;
}

static struct pbd_element_vtable integer_array_vtable = {
    pbd_type_integer_array, integer_array_to_buffer, integer_array_from_buffer, 
    integer_array_free
};

pbd_element* pbd_integer_array_new() {
    pbd_integer_array* s = malloc(sizeof(pbd_integer_array));
    if (s == NULL) {
        return NULL;
    }
    s->values = NULL;
    s->size = 0;
    s->capacity = 0;
    s->element.vtable = &integer_array_vtable;
    return &s->element;
}

size_t pbd_integer_array_size(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == integer_array_vtable.type);
    pbd_integer_array* s = (pbd_integer_array*) &(*e);
    return s->size;
}
    
const int64_t* pbd_integer_array_values(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == integer_array_vtable.type);
    pbd_integer_array* s = (pbd_integer_array*) &(*e);
    return s->values;
}

int pbd_integer_array_add(pbd_element* e, int64_t value) {
    assert(e != NULL);
    assert(e->vtable->type == integer_array_vtable.type);
    pbd_integer_array* s = (pbd_integer_array*) &(*e);
    if (s->values == NULL) {
        s->values = malloc(sizeof(int64_t) * 2);
        if (s->values == NULL) {
            return -1;
        }
        s->size = 1;
        s->capacity = 2;
        s->values[0] = value;
        
    } else if (s->size + 1 < s->capacity) {
        s->values[s->size] = value;
        ++s->size;
        
    } else {
        s->values = realloc(s->values, sizeof(int64_t) * s->capacity * 2);
        if (s->values == NULL) {
            return -1;
        }
        s->values[s->size] = value;
        ++s->size;
        s->capacity *= 2;
    }
    return 0;
}
