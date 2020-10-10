#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Memallocator/memallocator.h"

#define NUM_OF_TESTS 10000
#define BIG_BLOCK sizeof(int) * 1000
#define MEDIUM_BLOCK sizeof(int) * 500
#define SMALL_BLOCK sizeof(int) * 100

double MeasureMemallocMemFree(int size) {
  clock_t time1, time2;
  void *p1, *p2, *ptr;
  int i;
  ptr = malloc(sizeof(int) * 3000);
  meminit(ptr, sizeof(int) * 3000);
  time1 = clock();
  for (i = 0; i < NUM_OF_TESTS; ++i) {
    p1 = memalloc(size);
    p2 = memalloc(size);
    memfree(p1);
    memfree(p2);
  }
  time2 = clock();
  memdone();
  free(ptr);
  return (double)(time2 - time1) / NUM_OF_TESTS;
}

double MeasureMallocFree(int size) {
  clock_t time1, time2;
  void *p1, *p2;
  int i;
  time1 = clock();
  for (i = 0; i < NUM_OF_TESTS; ++i) {
    p1 = malloc(size);
    p2 = malloc(size);
    free(p1);
    free(p2);
  }
  time2 = clock();
  return (double)(time2 - time1) / NUM_OF_TESTS;
}

int main() {
  double myt1, myt2, myt3, st1, st2, st3;
  myt1 = MeasureMemallocMemFree(BIG_BLOCK); // my allocator time 1
  myt2 = MeasureMemallocMemFree(MEDIUM_BLOCK);
  myt3 = MeasureMemallocMemFree(SMALL_BLOCK);
  st1 = MeasureMallocFree(BIG_BLOCK); // standart allocator time 1
  st2 = MeasureMallocFree(MEDIUM_BLOCK);
  st3 = MeasureMallocFree(SMALL_BLOCK);
 
  printf("Big block alocate\nMy allocator: %lfms\nStandart allocator: %lfmms\n\n", myt1, st1);
  printf("Medium block alocate\nMy allocator: %lfms\nStandart allocator: %lfms\n\n", myt2, st2);
  printf("Small block alocate\nMy allocator: %lfms\nStandart allocator: %lfms\n\n", myt3, st3);
  printf("Custom allocator is near %lf times faster then standart\n", (st1 + st2 + st3) / (myt1, myt2, myt3));  // ” мен€ на тестах получилось примерно в 6-7 раз быстрее
  return 0;
}