/* 
 * File:   boolean.h
 * Author: jabelardo
 *
 * Created on August 9, 2015, 8:05 AM
 */

#ifndef PBD_BOOL_H
#define	PBD_BOOL_H

#include <stdbool.h>

#include "element.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct pbd_bool {
    struct pbd_element element;
    bool value;
} pbd_bool;

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_BOOL_H */

