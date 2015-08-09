/* 
 * File:   integerarray.h
 * Author: jabelardo
 *
 * Created on August 11, 2015, 4:38 PM
 */

#ifndef POD_INTEGERARRAY_H
#define	POD_INTEGERARRAY_H

#include "element.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct pbd_integer_array {
    struct pbd_element element;
    int64_t* values;
    size_t size;
    size_t capacity;
} pbd_integer_array;

#ifdef	__cplusplus
}
#endif

#endif	/* POD_INTEGERARRAY_H */

