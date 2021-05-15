#include "pch.h"
//#include "hashtable.h"

void createTestHashTable(hash_table* table, unsigned size) {
  createHashtable(table, size);
  insertInHashtable(table, "Hello");
}

TEST(insertInHashtable, tableEmpty_returnTrue) {
  hash_table table;
  createHashtable(&table, 10);
  ASSERT_EQ(insertInHashtable(&table, "World"), 1);
  clearHashtable(&table);
}

TEST(insertInHashtable, tableFill_returnTrue) {
  hash_table table;
  createTestHashTable(&table, 10);
  ASSERT_EQ(insertInHashtable(&table, "World"), 1);
  clearHashtable(&table);
}
TEST(insertInHashtable, tableIsAlreadyExist_returnFalse) {
  hash_table table;
  createTestHashTable(&table, 10);
  ASSERT_EQ(insertInHashtable(&table, "Hello"), 0);
  clearHashtable(&table);
}

TEST(findInHashtable, tableEmpty_returnFalse) {
  hash_table table;
  createHashtable(&table, 10);
  ASSERT_EQ(findInHashtable(&table, "Hello"), 0);
  clearHashtable(&table);
}

TEST(findInHashtable, tableExist_returnTrue) {
  hash_table table;
  createTestHashTable(&table, 10);
  ASSERT_EQ(findInHashtable(&table, "Hello"), 1);
  clearHashtable(&table);
}

TEST(findInHashtable, tableNotExist_returnFalse) {
  hash_table table;
  createTestHashTable(&table, 10);
  ASSERT_EQ(findInHashtable(&table, "World"), 0);
  clearHashtable(&table);
}

TEST(deleteInHashtable, tableEmpty_returnFalse) {
  hash_table table;
  createHashtable(&table, 10);
  ASSERT_EQ(deleteInHashtable(&table, "Hello"), 0);
  clearHashtable(&table);
}

TEST(deleteInHashtable, tableExist_returnTrue) {
  hash_table table;
  createTestHashTable(&table, 10);
  ASSERT_EQ(deleteInHashtable(&table, "Hello"), 1);
  clearHashtable(&table);
}
TEST(deleteInHashtable, tableNotExist_returnFalse) {
  hash_table table;
  createTestHashTable(&table, 10);
  ASSERT_EQ(deleteInHashtable(&table, "World"), 0);
  clearHashtable(&table);
}