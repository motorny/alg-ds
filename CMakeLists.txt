cmake_minimum_required(VERSION 3.17)
project(Alg_DS C)

set(CMAKE_C_STANDARD 99)

enable_testing()
add_subdirectory(googletest)

# change `I` to the actual lab name
option(build_I "Enable building I" ON)
if (build_I)
    add_subdirectory(I)
endif()
