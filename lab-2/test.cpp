#include "pch.h"
#include <cstdlib>
#include "memallocator.h"
/*
TEST(TestMemalloc, StressTest_DontCrush) //unofficial test
{
  char* a = (char*)malloc(1000);
  int* b[100];
  double* c[100];

  meminit(a, 1000);

  for (int i = 0; i < 75; i++)
  {
    if (b[i] = (int*)memalloc(sizeof(int)))
      *b[i] = 30;
    if (c[i] = (double*)memalloc(sizeof(double)))
      *c[i] = 30.0;
    if (i % 5 == 0)
    {
      memfree(b[i]);
      b[i] = nullptr;
    }
    if (i % 5 == 3)
    {
      memfree(c[i]);
      c[i] = nullptr;
    }
  }

  for (int i = 0; i < 100; i++)
  {
    memfree(b[i]);
    memfree(c[i]);
  }

  memdone();

  free(a);
}
*/
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