#include "pch.h"
extern "C" {
#include "../HashTableLin/HashTableLin.h"
#include <stdio.h>

#pragma warning(disable:4996)
}

HashTable_t* CreateHTable()
{
  HashTable_t* hTable = HashTableGet(100, 1);
  char buff[30];
  int* tmp;
  tmp = (int*)malloc(sizeof(int));
  *tmp = 1;
  sprintf(buff, "%i", 1);
  HashTableAdd(hTable, buff, tmp);
  tmp = (int*)malloc(sizeof(int));
  *tmp = 3;
  sprintf(buff, "%i", 3);
  HashTableAdd(hTable, buff, tmp);
  tmp = (int*)malloc(sizeof(int));
  *tmp = 4;
  sprintf(buff, "%i", 4);
  HashTableAdd(hTable, buff, tmp);
  tmp = (int*)malloc(sizeof(int));
  *tmp = 6;
  sprintf(buff, "%i", 6);
  HashTableAdd(hTable, buff, tmp);
  return hTable;
}

TEST(HashTableAdd, AddToEmpty)
{
  HashTable_t* hTable = HashTableGet(100, 1);
  char buff[30];
  int* tmp;
  tmp = (int*)malloc(sizeof(int));
  *tmp = 2;
  sprintf(buff, "%i", 2);
  EXPECT_EQ(HashTableAdd(hTable, buff, tmp), 1);
  HashTableFree(hTable);
}

TEST(HashTableAdd, AddToNotEmpty)
{
  HashTable_t* hTable = CreateHTable();
  char buff[30];
  int* tmp;
  tmp = (int*)malloc(sizeof(int));
  *tmp = 2;
  sprintf(buff, "%i", 2);
  EXPECT_EQ(HashTableAdd(hTable, buff, tmp), 1);
  HashTableFree(hTable);
}

TEST(HashTableAdd, AddExisting)
{
  HashTable_t* hTable = CreateHTable();
  char buff[30];
  int* tmp;
  tmp = (int*)malloc(sizeof(int));
  *tmp = 1;
  sprintf(buff, "%i", 1);
  EXPECT_EQ(HashTableAdd(hTable, buff, tmp), -1);
  HashTableFree(hTable);
}

TEST(HashTableFind, ItemInTable)
{
  HashTable_t* hTable = CreateHTable();
  char buff[30];
  int* tmp;
  sprintf(buff, "%i", 1);
  EXPECT_EQ(HashTableFind(hTable, buff, (void**)&tmp), 1);
  ASSERT_NE(tmp, (void*)0);
  EXPECT_EQ(*tmp, 1);
  HashTableFree(hTable);
}

TEST(HashTableFind, ItemNotInTable)
{
  HashTable_t* hTable = CreateHTable();
  char buff[30];
  int* tmp;
  sprintf(buff, "%i", 2);
  EXPECT_EQ(HashTableFind(hTable, buff, (void**)&tmp), -1);
  HashTableFree(hTable);
}

TEST(HashTableRemove, ItemInTable)
{
  HashTable_t* hTable = CreateHTable();
  char buff[30];
  int* tmp;
  sprintf(buff, "%i", 1);
  EXPECT_EQ(HashTableRemove(hTable, buff, (void**)&tmp), 1);
  ASSERT_NE(tmp, (void*)0);
  EXPECT_EQ(*tmp, 1);
  free(tmp);
  HashTableFree(hTable);
}

TEST(HashTableRemove, ItemNotInTable)
{
  HashTable_t* hTable = CreateHTable();
  char buff[30];
  int* tmp;
  sprintf(buff, "%i", 2);
  EXPECT_EQ(HashTableRemove(hTable, buff, (void**)&tmp), -1);
  HashTableFree(hTable);
}