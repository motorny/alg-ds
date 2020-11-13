#include "pch.h"
extern "C" {
#include "..\memallocator.h"
}

TEST(meminit_NULLpointer, return0) {
	EXPECT_EQ(0, meminit(NULL, 1));
}

TEST(meminit_NegativeSize, return0) {
	void* ptr = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(0, meminit(ptr, -1));
	free(ptr);
}

TEST(meminit_CorrectData, return1) {
	void* ptr = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(1, meminit(ptr, memgetminimumsize() + 1));
	free(ptr);
}

TEST(memalloc_NegativeSize, returnNULL) {
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	EXPECT_EQ(NULL, memalloc(-1));
	free(ptr);
}

TEST(memalloc_CorrectData, returnValidPointer) {
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	void* p1 = memalloc(1);
	EXPECT_TRUE(p1 != NULL);
	memfree(p1);
	free(ptr);
}

TEST(memalloc_NotEnoughMem, returnNULL) {
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	void* p1 = memalloc(2);
	EXPECT_TRUE(p1 == NULL);
	memfree(p1);
	free(ptr);
}

TEST(TestMemalloc, SizeLess0_NULLReturned)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz), * rez;

  meminit(a, sz);

  rez = (char*)memalloc(-1);

  ASSERT_EQ(rez, (char*)NULL);

  memdone();
  free(a);
}

TEST(TestMemalloc, Size0_NULLReturned)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz), * rez;

  meminit(a, sz);

  rez = (char*)memalloc(0);

  ASSERT_EQ(rez, (char*)NULL);

  memdone();
  free(a);
}

TEST(TestMemalloc, SizeBiggerRealMemSize_NULLReturned)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz), * rez;

  meminit(a, sz);

  rez = (char*)memalloc(sizeof(int) + 1);

  ASSERT_EQ(rez, (char*)NULL);

  memdone();
  free(a);
}

TEST(TestMemalloc, MemDontInited_NULLReturned)
{
  char* rez;

  rez = (char*)memalloc(1);

  ASSERT_EQ(rez, (char*)NULL);
}

TEST(TestMemalloc, MaxPossibleSize_ValidPtrReturned)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz);
  int* rez;

  meminit(a, sz);

  rez = (int*)memalloc(sizeof(int));

  ASSERT_NE(rez, (int*)NULL);

  *rez = 30;  //if we write in invalid ptr it must crush, if we run from IDE

  memdone();
  free(a);
}

TEST(TestMemalloc, SizeLessMaxPossible_ValidPtrReturned)
{
  int sz = memgetminimumsize() + sizeof(int) + 1;
  char* a = (char*)malloc(sz);
  int* rez;

  meminit(a, sz);

  rez = (int*)memalloc(sizeof(int));

  ASSERT_NE(rez, (int*)NULL);

  *rez = 30;

  memdone();
  free(a);
}

TEST(TestMemfree, NULL_DontCrush)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz);
  int* rez;

  meminit(a, sz);

  memfree(NULL);

  memdone();
  free(a);
}

TEST(TestMemfree, PtrNotFromMemoryRange_DontCrush)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz);
  int* rez;

  meminit(a, sz);

  memfree(a - 1);

  memdone();
  free(a);
}

TEST(TestMemfree, InvalidPtrFromMemoryRange_DontCrush)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz);
  char* rez;

  meminit(a, sz);

  rez = (char*)memalloc(sizeof(int));
  memfree(rez - 1);

  memdone();
  free(a);
}

TEST(TestMemfree, MemDoned_DontCrush)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz);
  int* rez;

  meminit(a, sz);
  memdone();

  memfree(a + 1);

  free(a);
}

TEST(TestMemfree, ValidPtr_DontCrush)
{
  int sz = memgetminimumsize() + sizeof(int);
  char* a = (char*)malloc(sz);
  int* rez;

  meminit(a, sz);

  rez = (int*)memalloc(sizeof(int));
  *rez = 30;
  memfree(rez);
  rez = (int*)memalloc(sizeof(int));
  *rez = 3030;

  memdone();
  free(a);
}