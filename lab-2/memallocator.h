#pragma once


typedef struct memBlock {
	int size;
	int isFree;
	struct memBlock* next;
}memBlock;



memBlock* getBlock(int size);

void* memalloc(int size);

void memfree(void* p);

void memdone();

int meminit(void* pMemory, int size);

int memgetminimumsize();

int memgetblocksize();