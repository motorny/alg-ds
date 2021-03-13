project(tests_B)

include_directories(../../googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../)

add_executable(tests_B_run main.cpp ../memallocator.c testMemInit.cpp testMemAlloc.cpp utils.h utils.cpp testMemFree.cpp)
target_link_libraries(tests_B_run gtest gtest_main)
