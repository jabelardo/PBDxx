/* 
 * File:   element.h
 * Author: Jose Abelardo Gutierrez
 *
 * Created on August 3, 2015, 4:05 AM
 */

#ifndef PBD_ELEMENT_H
#define	PBD_ELEMENT_H

#include <stddef.h>
#include <stdint.h>

#include <pbd/pbd.h>

#include "typeid.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
#define SIZEOF_TYPE_ID sizeof(uint8_t)
    
struct pbd_element;
    
typedef struct pbd_element_vtable {
    const pbd_type type;
    int (*to_buffer)(const struct pbd_element* e, char** buffer, size_t* size);
    int (*from_buffer)(struct pbd_element* e, const char* buffer, pbd_type_id type_id,  size_t* read_bytes);
    void (*free)(const struct pbd_element* e);
} pbd_element_vtable;

struct pbd_element {
    pbd_element_vtable* vtable;
};


#ifdef	__cplusplus
}
#endif

#endif	/* PBD_ELEMENT_H */

