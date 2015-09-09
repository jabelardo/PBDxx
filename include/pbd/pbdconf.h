/* 
 * File:   pbdconf.h
 * Author: jabelardo
 *
 * Created on September 9, 2015, 8:48 AM
 */

#ifndef PBDCONF_H
#define	PBDCONF_H

#include <stddef.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct pbd_conf {
    bool use_compression;
    void* (* mem_alloc)(size_t size);
    void (*free_mem)(void* ptr);
    void* (*mem_realloc)(void* ptr, size_t size);
    void* (*zero_init_array_alloc)(size_t num, size_t size);
} pbd_conf;

#ifdef	__cplusplus
}
#endif

#endif	/* PBDCONF_H */

