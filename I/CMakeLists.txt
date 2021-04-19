cmake_minimum_required(VERSION 3.17)
project(Alg_DS_I C)

set(CMAKE_C_STANDARD 99)

add_executable(Alg_DS_I main.c 23Tree.c 23Tree.h)

enable_testing()

add_subdirectory(tests)
