project(pdb)

set(C_LIB_NAME pbd)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(C_SOURCE_FILES
    arrayutils.c
    bool.c
    boolarray.c
    element.c
    elementarray.c
    endianess.c
    integer.c
    integerarray.c
    null.c
    pbdconf.c
    pbddoc.c
    real.c
    realarray.c
    string.c
    typeid.c)

add_library(${C_LIB_NAME} ${C_SOURCE_FILES})

target_link_libraries(${C_LIB_NAME} ${ZLIB_LIBRARY})

set(CXX_LIB_NAME pbdxx)

set(CXX_SOURCE_FILES 
    pbdxx.cpp)

add_library(${CXX_LIB_NAME} ${CXX_SOURCE_FILES})

target_link_libraries(${CXX_LIB_NAME} ${C_LIB_NAME} ${ZLIB_LIBRARY})
