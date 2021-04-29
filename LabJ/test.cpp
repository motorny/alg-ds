#include "pch.h"

#define SUCCESS 1
#define FAIL 0

typedef char* T;

typedef struct {
  T* data;
  int size;
} hash_table_t;

hash_table_t* HashCreate(int size);
int HashInsert(hash_table_t* t, const T key);
int HashSearch(const hash_table_t* t, const T key);
int HashDelete(hash_table_t* t, const T key);
void HashFree(hash_table_t* t);

TEST(HashInsert_InsertToEmpty_returnsSUCCESS) {
  hash_table_t* t = HashCreate(1);
  char str[] = "test";

  EXPECT_EQ(HashInsert(t, str), SUCCESS);

  HashFree(t);
}

TEST(HashInsert_Collision_returnsSUCCESS) {
  hash_table_t* t = HashCreate(2);
  char str1[] = "test";
  char str2[] = "tste";

  EXPECT_EQ(HashInsert(t, str1), SUCCESS);
  EXPECT_EQ(HashInsert(t, str2), SUCCESS);

  HashFree(t);
}

TEST(HashInsert_AlreadyIn_returnsFAIL) {
  hash_table_t* t = HashCreate(2);
  char str1[] = "test";
  char str2[] = "test";
  HashInsert(t, str1);

  EXPECT_EQ(HashInsert(t, str2), FAIL);

  HashFree(t);
}

TEST(HashInsert_FullTable_returnsFAIL) {
  hash_table_t* t = HashCreate(1);
  char str1[] = "test1";
  char str2[] = "test2";

  HashInsert(t, str1);
  EXPECT_EQ(HashInsert(t, str2), FAIL);

  HashFree(t);
}

TEST(HashSearch_InTable_returnsSUCCESS) {
  hash_table_t* t = HashCreate(1);
  char str[] = "test";

  HashInsert(t, str);
  EXPECT_EQ(HashSearch(t, str), SUCCESS);

  HashFree(t);
}

TEST(HashSearch_NotInTable_returnsFAIL) {
  hash_table_t* t = HashCreate(1);
  char str1[] = "test1";
  char str2[] = "test2";

  HashInsert(t, str1);
  EXPECT_EQ(HashSearch(t, str2), FAIL);

  HashFree(t);
}

TEST(HashSearch_EmptyTable_returnsFAIL) {
  hash_table_t* t = HashCreate(1);
  char str[] = "test";

  EXPECT_EQ(HashSearch(t, str), FAIL);

  HashFree(t);
}

TEST(HashDelete_InTable_returnsSUCCESS) {
  hash_table_t* t = HashCreate(1);
  char str[] = "test";

  HashInsert(t, str);
  EXPECT_EQ(HashDelete(t, str), SUCCESS);

  HashFree(t);
}

TEST(HashDelete_NotInTable_returnsFAIL) {
  hash_table_t* t = HashCreate(1);
  char str1[] = "test1";
  char str2[] = "test2";

  HashInsert(t, str1);
  EXPECT_EQ(HashDelete(t, str2), FAIL);

  HashFree(t);
}

TEST(HashSearch_EmptyTable_returnsFAIL) {
  hash_table_t* t = HashCreate(1);
  char str[] = "test";

  EXPECT_EQ(HashDelete(t, str), FAIL);

  HashFree(t);
}
