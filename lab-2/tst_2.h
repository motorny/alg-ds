#ifndef TST_2_H
#define TST_2_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../MemAllocatorTask/memallocator.cpp"
//#include "../MemAllocatorTask/memallocator.h"

using namespace testing;

TEST(MEMINIT_TEST, TOO_SMALL_MEMSIZE)
{
  char mem[10];

  EXPECT_EQ(meminit(mem, 10), TOO_SMALL_SIZE);
  memdone();
}

TEST(MEMINIT_TEST, NULL_PTR_ON_INPUT)
{
  EXPECT_EQ(meminit(NULL, 100), NULL_POINTER_ON_INPUT);
  memdone();
}

TEST(MEMINIT_TEST, CORRECT_INPUT)
{
  char mem[200];

  EXPECT_EQ(meminit(mem, 200), 0);
  EXPECT_EQ(firstFreeNode->size, 200 - memgetblocksize());
  EXPECT_EQ(firstFreeNode->key, KEY_NUMBER);
  EXPECT_EQ((char*)firstFreeNode, mem);
  memdone();
}

TEST(MEMALLOC_TEST, TOO_SMALL_MEMORY)
{
  char mem[40];

  meminit(mem, 40);
  char* testPtr1 = (char*)memalloc(100);
  char* testPtr2 = (char*)memalloc(40);
  EXPECT_TRUE(testPtr1 == NULL);
  EXPECT_TRUE(testPtr2 == NULL);
  memdone();
}

TEST(MEMALLOC_TEST, NO_FREE_BLOCKS)
{
  char mem[30];

  meminit(mem, 30);
  ((NodeEnder*)((char*)firstFreeNode + firstFreeNode->size + sizeof(NodeHeader)))->size = -1;
  firstFreeNode = NULL;
  char* testPtr = (char*)memalloc(1);
  EXPECT_TRUE(testPtr == NULL);
  memdone();
}

TEST(MEMALLOC_TEST, DIVISION_TEST)
{
  char mem[100];

  meminit(mem, 100);
  char* testPtr = (char*)memalloc(10);
  NodeHeader* testHeader = (NodeHeader*)((char*)testPtr - sizeof(NodeHeader));
  NodeEnder* testEnder = (NodeEnder*)((char*)testHeader + testHeader->size + sizeof(NodeHeader));
  NodeHeader* nextHeader = (NodeHeader*)((char*)testEnder + sizeof(NodeEnder));

  EXPECT_EQ(testHeader->key, KEY_NUMBER);
  EXPECT_EQ(testHeader->size, 10);
  EXPECT_TRUE(testHeader->ptrToNext == NULL);
  EXPECT_EQ(testEnder->size, -1);
  EXPECT_EQ(nextHeader->key, KEY_NUMBER);
  EXPECT_TRUE(nextHeader == firstFreeNode); \
  EXPECT_EQ(nextHeader->size, 100 - 2 * memgetminimumsize() - testHeader->size);
  memdone();
}

TEST(MEMALLOC_TEST, NO_DIVISION_TEST)
{
  char mem[100];

  meminit(mem, 100);
  NodeHeader* testPtr = (NodeHeader*)memalloc(100 - memgetblocksize());
  testPtr = (NodeHeader*)((char*)testPtr - sizeof(NodeHeader));
  EXPECT_TRUE((char*)testPtr == memory);
  EXPECT_TRUE(testPtr->key == KEY_NUMBER);
  EXPECT_TRUE(testPtr->ptrToNext == NULL);
  EXPECT_TRUE(((NodeEnder*)((char*)testPtr + testPtr->size + sizeof(NodeHeader)))->size == -1);
  memdone();
}

TEST(MEMFREE_TEST, CORRECT)
{
  char* mem[500];

  meminit(mem, 500);
  char* testPtr1 = (char*)memalloc(100 - memgetminimumsize());
  char* testPtr2 = (char*)memalloc(100 - memgetminimumsize());
  char* testPtr3 = (char*)memalloc(100 - memgetminimumsize());
  char* testPtr4 = (char*)memalloc(100 - memgetminimumsize());
  char* testPtr5 = (char*)memalloc(100 - memgetminimumsize());

  memfree(testPtr3);
  memfree(testPtr1);
  memfree(testPtr2);
  memfree(testPtr5);
  memfree(testPtr4);

  EXPECT_TRUE((char*)firstFreeNode == memory && (char*)firstFreeNode + firstFreeNode->size + memgetminimumsize() == memory + memSize);
}




/////////////////////////////////////////////////////////

//TEST(TOO_BIG_SIZE_REQUEST, RECUEST_MORE_THAN_INIT)
//{
//  char memory[20];

//  meminit(memory, 20);
//  int* a = (int*)memalloc(400);
//  ASSERT_EQ(a, nullptr);
//}

//TEST(TOO_BIG_SIZE_REQUEST, REQUEST_MORE_THAN_EXIST)
//{
//  char memory[60];

//  meminit(memory, 60);
//  void* a = memalloc(20);
//  void*b = memalloc(60);
//  EXPECT_EQ(b, nullptr);
//  EXPECT_TRUE(a != nullptr);
//}









#endif // TST_2_H
