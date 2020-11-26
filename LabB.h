#pragma once

#include <stdlib.h>

typedef struct list_t {
  struct list_t* next;
  int size;
} list_t;

int memGetMinSize();

int memGetBlockSize();

int memInit(void* memory, int size);

void* meMalloc(int size);

void memDone();

void memFree(void* memory);