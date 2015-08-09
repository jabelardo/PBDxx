/* 
 * File:   real.h
 * Author: jabelardo
 *
 * Created on August 9, 2015, 12:01 PM
 */

#ifndef PBD_REAL_H
#define	PBD_REAL_H

#include "element.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct pbd_real {
    struct pbd_element element;
    double value;
} pbd_real;

#ifdef	__cplusplus
}
#endif

#endif	/* PBD_REAL_H */

