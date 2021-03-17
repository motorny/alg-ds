cmake_minimum_required(VERSION 3.17)
project(Alg_DS C)

set(CMAKE_C_STANDARD 99)

enable_testing()
add_subdirectory(googletest)

# change `LAB` to the actual lab name
option(build_B "Enable building B" ON)
if (build_B)
    add_subdirectory(B)
endif()
