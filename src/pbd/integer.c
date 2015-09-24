#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "integer.h"
#include "typeid.h"
#include "endianess.h"

static struct pbd_element_vtable integer_vtable;

static int integer_to_buffer(pbd_conf conf, const pbd_element* e, char** buffer, 
        size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == integer_vtable.type);
    pbd_integer* s = (pbd_integer*) &(*e);
    uint8_t type_id = pbd_type_best_integer(s->value);   
    size_t sizeof_value = pbd_sizeof_integer_value(type_id);
    if (sizeof_value == 0) {
        return -1;
    }
	size_t full_size = SIZEOF_TYPE_ID + sizeof_value;
    *buffer = conf.mem_alloc(full_size);
    if (*buffer == NULL) {
        return -1;
    }
    *size = full_size;
    memcpy(*buffer, &type_id, SIZEOF_TYPE_ID);
    if (sizeof_value == sizeof(int8_t)) {
        int8_t tmp_value = (int8_t) s->value;
        memcpy(*buffer + SIZEOF_TYPE_ID, &tmp_value, sizeof_value);
    } else if (sizeof_value == sizeof(int16_t)) {
        int16_t tmp_value = (int16_t) s->value;
        memcpy(*buffer + SIZEOF_TYPE_ID, &tmp_value, sizeof_value);
    } else if (sizeof_value == sizeof(int32_t)) {
        int32_t tmp_value = (int32_t) s->value;
        memcpy(*buffer + SIZEOF_TYPE_ID, &tmp_value, sizeof_value);
    } else {
        memcpy(*buffer + SIZEOF_TYPE_ID, &s->value, sizeof_value);
    }
    return 0;
}

static int integer_from_buffer(pbd_conf conf, struct pbd_element* e, 
        const char* buffer, pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == integer_vtable.type);
    size_t sizeof_value = pbd_sizeof_integer_value(type_id);
    if (sizeof_value == 0) {
        return -1;
    }
    buffer += *read_bytes;
    int64_t value;
    bool little_endian = pbd_is_little_endian();
    if (sizeof_value == sizeof(int8_t)) {
        int8_t tmp_value;
        memcpy(&tmp_value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        value = pbd_is_unsigned(type_id) ? (uint8_t) tmp_value : tmp_value;
    } else if (sizeof_value == sizeof(int16_t)) {
        int16_t tmp_value;
        memcpy(&tmp_value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        tmp_value = pbd_get_uint16(little_endian, tmp_value);
        value = pbd_is_unsigned(type_id) ? (uint16_t) tmp_value : tmp_value;
    } else if (sizeof_value == sizeof(int32_t)) {
        int32_t tmp_value;
        memcpy(&tmp_value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        tmp_value = pbd_get_uint32(little_endian, tmp_value);
        value = pbd_is_unsigned(type_id) ? (uint32_t) tmp_value : tmp_value;
    } else {
        memcpy(&value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        value = pbd_get_uint64(little_endian, value);
    }
    pbd_integer_set(e, value);
    *read_bytes += SIZEOF_TYPE_ID + sizeof_value;
    return 0;
}

static struct pbd_element_vtable integer_vtable = {
    pbd_type_integer, integer_to_buffer, integer_from_buffer, NULL
};

pbd_element* pbd_integer_new_custom(pbd_conf conf) {
    pbd_integer* s = conf.mem_alloc(sizeof(pbd_integer));
    if (s == NULL) {
        return NULL;
    }
    s->element.vtable = &integer_vtable;
    return &s->element;
}

pbd_element* pbd_integer_new() {
    return pbd_integer_new_custom(pbd_default_conf);
}

pbd_element* pbd_integer_create_custom(pbd_conf conf, int64_t value) {
    pbd_element* e = pbd_integer_new_custom(conf);
    if (e == NULL) {
        return NULL;
    }
    pbd_integer_set(e, value);
    return e;
}

pbd_element* pbd_integer_create(int64_t value) {
    return pbd_integer_create_custom(pbd_default_conf, value);
}

void pbd_integer_set(pbd_element* e, int64_t value) {
    assert(e != NULL);
    assert(e->vtable->type == integer_vtable.type);
    pbd_integer* s = (pbd_integer*) &(*e);
    s->value = value;
}

int64_t pbd_integer_get(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == integer_vtable.type);
    const pbd_integer* s = (const pbd_integer*) &(*e);
    return s->value;
}