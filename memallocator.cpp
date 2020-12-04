#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "memallocator.h"
#define EMPTY 1
#define NOT_EMPTY 0

	typedef struct block_t {
		int size;
		int isempty;
		struct block_t* next;
	}block_t;

	void* FirstB;
	int AllSize;

	int memgetblocksize() {
		return sizeof(block_t);
	}

	int memgetminimumsize() {
		return sizeof(block_t);
	}

	int meminit(void* pMemory, int size) {
		if (!pMemory || size < memgetminimumsize()) {
			return 0;
		}
		FirstB = pMemory;
		AllSize = size;
		block_t* block = (block_t*)FirstB;
		block->size = AllSize;
		block->isempty = EMPTY;
		block->next = NULL;
		return 1;
	}


	// Allocate memory block of size 'size'.
	// Returns pointer to memory block is success, 0 otherwise
	void* memalloc(int size) {
		if (size <= 0 || size > AllSize - memgetblocksize()) {
			return 0;
		}
		size += memgetblocksize();
		block_t* sub = (block_t*)FirstB;
		block_t* block = NULL;
		block_t* nextb;
		int bestsize = 0;
		int nextsize;
		while (sub) {
			if (sub->isempty == EMPTY && (sub->size) >= size) {
				if (sub->size < bestsize || bestsize == 0) {
					bestsize = sub->size;
					block = sub;
				}
			}
			sub = sub->next;
		}
		if (!block) {
			return 0;
		}
		block->isempty = NOT_EMPTY;
		nextsize = block->size - size;
		if (nextsize <= memgetblocksize()) {
			return (void*)((char*)block + memgetblocksize());
		}
		block->size = size;
		nextb = (block_t*)((char*)block + size);
		nextb->isempty = EMPTY;
		nextb->size = nextsize;
		nextb->next = block->next;
		block->next = nextb;
		return (void*)((char*)block + memgetblocksize());
	}

	// Free memory previously allocated by memalloc
	void memfree(void* p) {
		if (p && p != FirstB) {
			block_t* block = (block_t*)((char*)p - memgetblocksize());
			if (block->isempty == NOT_EMPTY) {
				block_t* sub = (block_t*)FirstB;
				while (sub && sub != block) {
					sub = sub->next;
				}
				if (sub) {
					block_t* prevb = (block_t*)FirstB;
					while (prevb != block && prevb->next != block) {
						prevb = prevb->next;
					}
					if (prevb != block && prevb->isempty == EMPTY) {
						prevb->next = block->next;
						prevb->size += block->size;
						block = prevb;
					}
					sub = block->next;
					if (sub && sub->isempty == EMPTY) {
						block->next = sub->next;
						block->size += sub->size;
						sub->size = 0;
						sub->isempty = EMPTY;
						sub->next = NULL;
					}
					block->isempty = EMPTY;
				}
			}
		}
	}
	void memdone() {
		FirstB = NULL;
		AllSize = 0;
	}
#ifdef __cplusplus
}
#endif