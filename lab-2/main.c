#include "memallocator.h"
#include <stdlib.h>

void main() {
  int* p;
  void *ptr = malloc(memgetminimumsize() + (sizeof(int) + memgetblocksize())* 100);
  meminit(ptr, memgetminimumsize() + (sizeof(int) + memgetblocksize()) * 100);
  for (int i = 0; i < 30; i++)
  { 
    p = (int*)memalloc(sizeof(int)); // Success!
    p[0] = 30 + i;
  }
  memfree(p);
  memdone();
  free(ptr);
}