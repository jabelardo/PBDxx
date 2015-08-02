cmake_minimum_required(VERSION 3.2)

project(PortableBinaryDataC++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

#option(PBD_STATICLIB "Set to ON to build with static linking." ON)

add_subdirectory(src)

add_subdirectory(tests)