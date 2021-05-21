#include <gtest/gtest.h>

// if .h -> linker issues
#include "../hash_table.c"
//#include <hash_table.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
