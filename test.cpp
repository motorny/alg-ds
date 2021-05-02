#pragma warning (disable: 4996)
#include "pch.h"

extern "C" {
#include"hash.h"
}

#define SIZE 10

hashTable_t* createTable() {

  hashTable_t* hashTable = (hashTable_t*)malloc(sizeof(hashTable_t) * SIZE);
  if (hashTable == NULL)
    return NULL;

  for (int i = 0; i < SIZE; i++)
    hashTable[i].status = DELETED;

  hashTable[0].str = (char*)malloc(sizeof(char) + 1);
  strcpy(hashTable[0].str, "d");
  hashTable[0].status = NOTFREE;
  hashTable[1].str = (char*)malloc(sizeof(char) + 1);
  strcpy(hashTable[1].str, "e");
  hashTable[1].status = NOTFREE;
  hashTable[7].str = (char*)malloc(sizeof(char) + 1);
  strcpy(hashTable[7].str, "a");
  hashTable[7].status = NOTFREE;
  hashTable[8].str = (char*)malloc(sizeof(char) + 1);
  strcpy(hashTable[8].str, "b");
  hashTable[8].status = NOTFREE;
  hashTable[9].str = (char*)malloc(sizeof(char) + 1);
  strcpy(hashTable[9].str, "c");
  hashTable[9].status = NOTFREE;

  return hashTable;

}

TEST(hashInsert, successInsertOne) {

  hashTable_t* hashTable = createTable();
  hashInsert(hashTable, "f", SIZE);
  ASSERT_TRUE(strcmp(hashTable[2].str, "f") == 0);
  ASSERT_EQ(hashTable[2].status, NOTFREE);//

  hashDestroy(hashTable, SIZE);

}

TEST(hashInsert, successInsertTwoWithCollision) {

  hashTable_t* hashTable = createTable();
  hashInsert(hashTable, "f", SIZE);//ASCII 102 => hash = 2 
  hashInsert(hashTable, "p", SIZE);//ASCII 112 => hash = 2
  ASSERT_TRUE(strcmp(hashTable[2].str, "f") == 0);
  ASSERT_TRUE(strcmp(hashTable[3].str, "p") == 0);
  ASSERT_EQ(hashTable[2].status, NOTFREE);
  ASSERT_EQ(hashTable[3].status, NOTFREE);

  hashDestroy(hashTable, SIZE);

}

TEST(hashFind, successFind) {

  hashTable_t* hashTable = createTable();
  ASSERT_TRUE(hashFind(hashTable, "a", SIZE) == FOUND);

  hashDestroy(hashTable, SIZE);

}

TEST(hashDelete, sucessDelete) {

  hashTable_t* hashTable = createTable();
  hashDelete(hashTable, "b", SIZE);
  ASSERT_EQ(hashTable[8].status, FREE);

  hashDestroy(hashTable, SIZE);

}