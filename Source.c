#include<stdio.h>
#include <math.h>
#include"memallocator.h"
int SIZE;
void* start;
typedef struct blockofmemory {
	int Free;
	struct blockofmemory* next;
	int size;
}memBlock;
int memgetminimumsize() {
	return sizeof(blockofmemory);
}
int memgetblocksize() {
	return sizeof(blockofmemory);
}
int meminit(void* pMemory, int size) {
	if (!pMemory || (size < memgetminimumsize())) {
		return 0;
	}
	start = pMemory;
	SIZE = size;
	blockofmemory* block =(blockofmemory*) start;
	block->size = SIZE;
	block->Free = 1;
	block->next = NULL;
	return 1;
}
blockofmemory* getBlock(int size) {
	blockofmemory* block = (blockofmemory*)start;
	while (block) {
		if (block->Free && (block->size) >= size)
			return block;
		block = block->next;
	}
	return NULL;
}
void* memalloc(int size) {
	if (size <= 0) {
		return NULL;
	}
	size += memgetblocksize();
	blockofmemory* block = getBlock(size);
	if (!block) {
		return NULL;
	}
	block->Free = 0;
	if ((block->size - size) <= memgetblocksize()) {
		return (void*)((char*)block + memgetblocksize());
	}
	int lastSize = block->size - size;
	block->size = size;
	blockofmemory* nextBlock = (blockofmemory*)((char*)block + size);
	nextBlock->Free = 1;
	nextBlock->size = lastSize;
	nextBlock->next = NULL;
	block->next = nextBlock;
	return (void*)((char*)block + memgetblocksize());
}
void memfree(void* p) {
	if (!p || (p == start)) {
		return;
	}
	else {
		p = (blockofmemory*)((char*)p - memgetblocksize());
	}
	blockofmemory* freeBl = (blockofmemory*)p;
	blockofmemory* previous = (blockofmemory*)start;
	blockofmemory* nextBlock = NULL;
	blockofmemory* tmp = NULL;
	tmp = (blockofmemory*)start;
	while ((tmp != freeBl) && (tmp != NULL)) {
		tmp = tmp->next;
	}
	if ((!tmp) || (freeBl->Free == 1)) {
		return;
	}
	while ((previous != freeBl) && (previous->next != freeBl)) {
		previous = previous->next;
	}
	if (freeBl->next != NULL) {
		nextBlock = freeBl->next;
	}
	if ((nextBlock != NULL) && (nextBlock->Free == 1)) {
		tmp = nextBlock;
		freeBl->next = nextBlock->next;
		freeBl->size += nextBlock->size;
		tmp->size = -1;
		tmp->Free = 1;
		tmp->next = NULL;
	}
	if ((previous != freeBl) && (previous->Free == 1)) {
		tmp = freeBl;
		previous->next = freeBl->next;
		previous->size = previous->size + freeBl->size;
		tmp->size = -1;
		tmp->Free = 1;
		tmp->next = NULL;
		freeBl = previous;
	}
	freeBl->Free = 1;
}
void memdone() {
	blockofmemory* block = (blockofmemory*)start;
	while (block) {
		if (block->Free == 0)
			block->Free = 1;
		block = block->next;
	}
}