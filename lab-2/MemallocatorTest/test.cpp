#include "pch.h"
#include "..//memallocator/memallocator.c"
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

#define MINSIZE 2 * (sizeof(header_t) + sizeof(int))
#define ADDSIZE (sizeof(header_t) + sizeof(int))
#define NUM_FOR_COMPARE1 1000
#define NUM_FOR_COMPARE2 10000

void init(void* buf, int size) {
  memSys.buffer = (header_t*)buf;
  memSys.totalSize = size;
  memSys.buffer->next = (header_t*)((char*)buf + ADDSIZE);
  memSys.buffer->prev = (header_t*)((char*)buf + ADDSIZE);
  memSys.buffer->size = 0;
  *(int*)(memSys.buffer + 1) = 0;

  memSys.buffer->next->next = memSys.buffer;
  memSys.buffer->next->prev = memSys.buffer;
  memSys.buffer->next->size = size - MINSIZE;
  *(int*)((char*)buf + size - sizeof(int)) = memSys.buffer->next->size;
  memSys.cur = memSys.buffer->next;
}

TEST(memalloc_notInitializedBuffer_returnNull) {

  EXPECT_EQ(NULL, memalloc(1));
}

TEST(meminit_nullPointerAndSizeIsEqualMinsize_returnFalse) {
  void* buf = NULL;

  EXPECT_EQ(FALSE, meminit(buf, MINSIZE));
}

TEST(meminit_notNullPointerAndSizeLessMinsize_returnFalse) {
  void* buf[MINSIZE - 1];

  EXPECT_EQ(FALSE, meminit(buf, MINSIZE - 1));
}

TEST(meminit_notNullPointerAndSizeIsEqualMinsize_returnTrue) {
  void* buf[MINSIZE];

  EXPECT_EQ(TRUE, meminit(buf, MINSIZE));
}

TEST(meminit_notNullPointerAndSizeMoreMinsize_returnTrue) {
  void* buf[MINSIZE + 1];

  EXPECT_EQ(TRUE, meminit(buf, MINSIZE + 1));
}

TEST(memalloc_withoutNewHeader_returnPointer) {
  void* buf[MINSIZE + 1];
  char* res;
  init(buf, MINSIZE + 1);

  res = (char*)memalloc(1);
  EXPECT_EQ((char*)buf + MINSIZE - sizeof(int), res);
  // Check blocks
  EXPECT_EQ((header_t*)buf, ((header_t*)buf)->next);
  EXPECT_EQ((header_t*)buf, ((header_t*)buf)->prev);
  EXPECT_EQ(0, *(int*)((header_t*)buf + 1));

  EXPECT_EQ((header_t*)NULL, ((header_t*)((char*)buf + ADDSIZE))->next);
  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->prev);
  EXPECT_EQ(1, *(int*)((char*)buf + ADDSIZE + sizeof(header_t) + 1));
}

TEST(memalloc_withNewHeader_returnPointer) {
  void* buf[MINSIZE + 2 + ADDSIZE];
  char* res;
  init(buf, MINSIZE + 2 + ADDSIZE);

  res = (char*)memalloc(1);
  EXPECT_EQ((char*)buf + MINSIZE - sizeof(int), res);
  // Check blocks
  EXPECT_EQ((header_t*)((char*)buf + MINSIZE + 1), ((header_t*)buf)->next);
  EXPECT_EQ((header_t*)((char*)buf + MINSIZE + 1), ((header_t*)buf)->prev);
  EXPECT_EQ(0, *(int*)((header_t*)buf + 1));

  EXPECT_EQ((header_t*)NULL, ((header_t*)((char*)buf + ADDSIZE))->next);
  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->prev);
  EXPECT_EQ(1, *(int*)((char*)buf + ADDSIZE + sizeof(header_t) + 1));

  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + MINSIZE + 1))->next);
  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + MINSIZE + 1))->prev);
  EXPECT_EQ(1, *(int*)((char*)buf + MINSIZE + sizeof(header_t) + 2));
}

TEST(memalloc_notEnoughMemory_returnNull) {
  void* buf[MINSIZE + 1];
  char* res;
  init(buf, MINSIZE + 1);

  res = (char*)memalloc(2);
  EXPECT_EQ((char*)NULL, res);
  // Check blocks
  EXPECT_EQ((header_t*)((char*)buf + ADDSIZE), ((header_t*)buf)->next);
  EXPECT_EQ((header_t*)((char*)buf + ADDSIZE), ((header_t*)buf)->prev);
  EXPECT_EQ(0, *(int*)((header_t*)buf + 1));

  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->next);
  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->prev);
  EXPECT_EQ(1, *(int*)((char*)buf + ADDSIZE + sizeof(header_t) + 1));
}

TEST(memfree_withoutMerge_returnNone) {
  void* buf[MINSIZE + 1];
  init(buf, MINSIZE + 1);

  // "Allocate" block
  ((header_t*)((char*)buf + ADDSIZE))->next = (header_t*)NULL;
  ((header_t*)buf)->next = (header_t*)buf;
  ((header_t*)buf)->prev = (header_t*)buf;

  memfree((void*)((char*)buf + ADDSIZE + sizeof(header_t)));
  // Check blocks
  EXPECT_EQ((header_t*)((char*)buf + ADDSIZE), ((header_t*)buf)->next);
  EXPECT_EQ((header_t*)((char*)buf + ADDSIZE), ((header_t*)buf)->prev);
  EXPECT_EQ(0, *(int*)((header_t*)buf + 1));

  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->next);
  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->prev);
  EXPECT_EQ(1, *(int*)((char*)buf + ADDSIZE + sizeof(header_t) + 1));
}

TEST(memfree_mergeWithPrev_returnNone) {
  void* buf[MINSIZE + 2 + ADDSIZE];
  init(buf, MINSIZE + 2 + ADDSIZE);

  // "Allocate" block
  ((header_t*)((char*)buf + ADDSIZE))->size = 1;
  *(int*)((char*)buf + ADDSIZE + sizeof(header_t) + 1) = 1;
  ((header_t*)((char*)buf + MINSIZE + 1))->next = (header_t*)NULL;
  ((header_t*)((char*)buf + MINSIZE + 1))->prev = (header_t*)buf;
  ((header_t*)((char*)buf + MINSIZE + 1))->size = 1;
  *(int*)((char*)buf + MINSIZE + sizeof(header_t) + 2) = 1;

  memfree((void*)((char*)buf + MINSIZE + 1 + sizeof(header_t)));
  // Check blocks
  EXPECT_EQ((header_t*)((char*)buf + ADDSIZE), ((header_t*)buf)->next);
  EXPECT_EQ((header_t*)((char*)buf + ADDSIZE), ((header_t*)buf)->prev);
  EXPECT_EQ(0, *(int*)((header_t*)buf + 1));

  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->next);
  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->prev);
  EXPECT_EQ(2 + ADDSIZE, *(int*)((char*)buf + MINSIZE + 2 + ADDSIZE - sizeof(int)));
}

TEST(memfree_mergeWithNext_returnNone) {
  void* buf[MINSIZE + 2 + ADDSIZE];
  init(buf, MINSIZE + 2 + ADDSIZE);

  // "Allocate" block
  ((header_t*)buf)->next = (header_t*)((char*)buf + MINSIZE + 1);
  ((header_t*)buf)->prev = (header_t*)((char*)buf + MINSIZE + 1);
  ((header_t*)((char*)buf + ADDSIZE))->next = (header_t*)NULL;
  ((header_t*)((char*)buf + ADDSIZE))->size = 1;
  *(int*)((char*)buf + ADDSIZE + sizeof(header_t) + 1) = 1;
  ((header_t*)((char*)buf + MINSIZE + 1))->next = (header_t*)buf;
  ((header_t*)((char*)buf + MINSIZE + 1))->prev = (header_t*)buf;
  ((header_t*)((char*)buf + MINSIZE + 1))->size = 1;
  *(int*)((char*)buf + MINSIZE + sizeof(header_t) + 2) = 1;

  memfree((void*)((char*)buf + ADDSIZE + sizeof(header_t)));
  // Check blocks
  EXPECT_EQ((header_t*)((char*)buf + ADDSIZE), ((header_t*)buf)->next);
  EXPECT_EQ((header_t*)((char*)buf + ADDSIZE), ((header_t*)buf)->prev);
  EXPECT_EQ(0, *(int*)((header_t*)buf + 1));

  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->next);
  EXPECT_EQ((header_t*)buf, ((header_t*)((char*)buf + ADDSIZE))->prev);
  EXPECT_EQ(2 + ADDSIZE, *(int*)((char*)buf + MINSIZE + 2 + ADDSIZE - sizeof(int)));
}

TEST(memfree_NullPointer_NoAccessViolation) {
  void* p = NULL;

  memfree(p);
}

TEST(compareWithMalloc1) {
  void** p = (void**)malloc(NUM_FOR_COMPARE1 * sizeof(void*));
  int size = MINSIZE + (NUM_FOR_COMPARE1 - 1) * ADDSIZE + NUM_FOR_COMPARE1;
  void* buf = malloc(size);
  int counter;
  LARGE_INTEGER freq, count1, count2;

  printf("Test: allocate 1000 blocks then free half of them, allocate them again and free all\n");

  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&count1);
  for (counter = 0; counter < NUM_FOR_COMPARE1; counter++) {
    p[counter] = malloc(1);
  }
  for (counter = NUM_FOR_COMPARE1 / 4; counter < NUM_FOR_COMPARE1 / 4 * 3; counter++) {
    free(p[counter]);
  }
  for (counter = NUM_FOR_COMPARE1 / 4; counter < NUM_FOR_COMPARE1 / 4 * 3; counter++) {
    p[counter] = malloc(1);
  }
  for (counter = 0; counter < NUM_FOR_COMPARE1; counter++) {
    free(p[counter]);
  }
  QueryPerformanceCounter(&count2);
  printf("Default allocator: %lf\n", (count2.QuadPart - count1.QuadPart) / (double)freq.QuadPart);

  meminit(buf, size);
  QueryPerformanceCounter(&count1);
  for (counter = 0; counter < NUM_FOR_COMPARE1; counter++) {
    p[counter] = memalloc(1);
  }
  for (counter = NUM_FOR_COMPARE1 / 4; counter < NUM_FOR_COMPARE1 / 4 * 3; counter++) {
    memfree(p[counter]);
  }
  for (counter = NUM_FOR_COMPARE1 / 4; counter < NUM_FOR_COMPARE1 / 4 * 3; counter++) {
    p[counter] = memalloc(1);
  }
  for (counter = 0; counter < NUM_FOR_COMPARE1; counter++) {
    memfree(p[counter]);
  }
  QueryPerformanceCounter(&count2);
  printf("Custom allocator: %lf\n", (count2.QuadPart - count1.QuadPart) / (double)freq.QuadPart);
  memdone();

  free(p);
  free(buf);
}

TEST(compareWithMalloc2) {
  void** p = (void**)malloc(NUM_FOR_COMPARE2 * sizeof(void*));
  int size = MINSIZE + (NUM_FOR_COMPARE2 - 1) * ADDSIZE + NUM_FOR_COMPARE2;
  void* buf = malloc(size);
  int counter;
  LARGE_INTEGER freq, count1, count2;

  printf("Test: allocate 10000 blocks then free half of them, allocate them again and free all\n");

  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&count1);
  for (counter = 0; counter < NUM_FOR_COMPARE2; counter++) {
    p[counter] = malloc(1);
  }
  for (counter = NUM_FOR_COMPARE1 / 4; counter < NUM_FOR_COMPARE2 / 4 * 3; counter++) {
    free(p[counter]);
  }
  for (counter = NUM_FOR_COMPARE1 / 4; counter < NUM_FOR_COMPARE2 / 4 * 3; counter++) {
    p[counter] = malloc(1);
  }
  for (counter = 0; counter < NUM_FOR_COMPARE2; counter++) {
    free(p[counter]);
  }
  QueryPerformanceCounter(&count2);
  printf("Default allocator: %lf\n", (count2.QuadPart - count1.QuadPart) / (double)freq.QuadPart);

  meminit(buf, size);
  QueryPerformanceCounter(&count1);
  for (counter = 0; counter < NUM_FOR_COMPARE2; counter++) {
    p[counter] = memalloc(1);
  }
  for (counter = NUM_FOR_COMPARE1 / 4; counter < NUM_FOR_COMPARE2 / 4 * 3; counter++) {
    memfree(p[counter]);
  }
  for (counter = NUM_FOR_COMPARE1 / 4; counter < NUM_FOR_COMPARE2 / 4 * 3; counter++) {
    p[counter] = memalloc(1);
  }
  for (counter = 0; counter < NUM_FOR_COMPARE2; counter++) {
    memfree(p[counter]);
  }
  QueryPerformanceCounter(&count2);
  printf("Custom allocator: %lf\n", (count2.QuadPart - count1.QuadPart) / (double)freq.QuadPart);
  memdone();

  free(p);
  free(buf);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}