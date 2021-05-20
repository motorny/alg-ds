#include "pch.h"
#include "../LAB_J/LAB_J.c"

TEST(HashInsert, InsertToEmpty) {
	hash_t* t = HashCreate(1);
	char str[] = "abcd";
	EXPECT_EQ(HashInsert(t, str), SUCCESS);
	HashFree(t);
}

TEST(HashInsert, Collision) {
	hash_t* t = HashCreate(2);
	char str1[] = "abcd";
	char str2[] = "cbda";
	EXPECT_EQ(HashInsert(t, str1), SUCCESS);
	EXPECT_EQ(HashInsert(t, str2), SUCCESS);
	HashFree(t);
}

TEST(HashInsert, IsAlreadyIn) {
	hash_t* t = HashCreate(2);
	char str1[] = "abcd";
	char str2[] = "efgh";
	HashInsert(t, str1);
	EXPECT_EQ(HashInsert(t, str2), FAIL);
	HashFree(t);
}

TEST(HashInsert, FullTable) {
	hash_t* t = HashCreate(1);
	char str1[] = "abcd";
	char str2[] = "efgh";
	HashInsert(t, str1);
	EXPECT_EQ(HashInsert(t, str2), FAIL);
	HashFree(t);
}

TEST(HashSearch, IsInTable) {
	hash_t* t = HashCreate(1);
	char str[] = "abcd";
	HashInsert(t, str);
	EXPECT_EQ(HashSearch(t, str), SUCCESS);
	HashFree(t);
}

TEST(HashSearch, IsNotInTable) {
	hash_t* t = HashCreate(1);
	char str1[] = "abcd";
	char str2[] = "efgh";
	HashInsert(t, str1);
	EXPECT_EQ(HashSearch(t, str2), FAIL);
	HashFree(t);
}

TEST(HashSearch, EmptyTable) {
	hash_t* t = HashCreate(1);
	char str[] = "abcd";
	EXPECT_EQ(HashSearch(t, str), FAIL);
	HashFree(t);
}

TEST(HashDelete, IsInTable) {
	hash_t* t = HashCreate(1);
	char str[] = "abcd";
	HashInsert(t, str);
	EXPECT_EQ(HashDelete(t, str), SUCCESS);
	HashFree(t);
}

TEST(HashDelete, IsNotInTable) {
	hash_t* t = HashCreate(1);
	char str1[] = "abcd";
	char str2[] = "efgh";
	HashInsert(t, str1);
	EXPECT_EQ(HashDelete(t, str2), FAIL);
	HashFree(t);
}

TEST(HashDelete, EmptyTable) {
	hash_t* t = HashCreate(1);
	char str[] = "abcd";
	EXPECT_EQ(HashDelete(t, str), FAIL);
	HashFree(t);
}