/* 
 * File:   string.h
 * Author: Jose Abelardo Gutierrez
 *
 * Created on August 3, 2015, 4:04 AM
 */

#ifndef PBD_STRING_H
#define	PBD_STRING_H

#include "element.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct pbd_string {
    struct pbd_element element;
    char* value;
} pbd_string;

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_STRING_H */

