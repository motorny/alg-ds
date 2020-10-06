#include <stdio.h>
#include <windows.h>

#include "skip_list.h"
#include "list.h"

int main(void) {
  skip_list_t sl;
  list_t l;
  LARGE_INTEGER t0, t1, freq;

  SkipListIni(&sl);
  ListIni(&l);

  QueryPerformanceFrequency(&freq);

  printf("insert 30000\n");
  srand(30);
  QueryPerformanceCounter(&t0);
  for (int i = 0; i < 30000; i++)
    SkipListInsert(&sl, rand());
  QueryPerformanceCounter(&t1);
  printf("skip list: %f\n", (double)(t1.QuadPart - t0.QuadPart) / freq.QuadPart);
  srand(30);
  QueryPerformanceCounter(&t0);
  for (int i = 0; i < 30000; i++)
    ListInsert(&l, rand());
  QueryPerformanceCounter(&t1);
  printf("list: %f\n", (double)(t1.QuadPart - t0.QuadPart) / freq.QuadPart);

  printf("find 30000\n");
  srand(59);
  QueryPerformanceCounter(&t0);
  for (int i = 0; i < 30000; i++)
    SkipListFind(&sl, rand());
  QueryPerformanceCounter(&t1);
  printf("skip list: %f\n", (double)(t1.QuadPart - t0.QuadPart) / freq.QuadPart);
  srand(59);
  QueryPerformanceCounter(&t0);
  for (int i = 0; i < 30000; i++)
    ListFind(&l, rand());
  QueryPerformanceCounter(&t1);
  printf("list: %f\n", (double)(t1.QuadPart - t0.QuadPart) / freq.QuadPart);

  printf("extract 30000\n");
  srand(111);
  QueryPerformanceCounter(&t0);
  for (int i = 0; i < 30000; i++)
    SkipListExtract(&sl, rand());
  QueryPerformanceCounter(&t1);
  printf("skip list: %f\n", (double)(t1.QuadPart - t0.QuadPart) / freq.QuadPart);
  srand(111);
  QueryPerformanceCounter(&t0);
  for (int i = 0; i < 30000; i++)
    ListExtract(&l, rand());
  QueryPerformanceCounter(&t1);
  printf("list: %f\n", (double)(t1.QuadPart - t0.QuadPart) / freq.QuadPart);

  SkipListClose(&sl);
  ListClose(&l);

  return 0;
}