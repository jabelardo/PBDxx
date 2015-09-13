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

void test_null(void **state) {
    element null_1 = element::create_null();
    std::vector<char> buffer;
    null_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 1);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_null); 
}

void test_boolean(void **state) {
    element bool_1 = element::create_boolean(true);
    assert_int_equal(bool_1.as_boolean().get(), true);
    std::vector<char> buffer;
    bool_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 2);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_bool); 
    assert_int_equal(element.as_boolean().get(), true);
}

void test_integer(void **state) { 
    int64_t number = INT64_MAX;
    element integer_1 = element::create_integer(number);
    assert_int_equal(integer_1.as_integer().get(), number);
    std::vector<char> buffer;
    integer_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 9);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_integer); 
    assert_int_equal(element.as_integer().get(), number);
}

void test_real(void **state) { 
    double number = DBL_MAX;
    element real_1 = element::create_real(number);
    assert_int_equal(real_1.as_real().get(), number);
    std::vector<char> buffer;
    real_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 9);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_real); 
    assert_int_equal(element.as_real().get(), number);
}

void test_string(void **state) {   
    const char* STRING = "12345"; 
    element string_1 = element::create_string(STRING);
    assert_string_equal(string_1.as_string().get().c_str(), STRING);
    std::vector<char> buffer;
    string_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 7);
    size_t read_bytes = 0;
    element element = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element.type(), pbd_type_string);
    assert_string_equal(element.as_string().get().c_str(), STRING);
}

static const struct CMUnitTest group_tests[] = {
    cmocka_unit_test(test_null),
    cmocka_unit_test(test_boolean),
    cmocka_unit_test(test_integer),
    cmocka_unit_test(test_real),
    cmocka_unit_test(test_string),
};

int main() {
    return cmocka_run_group_tests(group_tests, NULL, NULL);
}
