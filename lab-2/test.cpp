#include "pch.h"
#include "gtest/gtest.h"
#include"../B15_bolshakova/main.c"



static double s_data[1000];

TEST(meminit, NegSizeReturnNULL) {
  ASSERT_EQ(0, meminit(s_data, -1));
  memdone();
}

TEST(meminit, Nullptr_ReturnNULL) {
  ASSERT_EQ(0, meminit(NULL, 2));
  memdone();
}

TEST(meminit, CorrectVales_Return1) {
  ASSERT_EQ(1, meminit(s_data, 20));
  memdone();
}

TEST(memalloc, AllocMoreThenOnce_ReturnsNotNULL) {
  void* p1 = 0, * p2 = 0;
  int  memsize = memgetminimumsize() + memgetblocksize() + 2;
  meminit(s_data, memsize);
  p1 = memalloc(1);
  ASSERT_TRUE(p1 != NULL);
  p2 = memalloc(1);
  ASSERT_TRUE(p2 != NULL);
  memfree(p2);
  memfree(p1);
  memdone();
}

TEST(memalloc, NotEnoughMemory_ReturnsNULL) {
  void* p1 = 0, * p2 = 0;
  meminit(s_data, memgetminimumsize() + 1);
  p1 = memalloc(1);
  p2 = memalloc(1);
  ASSERT_TRUE(p2 == NULL);
  memfree(p1);
  memdone();
}

TEST(memalloc, SizeNULL_ReturnsNULL) {
  void* p = 0;
  meminit(s_data, memgetminimumsize() + 1);
  p = memalloc(0);
  ASSERT_TRUE(p == NULL);
  memdone();
}

TEST(memalloc, SizeLessNULL_ReturnesNULL){
  int size = memgetminimumsize() + sizeof(int);
  void* p;
  meminit(s_data, size);
  p = (char*)memalloc(-1);
  ASSERT_EQ(p, (char*)NULL);
  memdone();
}

TEST(memalloc, LargeSize_ReturnesNULL){
  int size = memgetminimumsize() + sizeof(int);
  void* p;
  meminit(s_data, size);
  int block = sizeof(descriptor_t);
  p = (char*)memalloc(sizeof(int) + 1);
  ASSERT_EQ(p, (char*)NULL);
  memdone();
}

TEST(memalloc, NotInitMem_ReturnesNULL){
  void* p;
  p = memalloc(1);

  ASSERT_EQ(p, (char*)NULL);
}

TEST(memalloc, MaxPossibleSize_ReturnesValidPtr){
  int size = memgetminimumsize() + sizeof(int);
  void* p;
  meminit(s_data, size);
  p = memalloc(sizeof(int));
  ASSERT_NE(p, (int*)NULL);
  memfree(p);
  memdone();
}

TEST(memalloc, CorrectSize_ReturnesValid){
  int size = memgetminimumsize() + sizeof(int) + 1;
  void* p;
  meminit(s_data, size);
  p = memalloc(sizeof(int));
  ASSERT_NE(p, (int*)NULL);
  memfree(p);
  memdone();
}

TEST(memfree, Nullptr_DontCrush){
  int size = memgetminimumsize() + sizeof(int);
  meminit(s_data, size);
  memfree(NULL);
}

TEST(memfree, NotOurPtr_DontCrush){
  int size = memgetminimumsize() + sizeof(int);
  meminit(s_data, size);
  memfree((char*)s_data - 1);
  memdone();
}

TEST(memfree, InvalidPtrFromMemoryRange_DontCrush){
  int size = memgetminimumsize() + sizeof(int);
  void* p;
  meminit(s_data, size);
  p = memalloc(sizeof(int));
  memfree((char*)p - 1);
  memdone();
}

TEST(memfree, ValidPtr_DontCrush){
  int size = memgetminimumsize() + sizeof(int);
  void* p;
  meminit(s_data, size);
  p = memalloc(sizeof(int));
  memfree(p);
  memdone();
}



