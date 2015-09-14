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
    
    const char* STRING = "1029384756!@#$%ˆ*()-=_+asdA";
    
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
    e1.as_element_array().add(element::create_string(STRING));
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
    assert_string_equal(element_array2.values()[12].as_string().get().c_str(), STRING);
}

void test_pbd_element_array_single_element_array_childs(void **state) {
    
    element ba1 = element::create_boolean_array();
    ba1.as_boolean_array().add(false);
    ba1.as_boolean_array().add(true);
    ba1.as_boolean_array().add(true);
    ba1.as_boolean_array().add(false);
    ba1.as_boolean_array().add(false);
    ba1.as_boolean_array().add(false);
    ba1.as_boolean_array().add(true);
    ba1.as_boolean_array().add(true);
    ba1.as_boolean_array().add(true);
    ba1.as_boolean_array().add(true);
    ba1.as_boolean_array().add(true);
    assert_int_equal(ba1.as_boolean_array().size(), 11);
    
    element ia1 = element::create_integer_array();
    ia1.as_integer_array().add(UINT8_MAX);
    ia1.as_integer_array().add(UINT16_MAX);
    ia1.as_integer_array().add(UINT32_MAX);
    ia1.as_integer_array().add(INT8_MAX);
    ia1.as_integer_array().add(INT16_MAX);
    ia1.as_integer_array().add(INT32_MAX);
    ia1.as_integer_array().add(INT64_MAX);
    assert_int_equal(ia1.as_integer_array().size(), 7);
    
    element ra1 = element::create_real_array();
    ra1.as_real_array().add(FLT_MIN);
    ra1.as_real_array().add(DBL_MAX);
    ra1.as_real_array().add(DBL_MIN);
    ra1.as_real_array().add(FLT_MAX);
    assert_int_equal(ra1.as_real_array().size(), 4);
    
    element e1 = element::create_element_array();
    assert_int_equal(e1.as_element_array().size(), 0);
    e1.as_element_array().add(ba1);
    e1.as_element_array().add(ia1);
    e1.as_element_array().add(ra1);
    assert_int_equal(e1.as_element_array().size(), 3);
    
    std::vector<char> buffer;
    e1.to_buffer(buffer);
    
    size_t read_bytes = 0;
    element e2 = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(e2.type(), pbd_type_element_array);
    
    element_array& ea2 = e2.as_element_array();
    
    assert_int_equal(ea2.size(), 3);
    assert_int_equal(ea2.values()[0].type(), pbd_type_bool_array);
    assert_int_equal(ea2.values()[1].type(), pbd_type_integer_array);
    assert_int_equal(ea2.values()[2].type(), pbd_type_real_array);
    
    boolean_array& ba2 = ea2.values()[0].as_boolean_array();
    
    assert_int_equal(ba2.size(), 11);
    assert_int_equal(ba2.values()[0], false);
    assert_int_equal(ba2.values()[1], true);
    assert_int_equal(ba2.values()[2], true);
    assert_int_equal(ba2.values()[3], false);
    assert_int_equal(ba2.values()[4], false);
    assert_int_equal(ba2.values()[5], false);
    assert_int_equal(ba2.values()[6], true);
    assert_int_equal(ba2.values()[7], true);
    assert_int_equal(ba2.values()[8], true);
    assert_int_equal(ba2.values()[9], true);
    assert_int_equal(ba2.values()[10], true);
    
    integer_array& ia2 = ea2.values()[1].as_integer_array();
    
    assert_int_equal(ia2.size(), 7);
    assert_int_equal(ia2.values()[0], UINT8_MAX);
    assert_int_equal(ia2.values()[1], UINT16_MAX);
    assert_int_equal(ia2.values()[2], UINT32_MAX);
    assert_int_equal(ia2.values()[3], INT8_MAX);
    assert_int_equal(ia2.values()[4], INT16_MAX);
    assert_int_equal(ia2.values()[5], INT32_MAX);
    assert_int_equal(ia2.values()[6], INT64_MAX);
    
    real_array& ra2 = ea2.values()[2].as_real_array();
    
    assert_int_equal(ra2.size(), 4);
    assert_true(ra2.values()[0] == FLT_MIN);
    assert_true(ra2.values()[1] == DBL_MAX);
    assert_true(ra2.values()[2] == DBL_MIN);
    assert_true(ra2.values()[3] == FLT_MAX);
}

void test_pbd_element_array_element_array_childs(void **state) { 
    element e = element::create_element_array();
    element e1 = element::create_element_array();
    element e1_1 = element::create_element_array();
    element e2 = element::create_element_array();
    
    e.as_element_array().add(e1);
    e1.as_element_array().add(e1_1);
    e.as_element_array().add(e2);

    e.as_element_array().add(element::create_null());
    e1.as_element_array().add(element::create_null());
    e1_1.as_element_array().add(element::create_null());
    e2.as_element_array().add(element::create_null());
    e.as_element_array().add(element::create_boolean(true));
    e.as_element_array().add(element::create_integer(INT8_MAX/2));
    e.as_element_array().add(element::create_real(FLT_MAX/2.0f));
    
    element ba = element::create_boolean_array();
    e1.as_element_array().add(ba);
    ba.as_boolean_array().add(false);
    
    element ia = element::create_integer_array();
    e1_1.as_element_array().add(ia);
    ia.as_integer_array().add(UINT8_MAX);
    
    element ra = element::create_real_array();
    e2.as_element_array().add(ra);
    ra.as_real_array().add(FLT_MIN);
    
    std::vector<char> buffer;
    e.to_buffer(buffer);

    size_t read_bytes = 0;
    element ne = element::from_buffer(buffer, read_bytes);
    assert_int_equal(buffer.size(), read_bytes);
    assert_int_equal(ne.type(), pbd_type_element_array);

    element_array& nae = ne.as_element_array();
    
    assert_int_equal(nae.size(), 6);
    assert_int_equal(nae.values()[0].type(), pbd_type_element_array);
    assert_int_equal(nae.values()[1].type(), pbd_type_element_array);
    assert_int_equal(nae.values()[2].type(), pbd_type_null);
    assert_int_equal(nae.values()[3].type(), pbd_type_bool);
    assert_int_equal(nae.values()[4].type(), pbd_type_integer);
    assert_int_equal(nae.values()[5].type(), pbd_type_real);
    assert_int_equal(nae.values()[3].as_boolean().get(), true);
    assert_int_equal(nae.values()[4].as_integer().get(), INT8_MAX/2);
    assert_true(nae.values()[5].as_real().get() == FLT_MAX/2.0f);

    element_array& ne1 = nae.values()[0].as_element_array();
    assert_int_equal(ne1.size(), 3);
    assert_int_equal(ne1.values()[0].type(), pbd_type_element_array);
    assert_int_equal(ne1.values()[1].type(), pbd_type_null);
    assert_int_equal(ne1.values()[2].type(), pbd_type_bool_array);

//    const element ne1_1 = pbd_element_array_values(ne1)[0];
//    assert_int_equal(pbd_element_array_size(ne1_1), 2);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(ne1_1)[0]), pbd_type_null);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(ne1_1)[1]), pbd_type_integer_array);
//    
//    const element ne2 = pbd_element_array_values(ne)[1];
//    assert_int_equal(pbd_element_array_size(ne2), 2);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(ne2)[0]), pbd_type_null);
//    assert_int_equal(pbd_element_type(pbd_element_array_values(ne2)[1]), pbd_type_real_array);
//    
//    const element nba = pbd_element_array_values(ne1)[2];
//    assert_int_equal(pbd_bool_array_values(nba)[0], false);
//    
//    const element nia = pbd_element_array_values(ne1_1)[1];
//    assert_int_equal(pbd_integer_array_values(nia)[0], UINT8_MAX);
//    
//    const element nra = pbd_element_array_values(ne2)[1];
//    assert_true(pbd_real_array_values(nra)[0] == FLT_MIN);
}

static const struct CMUnitTest group_tests[] = {
    cmocka_unit_test(test_pbd_element_array_single_element_childs),
    cmocka_unit_test(test_pbd_element_array_single_element_array_childs),
    cmocka_unit_test(test_pbd_element_array_element_array_childs),
};

int main() {
    return cmocka_run_group_tests(group_tests, NULL, NULL);
}
