cmake_minimum_required(VERSION 3.16)
project(lab_1)

set(CMAKE_CXX_STANDARD 11)


include_directories(src)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)