#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "typeid.h"
#include "arrayutils.h"
#include "elementarray.h"

typedef struct buffer_item {
    char* buffer;
    size_t size;
} buffer_item;

static struct pbd_element_vtable element_array_vtable;

static int element_array_to_buffer(const pbd_element* e, char** buffer, size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == element_array_vtable.type);
    pbd_element_array* s = (pbd_element_array*) &(*e);
    uint8_t type_id = pbd_type_to_write(pbd_type_element_array, s->size);
    size_t sizeof_array_size = pbd_sizeof_array_size_by_value(s->size);
    size_t head_size = SIZEOF_TYPE_ID + sizeof_array_size;
    char* head_buffer = malloc(head_size);
    if (head_buffer == NULL) {
        return -1;
    }
    buffer_item* items = malloc(sizeof(buffer_item) * s->size + 1);
    if (items == NULL) {
        return -1;
    }
    memcpy(head_buffer, &type_id, SIZEOF_TYPE_ID);
    pbd_write_array_size(head_buffer, s->size, sizeof_array_size);
    items[0].buffer = head_buffer;
    items[0].size = head_size;
    *size = head_size;
    for (size_t i = 0; i < s->size; ++i) {
        pbd_element* e = s->values[i];
        buffer_item* item = &items[i + 1]; 
        item->buffer = NULL;
        item->size = 0;
        if (-1 ==s->values[i]->vtable->to_buffer(e, &item->buffer, &item->size)) {
            return -1;
        }
        *size += item->size;
    }
    *buffer = malloc(*size);
    if (*buffer == NULL) {
        return -1;
    }
    int delta = 0;
    for (size_t i = 0; i <= s->size; ++i) {
        buffer_item* item = &items[i]; 
        memcpy(*buffer + delta, item->buffer, item->size);
        delta += item->size;
        free(item->buffer);
    }
    free(items);
    return 0;
}

static int element_array_from_buffer(struct pbd_element* e, const char* buffer, 
        pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == element_array_vtable.type);
    size_t sizeof_array_size = pbd_sizeof_array_size_by_type(type_id);
    uint32_t size = pbd_read_array_size(buffer + *read_bytes, sizeof_array_size);
    *read_bytes += SIZEOF_TYPE_ID + sizeof_array_size;
    pbd_element_array* s = (pbd_element_array*) &(*e);
    s->size = size;
    s->capacity = size;
    s->values = malloc(sizeof(pbd_element*) * size);
    if (s->values == NULL) {
        return -1;
    }
    for (int i = 0; i < size; ++i) {
        if (NULL == (s->values[i] = pbd_element_from_buffer(buffer, read_bytes))) {
            return -1;
        }
    }
    return 0;
}

static void element_array_free(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == element_array_vtable.type);
    pbd_element_array* s = (pbd_element_array*) &(*e);
    for (size_t i = 0; i < s->size; ++i) {
        void (*method_free)(const struct pbd_element*) = s->values[i]->vtable->free;
        if (method_free) {
            method_free(s->values[i]);
        }
    }
    free(s->values);
    s->values = NULL;
    s->size = 0;
    s->capacity = 0;
}

static struct pbd_element_vtable element_array_vtable = {
    pbd_element_array_type, element_array_to_buffer, element_array_from_buffer, 
    element_array_free
};

pbd_element* pbd_element_array_new() {
    pbd_element_array* s = malloc(sizeof(pbd_element_array));
    if (s == NULL) {
        return NULL;
    }
    s->values = NULL;
    s->size = 0;
    s->capacity = 0;
    s->element.vtable = &element_array_vtable;
    return &s->element;
}

size_t pbd_element_array_size(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == element_array_vtable.type);
    pbd_element_array* s = (pbd_element_array*) &(*e);
    return s->size;
}
    
const pbd_element** pbd_element_array_values(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == element_array_vtable.type);
    pbd_element_array* s = (pbd_element_array*) &(*e);
    return (const pbd_element**) s->values;
}

int pbd_element_array_add(pbd_element* e, pbd_element* value) {
    assert(e != NULL);
    assert(e->vtable->type == element_array_vtable.type);
    pbd_element_array* s = (pbd_element_array*) &(*e);
    if (s->values == NULL) {
        s->values = malloc(sizeof(pbd_element*) * 2);
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
        s->values = realloc(s->values, sizeof(pbd_element*) * s->capacity * 2);
        if (s->values == NULL) {
            return -1;
        }
        s->values[s->size] = value;
        ++s->size;
        s->capacity *= 2;
    }
    return 0;
}
