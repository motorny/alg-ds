#include <gtest/gtest.h>

// needed to fix linker issues
#include "../AvlList.c"

int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}