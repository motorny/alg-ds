project(tests_I)

include_directories(../../googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../)

add_executable(tests_I_run main.cpp ../23Tree.h ../23Tree.c testInsertTerminate.cpp)
target_link_libraries(tests_I_run gtest gtest_main)
