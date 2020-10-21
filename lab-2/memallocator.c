#include<stdio.h>
#include"memallocator.h"

void* memStart;
int fullSize;

typedef struct memBlock {
	int isFree;
	struct memBlock* next;
	int size;
}memBlock;

int memgetblocksize() {
	return sizeof(memBlock);
}

int memgetminimumsize() {
	return sizeof(memBlock);
}

int meminit(void* pMemory, int size) {
	if (!pMemory || (size < memgetminimumsize()))
		return 0;
	memStart = pMemory;
	fullSize = size;
	memBlock* block = memStart;
	block->size = fullSize;
	block->isFree = 1;
	block->next = NULL;
	return 1;
}

memBlock* getBlock(int size) {
	memBlock* block = memStart;
	while (block) {
		if (block->isFree && (block->size) >= size)
			return block;
		block = block->next;
	}
	return NULL;
}

void* memalloc(int size){
	if ( size <= 0) {
		return NULL;
	}
	size += memgetblocksize();
	memBlock* block = getBlock(size);
	if (!block)
		return NULL;
	block->isFree = 0;
	
	if ((block->size - size) <= memgetblocksize()) {
		return (void*)((char*)block + memgetblocksize());//если не хватает памяти на "дробление" блока, то используем данный
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
	if (!p || (p == memStart))
		return;
	else
		p = (memBlock*)((char*)p - memgetblocksize());
	memBlock* freeBlock = p, *previousBlock = memStart, *nextBlock = NULL,*tmp = NULL;
	
	tmp =(memBlock*)memStart;
	while ((tmp != freeBlock) && (tmp != NULL)) {//проверка на то, что вообще есть такой блок
		tmp = tmp->next;							
	}
	if ((!tmp) || (freeBlock->isFree == 1))
		return;

	while ((previousBlock != freeBlock) && (previousBlock->next != freeBlock)) {
		previousBlock = previousBlock->next;				//поиск предыдущего блока
	}
	if (freeBlock->next != NULL)
		nextBlock = freeBlock->next;

	if ((nextBlock != NULL) && (nextBlock->isFree == 1)) {
		tmp = nextBlock;
		freeBlock->next = nextBlock->next;	//склейка блоков
		freeBlock->size += nextBlock->size;
		tmp->size = -1;
		tmp->isFree = 1;
		tmp->next = NULL;
		
	}
	if ((previousBlock != freeBlock) && (previousBlock->isFree == 1)) {
		tmp = freeBlock;
		previousBlock->next = freeBlock->next;  //склейка блоков
		previousBlock->size += freeBlock->size;
		tmp->size = -1;
		tmp->isFree = 1;
		tmp->next = NULL;
		freeBlock = previousBlock;
	}
	freeBlock->isFree = 1;
}
void memdone() {
	memBlock* block = memStart;
	while (block) {
		if (block->isFree == 0)
			block->isFree = 1;
		block = block->next;
	}
}