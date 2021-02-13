cmake_minimum_required(VERSION 3.10)
project(laba1 C)

set(CMAKE_C_STANDARD 11)

add_executable(laba1  main.c list.h list.c)
add_subdirectory(Google_tests)
