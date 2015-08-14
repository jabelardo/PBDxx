#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include <pbd/pbd.h>

void test_pbd_element_create_bogus_input_1(void **state) { 
    char *buffer = "z39fjceqw90vjqsiovdswqe9ewrqcq";
    errno = 0;
    pbd_element* element = pbd_element_create(buffer);
    assert_null(element);
    assert_int_equal(errno, EINVAL);
}

void test_pbd_element_create_bogus_input_2(void **state) { 
    pbd_element* bool_1 = pbd_bool_create(true);
    char *buffer = NULL;
    size_t size;
    pbd_element_to_buffer(bool_1, &buffer, &size);
    
    buffer[0] = 0;
    errno = 0;
    pbd_element* element = pbd_element_create(buffer);
    assert_null(element);
    assert_int_equal(errno, EINVAL);
}

static const struct CMUnitTest general_tests[] = {
    cmocka_unit_test(test_pbd_element_create_bogus_input_1),
    cmocka_unit_test(test_pbd_element_create_bogus_input_2),
};

int main() {
    return cmocka_run_group_tests(general_tests, NULL, NULL);
}