#include<stdio.h>
#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif


typedef struct memBlock {
	int size;
	int isFree;
	struct memBlock* next;
}memBlock;


int memgetblocksize() {
	return sizeof(memBlock);
}

int memgetminimumsize() {
	return sizeof(memBlock);
}

void* firstBlock;
int memSize;

int meminit(void* pMemory, int size) {
	if (!pMemory || (size < memgetminimumsize()))
		return 0;
	firstBlock = pMemory;
	memSize = size;
	memBlock* block = (memBlock*)firstBlock;
	block->size = memSize;
	block->isFree = 1;
	block->next = NULL;
	return 1;
}

memBlock* getBlock(int size) {
	memBlock* tmp = (memBlock*)firstBlock;
	memBlock* block = NULL;
	int best = -1;
	while (tmp) {
		if (tmp->isFree && (tmp->size) >= size) {
			if (tmp->size < best || best == -1) {
				best = tmp->size;
				block = tmp;
			}
		}
		tmp = tmp->next;
		
	}
	return block;
}

void* memalloc(int size) {
	if (size <= 0) {
		return NULL;
	}
	size += memgetblocksize();
	memBlock* block = getBlock(size);
	if (!block)
		return NULL;
	block->isFree = 0;

	if ((block->size - size) <= memgetblocksize()) {
		return (void*)((char*)block + memgetblocksize());
	}
	int lastSize = block->size - size;
	block->size = size;
	memBlock* nextBlock = (memBlock*)((char*)block + size);
	nextBlock->isFree = 1;
	nextBlock->size = lastSize;
	nextBlock->next = NULL;
	block->next = nextBlock;
	return (void*)((char*)block + memgetblocksize());
}

void memfree(void* p) {
	if (!p || (p == firstBlock))
		return;
	else
		p = (memBlock*)((char*)p - memgetblocksize());
	memBlock* freeBlock = (memBlock*)p, * prevBlock = (memBlock*)firstBlock, * nextBlock = NULL, * tmp = NULL;

	tmp = (memBlock*)firstBlock;
	while ((tmp != freeBlock) && (tmp != NULL)) {
		tmp = tmp->next;
	}
	if ((!tmp) || (freeBlock->isFree == 1))
		return;

	while ((prevBlock != freeBlock) && (prevBlock->next != freeBlock)) {
		prevBlock = prevBlock->next;				
	}
	if (freeBlock->next != NULL)
		nextBlock = freeBlock->next;

	if ((nextBlock != NULL) && (nextBlock->isFree == 1)) {
		tmp = nextBlock;
		freeBlock->next = nextBlock->next;	
		freeBlock->size += nextBlock->size;
		tmp->isFree = 1;
		tmp->size = -1;
		tmp->next = NULL;

	}
	if ((prevBlock != freeBlock) && (prevBlock->isFree == 1)) {
		tmp = freeBlock;
		prevBlock->next = freeBlock->next;  
		prevBlock->size += freeBlock->size;
		tmp->isFree = 1;
		tmp->size = -1;
		tmp->next = NULL;
		freeBlock = prevBlock;
	}
	freeBlock->isFree = 1;
}
void memdone() {
	firstBlock = NULL;
	memSize = 0;
}
#ifdef __cplusplus
}
#endif

#endif