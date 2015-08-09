#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <float.h>

#include <pbd/pbd.h>

void test_pbd_string(void **state) {   
    const char *STRING = "12345"; 
    pbd_element* string_1 = pbd_string_create(STRING);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(string_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 7);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_string_type);
    assert_string_equal(pbd_string_get(element), STRING);
    free(buffer);
    pbd_element_free(string_1);
    pbd_element_free(element);
}

void test_pbd_bool(void **state) {
    pbd_element* bool_1 = pbd_bool_create(true);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(bool_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 2);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_bool_type);    
    assert_int_equal(pbd_bool_get(element), true);   
    free(buffer); 
    pbd_element_free(bool_1);
    pbd_element_free(element);
}

void test_pbd_null(void **state) {
    pbd_element* null_1 = pbd_null_new();
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(null_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 1);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_null_type);   
    free(buffer); 
    pbd_element_free(null_1);
    pbd_element_free(element);
}

void test_int8_integer_pbd(void **state) { 
    int8_t number = INT8_MAX;
    pbd_element* integer_1 = pbd_integer_create(number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(integer_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 2);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_integer_type);
    assert_int_equal(pbd_integer_get(element), number);
    free(buffer); 
    pbd_element_free(integer_1);
    pbd_element_free(element);
}

void test_uint8_integer_pbd(void **state) {
    uint8_t number = UINT8_MAX;
    pbd_element* integer_1 = pbd_integer_create(number);
    assert_int_equal(pbd_integer_get(integer_1), number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(integer_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 2);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_integer_type);
    assert_int_equal(pbd_integer_get(element), number);
    free(buffer); 
    pbd_element_free(integer_1);
    pbd_element_free(element);
}

void test_int16_integer_pbd(void **state) {
    int16_t number = INT16_MAX;
    pbd_element* integer_1 = pbd_integer_create(number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(integer_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 3);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_integer_type);
    assert_int_equal(pbd_integer_get(element), number);
    free(buffer); 
    pbd_element_free(integer_1);
    pbd_element_free(element);
}

void test_uint16_integer_pbd(void **state) {
    uint16_t number = UINT16_MAX;
    pbd_element* integer_1 = pbd_integer_create(number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(integer_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 3);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_integer_type);
    assert_int_equal(pbd_integer_get(element), number);
    free(buffer); 
    pbd_element_free(integer_1);
    pbd_element_free(element);
}

void test_int32_integer_pbd(void **state) {
    int32_t number = INT32_MAX;
    pbd_element* integer_1 = pbd_integer_create(number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(integer_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 5);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_integer_type);
    assert_int_equal(pbd_integer_get(element), number);
    free(buffer); 
    pbd_element_free(integer_1);
    pbd_element_free(element);
}

void test_uint32_integer_pbd(void **state) {
    uint32_t number = UINT32_MAX;
    pbd_element* integer_1 = pbd_integer_create(number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(integer_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 5);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_integer_type);
    assert_int_equal(pbd_integer_get(element), number);
    free(buffer); 
    pbd_element_free(integer_1);
    pbd_element_free(element);
}

void test_int64_integer_pbd(void **state) {
    int64_t number = INT64_MAX;
    pbd_element* integer_1 = pbd_integer_create(number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(integer_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 9);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_integer_type);
    assert_int_equal(pbd_integer_get(element), number);
    free(buffer); 
    pbd_element_free(integer_1);
    pbd_element_free(element);
}

void test_float_real_pbd(void **state) {
    float number = FLT_MAX;
    pbd_element* real_1 = pbd_real_create(number);
    assert_true(pbd_real_get(real_1) == number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(real_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 5);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_real_type);
    assert_true(pbd_real_get(element) == number);
    free(buffer); 
    pbd_element_free(real_1);
    pbd_element_free(element);
}

void test_double_real_pbd(void **state) {
    double number = DBL_MAX;
    pbd_element* real_1 = pbd_real_create(number);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(real_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, 9);
    size_t read_bytes = 0;
    pbd_element* element = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element), pbd_real_type);
    assert_true(pbd_real_get(element) == number);
    free(buffer); 
    pbd_element_free(real_1);
    pbd_element_free(element);
}

static const struct CMUnitTest pbd_single_element_tests[] = {
    cmocka_unit_test(test_pbd_bool),
    cmocka_unit_test(test_pbd_null),
    cmocka_unit_test(test_pbd_string),
    cmocka_unit_test(test_int8_integer_pbd),
    cmocka_unit_test(test_uint8_integer_pbd),
    cmocka_unit_test(test_int16_integer_pbd),
    cmocka_unit_test(test_uint16_integer_pbd),
    cmocka_unit_test(test_int32_integer_pbd),
    cmocka_unit_test(test_uint32_integer_pbd),
    cmocka_unit_test(test_int64_integer_pbd),
    cmocka_unit_test(test_float_real_pbd),
    cmocka_unit_test(test_double_real_pbd),
};

int main() {
    return cmocka_run_group_tests(pbd_single_element_tests, NULL, NULL);
}
