project(PBD++)

set(LIB_NAME PBD++)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(SOURCE_FILES
    details/dynamic_bitset.cpp
    details/streams_operators.cpp
    details/type_id.cpp
    elements/boolean.cpp
    elements/boolean_array.cpp
    elements/element_array.cpp
    elements/element_implementation.cpp
    elements/element_map.cpp
    elements/integer.cpp
    elements/integer_array.cpp
    elements/null.cpp
    elements/real.cpp
    elements/real_array.cpp
    elements/string.cpp
    elements/string_array.cpp
    exceptions/bad_cast.cpp
    exceptions/checksum_error.cpp
    exceptions/duplicate_key.cpp
    exceptions/invalid_type_id.cpp
    exceptions/parsing_error.cpp
    exceptions/size_out_of_range.cpp
    element.cpp
    pbdoc.cpp
    pbdoc_head.cpp
    streams.cpp)

add_library(${LIB_NAME} ${SOURCE_FILES})

target_link_libraries(${LIB_NAME} ${ZLIB_LIBRARY})
