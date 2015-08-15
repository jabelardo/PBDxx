#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <zlib.h>

#include <pbd/pbd.h>
#include <pbd/pbddoc.h>

static size_t buffer_size_length_by_value(size_t size) {
    if (size > UINT32_MAX) {
        return 8;
    } else if (size > UINT16_MAX) {
        return 4;
    } else if (size > UINT8_MAX) {
        return 2;
    } else {
        return 1;
    }
}

uint8_t pbd_doc_head_create(bool compressed, size_t size_length) {
    size_t s = 0;
//#ifdef BIG_ENDIAN
//    s |= PBDDOC_BIG_ENDIAN_FLAG;
//#endif
    if (compressed) {
        s |= PBDDOC_COMPRESSED_FLAG;
    }
    if (size_length == 8) {
        s |= PBDDOC_SIZE_LENGTH_8;
    } else if (size_length == 4) {
        s |= PBDDOC_SIZE_LENGTH_4;
    } else if (size_length == 2) {
        s |= PBDDOC_SIZE_LENGTH_2;
    } else if (size_length == 1) {
        s |= PBDDOC_SIZE_LENGTH_1;
    } 
    s |= PBDDOC_VERSION;
    return s;
}

/* 
 * Implementing The CCITT Cyclical Redundancy Check
 * Taken verbatim from, By Bob Felice, June 17, 2007
 * http://www.drdobbs.com/implementing-the-ccitt-cyclical-redundan/199904926
 */
uint16_t pbd_doc_get_checksum(const char* buffer, size_t size) {
    
    unsigned int crc = 0xffff;
    if (size == 0) {
        return ~crc;
    }
    unsigned int data;
    do {
        for (unsigned char i = 0, data = (unsigned int) 0xff & *buffer++; 
                i < 8; i++, data >>= 1) {
            
            if ((crc & 0x0001) ^ (data & 0x0001)) {
                crc = (crc >> 1) ^ 0x8408;
                
            } else {
                crc >>= 1;
            }
        }
    } while (--size);
        
    crc = ~crc;
    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xFF);
    return crc;    
}

int pbd_doc_compress(char* in, size_t in_size, char** result, size_t* result_size) {
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = deflateInit(&strm, 9);
    if (ret != Z_OK) {
        return -1;
    }
    strm.avail_in = in_size;
    strm.next_in = (Bytef *) &in[0];

    size_t const CHUNK = 131072;
    unsigned char out[CHUNK];
    *result = NULL;
    *result_size = 0;
    do {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        deflate(&strm, Z_FINISH);
        unsigned have = CHUNK - strm.avail_out;
        *result = realloc(*result, have + *result_size);
        memcpy(*result + *result_size, out, have);
        *result_size += have;
    } while (strm.avail_out == 0);
    deflateEnd(&strm);
    if (in_size <= *result_size) {
        free(*result);
        return 0;
    }
    return 1;
}

int pbd_doc_to_buffer(pbd_element* e, char** buffer, size_t* size) {
    char* e_buffer = NULL;
    size_t e_size = 0;
    int rcode = pbd_element_to_buffer(e, &e_buffer, &e_size);
    if (rcode != 0) {
        return rcode;
    }
    char* c_buffer = NULL;
    size_t c_size = 0;
    bool compressed = false;
    rcode = pbd_doc_compress(e_buffer, e_size, &c_buffer, &c_size);
    if (rcode == -1) {
        free(e_buffer);
        return -1;
    }
    if (rcode == 1) {
        free(e_buffer);
        e_buffer = c_buffer;
        e_size = c_size;
        compressed = true;
    }
    size_t buffer_size_length = buffer_size_length_by_value(e_size);
    *size = PBDDOC_HEAD_SIZE + buffer_size_length + e_size + PBDDOC_CRC_SIZE;
    *buffer = malloc(*size);
    if (*buffer == NULL) {
        free(e_buffer);
        return -1;
    }
    uint8_t head_val = pbd_doc_head_create(compressed, buffer_size_length);
    memcpy(*buffer, &head_val, sizeof(uint8_t));
    if (buffer_size_length == 1) {
        uint8_t tmp_size = e_size;
        memcpy(*buffer + PBDDOC_HEAD_SIZE, &tmp_size, buffer_size_length);
    } else if (buffer_size_length == 2) {
        uint16_t tmp_size = e_size;
        memcpy(*buffer + PBDDOC_HEAD_SIZE, &tmp_size, buffer_size_length);
    } else if (buffer_size_length == 4) {
        uint32_t tmp_size = e_size;
        memcpy(*buffer + PBDDOC_HEAD_SIZE, &tmp_size, buffer_size_length);
    } else if (buffer_size_length == 8) {
        uint64_t tmp_size = e_size;
        memcpy(*buffer + PBDDOC_HEAD_SIZE, &tmp_size, buffer_size_length);
    }
    memcpy(*buffer + PBDDOC_HEAD_SIZE + buffer_size_length, e_buffer, e_size);
    uint16_t checksum = pbd_doc_get_checksum(*buffer, PBDDOC_HEAD_SIZE + 
            buffer_size_length + e_size);
    memcpy(*buffer + PBDDOC_HEAD_SIZE + buffer_size_length + e_size, &checksum , 
            sizeof(uint16_t));
    
    free(e_buffer);
    return 0;
}

static size_t pbd_doc_get_buffer_size(pbd_doc_head h, const char*  buffer) {
    size_t buffer_size;
    if (h.size_length == 1) {
        uint8_t tmp_size;
        memcpy(&tmp_size, buffer + PBDDOC_HEAD_SIZE, sizeof(uint8_t));
        buffer_size = tmp_size;
    } else if (h.size_length == 2) {
        uint16_t tmp_size;
        memcpy(&tmp_size, buffer + PBDDOC_HEAD_SIZE, sizeof(uint16_t));
        buffer_size = tmp_size;
    } else if (h.size_length == 4) {
        uint32_t tmp_size;
        memcpy(&tmp_size, buffer + PBDDOC_HEAD_SIZE, sizeof(uint32_t));
        buffer_size = tmp_size;
    } else if (h.size_length == 8) {
        uint64_t tmp_size;
        memcpy(&tmp_size, buffer + PBDDOC_HEAD_SIZE, sizeof(uint64_t));
        buffer_size = tmp_size;
    }  
    return buffer_size;
}

int pbd_doc_valid_checksum(const char* buffer) {
    pbd_doc_head h = pbd_doc_head_parse(buffer[0]);
    size_t buffer_size = pbd_doc_get_buffer_size(h, buffer);
    uint16_t checksum_calc = pbd_doc_get_checksum(buffer, PBDDOC_HEAD_SIZE + 
            h.size_length + buffer_size);
    uint16_t checksum_doc;
    memcpy(&checksum_doc, buffer + PBDDOC_HEAD_SIZE +  h.size_length + 
            buffer_size, sizeof(uint16_t));
    return (checksum_calc == checksum_doc) ? 0 : -1;
}

pbd_doc_head pbd_doc_head_parse(uint8_t value) {
    pbd_doc_head h;
    h.compressed = value & PBDDOC_COMPRESS_MASK;
    h.big_endian = value & PBDDOC_ENDIAN_MASK;
    h.version = value & PBDDOC_VERSION_MASK;
    
    switch (value & PBDDOC_SIZE_LENGTH_MASK) {
        case PBDDOC_SIZE_LENGTH_8:
            h.size_length = 8;
            break;
            
        case PBDDOC_SIZE_LENGTH_4:
            h.size_length = 4;
            break;   
            
        case PBDDOC_SIZE_LENGTH_2:
            h.size_length = 2;
            break; 
            
        default:
            h.size_length = 1;
    }
    return h;
}

int pbd_doc_decompress(const char* in, size_t in_size, char** result, size_t* result_size) {
    z_stream strm;    
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    int ret = inflateInit(&strm);
    if (ret != Z_OK) {
        return -1;
    }
    strm.avail_in = in_size;
    strm.next_in = (Bytef *) &in[0];

    size_t const CHUNK = 131072;
    unsigned char out[CHUNK];
    *result = NULL;
    *result_size = 0;
    do {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        ret = inflate(&strm, Z_NO_FLUSH);
        switch (ret)  {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&strm);
                free(*result);
                *result = NULL;
                *result_size = 0;
                return -1;
        }
        unsigned have = CHUNK - strm.avail_out;
        *result = realloc(*result, have + *result_size);
        memcpy(*result + *result_size, out, have);
        *result_size += have;
    } while (strm.avail_out == 0);
    inflateEnd(&strm);
    return 0;
}

pbd_element* pbd_doc_from_buffer(const char* buffer, size_t* read_bytes) {
    pbd_doc_head h = pbd_doc_head_parse(buffer[0]);
    size_t buffer_size = pbd_doc_get_buffer_size(h, buffer);
    uint16_t checksum_calc = pbd_doc_get_checksum(buffer, PBDDOC_HEAD_SIZE + 
            h.size_length + buffer_size);
    uint16_t checksum_doc;
    memcpy(&checksum_doc, buffer + PBDDOC_HEAD_SIZE +  h.size_length + 
            buffer_size, sizeof(uint16_t));
    if (checksum_calc != checksum_doc) {
        return NULL;
    }
    char* d_buffer;
    char* c_buffer = (char*) buffer + PBDDOC_HEAD_SIZE +  h.size_length;
    if (h.compressed) {
        size_t result_size;
        if (-1 == pbd_doc_decompress(c_buffer, buffer_size, &d_buffer, &result_size)) {
            return NULL;
        }
    } else {
        d_buffer = c_buffer;
    }
    *read_bytes =  PBDDOC_HEAD_SIZE +  h.size_length +  buffer_size + PBDDOC_CRC_SIZE;
    
    pbd_element* e = pbd_element_create(d_buffer);
    
    if (h.compressed) {
        free(d_buffer);
    }
    return e;
}