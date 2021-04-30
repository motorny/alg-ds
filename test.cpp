#include "pch.h"
extern "C" {
#include"htable.h"
}

TEST(htableinitvalidsize, returnptr) {
  EXPECT_TRUE(hInit(5) != NULL);
}

TEST(hAddgoodkey, returnSuccess) {
	htable* table = hInit(1);
	EXPECT_EQ(hAdd(table, "test", 1) ,SUCCESS);
}


TEST(hAddcollision, returnSuccess) {
	htable* table = hInit(2);

	EXPECT_EQ(hAdd(table, "test", 2), SUCCESS);
	EXPECT_EQ(hAdd(table, "tset", 2), SUCCESS);
}

TEST(hAddelemexist, returnFAIL) {
	htable* table = hInit(2);

	EXPECT_EQ(hAdd(table, "test", 2), SUCCESS);
	EXPECT_EQ(hAdd(table, "test", 2), FAIL);
}

TEST(hFindgoodelem, returnSuccess) {
	htable* table = hInit(1);
	hAdd(table, "test", 1);
	EXPECT_EQ(hFind(table , "test", 1), SUCCESS);
}

TEST(hFindElemNotFound, returnFail) {
	htable* table = hInit(1);
	hAdd(table, "test", 1);
	EXPECT_EQ(hFind(table, "tset", 1), FAIL);
}

TEST(hDeleteElemFound, returnSuccess) {
	htable* table = hInit(1);
	hAdd(table, "test", 1);
	EXPECT_EQ(hDelete(table, "test", 1), SUCCESS);
}

TEST(hDeleteElemnotFound, returnFail) {
	htable* table = hInit(1);
	hAdd(table, "test", 1);
	EXPECT_EQ(hDelete(table, "tset", 1), FAIL);
}