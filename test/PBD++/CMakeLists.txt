project(PBD++_test)

set(EXE_NAME PBD++_test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(SOURCE_FILES
    container_element_tests.cpp
    dynamic_bitset_tests.cpp
    main.cpp
    number_array_tests.cpp
    pbdoc_tests.cpp
    primitive_streams_tests.cpp
    single_element_tests.cpp)

add_executable(${EXE_NAME} ${SOURCE_FILES})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

target_link_libraries(${EXE_NAME} 
	PBD++ 
	${ZLIB_LIBRARY} 
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_definitions(-DBOOST_TEST_DYN_LINK)