project(pbdxxtest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

find_package(cmocka REQUIRED)

add_executable(boolean_array_tests_xx boolean_array_tests_xx.cpp)
target_link_libraries(boolean_array_tests_xx pbdxx ${CMOCKA_LIBRARY})

add_executable(element_array_tests_xx element_array_tests_xx.cpp)
target_link_libraries(element_array_tests_xx pbdxx ${CMOCKA_LIBRARY})

add_executable(number_array_tests_xx number_array_tests_xx.cpp)
target_link_libraries(number_array_tests_xx pbdxx ${CMOCKA_LIBRARY})

#add_executable(pbddoc_tests_xx pbddoc_tests_xx.cpp)
#target_link_libraries(pbddoc_tests_xx pbdxx ${CMOCKA_LIBRARY})

add_executable(single_element_tests_xx single_element_tests_xx.cpp)
target_link_libraries(single_element_tests_xx pbdxx ${CMOCKA_LIBRARY})
