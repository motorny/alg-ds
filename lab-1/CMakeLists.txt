cmake_minimum_required(VERSION 3.10)
project(laba1 C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -DHOME -Wno-unused-result -Wshadow -D_GLIBCXX_DEBUG -fsanitize=address")
#set(CMAKE_C_FLAGS "-fsanitize=address")

add_executable(laba1  main.c list.h list.c)
add_subdirectory(Google_tests)
