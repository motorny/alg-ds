cmake_minimum_required(VERSION 3.17)
project(Alg_DS C)

set(CMAKE_C_STANDARD 99)

add_executable(Alg_DS main.c AVL.c AVL.h)

enable_testing()

add_subdirectory(tests)