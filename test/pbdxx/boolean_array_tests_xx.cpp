#include <cstdlib>
#include <cstdarg>
#include <cstddef>
#include <csetjmp>
#include <cassert>

#include <pbd/pbdxx.h>

extern "C" {
#include <cmocka.h>    
}

using namespace pbdxx;

void test_pbd_boolean_array(void **state) {
    element element_1 = element::create_boolean_array();
    assert_int_equal(element_1.as_boolean_array().size(), 0);
    
    int n_elem = 524281;
    for (int i = 0; i < n_elem; ++i) {
        element_1.as_boolean_array().add(i % 3 != 0);
    }
    assert_int_equal(element_1.as_boolean_array().size(), n_elem);
    
    std::vector<char> buffer;
    element_1.to_buffer(buffer);
    assert_int_equal(buffer.size(), 65542);

    size_t read_bytes = 0;
    element element_2 = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(element_2.type(), pbd_type_bool_array);
    assert_int_equal(element_2.as_boolean_array().size(), n_elem);
    std::vector<bool> values = element_2.as_boolean_array().values();
    for (int i = 0; i < n_elem; ++i) {
        assert_int_equal(values[i], i % 3 != 0);
    }
}

static const struct CMUnitTest group_tests[] = {
    cmocka_unit_test(test_pbd_boolean_array),
};

int main() {
    return cmocka_run_group_tests(group_tests, NULL, NULL);
}