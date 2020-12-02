#include <stdio.h>
#include <stdlib.h>
#include"memallocator.h"
#define VALID 1
#define INVALID -1
//#define SUCCESS 1
#define FAIL 0

void* INIT;
int SIZE;

// Односвязный список
typedef struct list_t {
	int size;
	list_t* next;
	int validation;
}list_t;


// Return minimum size in bytes of the memory pool to allocate 0-bytes block
int memgetminimumsize() {
	return sizeof(list_t);
};


// Returns size in bytes of additional information per allocation
int memgetblocksize() {
	return sizeof(list_t);
};

// Init memory system with memory block pMemory.
int meminit(void* pMemory, int size) {
	// Если указатель NULL
	if (!pMemory)
		return FAIL;
	// или требуемый размер меньше допустимого
	if (size < memgetminimumsize())
		return FAIL;
	// Если все в порядке
	INIT = pMemory;
	SIZE = size;
	// то создаем начальную переменную
	list_t* block = (list_t*)INIT;
	block->size = SIZE;
	block->validation = VALID;
	block->next = NULL;
	return VALID;
};

// You can implement memory leak checks here
void memdone() {
	list_t* block = (list_t*)INIT;
	while (block) {
		if (block->validation == INVALID)
			block->validation = VALID;
		block = block->next;
	}
};

// Allocate memory block of size 'size'.
void* memalloc(int size) {
	if (size <= 0) {
		return NULL;
	}
	size = size + memgetblocksize();
	list_t* myblock = (list_t*)INIT;
	list_t* block = NULL;
	// Будем искать первый подходящий
	while (myblock) {
		if ((myblock->validation == VALID) && (myblock->size >= size)) {
			block = myblock;
		}
		myblock = myblock->next;
	}
	// Если не нашли подходящий
	if (block == NULL) {
		return NULL;
	}
	block->validation = INVALID;
	if ((block->size - size) <= memgetblocksize()) {
		return (void*)((char*)block + memgetblocksize());
	}
	// Внесем в список блок
	int newSize = block->size - size;
	block->size = size;
	list_t* nextBlock = (list_t*)((char*)block + size);
	nextBlock->validation = VALID;
	nextBlock->size = newSize;
	nextBlock->next = NULL;
	block->next = nextBlock;
	return (void*)((char*)block + memgetblocksize());
};

// Free memory previously allocated by memalloc
void memfree(void* p) {
	if ((!p) || (p == INIT))
		return;
	else
		p = (list_t*)((char*)p - memgetblocksize());

	list_t* nextBlock = NULL;
	list_t* reserveBlock = (list_t*)INIT;;
	list_t* prevBlock = (list_t*)INIT;
	list_t* freeBlock = (list_t*)p;
	// Бежим до конца
	while ((reserveBlock) && (reserveBlock != freeBlock))
		reserveBlock = reserveBlock->next;

	if ((!reserveBlock) || (freeBlock->validation == VALID))
		return;

	while ((prevBlock->next != freeBlock) && (prevBlock != freeBlock))
		prevBlock = prevBlock->next;

	if (freeBlock->next != NULL)
		nextBlock = freeBlock->next;

	if ((nextBlock) && (nextBlock->validation == VALID)) {
		reserveBlock = nextBlock;
		freeBlock->next = nextBlock->next;
		freeBlock->size = freeBlock->size + nextBlock->size;
		reserveBlock->size = INVALID;
		reserveBlock->validation = VALID;
		reserveBlock->next = NULL;
	}
	// Проверим предыдущий
	if ((prevBlock->validation == VALID) && (prevBlock != freeBlock)) {
		reserveBlock = freeBlock;
		prevBlock->next = freeBlock->next;
		prevBlock->size = prevBlock->size + freeBlock->size;
		reserveBlock->size = INVALID;
		reserveBlock->validation = VALID;
		reserveBlock->next = NULL;
		freeBlock = prevBlock;
	}
	freeBlock->validation = VALID;
};



