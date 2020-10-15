#include "pch.h"
#include "memallocator.h"
#include "memallocator.c"

#define MINSIZE (sizeof(descriptor_t) + sizeof(int))
#define ADDSIZE (sizeof(descriptor_t) + sizeof(int))
#define NUM_FOR_COMPARE1 1000
#define NUM_FOR_COMPARE2 10000

void init(void* pMemory, int size) {
   s_memSystem.descriptor = (descriptor_t*)pMemory;
   s_memSystem.descriptor->next = NULL;
   s_memSystem.descriptor->prev = NULL;
   s_memSystem.descriptor->size = size;
   s_memSystem.totalSize = size;
   s_memSystem.begin = pMemory;
   *(int*)((char*)((char*)s_memSystem.descriptor + size - sizeof(int))) = size;
}
TEST(meminit, nullPointer_returnZero) {
  void* buf = NULL;
  EXPECT_EQ(0, meminit(buf, 1000));
}
TEST(meminit, notEnoughtSize_returnZero) {
  void* buf[MINSIZE - 1];
  EXPECT_EQ(0, meminit(buf, MINSIZE - 1));
}
TEST(meminit, notNullPointerAndSizeIsEqualMinsize_returnOne) {
  void* buf[MINSIZE];
  EXPECT_EQ(1, meminit(buf, MINSIZE));
}
TEST(meminit, notNullPointerAndSizeMoreMinsize_returnOne) {
  void* buf[MINSIZE + 1];
  EXPECT_EQ(1, meminit(buf, MINSIZE + 1));
}
TEST(memalloc, tooLargeBlockRequest_returnNULL) {
  void* buf[MINSIZE + sizeof(int) - 1];
  init(buf, MINSIZE + sizeof(int) - 1);
  EXPECT_EQ(NULL, memalloc(sizeof(int) * 5));
}
TEST(memalloc, oneOkBlock_returnPointer) {
  void* buf[MINSIZE + ADDSIZE + sizeof(int) * 2];
  int* p;
  init(buf, MINSIZE + ADDSIZE + sizeof(int) * 2);
  p = (int*)memalloc(sizeof(int));
  EXPECT_NE((int*)NULL, p);
  *p = 125;
  EXPECT_EQ(*p, *(int*)((char*)s_memSystem.descriptor - sizeof(int) * 2));
  EXPECT_EQ(-(int)(MINSIZE + sizeof(int)), *(int*)((char*)s_memSystem.descriptor - sizeof(int)));
  EXPECT_EQ(MINSIZE + sizeof(int), s_memSystem.descriptor->size);
  EXPECT_EQ(MINSIZE + ADDSIZE + sizeof(int) * 2, s_memSystem.totalSize);
}

TEST(memalloc, TwoOkBlockAfterFragmentation_returnPointers) {
  void* buf[MINSIZE + ADDSIZE * 5 + sizeof(int) * 6];
  int *p1, *p2;
  init(buf, MINSIZE + ADDSIZE * 5 + sizeof(int) * 6);
  descriptor_t *descriptor1, *descriptor2, *descriptor3, *descriptor4, *descriptor5;

  descriptor1 = s_memSystem.descriptor;
  descriptor1->size = -(int)(MINSIZE + sizeof(int));
  *(int*)((char*)descriptor1 + (-descriptor1->size) - sizeof(int)) = descriptor1->size;
  descriptor1->next = NULL;
  descriptor1->prev = NULL;

  descriptor2 = (descriptor_t*)((char*)s_memSystem.descriptor + (-descriptor1->size));
  descriptor2->size = MINSIZE + sizeof(int) - 3;
  *(int*)((char*)descriptor2 + descriptor2->size - sizeof(int)) = descriptor2->size;

  descriptor3 = (descriptor_t*)((char*)s_memSystem.descriptor + (-descriptor1->size) + descriptor2->size);
  descriptor3->size = -(int)(MINSIZE + sizeof(int));
  *(int*)((char*)descriptor1 + (-descriptor3->size) - sizeof(int)) = descriptor3->size;
  descriptor3->next = NULL;
  descriptor3->prev = NULL;

  descriptor4 = (descriptor_t*)((char*)s_memSystem.descriptor + (-descriptor1->size) + descriptor2->size + (-descriptor3->size));
  descriptor4->size = MINSIZE * 2 + sizeof(int) * 2 + 3;
  *(int*)((char*)descriptor4 + descriptor4->size - sizeof(int)) = descriptor4->size;

  descriptor5 = (descriptor_t*)((char*)s_memSystem.descriptor + (-descriptor1->size) + descriptor2->size + (-descriptor3->size) + descriptor4->size);
  descriptor5->size = -(int)(MINSIZE + sizeof(int));
  *(int*)((char*)descriptor5 + (-descriptor5->size) - sizeof(int)) = descriptor5->size;
  descriptor5->next = NULL;
  descriptor5->prev = NULL;

  s_memSystem.descriptor = descriptor2;
  descriptor2->prev = NULL;
  descriptor2->next = descriptor4;
  descriptor4->prev = descriptor2;
  descriptor4->next = NULL;

  //[-20, 17, -20, 43, -20]
  p1 = (int*)memalloc(sizeof(int));
  EXPECT_EQ(p1, (int*)((char*)descriptor4 + MINSIZE - sizeof(int)));
  EXPECT_EQ(-(int)(MINSIZE + sizeof(int)), descriptor4->size);
  //[-20, 17, -20, -20, 23, -20]
  p2 = (int*)memalloc(sizeof(int));
  EXPECT_EQ(p2, (int*)((char*)descriptor4 + MINSIZE * 2));
  EXPECT_EQ(-(int)(MINSIZE + sizeof(int) + 3), *(int*)((char*)descriptor4 - descriptor4->size));
}

TEST(memfree, freeAll_emptyMemSystem) {
  void* buf[MINSIZE + ADDSIZE * 5 + sizeof(int) * 6];
  int *p1, *p2, *p3;
  init(buf, MINSIZE + ADDSIZE * 5 + sizeof(int) * 6);
  descriptor_t *descriptor1, *descriptor2, *descriptor3, *descriptor4, *descriptor5;

  descriptor1 = s_memSystem.descriptor;
  descriptor1->size = -(int)(MINSIZE + sizeof(int));
  *(int*)((char*)descriptor1 + (-descriptor1->size) - sizeof(int)) = descriptor1->size;
  descriptor1->next = NULL;
  descriptor1->prev = NULL;
  p1 = (int*)((char*)descriptor1 + sizeof(descriptor_t));

  descriptor2 = (descriptor_t*)((char*)s_memSystem.descriptor + (-descriptor1->size));
  descriptor2->size = MINSIZE + sizeof(int) - 3;
  *(int*)((char*)descriptor2 + descriptor2->size - sizeof(int)) = descriptor2->size;

  descriptor3 = (descriptor_t*)((char*)s_memSystem.descriptor + (-descriptor1->size) + descriptor2->size);
  descriptor3->size = -(int)(MINSIZE + sizeof(int));
  *(int*)((char*)descriptor1 + (-descriptor3->size) - sizeof(int)) = descriptor3->size;
  descriptor3->next = NULL;
  descriptor3->prev = NULL;
  p2 = (int*)((char*)descriptor3 + sizeof(descriptor_t));

  descriptor4 = (descriptor_t*)((char*)s_memSystem.descriptor + (-descriptor1->size) + descriptor2->size + (-descriptor3->size));
  descriptor4->size = MINSIZE * 2 + sizeof(int) * 2 + 3;
  *(int*)((char*)descriptor4 + descriptor4->size - sizeof(int)) = descriptor4->size;

  descriptor5 = (descriptor_t*)((char*)s_memSystem.descriptor + (-descriptor1->size) + descriptor2->size + (-descriptor3->size) + descriptor4->size);
  descriptor5->size = -(int)(MINSIZE + sizeof(int));
  *(int*)((char*)descriptor5 + (-descriptor5->size) - sizeof(int)) = descriptor5->size;
  descriptor5->next = NULL;
  descriptor5->prev = NULL;
  p3 = (int*)((char*)descriptor5 + sizeof(descriptor_t));

  s_memSystem.descriptor = descriptor2;
  descriptor2->prev = NULL;
  descriptor2->next = descriptor4;
  descriptor4->prev = descriptor2;
  descriptor4->next = NULL;

  memfree((void*)p1);
  memfree((void*)p3);
  memfree((void*)p2);
  EXPECT_EQ(MINSIZE + ADDSIZE * 5 + sizeof(int) * 6, s_memSystem.descriptor->size);
  EXPECT_EQ(MINSIZE + ADDSIZE * 5 + sizeof(int) * 6, *(int*)((char*)s_memSystem.descriptor + s_memSystem.descriptor->size - sizeof(int)));
}

TEST(all, testingAllFunctionWork) {
  void* buf[MINSIZE + ADDSIZE * 5 + sizeof(int) * 6];
  int* p1, * p2, * p3, * p4, * p5, * p6, *p7;
  meminit(buf, MINSIZE + ADDSIZE * 5 + sizeof(int) * 6);
  p1 = (int*)memalloc(sizeof(int));
  p2 = (int*)memalloc(sizeof(int));
  p3 = (int*)memalloc(sizeof(int));
  memfree((void*)p3);
  memfree((void*)p1);
  memfree((void*)p2);
  p1 = (int*)memalloc(sizeof(int));
  p2 = (int*)memalloc(sizeof(int));
  p3 = (int*)memalloc(sizeof(int));
  p4 = (int*)memalloc(sizeof(int));
  p5 = (int*)memalloc(sizeof(int));
  p6 = (int*)memalloc(sizeof(int));
  p7 = (int*)memalloc(sizeof(int));
  memfree((void*)p2);
  memfree((void*)p3);
  memfree((void*)p1);
  memfree((void*)p5);
  memfree((void*)p6);
  memfree((void*)p4);
  memfree((void*)p7);
  memdone();
  EXPECT_EQ(MINSIZE + ADDSIZE * 5 + sizeof(int) * 6, s_memSystem.descriptor->size);
  EXPECT_EQ(MINSIZE + ADDSIZE * 5 + sizeof(int) * 6, *(int*)((char*)s_memSystem.descriptor + s_memSystem.descriptor->size - sizeof(int)));
}