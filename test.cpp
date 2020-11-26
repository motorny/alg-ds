#pragma warning(disable:4996)

#include "pch.h"
extern "C"
{
#include "LabB.h"
}

TEST(TestMemInit, TestGood) {

  int testSize = memGetMinSize() + 1;
  char* test = (char*)malloc(testSize);
  EXPECT_EQ(memInit(test, testSize), 1);
  free(test);
}

TEST(TestMemInit, TestNullPtr) {

  char* test = NULL;
  EXPECT_EQ(memInit(test, 1), 0);
}

TEST(TestMemInit, TestMinSize) {

  int testSize = memGetMinSize() - 1;
  char* test = (char*)malloc(testSize);
  EXPECT_EQ(memInit(test, testSize), 1);
  free(test);
}

TEST(TestMeMalloc, TestGood) {

  int testSize = memGetMinSize() + 1;
  char* test = (char*)malloc(testSize);
  memInit(test, testSize);
  char* t = (char*)meMalloc(1);
  EXPECT_NE(t, (char*)NULL);
  memFree(t);
  free(test);
}

TEST(TestMeMalloc, TestNotEnoughMemory) {

  int testSize = memGetMinSize() + 1;
  char* test = (char*)malloc(testSize);
  memInit(test, testSize);
  void* t = meMalloc(2);
  EXPECT_TRUE(!t);
  memFree(t);
  free(test);
}

TEST(TestMeMalloc, TestNegSize) {

  int testSize = memGetMinSize() + 1;
  char* test = (char*)malloc(testSize);
  memInit(test, testSize);
  char* t = (char*)meMalloc(-1);
  EXPECT_EQ(t, (char*)NULL);
  free(test);
}

int main(void) {

  return RUN_ALL_TESTS();
}