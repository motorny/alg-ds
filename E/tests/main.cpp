#include <gtest/gtest.h>

// I somehow managed to use only .h
// in B lab, unfortunately, can't reproduce
// even with the same CMakeLists :(
#include "../BinTree.c"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
