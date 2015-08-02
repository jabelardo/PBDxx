cmake_minimum_required(VERSION 3.2)

project(PortableBinaryDataC++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

find_package(Boost)

find_package(zlib)

include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)

add_subdirectory(test)