#pragma once
#include <stdio.h>
#include <malloc.h>

int memgetblocksize();
int memgetminimumsize();
int meminit(void* pMemory, int size);
void* memalloc(int size);
void memfree(void* pBlock);
void memdone();
