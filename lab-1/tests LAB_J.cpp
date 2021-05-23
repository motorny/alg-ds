#include "pch.h"

extern "C" {
#include "../LAB_J/hashTable.c"
}

TEST(FindFunction, Exist) {
	hash_t* t = CreateTable(1);
	char str[] = "dimon";
	Add(t, str);
	EXPECT_EQ(Find(t, str), 1);
	Destroy(t);
}

TEST(FindFunction, NotExist) {
	hash_t* t = CreateTable(1);
	char str1[] = "dimon";
	char str2[] = "1234";
	Add(t, str1);
	EXPECT_EQ(Find(t, str2), -1);
	Destroy(t);
}

TEST(FindFunction, EmptyTable) {
	hash_t* t = CreateTable(1);
	char str[] = "dimon";
	EXPECT_EQ(Find(t, str), -1);
	Destroy(t);
}

TEST(AddFunction, AddToEmpty) {
	hash_t* t = CreateTable(1);
	char str[] = "dimon";
	EXPECT_EQ(Add(t, str), 1);
	Destroy(t);
}

TEST(AddFunction, NormalCase) {
	hash_t* t = CreateTable(2);
	char str1[] = "dimon";
	char str2[] = "1234";
	EXPECT_EQ(Add(t, str1), 1);
	EXPECT_EQ(Add(t, str2), 1);
	Destroy(t);
}

TEST(AddFunction, Exist) {
	hash_t* t = CreateTable(2);
	char str1[] = "dimon";
	char str2[] = "1234";
	Add(t, str1);
	EXPECT_EQ(Add(t, str2), 0);
	Destroy(t);
}

TEST(DelFunction, Exist) {
	hash_t* t = CreateTable(1);
	char str[] = "dimon";
	Add(t, str);
	EXPECT_EQ(Del(t, str), 1);
	Destroy(t);
}

TEST(DelFunction, NotExist) {
	hash_t* t = CreateTable(1);
	char str1[] = "dimon";
	char str2[] = "1234";
	Add(t, str1);
	EXPECT_EQ(Del(t, str2), 0);
	Destroy(t);
}

TEST(DelFunction, EmptyTable) {
	hash_t* t = CreateTable(1);
	char str[] = "dimon";
	EXPECT_EQ(Del(t, str), 0);
	Destroy(t);
} 