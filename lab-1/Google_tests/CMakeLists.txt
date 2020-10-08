# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -DHOME -Wno-unused-result -Wshadow -D_GLIBCXX_DEBUG -fsanitize=address")
# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests

add_executable(Google_Tests_run test1.cpp ../list.c ../list.hpp)

target_link_libraries(Google_Tests_run gtest gtest_main)