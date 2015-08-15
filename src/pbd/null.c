#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "null.h"
#include "typeid.h"

static struct pbd_element_vtable null_vtable;

static int null_to_buffer(const pbd_element* e, char** buffer, size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == null_vtable.type);
    pbd_null* s = (pbd_null*) &(*e);
    uint8_t type_id = pbd_type_null;  
    size_t full_size = sizeof(type_id);
    *buffer = malloc(full_size);
    if (*buffer == NULL) {
        return -1;
    }
    *size = full_size;
    memcpy(*buffer, &type_id, sizeof(type_id));
    return 0;
}

static int null_from_buffer(struct pbd_element* e, const char* buffer, 
        pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == null_vtable.type);
    *read_bytes += SIZEOF_TYPE_ID;
    return 0;
}

static struct pbd_element_vtable null_vtable = {
    pbd_type_null, null_to_buffer, null_from_buffer, NULL
};

pbd_element* pbd_null_new() {
    pbd_null* s = malloc(sizeof(pbd_null));
    if (s == NULL) {
        return NULL;
    }
    s->element.vtable = &null_vtable;
    return &s->element;
}