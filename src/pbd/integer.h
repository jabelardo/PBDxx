/* 
 * File:   integer.h
 * Author: jabelardo
 *
 * Created on August 9, 2015, 9:05 AM
 */

#ifndef PBD_INTEGER_H
#define	PBD_INTEGER_H

#include "element.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct pbd_integer {
    struct pbd_element element;
    int64_t value;
} pbd_integer;

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_INTEGER_H */

