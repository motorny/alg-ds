#include "pch.h"
#include "gtest/gtest.h"
#include"../Memallocator/memallocator.h"

#define SUCCESS 1
#define FAIL 0


TEST(meminit, NullPointer_ReturnsFAIL) {
  int size = 100;
  EXPECT_EQ(meminit(NULL, size), FAIL);
  memdone();
}

TEST(meminit, TooSmallSize_ReturnsZero) {
  int size = 5;
  void* pMemory = malloc(size);
  EXPECT_EQ(meminit(pMemory, size), FAIL);
  free(pMemory);
  memdone();
}

TEST(meminit, RepeatedInit_ReturnsZero) {
  int size1 = 100, size2 = 50;
  void* pMemory1 = malloc(size1);
  void* pMemory2 = malloc(size2);
  meminit(pMemory1, size1);
  EXPECT_EQ(meminit(pMemory2, size2), FAIL);
  memdone();
  free(pMemory1);
  free(pMemory2);
}

TEST(meminit, AllRight_ReturnsSUCCESS) {
  int size = 100;
  void* pMemory = malloc(size);
  EXPECT_EQ(meminit(pMemory, size), SUCCESS);
  memdone();
  free(pMemory);
}

TEST(memalloc, Alloc2times_ReturnsValid) {
  void *p1 = 0, *p2 = 0;
  int  memsize = memgetminimumsize() + memgetblocksize() + 2;
  void *ptr = malloc(memsize);
  meminit(ptr, memsize);
  p1 = memalloc(1);
  ASSERT_TRUE(p1 != NULL);
  p2 = memalloc(1);
  ASSERT_TRUE(p2 != NULL);
  memfree(p2);
  memfree(p1);
  memdone();
  free(ptr);
}

TEST(memalloc, NotEnaughMemory_ReturnsNull) {
  void *p1 = 0, *p2 = 0;
  void *ptr = malloc(memgetminimumsize() + 1);
  meminit(ptr, memgetminimumsize() + 1);
  p1 = memalloc(1);
  p2 = memalloc(1);
  ASSERT_TRUE(p2 == NULL);
  memfree(p1);
  memdone();
  free(ptr);
}

TEST(memalloc, SizeEq0_ReturnsNull) {
  void* p = 0;
  void* ptr = malloc(memgetminimumsize() + 1);
  meminit(ptr, memgetminimumsize() + 1);
  p = memalloc(0);
  ASSERT_TRUE(p == NULL);
  memdone();
  free(ptr);
}

TEST(memfree, alloc_free_alloc__p2_NOT_EQ_Null) {
  void* p1 = 0, * p2 = 0;
  void* ptr = malloc(memgetminimumsize() + 1);
  meminit(ptr, memgetminimumsize() + 1);
  p1 = memalloc(1);
  memfree(p1);
  p2 = memalloc(1);
  ASSERT_TRUE(p2 != NULL);
  memfree(p2);
  memdone();
  free(ptr);
}


TEST(memfree, NullPointer_ASSERT) {
  ASSERT_DEATH(memfree(NULL), "");
}

TEST(memdone, MemoryLeak_ASSERT) {
  int size = 100;
  void* pMemory = malloc(size);
  void* p;
  meminit(pMemory, size);
  p = memalloc(20);
  ASSERT_DEATH(memdone(), "");
  memfree(p);
  memdone();
  free(pMemory);
}

TEST(memdone, NoMemoryLeaks_NO_ASSERT) {
  int size = 200;
  void* pMemory = malloc(size);
  void *p1, *p2, *p3;
  meminit(pMemory, size);
  p1 = memalloc(20);
  memfree(p1);
  p2 = memalloc(10);
  p3 = memalloc(80);
  memfree(p2);
  memfree(p3);
  memdone();
  free(pMemory);
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}