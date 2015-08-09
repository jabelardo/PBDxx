#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <assert.h>

#include <pbd/pbd.h>

void test_pbd_bool_array_one_byte_size(void **state) {  
    pbd_element* element_1 = pbd_bool_array_new();
    assert_int_equal(pbd_bool_array_size(element_1), 0);
    
    int n_elem = 255;
    
    for (int i = 0; i < n_elem; ++i) {
        pbd_bool_array_add(element_1, i % 3 != 0);
    }
    assert_int_equal(pbd_bool_array_size(element_1), n_elem);
    
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 35);

    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_int_equal(size, read_bytes);
    assert_non_null(element_2);
    assert_int_equal(pbd_element_type(element_2), pbd_bool_array_type);
    assert_int_equal(pbd_bool_array_size(element_2), n_elem);
    for (int i = 0; i < n_elem; ++i) {
        assert_int_equal(pbd_bool_array_values(element_2)[i], i % 3 != 0);
    }
    
    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

void test_pbd_bool_array_two_bytes_size(void **state) {
    pbd_element* element_1 = pbd_bool_array_new();
    assert_int_equal(pbd_bool_array_size(element_1), 0);
    
    int n_elem = 2041;
    
    for (int i = 0; i < n_elem; ++i) {
        pbd_bool_array_add(element_1, i % 3 != 0);
    }
    assert_int_equal(pbd_bool_array_size(element_1), n_elem);
    
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 260);
    
    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_int_equal(size, read_bytes);
    assert_non_null(element_2);
    assert_int_equal(pbd_element_type(element_2), pbd_bool_array_type);
    assert_int_equal(pbd_bool_array_size(element_2), n_elem);
    for (int i = 0; i < n_elem; ++i) {
        assert_int_equal(pbd_bool_array_values(element_2)[i], i % 3 != 0);
    }
    
    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

void test_pbd_bool_array_four_bytes_size(void **state) {
    pbd_element* element_1 = pbd_bool_array_new();
    assert_int_equal(pbd_bool_array_size(element_1), 0);
    
    int n_elem = 524281;
    
    for (int i = 0; i < n_elem; ++i) {
        pbd_bool_array_add(element_1, i % 3 != 0);
    }
    assert_int_equal(pbd_bool_array_size(element_1), n_elem);
    
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 65542);

    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_int_equal(size, read_bytes);
    assert_non_null(element_2);
    assert_int_equal(pbd_element_type(element_2), pbd_bool_array_type);
    assert_int_equal(pbd_bool_array_size(element_2), n_elem);
    for (int i = 0; i < n_elem; ++i) {
        assert_int_equal(pbd_bool_array_values(element_2)[i], i % 3 != 0);
    }
    
    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

static const struct CMUnitTest pbd_bool_array_tests[] = {
    cmocka_unit_test(test_pbd_bool_array_one_byte_size),
    cmocka_unit_test(test_pbd_bool_array_two_bytes_size),
    cmocka_unit_test(test_pbd_bool_array_four_bytes_size),
};

int main() {
    return cmocka_run_group_tests(pbd_bool_array_tests, NULL, NULL);
}
