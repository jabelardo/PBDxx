/* 
 * File:   elementarray.h
 * Author: jabelardo
 *
 * Created on August 11, 2015, 7:46 PM
 */

#ifndef PBD_ELEMENTARRAY_H
#define	PBD_ELEMENTARRAY_H

#include "element.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct pbd_element_array {
    struct pbd_element element;
    const struct pbd_element** values;
    size_t size;
    size_t capacity;
} pbd_element_array;

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_ELEMENTARRAY_H */

