#pragma warning(disable:4996)

#include "pch.h"
extern "C"
{
#include "memallocator.h"
}

TEST(meminit, TestGood) {

  char* testMem = NULL;
  int testSize = memgetminimumsize() + 1, test;
  testMem = (char*)malloc(testSize);
  test = meminit(testMem, testSize);
  EXPECT_EQ(test, 0);
  free(testMem);
}

TEST(meminit, TestNullPtr) {

  int test;
  char* testMem = NULL;
  test = meminit(testMem, 1);
  EXPECT_EQ(test, 1);
}

TEST(meminit, TestMinSize) {

  int testSize = memgetminimumsize() + 1, test;
  char* testMem = (char*)malloc(testSize);
  test = meminit(testMem, testSize);
  EXPECT_EQ(test, 0);
  free(testMem);
}

TEST(TestMeMalloc, TestGood) {

  int testSize = memgetminimumsize() + 1;
  char* test = (char*)malloc(testSize);
  meminit(test, testSize);
  char* t = (char*)memalloc(1);
  EXPECT_NE(t, (char*)NULL);
  memfree(t);
  free(test);
}

TEST(TestMeMalloc, TestNotEnoughMemory) {

  int testSize = memgetminimumsize() + 1;
  char* test = (char*)malloc(testSize);
  meminit(test, testSize);
  void* t = memalloc(2);
  EXPECT_TRUE(!t);
  memfree(t);
  free(test);
}

TEST(TestMeMalloc, TestNegSize) {

  int testSize = memgetminimumsize() + 1;
  char* test = (char*)malloc(testSize);
  meminit(test, testSize);
  char* t = (char*)memalloc(-1);
  EXPECT_EQ(t, (char*)NULL);
  free(test);
}

int main(void) {

  return RUN_ALL_TESTS();
}