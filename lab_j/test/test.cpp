#include "pch.h"
#include "hash_table.c"

TEST(hashInit_validsize, returnptr) {
  hash_table_t* h = hashInit(5);
  EXPECT_TRUE(h != (hash_table_t*)NULL);
  clear(h);
}

TEST(hashAdd_goodkey, returnSuccess) {
  hash_table_t* h = hashInit(1);
  EXPECT_EQ(hashAdd(h, "1"), MSUCCESS);
  clear(h);
}

TEST(hashAdd_collision, returnSuccess) {
  hash_table_t* h = hashInit(2);

  EXPECT_EQ(hashAdd(h, "1"), MSUCCESS);
  EXPECT_EQ(hashAdd(h, "3"), MSUCCESS);
  clear(h);
}

TEST(hashAdd_elemExist, returnALREADYEXISTS) {
  hash_table_t* h = hashInit(2);

  EXPECT_EQ(hashAdd(h, "1"), MSUCCESS);
  EXPECT_EQ(hashAdd(h, "1"), ALREADYEXISTS);
  clear(h);
}

TEST(hashFind_elemExist, returnCorrectptr) {
  hash_table_t* h = hashInit(1);
  h->table[0].str = (char*)malloc(sizeof(char) * 2);
  h->table[0].status = FULL;
  strcpy(h->table[0].str, "1");

  EXPECT_EQ(hashFind(h, "1"), &h->table[0]);
  clear(h);
}

TEST(hashFind_elemNotFound, returnNULL) {
  hash_table_t* h = hashInit(1);
  h->table[0].str = (char*)malloc(sizeof(char) * 2);
  h->table[0].status = FULL;
  strcpy(h->table[0].str, "1");

  EXPECT_EQ(hashFind(h, "2"), (hash_elem_t*)NULL);
  clear(h);
}

TEST(hashDelete_elemExist, returnSuccess) {
  hash_table_t* h = hashInit(1);
  h->table[0].str = (char*)malloc(sizeof(char) * 2);
  h->table[0].status = FULL;
  strcpy(h->table[0].str, "1");

  EXPECT_EQ(hashDelete(h, "1"), MSUCCESS);
  clear(h);
}

TEST(hashDelete_elemNotFound, returnFail) {
  hash_table_t* h = hashInit(1);
  h->table[0].str = (char*)malloc(sizeof(char) * 2);
  h->table[0].status = FULL;
  strcpy(h->table[0].str, "1");

  EXPECT_EQ(hashDelete(h, "2"), MFAIL);
  clear(h);
}