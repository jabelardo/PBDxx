/* 
 * File:   realarray.h
 * Author: jabelardo
 *
 * Created on August 9, 2015, 2:50 PM
 */

#ifndef PBD_REALARRAY_H
#define	PBD_REALARRAY_H

#include "element.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct pbd_real_array {
    struct pbd_element element;
    double* values;
    size_t size;
    size_t capacity;
} pbd_real_array;

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_REALARRAY_H */

