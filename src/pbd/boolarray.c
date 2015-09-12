#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "typeid.h"
#include "boolarray.h"
#include "arrayutils.h"
#include "pbdconf_internal.h"

static struct pbd_element_vtable bool_array_vtable;

static int bool_array_to_buffer(pbd_conf conf, const pbd_element* e, 
        char** buffer, size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == bool_array_vtable.type);
    pbd_bool_array* s = (pbd_bool_array*) &(*e);
    size_t raw_data_size = (s->size / 8) + (s->size % 8 != 0);
    uint8_t type_id = pbd_type_to_write(pbd_type_bool_array, raw_data_size);
    size_t sizeof_array_size = pbd_sizeof_array_size_by_value(raw_data_size);
    size_t full_size = SIZEOF_TYPE_ID + sizeof_array_size + raw_data_size + 
            sizeof(uint8_t);
    *buffer = conf.mem_alloc(full_size);
    if (*buffer == NULL) {
        return -1;
    }
    *size = full_size;
    memcpy(*buffer, &type_id, SIZEOF_TYPE_ID);
    pbd_write_array_size(*buffer, raw_data_size, sizeof_array_size);
    uint8_t ctrl = 0;
    for (size_t i = 0; i < s->size; i += 8) {
        uint8_t byte = 0;
        ctrl = 0;
        for (size_t j = 0; j < 8; ++j) {
            if (i + j == s->size)  {
                break;
            }
            byte |= s->values[i + j] << j;
            ++ctrl;
        }
        int delta = i / 8;
        memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size + delta, &byte, 
                sizeof(byte));
    }
    uint8_t padding = (ctrl < 8) ? 8 - ctrl : 0;
    memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size + raw_data_size, &padding, 
            sizeof(padding));
    return 0;
}

static int bool_from_buffer(pbd_conf conf, struct pbd_element* e, 
        const char* buffer, pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == bool_array_vtable.type);
    buffer += *read_bytes;
    size_t sizeof_raw_data_size = pbd_sizeof_array_size_by_type(type_id);
    uint32_t raw_data_size = pbd_read_array_size(buffer, sizeof_raw_data_size);
    uint8_t padding;
    pbd_bool_array* s = (pbd_bool_array*) &(*e);
    if (raw_data_size > 0) {
        uint8_t* raw_data = conf.mem_alloc(raw_data_size);
        memcpy(raw_data, buffer + SIZEOF_TYPE_ID + sizeof_raw_data_size, 
                raw_data_size);
        memcpy(&padding, buffer + SIZEOF_TYPE_ID + sizeof_raw_data_size + 
                raw_data_size, sizeof(padding));
        size_t array_size = raw_data_size * 8 - padding;
        if (array_size > 0) {
            bool* values = conf.mem_alloc(sizeof(bool) * array_size);
            for (size_t i = 0, k = 0; i < raw_data_size; ++i) {
                for (size_t j = 0; j < 8; ++j, ++k) {
                    if (k > array_size) {
                        i = raw_data_size;
                        break;
                    }
                    bool bit = (raw_data[i] & (0x01 << j)) != 0;
                    values[k] = bit;
                }
            }
            s->values = values;
            s->size = array_size;
            s->capacity = array_size;
        }
        conf.free_mem(raw_data);
    }
    *read_bytes += SIZEOF_TYPE_ID + sizeof_raw_data_size + raw_data_size 
            + sizeof(padding);
    return 0;
}

static void bool_array_free(pbd_conf conf, const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == bool_array_vtable.type);
    pbd_bool_array* s = (pbd_bool_array*) &(*e);
    conf.free_mem(s->values);
    s->values = NULL;
    s->size = 0;
    s->capacity = 0;
}

static struct pbd_element_vtable bool_array_vtable = {
    pbd_type_bool_array, bool_array_to_buffer, bool_from_buffer, bool_array_free
};

pbd_element* pbd_bool_array_new_custom(pbd_conf conf) {
    pbd_bool_array* s = conf.mem_alloc(sizeof(pbd_bool_array));
    if (s == NULL) {
        return NULL;
    }
    s->values = NULL;
    s->size = 0;
    s->capacity = 0;
    s->element.vtable = &bool_array_vtable;
    return &s->element;
}

pbd_element* pbd_bool_array_new() {
    return pbd_bool_array_new_custom(pbd_default_conf);
}

size_t pbd_bool_array_size(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == bool_array_vtable.type);
    pbd_bool_array* s = (pbd_bool_array*) &(*e);
    return s->size;
}
    
const bool* pbd_bool_array_values(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == bool_array_vtable.type);
    pbd_bool_array* s = (pbd_bool_array*) &(*e);
    return s->values;
}

int pbd_bool_array_add_custom(pbd_conf conf, pbd_element* e, bool value) {
    assert(e != NULL);
    assert(e->vtable->type == bool_array_vtable.type);
    pbd_bool_array* s = (pbd_bool_array*) &(*e);
    if (s->values == NULL) {
        s->values = conf.mem_alloc(sizeof(bool) * 2);
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
        s->values = conf.mem_realloc(s->values, sizeof(bool) * s->capacity * 2);
        if (s->values == NULL) {
            return -1;
        }
        s->values[s->size] = value;
        ++s->size;
        s->capacity *= 2;
    }
    return 0;
}

int pbd_bool_array_add(pbd_element* e, bool value) {
    return pbd_bool_array_add_custom(pbd_default_conf, e, value);
}