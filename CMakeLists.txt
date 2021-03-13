cmake_minimum_required(VERSION 3.17)
project(Alg_DS C)

set(CMAKE_C_STANDARD 99)

enable_testing()
add_subdirectory(googletest)

option(build_E "Enable building E" ON)
if (build_E)
    add_subdirectory(E)
endif()
