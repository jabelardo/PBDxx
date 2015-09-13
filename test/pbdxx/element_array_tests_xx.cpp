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
    
    assert_int_equal(e1.as_element_array().size(), 0);
    
    e1.as_element_array().add(element::create_null());
    
    e1.as_element_array().add(element::create_boolean(true));
    e1.as_element_array().add(element::create_boolean(false));
    e1.as_element_array().add(element::create_null());
    e1.as_element_array().add(element::create_integer(INT8_MAX/2));
    e1.as_element_array().add(element::create_integer(INT16_MAX/2));
    e1.as_element_array().add(element::create_integer(INT32_MAX/2));
    e1.as_element_array().add(element::create_integer(INT64_MAX/2));
    e1.as_element_array().add(element::create_null());
    e1.as_element_array().add(element::create_real(FLT_MAX/2.0f));
    e1.as_element_array().add(element::create_real(DBL_MAX/2.0));
    e1.as_element_array().add(element::create_null());
    e1.as_element_array().add(element::create_string("1029384756!@#$%ˆ*()-=_+asdA"));
    e1.as_element_array().add(element::create_null());
    
    std::vector<char> buffer;
    e1.to_buffer(buffer);
    
    size_t read_bytes = 0;
    element e2 = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(e2.type(), pbd_type_element_array);
    
    element_array& element_array2 = e2.as_element_array();
    
    assert_int_equal(element_array2.size(), 14);
    assert_int_equal(element_array2.values()[0].type(), pbd_type_null);
    assert_int_equal(element_array2.values()[1].type(), pbd_type_bool);
    assert_int_equal(element_array2.values()[2].type(), pbd_type_bool);
    assert_int_equal(element_array2.values()[3].type(), pbd_type_null);
    assert_int_equal(element_array2.values()[4].type(), pbd_type_integer);
    assert_int_equal(element_array2.values()[5].type(), pbd_type_integer);
    assert_int_equal(element_array2.values()[6].type(), pbd_type_integer);
    assert_int_equal(element_array2.values()[7].type(), pbd_type_integer);
    assert_int_equal(element_array2.values()[8].type(), pbd_type_null);
    assert_int_equal(element_array2.values()[9].type(), pbd_type_real);
    assert_int_equal(element_array2.values()[10].type(), pbd_type_real);
    assert_int_equal(element_array2.values()[11].type(), pbd_type_null);
    assert_int_equal(element_array2.values()[12].type(), pbd_type_string);
    assert_int_equal(element_array2.values()[13].type(), pbd_type_null);
    
    assert_int_equal(element_array2.values()[1].as_boolean().get(), true);
    assert_int_equal(element_array2.values()[2].as_boolean().get(), false);
    assert_int_equal(element_array2.values()[4].as_integer().get(), INT8_MAX/2);
    assert_int_equal(element_array2.values()[5].as_integer().get(), INT16_MAX/2);
    assert_int_equal(element_array2.values()[6].as_integer().get(), INT32_MAX/2);
    assert_int_equal(element_array2.values()[7].as_integer().get(), INT64_MAX/2);
    assert(element_array2.values()[9].as_real().get() == FLT_MAX/2.0f);
    assert(element_array2.values()[10].as_real().get() == DBL_MAX/2.0);
    assert_string_equal(element_array2.values()[12].as_string().get().c_str(), "1029384756!@#$%ˆ*()-=_+asdA");
}

static const struct CMUnitTest group_tests[] = {
    cmocka_unit_test(test_pbd_element_array_single_element_childs),
};

int main() {
    return cmocka_run_group_tests(group_tests, NULL, NULL);
}
