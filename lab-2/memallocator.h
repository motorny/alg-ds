#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#define MYCOMP
#define NOT_ENOUGH_MEMORY     1
#define NULL_POINTER_ON_INPUT 2

typedef struct nodeheader {
  int size;
  struct nodeheader* ptrToNext;
}NodeHeader;

typedef struct nodeender {
  int size;
}NodeEnder;

bool MemoryLeaksCheckTrueIfNoLeaks();

int memgetminimumsize();

int meminit(void* pMemory, int size);

void memdone();

void* memalloc(int size);

void memfree(void* p);

int memgetblocksize();


#ifdef __cplusplus
}
#endif
