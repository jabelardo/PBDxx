#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <float.h>
#include <assert.h>

#include <pbd/pbd.h>

void test_pbd_element_array_single_element_childs(void **state) { 
    pbd_element* e1 = pbd_element_array_new();
    assert_non_null(e1);
    assert_int_equal(pbd_element_array_size(e1), 0);
    
    pbd_element_array_add(e1, pbd_null_new());
    pbd_element_array_add(e1, pbd_bool_create(true));
    pbd_element_array_add(e1, pbd_bool_create(false));
    pbd_element_array_add(e1, pbd_null_new());
    pbd_element_array_add(e1, pbd_integer_create(INT8_MAX/2));
    pbd_element_array_add(e1, pbd_integer_create(INT16_MAX/2));
    pbd_element_array_add(e1, pbd_integer_create(INT32_MAX/2));
    pbd_element_array_add(e1, pbd_integer_create(INT64_MAX/2));
    pbd_element_array_add(e1, pbd_null_new());
    pbd_element_array_add(e1, pbd_real_create(FLT_MAX/2.0f));
    pbd_element_array_add(e1, pbd_real_create(DBL_MAX/2.0));
    pbd_element_array_add(e1, pbd_null_new());
    pbd_element_array_add(e1, pbd_string_create("1029384756!@#$%ˆ*()-=_+asdA"));
    pbd_element_array_add(e1, pbd_null_new());
    
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(e1, &buffer, &size);
    assert_non_null(buffer);
    
    size_t read_bytes = 0;
    pbd_element* e2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(e2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(e2), pbd_element_array_type);
    
    assert_int_equal(pbd_element_array_size(e2), 14);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[0]), pbd_null_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[1]), pbd_bool_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[2]), pbd_bool_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[3]), pbd_null_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[4]), pbd_integer_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[5]), pbd_integer_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[6]), pbd_integer_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[7]), pbd_integer_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[8]), pbd_null_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[9]), pbd_real_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[10]), pbd_real_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[11]), pbd_null_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[12]), pbd_string_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[13]), pbd_null_type);
    
    assert_int_equal(pbd_bool_get(pbd_element_array_values(e2)[1]), true);
    assert_int_equal(pbd_bool_get(pbd_element_array_values(e2)[2]), false);
    assert_int_equal(pbd_integer_get(pbd_element_array_values(e2)[4]), INT8_MAX/2);
    assert_int_equal(pbd_integer_get(pbd_element_array_values(e2)[5]), INT16_MAX/2);
    assert_int_equal(pbd_integer_get(pbd_element_array_values(e2)[6]), INT32_MAX/2);
    assert_int_equal(pbd_integer_get(pbd_element_array_values(e2)[7]), INT64_MAX/2);
    assert(pbd_real_get(pbd_element_array_values(e2)[9]) == FLT_MAX/2.0f);
    assert(pbd_real_get(pbd_element_array_values(e2)[10]) == DBL_MAX/2.0);
    assert_string_equal(pbd_string_get(pbd_element_array_values(e2)[12]), "1029384756!@#$%ˆ*()-=_+asdA");
    
    pbd_element_free(e1);
    pbd_element_free(e2);
    free(buffer);
}

void test_pbd_element_array_single_element_array_childs(void **state) { 
    pbd_element* e1 = pbd_element_array_new();
    assert_non_null(e1);
    assert_int_equal(pbd_element_array_size(e1), 0);
    
    pbd_element* ba = pbd_bool_array_new();
    pbd_bool_array_add(ba, false);
    pbd_bool_array_add(ba, true);
    pbd_bool_array_add(ba, true);
    pbd_bool_array_add(ba, false);
    pbd_bool_array_add(ba, false);
    pbd_bool_array_add(ba, false);
    pbd_bool_array_add(ba, true);
    pbd_bool_array_add(ba, true);
    pbd_bool_array_add(ba, true);
    pbd_bool_array_add(ba, true);
    pbd_bool_array_add(ba, true);
    pbd_element_array_add(e1, ba);
    
    pbd_element* ia = pbd_integer_array_new();
    pbd_integer_array_add(ia, UINT8_MAX);
    pbd_integer_array_add(ia, UINT16_MAX);
    pbd_integer_array_add(ia, UINT32_MAX);
    pbd_integer_array_add(ia, INT8_MAX);
    pbd_integer_array_add(ia, INT16_MAX);
    pbd_integer_array_add(ia, INT32_MAX);
    pbd_integer_array_add(ia, INT64_MAX);
    pbd_element_array_add(e1, ia);
    
    pbd_element* ra = pbd_real_array_new();
    pbd_real_array_add(ra, FLT_MIN);
    pbd_real_array_add(ra, DBL_MAX);
    pbd_real_array_add(ra, DBL_MIN);
    pbd_real_array_add(ra, FLT_MAX);
    pbd_element_array_add(e1, ra);
    
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(e1, &buffer, &size);
    assert_non_null(buffer);
    
    size_t read_bytes = 0;
    pbd_element* e2 = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(e2);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(e2), pbd_element_array_type);
    
    assert_int_equal(pbd_element_array_size(e2), 3);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[0]), pbd_bool_array_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[1]), pbd_integer_array_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(e2)[2]), pbd_real_array_type);
    
    assert_int_equal(pbd_bool_array_size(pbd_element_array_values(e2)[0]), 11);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[0], false);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[1], true);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[2], true);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[3], false);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[4], false);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[5], false);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[6], true);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[7], true);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[8], true);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[9], true);
    assert_int_equal(pbd_bool_array_values(pbd_element_array_values(e2)[0])[10], true);
    
    assert_int_equal(pbd_integer_array_size(pbd_element_array_values(e2)[1]), 7);
    assert_int_equal(pbd_integer_array_values(pbd_element_array_values(e2)[1])[0], UINT8_MAX);
    assert_int_equal(pbd_integer_array_values(pbd_element_array_values(e2)[1])[1], UINT16_MAX);
    assert_int_equal(pbd_integer_array_values(pbd_element_array_values(e2)[1])[2], UINT32_MAX);
    assert_int_equal(pbd_integer_array_values(pbd_element_array_values(e2)[1])[3], INT8_MAX);
    assert_int_equal(pbd_integer_array_values(pbd_element_array_values(e2)[1])[4], INT16_MAX);
    assert_int_equal(pbd_integer_array_values(pbd_element_array_values(e2)[1])[5], INT32_MAX);
    assert_int_equal(pbd_integer_array_values(pbd_element_array_values(e2)[1])[6], INT64_MAX);
    
    assert_int_equal(pbd_real_array_size(pbd_element_array_values(e2)[2]), 4);
    assert_true(pbd_real_array_values(pbd_element_array_values(e2)[2])[0] == FLT_MIN);
    assert_true(pbd_real_array_values(pbd_element_array_values(e2)[2])[1] == DBL_MAX);
    assert_true(pbd_real_array_values(pbd_element_array_values(e2)[2])[2] == DBL_MIN);
    assert_true(pbd_real_array_values(pbd_element_array_values(e2)[2])[3] == FLT_MAX);

    pbd_element_free(e1);
    pbd_element_free(e2);
    free(buffer);
}

void test_pbd_element_array_element_array_childs(void **state) { 
    pbd_element* e = pbd_element_array_new();
    pbd_element* e1 = pbd_element_array_new();
    pbd_element* e1_1 = pbd_element_array_new();
    pbd_element* e2 = pbd_element_array_new();
    
    pbd_element_array_add(e, e1);
    pbd_element_array_add(e1, e1_1);
    pbd_element_array_add(e, e2);
    
    pbd_element_array_add(e, pbd_null_new());
    pbd_element_array_add(e1, pbd_null_new());
    pbd_element_array_add(e1_1, pbd_null_new());
    pbd_element_array_add(e2, pbd_null_new());
    pbd_element_array_add(e, pbd_bool_create(true));
    pbd_element_array_add(e, pbd_integer_create(INT8_MAX/2));
    pbd_element_array_add(e, pbd_real_create(FLT_MAX/2.0f));
    
    pbd_element* ba = pbd_bool_array_new();
    pbd_element_array_add(e1, ba);
    pbd_bool_array_add(ba, false);
    
    pbd_element* ia = pbd_integer_array_new();
    pbd_element_array_add(e1_1, ia);
    pbd_integer_array_add(ia, UINT8_MAX);
    
    pbd_element* ra = pbd_real_array_new();
    pbd_element_array_add(e2, ra);
    pbd_real_array_add(ra, FLT_MIN);
    
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(e, &buffer, &size);
    assert_non_null(buffer);
    
    size_t read_bytes = 0;
    pbd_element* ne = pbd_element_from_buffer(buffer, &read_bytes);
    assert_non_null(ne);
    assert_int_equal(size, read_bytes);
    assert_int_equal(pbd_element_type(ne), pbd_element_array_type);
    
    assert_int_equal(pbd_element_array_size(ne), 6);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne)[0]), pbd_element_array_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne)[1]), pbd_element_array_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne)[2]), pbd_null_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne)[3]), pbd_bool_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne)[4]), pbd_integer_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne)[5]), pbd_real_type);
    assert_int_equal(pbd_bool_get(pbd_element_array_values(ne)[3]), true);
    assert_int_equal(pbd_integer_get(pbd_element_array_values(ne)[4]), INT8_MAX/2);
    assert_true(pbd_real_get(pbd_element_array_values(ne)[5]) == FLT_MAX/2.0f);
    
    const pbd_element* ne1 = pbd_element_array_values(ne)[0];
    assert_int_equal(pbd_element_array_size(ne1), 3);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne1)[0]), pbd_element_array_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne1)[1]), pbd_null_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne1)[2]), pbd_bool_array_type);
    
    const pbd_element* ne1_1 = pbd_element_array_values(ne1)[0];
    assert_int_equal(pbd_element_array_size(ne1_1), 2);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne1_1)[0]), pbd_null_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne1_1)[1]), pbd_integer_array_type);
    
    const pbd_element* ne2 = pbd_element_array_values(ne)[1];
    assert_int_equal(pbd_element_array_size(ne2), 2);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne2)[0]), pbd_null_type);
    assert_int_equal(pbd_element_type(pbd_element_array_values(ne2)[1]), pbd_real_array_type);
    
    const pbd_element* nba = pbd_element_array_values(ne1)[2];
    assert_int_equal(pbd_bool_array_values(nba)[0], false);
    
    const pbd_element* nia = pbd_element_array_values(ne1_1)[1];
    assert_int_equal(pbd_integer_array_values(nia)[0], UINT8_MAX);
    
    const pbd_element* nra = pbd_element_array_values(ne2)[1];
    assert_true(pbd_real_array_values(nra)[0] == FLT_MIN);
    
    pbd_element_free(e);
    pbd_element_free(ne);
    free(buffer);
}

static const struct CMUnitTest pbd_element_array_tests[] = {
    cmocka_unit_test(test_pbd_element_array_single_element_childs),
    cmocka_unit_test(test_pbd_element_array_single_element_array_childs),
    cmocka_unit_test(test_pbd_element_array_element_array_childs),
};

int main() {
    return cmocka_run_group_tests(pbd_element_array_tests, NULL, NULL);
}
