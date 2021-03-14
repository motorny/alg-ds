project(tests_LAB)

include_directories(../../googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../)

add_executable(tests_LAB_run main.cpp ../example.c)
target_link_libraries(tests_LAB_run gtest gtest_main)
