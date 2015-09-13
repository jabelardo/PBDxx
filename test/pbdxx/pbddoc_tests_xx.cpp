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

static const struct CMUnitTest group_tests[] = {
//    cmocka_unit_test(test_pbd_boolean_array),
};

int main() {
    return cmocka_run_group_tests(group_tests, NULL, NULL);
}

