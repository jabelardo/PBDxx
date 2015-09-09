#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include <pbd/pbd.h>
#include <pbd/pbddoc.h>
#include "../../src/pbd/endianess.h"

void test_pbd_doc_uncompressed(void **state) { 
    uint8_t const number = 4;

    pbd_element* element_1 = pbd_integer_create(number);
    
    char *buffer = NULL;
    size_t size;
    pbd_doc_to_buffer(element_1, &buffer, &size);
    
    assert_int_equal((uint8_t) buffer[0], (uint8_t) 0);
    assert_int_equal((uint8_t) buffer[1], (uint8_t) 2);
    assert_int_equal((uint8_t) buffer[2], (uint8_t) 4);
    assert_int_equal((uint8_t) buffer[3], (uint8_t) 4);

    if (pbd_is_little_endian()) {
        assert_int_equal((buffer[0] & PBDDOC_ENDIAN_MASK), PBDDOC_LITTLE_ENDIAN_FLAG);
    } else {
        assert_int_equal((buffer[0] & PBDDOC_ENDIAN_MASK), PBDDOC_BIG_ENDIAN_FLAG);
    }
    assert_int_equal((buffer[0] & PBDDOC_VERSION_MASK), PBDDOC_VERSION_1);
    assert_int_equal((buffer[0] & PBDDOC_COMPRESS_MASK), PBDDOC_UNCOMPRESSED_FLAG);
    assert_int_equal((buffer[0] & PBDDOC_SIZE_LENGTH_MASK), PBDDOC_SIZE_LENGTH_1);
    assert_int_equal((buffer[0] & PBDDOC_UNC_SIZE_LENGTH_MASK), PBDDOC_UNC_SIZE_LENGTH_0_OR_1);

    pbd_doc_head head = pbd_doc_head_parse(buffer[0]);
    if (pbd_is_little_endian()) {
        assert_int_equal(head.little_endian, true);
    } else {
        assert_int_equal(head.little_endian, false);
    }
    assert_int_equal(head.version, PBDDOC_VERSION);
    assert_int_equal(head.compressed, false);
    assert_int_equal(head.size_length, 1);
    assert_int_equal(head.uncompressed_size_length, 0);
    assert_int_equal(pbd_doc_valid_checksum(buffer), 0);

    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_doc_from_buffer(buffer, &read_bytes);
    
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element_2), pbd_type_integer);
    assert_int_equal(pbd_integer_get(element_2), number);
  
    free(buffer); 
    pbd_element_free(element_1);
    pbd_element_free(element_2);
}

void test_pbd_doc_compressed(void **state) { 

    pbd_element* element_1 = pbd_integer_array_new();
    
    for (int i = 0; i < UINT16_MAX; ++i) {
        pbd_integer_array_add(element_1, i);
    }
    
    char *buffer = NULL;
    size_t size;
    pbd_doc_to_buffer(element_1, &buffer, &size);

    if (pbd_is_little_endian()) {
        assert_int_equal((buffer[0] & PBDDOC_ENDIAN_MASK), PBDDOC_LITTLE_ENDIAN_FLAG);
    } else {
        assert_int_equal((buffer[0] & PBDDOC_ENDIAN_MASK), PBDDOC_BIG_ENDIAN_FLAG);
    }
    assert_int_equal((buffer[0] & PBDDOC_VERSION_MASK), PBDDOC_VERSION_1);
    assert_int_equal((buffer[0] & PBDDOC_COMPRESS_MASK), PBDDOC_COMPRESSED_FLAG);
    assert_int_equal((buffer[0] & PBDDOC_SIZE_LENGTH_MASK), PBDDOC_SIZE_LENGTH_4);
    assert_int_equal((buffer[0] & PBDDOC_UNC_SIZE_LENGTH_MASK), PBDDOC_UNC_SIZE_LENGTH_4);

    pbd_doc_head head = pbd_doc_head_parse(buffer[0]);
    if (pbd_is_little_endian()) {
        assert_int_equal(head.little_endian, true);
    } else {
        assert_int_equal(head.little_endian, false);
    }
    assert_int_equal(head.version, PBDDOC_VERSION);
    assert_int_equal(head.compressed, true);
    assert_int_equal(head.size_length, 4);
    assert_int_equal(head.uncompressed_size_length, 4);
    assert_int_equal(pbd_doc_valid_checksum(buffer), 0);

    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_doc_from_buffer(buffer, &read_bytes);
    
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element_2), pbd_type_integer_array);
    
    for (int i = 0; i < UINT16_MAX; ++i) {
        assert_int_equal(pbd_integer_array_values(element_2)[i], i);
    }
  
    free(buffer); 
    pbd_element_free(element_1);
    pbd_element_free(element_2);
}

static const struct CMUnitTest pbddoc_tests[] = {
    cmocka_unit_test(test_pbd_doc_uncompressed),
    cmocka_unit_test(test_pbd_doc_compressed),
};

int main() {
    return cmocka_run_group_tests(pbddoc_tests, NULL, NULL);
}
