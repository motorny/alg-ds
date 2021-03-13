#include <gtest/gtest.h>

#include "../BinTree.h"

TEST(NTOL, 0) {
    ASSERT_EQ(ntol(0), 1);
}

TEST(NTOL, 1) {
    ASSERT_EQ(ntol(1), 1);
}

TEST(NTOL, 10) {
    ASSERT_EQ(ntol(10), 2);
}

TEST(NTOL, 11) {
    ASSERT_EQ(ntol(11), 2);
}

TEST(NTOL, N11) {
    ASSERT_EQ(ntol(-11), 3);
}

TEST(NTOL, N10) {
    ASSERT_EQ(ntol(-10), 3);
}