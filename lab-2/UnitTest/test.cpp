#include "pch.h"
extern "C" {
#include "..\memallocator.h"
}

TEST(Memalloc, SizeLess0_NULLReturned)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  char* output;

  meminit(pool, size);

  output = (char*)memalloc(-1);

  ASSERT_EQ(output, (char*)NULL);

  memdone();
  free(pool);
}

TEST(Memalloc, Size0_NULLReturned)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  char* output;

  meminit(pool, size);

  output = (char*)memalloc(0);

  ASSERT_EQ(output, (char*)NULL);

  memdone();
  free(pool);
}

TEST(Memalloc, SizeBiggerRealMemSize_NULLReturned)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  char* output;

  meminit(pool, size);

  output = (char*)memalloc(sizeof(int) + 1);

  ASSERT_EQ(output, (char*)NULL);

  memdone();
  free(pool);
}

TEST(Memalloc, MemDontInited_NULLReturned)
{
  char* output;

  output = (char*)memalloc(1);

  ASSERT_EQ(output, (char*)NULL);
}

TEST(Memalloc, MaxPossibleSize_ValidPtrReturned)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  int* output;

  meminit(pool, size);

  output = (int*)memalloc(sizeof(int));

  ASSERT_NE(output, (int*)NULL);

  *output = 42;

  memdone();
  free(pool);
}

TEST(Memalloc, SizeLessMaxPossible_ValidPtrReturned)
{
  int size = memgetminimumsize() + sizeof(int) + 1;
  char* pool = (char*)malloc(size);
  int* output;

  meminit(pool, size);

  output = (int*)memalloc(sizeof(int));

  ASSERT_NE(output, (int*)NULL);

  *output = 42;

  memdone();
  free(pool);
}

TEST(Memfree, NULL_DontCrush)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  int* output;

  meminit(pool, size);

  memfree(NULL);

  memdone();
  free(pool);
}

TEST(Memfree, PtrNotFromMemoryRange_DontCrush)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  int* rez;

  meminit(pool, size);

  memfree(pool - 1);

  memdone();
  free(pool);
}

TEST(Memfree, InvalidPtrFromMemoryRange_DontCrush)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  char* output;

  meminit(pool, size);

  output = (char*)memalloc(sizeof(int));
  memfree(output - 1);

  memdone();
  free(pool);
}

TEST(Memfree, MemDoned_DontCrush)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  int* output;

  meminit(pool, size);
  memdone();

  memfree(pool + 1);

  free(pool);
}

TEST(Memfree, ValidPtr_DontCrush)
{
  int size = memgetminimumsize() + sizeof(int);
  char* pool = (char*)malloc(size);
  int* output;

  meminit(pool, size);

  output = (int*)memalloc(sizeof(int));
  *output = 42;
  memfree(output);
  output = (int*)memalloc(sizeof(int));
  *output = 0451;

  memdone();
  free(pool);
}