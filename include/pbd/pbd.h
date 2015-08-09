/* 
 * File:   pbd.h
 * Author: jabelardo
 *
 * Created on August 10, 2015, 12:07 PM
 */

#ifndef PBD_H
#define	PBD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum pbd_type {
    pbd_unknown_type            =   0
    , pbd_bool_type             =  82
    , pbd_bool_array_type       =  93
    , pbd_element_array_type    =  96
    , pbd_integer_type          =  81
    , pbd_integer_array_type    =  87
    , pbd_null_type             =  83
    , pbd_real_type             =  80
    , pbd_real_array_type       =  90
    , pbd_string_type           =  84
 } pbd_type; 
    
typedef struct pbd_element pbd_element;

/* element */
pbd_type pbd_element_type(const pbd_element* e);

int pbd_element_to_buffer(pbd_element* e, char** buffer, size_t* size);

pbd_element* pbd_element_from_buffer(const char* buffer, size_t* read_bytes);

pbd_element* pbd_element_create(const char* buffer);

void pbd_element_free(const pbd_element* e);

pbd_element* pbd_element_new(pbd_type type);

/* null */
pbd_element* pbd_null_new();

/* bool */
pbd_element* pbd_bool_new();

pbd_element* pbd_bool_create(bool value);

void pbd_bool_set(pbd_element* e, bool value);

bool pbd_bool_get(const pbd_element* e);

/* integer */
pbd_element* pbd_integer_new();

pbd_element* pbd_integer_create(int64_t value);

void pbd_integer_set(pbd_element* e, int64_t value);

int64_t pbd_integer_get(const pbd_element* e);

/* real */
pbd_element* pbd_real_new();

pbd_element* pbd_real_create(double value);

void pbd_real_set(pbd_element* e, double value);

double pbd_real_get(const pbd_element* e);

/* string */
pbd_element* pbd_string_new();

pbd_element* pbd_string_create(const char* value);

int pbd_string_set(pbd_element* e, const char* value);

const char* pbd_string_get(const pbd_element* e);

/* bool_array */
pbd_element* pbd_bool_array_new();

int pbd_bool_array_add(pbd_element* s, bool value);

size_t pbd_bool_array_size(const pbd_element* s);
    
const bool* pbd_bool_array_values(const pbd_element* s);

/* element_array */
pbd_element* pbd_element_array_new();

int pbd_element_array_add(pbd_element* s, pbd_element* value);

size_t pbd_element_array_size(const pbd_element* s);
    
const pbd_element** pbd_element_array_values(const pbd_element* s);

/* integer_array */
pbd_element* pbd_integer_array_new();

int pbd_integer_array_add(pbd_element* s, int64_t value);

size_t pbd_integer_array_size(const pbd_element* s);
    
const int64_t* pbd_integer_array_values(const pbd_element* s);

/* real_array */
pbd_element* pbd_real_array_new();

int pbd_real_array_add(pbd_element* s, double value);

size_t pbd_real_array_size(const pbd_element* s);
    
const double* pbd_real_array_values(const pbd_element* s);

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_H */

