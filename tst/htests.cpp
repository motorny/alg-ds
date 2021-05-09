//
// Created by ikuzin on 09.05.2021.
//

#include "HashTable.h"

#include <gtest/gtest.h>

TEST(hashFunction, simpleString) {
    EXPECT_EQ(hashcode((char *) "a"), 33);
    EXPECT_EQ(hashcode((char *) "*"), 42);
    EXPECT_EQ(hashcode((char *) "abc"), 38);
}

TEST(hashFunction, NULLstring) {
    EXPECT_EQ(hashcode(NULL), 0);
}

TEST(addStr, simpleString) {

    EXPECT_EQ(hashcode((char *) "a"), 33);
    hashTableAdd((char *) "a");
    EXPECT_TRUE(hash[33]);
    EXPECT_STREQ(hash[33]->str, "a");

    EXPECT_EQ(hashcode((char *) "*"), 42);
    hashTableAdd((char *) "*");
    EXPECT_TRUE(hash[42]);
    EXPECT_STREQ(hash[42]->str, "*");

    EXPECT_EQ(hashcode((char *) "abc"), 38);
    hashTableAdd((char *) "abc");
    EXPECT_TRUE(hash[38]);
    EXPECT_STREQ(hash[38]->str, "abc");
}

TEST(rmStr, simpleString) {
    EXPECT_EQ(hashcode((char *) "a"), 33);
    hashTableAdd((char *) "a");
    EXPECT_TRUE(hash[33]);
    EXPECT_STREQ(hash[33]->str, "a");
    hashTableDelete((char *) "a");
    EXPECT_TRUE(hash[33] == NULL);

    EXPECT_EQ(hashcode((char *) "*"), 42);
    hashTableAdd((char *) "*");
    EXPECT_TRUE(hash[42]);
    EXPECT_STREQ(hash[42]->str, "*");
    hashTableDelete((char *) "*");
    EXPECT_TRUE(hash[42] == NULL);

    EXPECT_EQ(hashcode((char *) "abc"), 38);
    hashTableAdd((char *) "abc");
    EXPECT_TRUE(hash[38]);
    EXPECT_STREQ(hash[38]->str, "abc");
    hashTablDelete((char *) "abc");
    EXPECT_TRUE(hash[38] == NULL);
}

TEST(findStr, simpleString) {
    EXPECT_EQ(hashcode((char *) "a"), 33);
    hashTableAdd((char *) "a");
    EXPECT_TRUE(hash[33]);
    EXPECT_STREQ(hash[33]->str, "a");

    EXPECT_TRUE(hashTableFind((char *) "a"));
    EXPECT_FALSE(hashTableFind((char *) "b"));
}

TEST(findStr, NULLstring) {
    EXPECT_FALSE(hashTableFind((char *) NULL));
}