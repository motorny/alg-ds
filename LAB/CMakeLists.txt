cmake_minimum_required(VERSION 3.17)
project(Alg_DS_LAB C)

set(CMAKE_C_STANDARD 99)

add_executable(Alg_DS_LAB main.c )

enable_testing()

add_subdirectory(tests)
