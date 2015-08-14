project(pbdtest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

find_package(cmocka REQUIRED)

add_executable(bool_array_tests bool_array_tests.c)
target_link_libraries(bool_array_tests pbd ${CMOCKA_LIBRARY})

add_executable(element_array_tests element_array_tests.c)
target_link_libraries(element_array_tests pbd ${CMOCKA_LIBRARY})

add_executable(number_array_tests number_array_tests.c)
target_link_libraries(number_array_tests pbd ${CMOCKA_LIBRARY})

add_executable(single_element_tests single_element_tests.c)
target_link_libraries(single_element_tests pbd ${CMOCKA_LIBRARY})

add_executable(general_tests general_tests.c)
target_link_libraries(general_tests pbd ${CMOCKA_LIBRARY})
