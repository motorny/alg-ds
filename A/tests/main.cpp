#include <gtest/gtest.h>

// if .h -> linker issues
#include "../List.c"
#include "../Array.c"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
