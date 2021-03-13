project(tests_E)

include_directories(../../googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../)

add_executable(tests_E_run main.cpp ../BinTree.c testNTOL.cpp testInsertion.cpp testFixLen.cpp testFindNode.cpp testDeletion.cpp)
target_link_libraries(tests_E_run gtest gtest_main)
