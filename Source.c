#include<stdio.h>
#include <math.h>
#include"memallocator.h"
int SIZE;
void* start;
typedef struct blockofmemory {
	int Free;
	struct blockofmemory* next;
	int size;
} memBlock;
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
	blockofmemory* block = (blockofmemory*)start;
	block->size = SIZE;
	block->Free = 1;
	block->next = NULL;
	return 1;
}
blockofmemory* getBlock(int size) {
	blockofmemory* block = (blockofmemory*)start;
	while (block) {
		if (block->Free && (block->size) >= size) {
			return block;
		}
		block = block->next;
	}
	return NULL;
}
void* memalloc(int size) {
	if (size <= 0) {
		return NULL;
	}
	size = size + memgetblocksize();
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
	blockofmemory* next = (blockofmemory*)((char*)block + size);
	next->Free = 1;
	next->size = lastSize;
	next->next = NULL;
	block->next = next;
	return (void*)((char*)block + memgetblocksize());
}
void memfree(void* p) {
	if (!p || (p == start)) {
		return;
	}
	else {
		p = (blockofmemory*)((char*)p - memgetblocksize());
	}
	blockofmemory* freeb = (blockofmemory*)p;
	blockofmemory* previous = (blockofmemory*)start;
	blockofmemory* next = NULL;
	blockofmemory* tmp = NULL;
	tmp = (blockofmemory*)start;
	while ((tmp != freeb) && (tmp != NULL)) {
		tmp = tmp->next;
	}
	if ((!tmp) || (freeb->Free == 1)) {
		return;
	}
	while ((previous != freeb) && (previous->next != freeb)) {
		previous = previous->next;
	}
	if (freeb->next != NULL) {
		next = freeb->next;
	}
	if ((next != NULL) && (next->Free == 1)) {
		tmp = next;
		freeb->next = next->next;
		freeb->size = freeb->size + next->size;
		tmp->size = -1;
		tmp->Free = 1;
		tmp->next = NULL;
	}
	if ((previous != freeb) && (previous->Free == 1)) {
		tmp = freeb;
		previous->next = freeb->next;
		previous->size = previous->size + freeb->size;
		tmp->size = -1;
		tmp->Free = 1;
		tmp->next = NULL;
		freeb = previous;
	}
	freeb->Free = 1;
}
void memdone() {
	blockofmemory* block = (blockofmemory*)start;
	while (block) {
		if (block->Free == 0) {
			block->Free = 1;
		}
		block = block->next;
	}
}
