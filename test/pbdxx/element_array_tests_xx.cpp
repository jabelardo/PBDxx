#include <cstdlib>
#include <cstdarg>
#include <cstddef>
#include <csetjmp>
#include <cassert>
#include <cfloat>

#include <pbd/pbdxx.h>

extern "C" {
#include <cmocka.h>    
}

using namespace pbdxx;

void test_pbd_element_array_single_element_childs(void **state) { 
    element e1 = element::create_element_array();
//    printf("e1 count %ld\n", e1.impl.use_count());
    
    assert_int_equal(e1.as_element_array().size(), 0);
    
//    e1.as_element_array().add(null());
//    printf("0 add count %ld\n", e1.elements[0].impl.use_count());
    
//    e1.as_element_array().add(boolean(true));
//    e1.add(boolean(false));
//    e1.add(null());
//    e1.add(integer(INT8_MAX/2));
//    e1.add(integer(INT16_MAX/2));
//    e1.add(integer(INT32_MAX/2));
//    e1.add(integer(INT64_MAX/2));
//    e1.add(null());
//    e1.add(real(FLT_MAX/2.0f));
//    e1.add(real(DBL_MAX/2.0));
//    e1.add(null());
//    e1.add(string("1029384756!@#$%ˆ*()-=_+asdA"));
//    e1.add(null());
    
    std::vector<char> buffer;
    //e1.to_buffer(buffer);
    
//    size_t read_bytes = 0;
//    element e2 = element::from_buffer(buffer, read_bytes);
//    assert_int_equal(buffer.size(), read_bytes);
//    assert_int_equal(e2.type(), pbd_type_element_array);
    
//    assert_int_equal(pbd_element_array_size(e2), 14);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[0]), pbd_type_null);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[1]), pbd_type_bool);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[2]), pbd_type_bool);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[3]), pbd_type_null);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[4]), pbd_type_integer);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[5]), pbd_type_integer);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[6]), pbd_type_integer);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[7]), pbd_type_integer);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[8]), pbd_type_null);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[9]), pbd_type_real);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[10]), pbd_type_real);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[11]), pbd_type_null);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[12]), pbd_type_string);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[13]), pbd_type_null);
//    
//    assert_int_equal(pbd_bool_get(pbd_element_array_values(e2)[1]), true);
//    assert_int_equal(pbd_bool_get(pbd_element_array_values(e2)[2]), false);
//    assert_int_equal(pbd_integer_get(pbd_element_array_values(e2)[4]), INT8_MAX/2);
//    assert_int_equal(pbd_integer_get(pbd_element_array_values(e2)[5]), INT16_MAX/2);
//    assert_int_equal(pbd_integer_get(pbd_element_array_values(e2)[6]), INT32_MAX/2);
//    assert_int_equal(pbd_integer_get(pbd_element_array_values(e2)[7]), INT64_MAX/2);
//    assert(pbd_real_get(pbd_element_array_values(e2)[9]) == FLT_MAX/2.0f);
//    assert(pbd_real_get(pbd_element_array_values(e2)[10]) == DBL_MAX/2.0);
//    assert_string_equal(pbd_string_get(pbd_element_array_values(e2)[12]), "1029384756!@#$%ˆ*()-=_+asdA");
}

static const struct CMUnitTest group_tests[] = {
    cmocka_unit_test(test_pbd_element_array_single_element_childs),
};

int main() {
    return cmocka_run_group_tests(group_tests, NULL, NULL);
}
