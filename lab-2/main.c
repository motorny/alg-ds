#include "memallocator.h"
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>

#define SIZE 500

int main(void) {
  int i = 0;
  int memsize = memgetminimumsize() + (SIZE-1) * memgetblocksize() + SIZE;
  char* memory = malloc(memsize);

  char** arr = malloc(SIZE * sizeof(char*)); //array of 'SIZE' pointers to 'char' data

  if (!memory || !arr)
    return 1;

  LARGE_INTEGER freq;
  LARGE_INTEGER start, end; 
  QueryPerformanceFrequency(&freq);

  //Default memory manager
  QueryPerformanceCounter(&start);

  for (i = 0; i < SIZE; ++i)
    arr[i] = (char*)malloc(1);

  for (i = 0; i < SIZE; ++i)
    free(arr[i]);

  QueryPerformanceCounter(&end);
  printf("Default memory manager: %lf\n", ((double)end.QuadPart - (double)start.QuadPart) / (double)freq.QuadPart);


  //My memory manager
  QueryPerformanceCounter(&start);

  if (!meminit(memory, memsize))
    return 1;

  for (i = 0; i < SIZE; ++i)
    arr[i] = memalloc(1);

  for (i = 0; i < SIZE; ++i)
    memfree(arr[i]);

  QueryPerformanceCounter(&end);
  printf("My memory manager: %lf\n", ((double)end.QuadPart - (double)start.QuadPart) / (double)freq.QuadPart);

  memdone();
  free(arr);
  free(memory);
  return 0;
}