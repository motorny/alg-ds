#include <gtest/gtest.h>
#define GTEST
#include "LAb-J.c"

TEST(hashFunction, simpleString) {
    EXPECT_EQ(hashFunction((char*)"a"), 33);
    EXPECT_EQ(hashFunction((char*)"*"), 42);
    EXPECT_EQ(hashFunction((char*)"abc"), 38);
}

TEST(hashFunction, NULLstring) {
    EXPECT_EQ(hashFunction(NULL), 0);
}

TEST(addStr, simpleString) {

    EXPECT_EQ(hashFunction((char*)"a"), 33);
    addStr((char*)"a");
    EXPECT_TRUE(hash[33]);
    EXPECT_STREQ(hash[33]->str, "a");

    EXPECT_EQ(hashFunction((char*)"*"), 42);
    addStr((char*)"*");
    EXPECT_TRUE(hash[42]);
    EXPECT_STREQ(hash[42]->str, "*");

    EXPECT_EQ(hashFunction((char*)"abc"), 38);
    addStr((char*)"abc");
    EXPECT_TRUE(hash[38]);
    EXPECT_STREQ(hash[38]->str, "abc");
}

TEST(rmStr, simpleString) {
    EXPECT_EQ(hashFunction((char*)"a"), 33);
    addStr((char*)"a");
    EXPECT_TRUE(hash[33]);
    EXPECT_STREQ(hash[33]->str, "a");
    rmStr((char*)"a");
    EXPECT_TRUE(hash[33] == NULL);

    EXPECT_EQ(hashFunction((char*)"*"), 42);
    addStr((char*)"*");
    EXPECT_TRUE(hash[42]);
    EXPECT_STREQ(hash[42]->str, "*");
    rmStr((char*)"*");
    EXPECT_TRUE(hash[42] == NULL);

    EXPECT_EQ(hashFunction((char*)"abc"), 38);
    addStr((char*)"abc");
    EXPECT_TRUE(hash[38]);
    EXPECT_STREQ(hash[38]->str, "abc");
    rmStr((char*)"abc");
    EXPECT_TRUE(hash[38] == NULL);
}

TEST(findStr, simpleString) {
    EXPECT_EQ(hashFunction((char*)"a"), 33);
    addStr((char*)"a");
    EXPECT_TRUE(hash[33]);
    EXPECT_STREQ(hash[33]->str, "a");

    EXPECT_TRUE(findStr((char*)"a"));
    EXPECT_FALSE(findStr((char*)"b"));
}

TEST(findStr, NULLstring) {
    EXPECT_FALSE(findStr((char*)NULL));
}