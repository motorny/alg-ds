#include "pch.h"
#include <string.h>
extern "C"
{
#include "HashTable.h"
}

unsigned HashFunction(HASH_TABLE* tmp, char* data)
{
  unsigned hash = 0;
  for (int i = 0; i < strlen(data); i++)
  {
    hash += data[i] * i;
    hash %= tmp->Size;
  }
  return (hash) % tmp->Size;
}

HASH_TABLE *CreateTable(void)
{
  HASH_TABLE *t;
  t = HashTableCreate(10);
  HashTableAdd(t, "Hello");
  HashTableAdd(t, "World");
  HashTableAdd(t, "Poly");
  return t;
}

TEST(HashTableAddElement_TableNull_NotCrush) {
  HashTableAdd(NULL, "Hee-Hoo");
}

TEST(HashTableAddElement_AddSame_NotCrush) {
  HASH_TABLE* t = CreateTable();
  HashTableAdd(t, "Poly");
  HashTableClear(t);
}
TEST(HashTableAddElement_Correct_NotCrush) {
  HASH_TABLE* t = CreateTable();
  HashTableAdd(t, "Hee-Hoo");
  HashTableClear(t);
}

TEST(HashTableDeleteElement_TableNull_NotCrush) {
  HashTableDelete(NULL, "Hello");
}
TEST(HashTableDeleteElement_DelNotExist_NotCrush) {
  HASH_TABLE* t = CreateTable();
  HashTableDelete(t, "Hi");
  HashTableClear(t);
}
TEST(HashTableDeleteElement_Correct_NotCrush) {
  HASH_TABLE* t = CreateTable();
  HashTableDelete(t, "Hello");
  HashTableClear(t);
}
TEST(HashTableFindElement_Exist_NotCrush) {
  HASH_TABLE* t = CreateTable();
  ASSERT_EQ(HashTableFind(t, "Hello"), TRUE);
  HashTableClear(t);
}
TEST(HashTableFindElement_NotExist_NotCrush) {
  HASH_TABLE* t = CreateTable();
  ASSERT_EQ(HashTableFind(t, "Hi"), FALSE);
  HashTableClear(t);
}

TEST(HashTableAdd_StressTest_NotCrush) {
  HASH_TABLE* t;
  char buf[3] = {0};
  t = HashTableCreate(100000);
  for (int i = 0; i < 3000000; i++)
  {
    buf[0] = rand();
    switch (rand() % 3)
    {
    case 0:
      HashTableFind(t, buf);
      break;
    case 1:
      HashTableAdd(t, buf);
      break;
    case 2:
      HashTableDelete(t, buf);
      break;
    default:
      break;
    }
  }
  HashTableClear(t);
}
