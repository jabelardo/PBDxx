#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "real.h"
#include "typeid.h"
#include "endianess.h"

static struct pbd_element_vtable real_vtable;

static int real_to_buffer(pbd_conf conf, const pbd_element* e, char** buffer, 
        size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == real_vtable.type);
    pbd_real* s = (pbd_real*) &(*e);
    uint8_t type_id = pbd_type_best_real(s->value); 
    size_t sizeof_value = pbd_sizeof_real_value(type_id);
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
    if (sizeof_value == sizeof(float)) {
        float value = (float) s->value;
        memcpy(*buffer + SIZEOF_TYPE_ID, &value, sizeof_value);
    } else {
        memcpy(*buffer + SIZEOF_TYPE_ID, &s->value, sizeof_value);
    }
    return 0;
}

static int real_from_buffer(pbd_conf conf, struct pbd_element* e, 
        const char* buffer, pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == real_vtable.type);
    size_t sizeof_value = pbd_sizeof_real_value(type_id);
    if (sizeof_value == 0) {
        return -1;
    }
    buffer += *read_bytes;
    double value;
    bool little_endian = pbd_is_little_endian();
    if (sizeof_value == sizeof(float)) {
        float tmp_value;
        memcpy(&tmp_value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        value = pbd_get_float(little_endian, tmp_value);
    } else {
        memcpy(&value, buffer + SIZEOF_TYPE_ID, sizeof_value);
        value = pbd_get_double(little_endian, value);
    }
    pbd_real_set(e, value);
    *read_bytes += SIZEOF_TYPE_ID + sizeof_value;
    return 0;
}

static struct pbd_element_vtable real_vtable = {
    pbd_type_real, real_to_buffer, real_from_buffer, NULL
};

pbd_element* pbd_real_new_custom(pbd_conf conf) {
    pbd_real* s = conf.mem_alloc(sizeof(pbd_real));
    if (s == NULL) {
        return NULL;
    }
    s->element.vtable = &real_vtable;
    return &s->element;
}

pbd_element* pbd_real_new(pbd_conf conf) {
    return pbd_real_new_custom(pbd_default_conf);
}

pbd_element* pbd_real_create(double value) {
    return pbd_real_create_custom(pbd_default_conf, value);
}

pbd_element* pbd_real_create_custom(pbd_conf conf, double value) {
    pbd_element* e = pbd_real_new_custom(conf);
    if (e == NULL) {
        return NULL;
    }
    pbd_real_set(e, value);
    return e;
}

void pbd_real_set(pbd_element* e, double value) {
    assert(e != NULL);
    assert(e->vtable->type == real_vtable.type);
    pbd_real* s = (pbd_real*) &(*e);
    s->value = value;
}

double pbd_real_get(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == real_vtable.type);
    const pbd_real* s = (const pbd_real*) &(*e);
    return s->value;
}
