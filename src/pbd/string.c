#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "string.h"
#include "typeid.h"
#include "arrayutils.h"

static struct pbd_element_vtable string_vtable;

static int string_to_buffer(const pbd_element* e, char** buffer, size_t* size) {
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
    *buffer = malloc(full_size);
    if (*buffer == NULL) {
        return -1;
    }
    *size = full_size;
    memcpy(*buffer, &type_id, SIZEOF_TYPE_ID);
    pbd_write_array_size(*buffer, len, sizeof_array_size);
    memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size, s->value, len);
    return 0;
}

static int string_from_buffer(struct pbd_element* e, const char* buffer, 
        pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == string_vtable.type);
    buffer += *read_bytes;
    size_t sizeof_array_size = pbd_sizeof_array_size_by_type(type_id);
    uint32_t len = pbd_read_array_size(buffer, sizeof_array_size);
    char* str = malloc(len + 1);
    strlcpy(str, buffer + SIZEOF_TYPE_ID + sizeof_array_size, len + 1);
    pbd_string* s = (pbd_string*) &(*e);
    s->value = str;
    *read_bytes += SIZEOF_TYPE_ID + sizeof_array_size + len;
    return 0;
}

static void string_free(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == string_vtable.type);
    pbd_string* s = (pbd_string*) &(*e);
    free(s->value);
    s->value = NULL;
}

static struct pbd_element_vtable string_vtable = {
    pbd_string_type, string_to_buffer, string_from_buffer, string_free
};

pbd_element* pbd_string_new() {
    pbd_string* s = malloc(sizeof(pbd_string));
    if (s == NULL) {
        return NULL;
    }
    s->value = NULL;
    s->element.vtable = &string_vtable;
    return &s->element;
}

pbd_element* pbd_string_create(const char* value) {
    assert(value != NULL);
    pbd_element* e = pbd_string_new();
    if (e == NULL) {
        return NULL;
    }
    pbd_string_set(e, value);
    return e;
}

int pbd_string_set(pbd_element* e, const char* value) {
    assert(e != NULL);
    assert(value != NULL);
    assert(e->vtable->type == string_vtable.type);
    pbd_string* s = (pbd_string*) &(*e);
    size_t size = strlen(value) + 1;
    if (s->value) {
        s->value = realloc(s->value, size);
    } else {
        s->value = malloc(size);
    }
    if (s == NULL) {
        return -1;
    }
    strlcpy(s->value, value, size);
    return 0;
}

const char* pbd_string_get(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == string_vtable.type);
    const pbd_string* s = (const pbd_string*) &(*e);
    return s->value;
}