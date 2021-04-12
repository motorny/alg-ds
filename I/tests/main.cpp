#include <gtest/gtest.h>

// if .h -> linker issues
#include "../23Tree.c"
//#include "../23Tree.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
