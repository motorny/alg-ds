#include <stdlib.h>
#include "memallocator.h"
#define FREE 0
#define NOTFREE 1
#define SUCCESS 1
#define ERROR 0

int AllSize;
void* StartBlock;

int MemInit(void* Memory, int size) {

	if (!Memory || size < sizeof(block_t)) {
		return ERROR;
	}

	StartBlock = Memory;
	AllSize = size;
	block_t* block = (block_t*)StartBlock;
	block->size = AllSize;
	block->free = FREE;
	block->next = NULL;

	return SUCCESS;
}

void* Memalloc(int size) {

	if (size > AllSize - sizeof(block_t)) {
		return 0;
	}
	size += sizeof(block_t);
	block_t* tmp = (block_t*)StartBlock;
	block_t* block = NULL;
	int BestSize = 0;
	int nexts;
	while (tmp) {
		if (tmp->free == FREE && (tmp->size) >= size) {
			if (BestSize == 0 || tmp->size < BestSize) {
				BestSize = tmp->size;
				block = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (!block) {
		return 0;
	}
	block->free = NOTFREE;
	if (block->size <= sizeof(block_t) + size) {
		return (void*)((char*)block + sizeof(block_t));
	}
	nexts = block->size - size;
	block->size = size;
	block_t* next = (block_t*)((char*)block + size);
	next->size = nexts;
	next->next = NULL;
	next->free = FREE;
	block->next = next;

	return (void*)((char*)block + sizeof(block_t));
}

void FreeMem(void* mem) {

	if (mem && mem != StartBlock) {
		block_t* block = (block_t*)((char*)mem - sizeof(block_t));
		if (block->free == NOTFREE) {
			block_t* tmp = (block_t*)StartBlock;
			while (tmp && tmp != block) {
				tmp = tmp->next;
			}
			if (tmp) {
				block_t* last = (block_t*)StartBlock;
				while (last != block && last->next != block) {
					last = last->next;
				}
				if (last != block && last->free == FREE) {
					last->next = block->next;
					last->size += block->size;
					block = last;
				}
				tmp = block->next;
				if (tmp && tmp->free == FREE) {
					block->next = tmp->next;
					block->size += tmp->size;
					tmp->size = 0;
					tmp->free = FREE;
					tmp->next = NULL;
				}
				block->free = FREE;
			}
		}
	}

	
}

void clear() {
	StartBlock = NULL;
	AllSize = 0;
}