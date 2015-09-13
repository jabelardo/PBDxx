#include <cstdlib>
#include <cstdarg>
#include <cstddef>
#include <csetjmp>
#include <cfloat>
#include <cassert>

#include <pbd/pbdxx.h>

extern "C" {
#include <cmocka.h>    
}

using namespace pbdxx;

void test_real_array_to_buffer(void **state) {
    real_array element_1;
    double min = FLT_MIN;
    double max = FLT_MAX;
    element_1.add(min);
    element_1.add(max);

    assert_int_equal(element_1.type(), pbd_type_real_array);
    assert_int_equal(element_1.size(), 2);
    assert_int_equal(element_1.values()[0], min);
    assert_int_equal(element_1.values()[1], max);

    std::vector<char> buffer;
    element_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), sizeof(uint8_t) + sizeof(uint8_t) + sizeof(float) * 2);

    size_t read_bytes = 0;
    element element_2 = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element_2.type(), pbd_type_real_array);
    assert_int_equal(element_2.real_array().size(), 2);
    assert_int_equal(element_2.real_array().values()[0], min);
    assert_int_equal(element_2.real_array().values()[1], max);
}

void test_real_array_from_buffer(void **state) {
    real_array element_1;
    double min = DBL_MIN;
    double max = DBL_MAX;
    element_1.add(min);
    element_1.add(max/4);
    element_1.add(max/3);
    element_1.add(max/2);
    element_1.add(max);
    
    assert_int_equal(element_1.size(), 5);
    assert_true(element_1.values()[0] == min);
    assert_true(element_1.values()[1] == max/4);
    assert_true(element_1.values()[2] == max/3);
    assert_true(element_1.values()[3] == max/2);
    assert_true(element_1.values()[4] == max);

    std::vector<char> buffer;
    element_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), sizeof(uint8_t) + sizeof(uint8_t) + sizeof(double) * element_1.size());

    size_t read_bytes = 0;    
    element element_2 = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element_2.real_array().size(), 5);
    assert_true(element_2.real_array().values()[0] == min);
    assert_true(element_2.real_array().values()[1] == max/4);
    assert_true(element_2.real_array().values()[2] == max/3);
    assert_true(element_2.real_array().values()[3] == max/2);
    assert_true(element_2.real_array().values()[4] == max);
}

void test_integer_array_to_buffer(void **state) {
    integer_array element_1;
    int64_t max = INT64_MAX;
    element_1.add(max);

    assert_int_equal(element_1.type(), pbd_type_integer_array);

    std::vector<char> buffer;
    element_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), sizeof(uint8_t) + sizeof(uint8_t) + sizeof(int64_t));
}

void test_integer_array_from_buffer(void **state) {
    integer_array element_1;
    int64_t min = INT64_MIN;
    int64_t max = INT64_MAX;
    element_1.add(min);
    element_1.add(max/4);
    element_1.add(max/3);
    element_1.add(max/2);
    element_1.add(max);
    
    assert_int_equal(element_1.size(), 5);
    assert_true(element_1.values()[0] == min);
    assert_true(element_1.values()[1] == max/4);
    assert_true(element_1.values()[2] == max/3);
    assert_true(element_1.values()[3] == max/2);
    assert_true(element_1.values()[4] == max);

    std::vector<char> buffer;
    element_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), sizeof(uint8_t) + sizeof(uint8_t) + sizeof(double) * element_1.size());
    
    size_t read_bytes = 0;
    element element_2 = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element_2.integer_array().size(), 5);
    assert_true(element_2.integer_array().values()[0] == min);
    assert_true(element_2.integer_array().values()[1] == max/4);
    assert_true(element_2.integer_array().values()[2] == max/3);
    assert_true(element_2.integer_array().values()[3] == max/2);
    assert_true(element_2.integer_array().values()[4] == max);
}

static const struct CMUnitTest pbd_number_array_tests_xx[] = {
    cmocka_unit_test(test_real_array_to_buffer),
    cmocka_unit_test(test_real_array_from_buffer),
    cmocka_unit_test(test_integer_array_to_buffer),
    cmocka_unit_test(test_integer_array_from_buffer),
};

int main() {
    return cmocka_run_group_tests(pbd_number_array_tests_xx, NULL, NULL);
}