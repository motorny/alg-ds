project(tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests_run main.cpp testInsertion.cpp testDeletion.cpp testFind.cpp)

target_link_libraries(tests_run gtest gtest_main)
