#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <float.h>
#include <assert.h>

#include <pbd/pbd.h>

void test_real_array_to_buffer_float(void **state) {    
    pbd_element* element_1 = pbd_real_array_new();
    double min = FLT_MIN;
    double max = FLT_MAX;
    pbd_real_array_add(element_1, min);
    pbd_real_array_add(element_1, max);

    assert_int_equal(pbd_element_type(element_1), pbd_real_array_type);
    assert_int_equal(pbd_real_array_size(element_1), 2);
    assert_int_equal(pbd_real_array_values(element_1)[0], min);
    assert_int_equal(pbd_real_array_values(element_1)[1], max);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint8_t) + sizeof(float) * 2);

    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element_2), pbd_real_array_type);
    assert_int_equal(pbd_real_array_size(element_2), 2);
    assert_int_equal(pbd_real_array_values(element_2)[0], min);
    assert_int_equal(pbd_real_array_values(element_2)[1], max);
    
    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

void test_real_array_to_buffer_double(void **state) {
    pbd_element* element_1 = pbd_real_array_new();
    double min = FLT_MIN;
    double max = FLT_MAX;
    pbd_real_array_add(element_1, min);
    pbd_real_array_add(element_1, max);

    assert_int_equal(pbd_element_type(element_1), pbd_real_array_type);
    assert_int_equal(pbd_real_array_size(element_1), 2);
    assert_int_equal(pbd_real_array_values(element_1)[0], min);
    assert_int_equal(pbd_real_array_values(element_1)[1], max);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint8_t) + sizeof(float) * 2);

    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element_2), pbd_real_array_type);
    assert_int_equal(pbd_real_array_size(element_2), 2);
    assert_int_equal(pbd_real_array_values(element_2)[0], min);
    assert_int_equal(pbd_real_array_values(element_2)[1], max);
    
    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

void test_real_array_two_bytes(void **state) {
    pbd_element* element_1 = pbd_real_array_new();
    double num = DBL_MAX;
    for (int i = 0; i < 256; ++i) {
        if (num == 0.0) num = DBL_MAX;
        pbd_real_array_add(element_1, num);
        num /= -2;
    }
    assert_int_equal(pbd_element_type(element_1), pbd_real_array_type);
    assert_int_equal(pbd_real_array_size(element_1), 256);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint16_t) + sizeof(double) * 256);

    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element_2), pbd_real_array_type);
    assert_int_equal(pbd_real_array_size(element_2), 256);

    for (int i = 0; i < 256; ++i) {
        assert_true(pbd_real_array_values(element_1)[i] == pbd_real_array_values(element_2)[i]);
    }
    
    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

void test_real_array_from_buffer(void **state) {
    pbd_element* element_1 = pbd_real_array_new();
    double min = DBL_MIN;
    double max = DBL_MAX;
    pbd_real_array_add(element_1, min);
    pbd_real_array_add(element_1, max/4);
    pbd_real_array_add(element_1, max/3);
    pbd_real_array_add(element_1, max/2);
    pbd_real_array_add(element_1, max);
    
    size_t element_1_size = pbd_real_array_size(element_1);
    assert_int_equal(element_1_size, 5);
    assert_true(pbd_real_array_values(element_1)[0] == min);
    assert_true(pbd_real_array_values(element_1)[1] == max/4);
    assert_true(pbd_real_array_values(element_1)[2] == max/3);
    assert_true(pbd_real_array_values(element_1)[3] == max/2);
    assert_true(pbd_real_array_values(element_1)[4] == max);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint8_t) + sizeof(double) * element_1_size);

    size_t read_bytes = 0;    
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_real_array_size(element_2), 5);
    assert_true(pbd_real_array_values(element_2)[0] == min);
    assert_true(pbd_real_array_values(element_2)[1] == max/4);
    assert_true(pbd_real_array_values(element_2)[2] == max/3);
    assert_true(pbd_real_array_values(element_2)[3] == max/2);
    assert_true(pbd_real_array_values(element_2)[4] == max);
    
    free(buffer);
    pbd_element_free(element_1);
    pbd_element_free(element_2);
}

void test_integer_array_to_buffer_int8_one_byte(void **state) {
    pbd_element* element_1 = pbd_integer_array_new();
    int8_t min = INT8_MIN;
    int8_t max = INT8_MAX;
    pbd_integer_array_add(element_1, min);
    pbd_integer_array_add(element_1, max);

    assert_int_equal(pbd_integer_array_size(element_1), 2);
    assert_int_equal(pbd_integer_array_values(element_1)[0], min);
    assert_int_equal(pbd_integer_array_values(element_1)[1], max);
    assert_int_equal(pbd_element_type(element_1), pbd_integer_array_type);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint8_t) + sizeof(int8_t) * 2);
    
    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element_2), pbd_integer_array_type);
    assert_int_equal(pbd_integer_array_size(element_2), 2);
    assert_int_equal(pbd_integer_array_values(element_2)[0], min);
    assert_int_equal(pbd_integer_array_values(element_2)[1], max);
    
    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

void test_integer_array_to_buffer_int8_two_bytes(void **state) {
    pbd_element* element_1 = pbd_integer_array_new();
    int8_t num = INT8_MAX;
    for (int i = 0; i < 256; ++i) {
        if (num == 0) num = INT8_MAX;
        pbd_integer_array_add(element_1, num);
        num /= -2;
    }
    assert_int_equal(pbd_element_type(element_1), pbd_integer_array_type);
    assert_int_equal(pbd_integer_array_size(element_1), 256);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint16_t) + sizeof(int8_t) * 256);
    
    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(element_2), pbd_integer_array_type);
    assert_int_equal(pbd_integer_array_size(element_2), 256);
    
    assert_int_equal(
        pbd_integer_array_values(element_1)[1], 
        pbd_integer_array_values(element_2)[1]);
    
    for (int i = 0; i < 256; ++i) {
        assert_int_equal(
            pbd_integer_array_values(element_1)[i], 
            pbd_integer_array_values(element_2)[i]);
    }
    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

void test_integer_array_to_buffer_int8_four_bytes(void **state) {
    pbd_element* element_1 = pbd_integer_array_new();
    int8_t max = INT8_MAX;
    for (int i = 0; i < 65536; ++i) {
        pbd_integer_array_add(element_1, max);
    }

    assert_int_equal(pbd_element_type(element_1), pbd_integer_array_type);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint32_t) + sizeof(int8_t) * 65536);
    
    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_integer_array_size(element_2), 65536);

    pbd_element_free(element_1);
    pbd_element_free(element_2);
    free(buffer);
}

void test_integer_array_to_buffer_int16(void **state) {
    pbd_element* element_1 = pbd_integer_array_new();
    int16_t max = INT16_MAX;
    pbd_integer_array_add(element_1, max);

    assert_int_equal(pbd_element_type(element_1), pbd_integer_array_type);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint8_t) + sizeof(int16_t));

    pbd_element_free(element_1);
    free(buffer);
}

void test_integer_array_to_buffer_int32(void **state) {
    pbd_element* element_1 = pbd_integer_array_new();
    int32_t max = INT32_MAX;
    pbd_integer_array_add(element_1, max);

    assert_int_equal(pbd_element_type(element_1), pbd_integer_array_type);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint8_t) + sizeof(int32_t));

    pbd_element_free(element_1);
    free(buffer);
}

void test_integer_array_to_buffer_int64(void **state) {
    pbd_element* element_1 = pbd_integer_array_new();
    int64_t max = INT64_MAX;
    pbd_integer_array_add(element_1, max);

    assert_int_equal(pbd_element_type(element_1), pbd_integer_array_type);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint8_t) + sizeof(int64_t));

    pbd_element_free(element_1);
    free(buffer);
}

void test_integer_array_from_buffer(void **state) {
    pbd_element* element_1 = pbd_integer_array_new();
    int64_t min = INT64_MIN;
    int64_t max = INT64_MAX;
    pbd_integer_array_add(element_1, min);
    pbd_integer_array_add(element_1, max/4);
    pbd_integer_array_add(element_1, max/3);
    pbd_integer_array_add(element_1, max/2);
    pbd_integer_array_add(element_1, max);
    
    size_t element_1_size = pbd_integer_array_size(element_1);
    assert_int_equal(element_1_size, 5);
    assert_true(pbd_integer_array_values(element_1)[0] == min);
    assert_true(pbd_integer_array_values(element_1)[1] == max/4);
    assert_true(pbd_integer_array_values(element_1)[2] == max/3);
    assert_true(pbd_integer_array_values(element_1)[3] == max/2);
    assert_true(pbd_integer_array_values(element_1)[4] == max);

    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(element_1, &buffer, &size);
    assert_non_null(buffer);
    assert_int_equal(size, sizeof(uint8_t) + sizeof(uint8_t) + sizeof(double) * element_1_size);
    
    size_t read_bytes = 0;
    pbd_element* element_2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(element_2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_integer_array_size(element_2), 5);
    assert_true(pbd_integer_array_values(element_2)[0] == min);
    assert_true(pbd_integer_array_values(element_2)[1] == max/4);
    assert_true(pbd_integer_array_values(element_2)[2] == max/3);
    assert_true(pbd_integer_array_values(element_2)[3] == max/2);
    assert_true(pbd_integer_array_values(element_2)[4] == max);
    
    free(buffer);
    pbd_element_free(element_1);
    pbd_element_free(element_2);
}

static const struct CMUnitTest pbd_number_array_tests[] = {
    cmocka_unit_test(test_real_array_to_buffer_float),
    cmocka_unit_test(test_real_array_to_buffer_double),
    cmocka_unit_test(test_real_array_two_bytes),
    cmocka_unit_test(test_real_array_from_buffer),
    cmocka_unit_test(test_integer_array_to_buffer_int8_one_byte),
    cmocka_unit_test(test_integer_array_to_buffer_int8_two_bytes),
    cmocka_unit_test(test_integer_array_to_buffer_int8_four_bytes),
    cmocka_unit_test(test_integer_array_to_buffer_int16),
    cmocka_unit_test(test_integer_array_to_buffer_int32),
    cmocka_unit_test(test_integer_array_to_buffer_int64),
    cmocka_unit_test(test_integer_array_from_buffer),
};

int main() {
    return cmocka_run_group_tests(pbd_number_array_tests, NULL, NULL);
}
