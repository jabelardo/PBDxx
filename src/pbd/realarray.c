#include <stddef.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "realarray.h"
#include "real.h"
#include "typeid.h"
#include "arrayutils.h"

typedef struct pbd_double_min_max {
    double min;
    double max;
} pbd_double_min_max;
    
static pbd_double_min_max get_min_max(const pbd_real_array* s) {
    pbd_double_min_max min_max;
    min_max.min = 0;
    min_max.max = 0;
    if (s->size) {
        min_max.min = DBL_MAX;
        min_max.max = DBL_MIN;
        for (int i = 0; i < s->size; ++i) {
            min_max.min = fmin(min_max.min, s->values[i]);
            min_max.max = fmax(min_max.max, s->values[i]);
        }
    }
    return min_max;
}

static struct pbd_element_vtable real_array_vtable;
    
static int real_array_to_buffer(const pbd_element* e, char** buffer, size_t* size) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(size != NULL);
    assert(e->vtable->type == real_array_vtable.type);
    pbd_real_array* s = (pbd_real_array*) &(*e);
    pbd_double_min_max min_max = get_min_max(s);
    uint8_t type_id = pbd_type_to_write(
            pbd_type_best_real_array(min_max.min, min_max.max),
            s->size);
    size_t sizeof_array_size = pbd_sizeof_array_size_by_value(s->size);
    size_t sizeof_value = pbd_sizeof_real_array_value(type_id);
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
        if (sizeof_value == sizeof(float)) {
            float value = s->values[i];  
            memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * i, 
                    &value, sizeof_value);
        } else {
            memcpy(*buffer + SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * i, 
                    &s->values[i], sizeof_value);
        }
    }
    return 0;
}

static int real_array_from_buffer(struct pbd_element* e, const char* buffer, 
        pbd_type_id type_id, size_t* read_bytes) {
    assert(e != NULL);
    assert(buffer != NULL);
    assert(read_bytes != NULL);
    assert(type_id != pbd_type_unknown);
    assert(e->vtable->type == real_array_vtable.type);
    size_t sizeof_value = pbd_sizeof_real_array_value(type_id);
    if (sizeof_value == 0) {
        return -1;
    }
    buffer += *read_bytes;
    size_t sizeof_array_size = pbd_sizeof_array_size_by_type(type_id);
    uint32_t size = pbd_read_array_size(buffer, sizeof_array_size);
    for (int i = 0; i < size; ++i) {
        double value;
        if (sizeof_value == sizeof(float)) {
            float tmp_value;
            memcpy(&tmp_value, buffer + SIZEOF_TYPE_ID + sizeof_array_size + 
                    sizeof_value * i, sizeof_value);
            value = tmp_value;
        } else {
            memcpy(&value, buffer + SIZEOF_TYPE_ID + sizeof_array_size + 
                    sizeof_value * i, sizeof_value);
        }
        pbd_real_array_add(e, value);
    }
    *read_bytes += SIZEOF_TYPE_ID + sizeof_array_size + sizeof_value * size;
    return 0;
}

static void real_array_free(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == real_array_vtable.type);
    pbd_real_array* s = (pbd_real_array*) &(*e);
    free(s->values);
    s->values = NULL;
    s->size = 0;
    s->capacity = 0;
}

static struct pbd_element_vtable real_array_vtable = {
    pbd_type_real_array, real_array_to_buffer, real_array_from_buffer, real_array_free
};

pbd_element* pbd_real_array_new() {
    pbd_real_array* s = malloc(sizeof(pbd_real_array));
    if (s == NULL) {
        return NULL;
    }
    s->values = NULL;
    s->size = 0;
    s->capacity = 0;
    s->element.vtable = &real_array_vtable;
    return &s->element;
}

size_t pbd_real_array_size(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == real_array_vtable.type);
    pbd_real_array* s = (pbd_real_array*) &(*e);
    return s->size;
}
    
const double* pbd_real_array_values(const pbd_element* e) {
    assert(e != NULL);
    assert(e->vtable->type == real_array_vtable.type);
    pbd_real_array* s = (pbd_real_array*) &(*e);
    return s->values;
}

int pbd_real_array_add(pbd_element* e, double value) {
    assert(e != NULL);
    assert(e->vtable->type == real_array_vtable.type);
    pbd_real_array* s = (pbd_real_array*) &(*e);
    if (s->values == NULL) {
        s->values = malloc(sizeof(double) * 2);
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
        s->values = realloc(s->values, sizeof(double) * s->capacity * 2);
        if (s->values == NULL) {
            return -1;
        }
        s->values[s->size] = value;
        ++s->size;
        s->capacity *= 2;
    }
    return 0;
}