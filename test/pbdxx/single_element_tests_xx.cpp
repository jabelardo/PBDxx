#include <cstdlib>
#include <cstdarg>
#include <cstddef>
#include <csetjmp>
#include <cfloat>

#include <pbd/pbdxx.h>

extern "C" {
#include <cmocka.h>    
}

using namespace pbdxx;

void test_string(void **state) {   
    const char* STRING = "12345"; 
    string string_1(STRING);
    std::vector<char> buffer;
    string_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 7);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_string);
    assert_string_equal(element.string().get().c_str(), STRING);
}

void test_boolean(void **state) {
    boolean bool_1(true);
    std::vector<char> buffer;
    bool_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 2);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_bool); 
    assert_int_equal(element.boolean().get(), true);
}

void test_null(void **state) {
    null null_1;
    std::vector<char> buffer;
    null_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 1);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_null); 
    element.null();
}

void test_integer(void **state) { 
    int64_t number = INT64_MAX;
    integer integer_1(number);
    std::vector<char> buffer;
    integer_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 9);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_integer); 
    assert_int_equal(element.integer().get(), number);
}

void test_real(void **state) { 
    double number = DBL_MAX;
    real real_1(number);
    std::vector<char> buffer;
    real_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 9);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_real); 
    assert_int_equal(element.real().get(), number);
}

static const struct CMUnitTest pbd_single_element_tests_xx[] = {
    cmocka_unit_test(test_boolean),
    cmocka_unit_test(test_null),
    cmocka_unit_test(test_string),
    cmocka_unit_test(test_integer),
    cmocka_unit_test(test_real),
};

int main() {
    return cmocka_run_group_tests(pbd_single_element_tests_xx, NULL, NULL);
}
