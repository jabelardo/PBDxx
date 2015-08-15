/* 
 * File:   pbddoc.h
 * Author: jabelardo
 *
 * Created on August 14, 2015, 4:27 PM
 */

#ifndef PBDDOC_H
#define	PBDDOC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Version
 */
/* 0000 0000 */
#define PBDDOC_VERSION_1            ((uint8_t) 0x00)
/* 0000 1111 */
#define PBDDOC_VERSION_MASK         ((uint8_t) 0x0f)

#define PBDDOC_VERSION              PBDDOC_VERSION_1
    
/**
 * Payload size length
 */
/* 0000 0000 */
#define PBDDOC_SIZE_LENGTH_1        ((uint8_t) 0x00)
/* 0001 0000 */    
#define PBDDOC_SIZE_LENGTH_2        ((uint8_t) 0x10)
/* 0010 0000 */
#define PBDDOC_SIZE_LENGTH_4        ((uint8_t) 0x20)
/* 0011 0000 */    
#define PBDDOC_SIZE_LENGTH_8        ((uint8_t) 0x30)
/* 0011 0000 */    
#define PBDDOC_SIZE_LENGTH_MASK     ((uint8_t) 0x30)  

/**
 * Endianess
 */
/* 0100 0000 */
#define PBDDOC_BIG_ENDIAN_FLAG      ((uint8_t) 0x40)
/* 0000 0000 */    
#define PBDDOC_LITTLE_ENDIAN_FLAG   ((uint8_t) 0x00)
/* 0100 0000 */    
#define PBDDOC_ENDIAN_MASK          ((uint8_t) 0x40)  

/**
 * Compress
 */
/* 1000 0000 */ 
#define PBDDOC_COMPRESSED_FLAG      ((uint8_t) 0x80)
/* 0000 0000 */ 
#define PBDDOC_UNCOMPRESSED_FLAG    ((uint8_t) 0x00)
/* 1000 0000 */ 
#define PBDDOC_COMPRESS_MASK        ((uint8_t) 0x80)

/**
 * doc parts sizes
 */
#define PBDDOC_HEAD_SIZE sizeof(uint8_t)

#define PBDDOC_CRC_SIZE sizeof(uint16_t)
    
typedef struct pbd_doc_head {
    bool big_endian;
    bool compressed;
    uint8_t version;
    uint8_t size_length;
} pbd_doc_head;
    
int pbd_doc_to_buffer(pbd_element* e, char** buffer, size_t* size);

pbd_doc_head pbd_doc_head_parse(uint8_t value);

pbd_element* pbd_doc_from_buffer(const char* buffer, size_t* read_bytes);

int pbd_doc_valid_checksum(const char* buffer);

uint16_t pbd_doc_get_checksum(const char* buffer, size_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* PBDDOC_H */

