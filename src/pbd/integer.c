#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "integer.h"
#include "typeid.h"

static struct pbd_element_vtable integer_vtable;

static int integer_to_buffer(const pbd_element* e, char** buffer, size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == integer_vtable.type);
    pbd_integer* s = (pbd_integer*) &(*e);
    uint8_t type_id = pbd_type_best_integer(s->value);   
    size_t sizeof_value = pbd_sizeof_integer_value(type_id);
    uint16_t full_size = SIZEOF_TYPE_ID + sizeof_value;
    *buffer = malloc(full_size);
    if (*buffer == NULL) {
        return -1;
    }
    *size = full_size;
    memcpy(*buffer, &type_id, SIZEOF_TYPE_ID);
    if (sizeof_value == sizeof(int8_t)) {
        int8_t tmp_value = s->value;
        memcpy(*buffer + SIZEOF_TYPE_ID, &tmp_value, sizeof_value);
    } else if (sizeof_value == sizeof(int16_t)) {
        int16_t tmp_value = s->value;
        memcpy(*buffer + SIZEOF_TYPE_ID, &tmp_value, sizeof_value);
    } else if (sizeof_value == sizeof(int32_t)) {
        int32_t tmp_value = s->value;
        memcpy(*buffer + SIZEOF_TYPE_ID, &tmp_value, sizeof_value);
    } else {
        memcpy(*buffer + SIZEOF_TYPE_ID, &s->value, sizeof_value);
    }
    return 0;
}

static int integer_from_buffer(struct pbd_element* e, const char* buffer, 
        pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == integer_vtable.type);
    buffer += *read_bytes;
    size_t sizeof_value = pbd_sizeof_integer_value(type_id);
    int64_t value;
    if (sizeof_value == sizeof(int8_t)) {
        int8_t tmp_value;
        memcpy(&tmp_value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        value = pbd_is_unsigned(type_id) ? (uint8_t) tmp_value : tmp_value;
    } else if (sizeof_value == sizeof(int16_t)) {
        int16_t tmp_value;
        memcpy(&tmp_value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        value = pbd_is_unsigned(type_id) ? (uint16_t) tmp_value : tmp_value;
    } else if (sizeof_value == sizeof(int32_t)) {
        int32_t tmp_value;
        memcpy(&tmp_value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        value = pbd_is_unsigned(type_id) ? (uint32_t) tmp_value : tmp_value;
    } else {
        memcpy(&value, buffer + SIZEOF_TYPE_ID, sizeof_value);
    }
    pbd_integer_set(e, value);
    *read_bytes += SIZEOF_TYPE_ID + sizeof_value;
    return 0;
}

static struct pbd_element_vtable integer_vtable = {
    pbd_integer_type, integer_to_buffer, integer_from_buffer, NULL
};

pbd_element* pbd_integer_new() {
    pbd_integer* s = malloc(sizeof(pbd_integer));
    if (s == NULL) {
        return NULL;
    }
    s->element.vtable = &integer_vtable;
    return &s->element;
}

pbd_element* pbd_integer_create(int64_t value) {
    pbd_element* e = pbd_integer_new();
    if (e == NULL) {
        return NULL;
    }
    pbd_integer_set(e, value);
    return e;
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