project(pdb)

set(LIB_NAME pbd)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(SOURCE_FILES
    arrayutils.c
    bool.c
    boolarray.c
    element.c
    elementarray.c
    integer.c
    integerarray.c
    null.c
    pbddoc.c
    real.c
    realarray.c
    string.c
    typeid.c)

add_library(${LIB_NAME} ${SOURCE_FILES})

target_link_libraries(${LIB_NAME} ${ZLIB_LIBRARY})
