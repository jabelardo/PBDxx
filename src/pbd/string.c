#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "string.h"
#include "typeid.h"
#include "arrayutils.h"

static struct pbd_element_vtable string_vtable;

static int string_to_buffer(pbd_conf conf, const pbd_element* e, char** buffer, 
        size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == string_vtable.type);
    pbd_string* s = (pbd_string*) &(*e);
    pbd_type_id type = (pbd_type_id) string_vtable.type;
    size_t len = strlen(s->value);
    uint8_t type_id = pbd_type_to_write(type, len);
    size_t sizeof_array_size = pbd_sizeof_array_size_by_value(len);
    size_t full_size = SIZEOF_TYPE_ID + sizeof_array_size + len;
    *buffer = conf.mem_alloc(full_size);
    if (*buffer == NULL) {
        return -1;
    }
    *size = full_size;
    memcpy(*buffer, &type_id, SIZEOF_TYPE_ID);
    pbd_write_array_size(*buffer, len, sizeof_array_size);
    memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size, s->value, len);
    return 0;
}

static int string_from_buffer(pbd_conf conf, struct pbd_element* e, 
        const char* buffer, pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == string_vtable.type);
    buffer += *read_bytes;
    size_t sizeof_array_size = pbd_sizeof_array_size_by_type(type_id);
    uint32_t len = pbd_read_array_size(buffer, sizeof_array_size);
    char* str = conf.mem_alloc(len + 1);
    memcpy(str, buffer + SIZEOF_TYPE_ID + sizeof_array_size, len);
	str[len] = 0;
    pbd_string* s = (pbd_string*) &(*e);
    s->value = str;
    *read_bytes += SIZEOF_TYPE_ID + sizeof_array_size + len;
    return 0;
}

static void string_free(pbd_conf conf, const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == string_vtable.type);
    pbd_string* s = (pbd_string*) &(*e);
    conf.free_mem(s->value);
    s->value = NULL;
}

static struct pbd_element_vtable string_vtable = {
    pbd_type_string, string_to_buffer, string_from_buffer, string_free
};

pbd_element* pbd_string_new_custom(pbd_conf conf) {
    pbd_string* s = conf.mem_alloc(sizeof(pbd_string));
    if (s == NULL) {
        return NULL;
    }
    s->value = NULL;
    s->element.vtable = &string_vtable;
    return &s->element;
}

pbd_element* pbd_string_new() {
    return pbd_string_new_custom(pbd_default_conf);
}

pbd_element* pbd_string_create(const char* value) {
    return pbd_string_create_custom(pbd_default_conf, value);
}

pbd_element* pbd_string_create_custom(pbd_conf conf, const char* value) {
    assert(value != NULL);
    pbd_element* e = pbd_string_new_custom(conf);
    if (e == NULL) {
        return NULL;
    }
    pbd_string_set_custom(conf, e, value);
    return e;
}

int pbd_string_set(pbd_element* e, const char* value) {
    return pbd_string_set_custom(pbd_default_conf, e, value);
}

int pbd_string_set_custom(pbd_conf conf, pbd_element* e, const char* value) {
    assert(e != NULL);
    assert(value != NULL);
    assert(e->vtable->type == string_vtable.type);
    pbd_string* s = (pbd_string*) &(*e);
    size_t size = strlen(value) + 1;
    if (s->value) {
        s->value = conf.mem_realloc(s->value, size);
    } else {
        s->value = conf.mem_alloc(size);
    }
    if (s == NULL) {
        return -1;
    }
    memcpy(s->value, value, size - 1);
	s->value[size] = 0;
    return 0;
}

const char* pbd_string_get(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == string_vtable.type);
    const pbd_string* s = (const pbd_string*) &(*e);
    return s->value;
}