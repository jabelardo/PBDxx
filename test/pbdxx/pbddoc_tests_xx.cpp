#include <cstdlib>
#include <cstdarg>
#include <cstddef>
#include <csetjmp>
#include <cassert>

#include <pbd/pbdxx.h>
#include <pbd/pbddoc.h>
#include "../../src/pbd/endianess.h"

extern "C" {
#include <cmocka.h>    
}

using namespace pbdxx;

void test_pbd_doc_uncompressed(void **state) { 
    uint8_t const number = 4;

    element element_1 = element::create_integer(number);
    
    std::vector<char> buffer;
    element_1.to_doc_buffer(buffer);
    
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
    assert_int_equal(doc_buffer_valid_checksum(buffer), 0);

    size_t read_bytes = 0;
    element element_2 = element::from_doc_buffer(buffer, read_bytes);

    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element_2.type(), pbd_type_integer);
    assert_int_equal(element_2.as_integer().get(), number);
}

void test_pbd_doc_compressed(void **state) { 
    element element_1 = element::create_integer_array();
    
    for (int i = 0; i < UINT16_MAX; ++i) {
        element_1.as_integer_array().add(i);
    }
    
    std::vector<char> buffer;
    element_1.to_doc_buffer(buffer);

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
    assert_int_equal(doc_buffer_valid_checksum(buffer), 0);

    size_t read_bytes = 0;
    element element_2 = element::from_doc_buffer(buffer, read_bytes);
    
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element_2.type(), pbd_type_integer_array);
    
    std::vector<int64_t> values = element_2.as_integer_array().values();
    for (int i = 0; i < UINT16_MAX; ++i) {
        assert_int_equal(values[i], i);
    }
}

static const struct CMUnitTest group_tests[] = {
    cmocka_unit_test(test_pbd_doc_uncompressed),
    cmocka_unit_test(test_pbd_doc_compressed),
};

int main() {
    return cmocka_run_group_tests(group_tests, NULL, NULL);
}

