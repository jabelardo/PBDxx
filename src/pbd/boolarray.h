/* 
 * File:   boolarray.h
 * Author: jabelardo
 *
 * Created on August 12, 2015, 5:50 PM
 */

#ifndef PBD_BOOLARRAY_H
#define	PBD_BOOLARRAY_H

#include "element.h"

#ifdef	__cplusplus
extern "C" {
#endif


typedef struct pbd_bool_array {
    struct pbd_element element;
    bool* values;
    size_t size;
    size_t capacity;
} pbd_bool_array;

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_BOOLARRAY_H */

