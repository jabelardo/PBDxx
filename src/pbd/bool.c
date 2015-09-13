#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bool.h"
#include "typeid.h"

static struct pbd_element_vtable bool_vtable;

static int bool_to_buffer(pbd_conf conf, const pbd_element* e, char** buffer, 
        size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == bool_vtable.type);
    pbd_bool* s = (pbd_bool*) &(*e);
    uint8_t type_id = pbd_type_bool;    
    uint8_t value = s->value;    
    uint16_t full_size = sizeof(type_id) + sizeof(value);
    *buffer = conf.mem_alloc(full_size);
    if (*buffer == NULL) {
        return -1;
    }
    *size = full_size;
    memcpy(*buffer, &type_id, sizeof(type_id));
    memcpy(*buffer + sizeof(type_id), &value, sizeof(value));
    return 0;
}

static int bool_from_buffer(pbd_conf conf, struct pbd_element* e, 
        const char* buffer, pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == bool_vtable.type);
    buffer += *read_bytes;
    uint8_t value;
    memcpy(&value, buffer + SIZEOF_TYPE_ID, sizeof(value));
    pbd_bool_set(e, value);
    *read_bytes += SIZEOF_TYPE_ID + sizeof(value);
    return 0;
}

static struct pbd_element_vtable bool_vtable = {
    pbd_type_bool, bool_to_buffer, bool_from_buffer, NULL
};

pbd_element* pbd_bool_new_custom(pbd_conf conf) {
    pbd_bool* s = conf.mem_alloc(sizeof(pbd_bool));
    if (s == NULL) {
        return NULL;
    }
    s->element.vtable = &bool_vtable;
    return &s->element;
}

pbd_element* pbd_bool_new() {
    return pbd_bool_new_custom(pbd_default_conf);
}

pbd_element* pbd_bool_create_custom(pbd_conf conf, bool value) {
    pbd_element* e = pbd_bool_new_custom(conf);
    if (e == NULL) {
        return NULL;
    }
    pbd_bool_set(e, value);
    return e;
}

pbd_element* pbd_bool_create(bool value) {
    return pbd_bool_create_custom(pbd_default_conf, value);
}

void pbd_bool_set(pbd_element* e, bool value) {
    assert(e != NULL);
    assert(e->vtable->type == bool_vtable.type);
    pbd_bool* s = (pbd_bool*) &(*e);
    s->value = value;
}

bool pbd_bool_get(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == bool_vtable.type);
    const pbd_bool* s = (const pbd_bool*) &(*e);
    return s->value;
}
