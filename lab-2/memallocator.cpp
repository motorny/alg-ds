#include <stdlib.h>
#include <stdio.h>
#include "memallocator.h"

#define BLOCK_NO_TOG 0
#define BLOCK_BEFORE_TOG 1
#define BLOCK_AFTER_TOG 2
#define BLOCK_BOTH_TOG 3
#define MAGIC_KEY 135000
#define FREEBLOCK 1
#define BUSYBLOCK 0
typedef struct memory_block_t {
	int size;
	int magicKey;
	struct memory_block_t* next;
	struct memory_block_t* prev;
}memory_block_t;

typedef struct {
	//Указатель на первый свободный блок
	memory_block_t* startFree;
	int size;
}all_mem_info_t;

all_mem_info_t* g_allMemory = 0;

int memgetminimumsize() {
	return sizeof(memory_block_t) + sizeof(int) + sizeof(all_mem_info_t);
}

int memgetblocksize() {
	return sizeof(memory_block_t) + sizeof(int);
}

static void AddEnder(memory_block_t* block, int freeFlag) {
	if (freeFlag)
		*((int*)((char*)block + sizeof(memory_block_t) + block->size)) = block->size;
	else
		*((int*)((char*)block + sizeof(memory_block_t) + block->size)) = -block->size;
}

int meminit(void* pMemory, int size) {
	g_allMemory = (all_mem_info_t*)pMemory;

	if (g_allMemory == NULL || size < memgetminimumsize() + 1) {
		return 0;
	}

	g_allMemory->size = size;
	g_allMemory->startFree = (memory_block_t*)((char*)g_allMemory + sizeof(all_mem_info_t));
	(g_allMemory->startFree)->size = size - sizeof(all_mem_info_t) - memgetblocksize();
	(g_allMemory->startFree)->next = NULL;
	(g_allMemory->startFree)->prev = NULL;
	(g_allMemory->startFree)->magicKey = MAGIC_KEY;
	AddEnder(g_allMemory->startFree, FREEBLOCK);
	return 1;
}


void* memalloc(int size) {
	memory_block_t* curBlock = g_allMemory->startFree;
	memory_block_t* bittenBlock = NULL;

	while (curBlock != NULL) {
		if (size <= curBlock->size) {
			break;
		}
		curBlock = curBlock->next;
	}

	if (curBlock != NULL) {
		if (curBlock->size - size > memgetblocksize()) {
			bittenBlock = (memory_block_t*)((char*)curBlock + memgetblocksize() + size);
			bittenBlock->size = curBlock->size - size - memgetblocksize();
			bittenBlock->next = curBlock->next;
			bittenBlock->prev = curBlock->prev;
			bittenBlock->magicKey = MAGIC_KEY;
			AddEnder(bittenBlock, FREEBLOCK);
			if (bittenBlock->next != NULL)
				(bittenBlock->next)->prev = bittenBlock;
			if (bittenBlock->prev != NULL)
				(bittenBlock->prev)->next = bittenBlock;
			if (curBlock == g_allMemory->startFree)
				g_allMemory->startFree = bittenBlock;
		}
		else {
			if (curBlock->prev != NULL)
				(curBlock->prev)->next = curBlock->next;
			if (curBlock->next != NULL)
				(curBlock->next)->prev = curBlock->prev;

			if (curBlock == g_allMemory->startFree) {
				g_allMemory->startFree = curBlock->next;
			}
		}
		curBlock->size = size;
		curBlock->next = NULL;
		curBlock->prev = NULL;
		AddEnder(curBlock, BUSYBLOCK);
		return (char*)curBlock + sizeof(memory_block_t);
	}
	return NULL;

}

static void DeleteBlock(memory_block_t* block) {
	if(block->prev != NULL) {
		(block->prev)->next = block->next;
		if (block->next != NULL)
			(block->next)->prev = block->prev;
		(block->prev)->size += (block->size + memgetblocksize());
		AddEnder(block->prev, FREEBLOCK);
	}
}

static int insertBlock(memory_block_t* prevBlock, memory_block_t* blockToInsert) {
	//если свободен предыдущий блок
	if ((*(int*)((char*)prevBlock + sizeof(memory_block_t) + prevBlock->size)) == prevBlock->size) {
		blockToInsert->next = prevBlock->next;
		if (blockToInsert->next != NULL)
			(blockToInsert->next)->prev = blockToInsert;

		blockToInsert->prev = prevBlock;
		prevBlock->next = blockToInsert;
		AddEnder(blockToInsert, FREEBLOCK);
	}
	else if ((*(int*)((char*)blockToInsert + sizeof(memory_block_t) + blockToInsert->size)) == blockToInsert->size) {
		//если свободен блок, который надо вставить
		prevBlock->next = blockToInsert;
		prevBlock->prev = blockToInsert->prev;
		if (prevBlock->prev != NULL)
			(prevBlock->prev)->next = prevBlock;
		blockToInsert->prev = prevBlock;
		AddEnder(prevBlock, FREEBLOCK);

	}
	if (blockToInsert->prev != NULL) {
		if ((char*)blockToInsert - (char*)blockToInsert->prev == (blockToInsert->prev)->size + memgetblocksize()) {
			if (blockToInsert->next != NULL)
				if ((char*)blockToInsert->next - (char*)blockToInsert == blockToInsert->size + memgetblocksize())
					return BLOCK_BOTH_TOG;
			return BLOCK_BEFORE_TOG;
		}
	}

	if (blockToInsert->next != NULL) {
		if ((char*)blockToInsert->next - (char*)blockToInsert == blockToInsert->size + memgetblocksize())
			return BLOCK_AFTER_TOG;
	}
	return BLOCK_NO_TOG;
}

static int glueBlocks(int togFlag, memory_block_t* block) {
	if (togFlag == BLOCK_NO_TOG)
		return 0;
	//склеиваем в зависимости от TOG_FLAG
	switch (togFlag) {
	case BLOCK_BEFORE_TOG:
		DeleteBlock(block);
		break;
	case BLOCK_AFTER_TOG:
		DeleteBlock(block->next);
		break;
	case BLOCK_BOTH_TOG:
		DeleteBlock(block->next);
		DeleteBlock(block);
		break;
	}
	return 1;
}

void memfree(void* p) {
	memory_block_t* ptr = (memory_block_t*)((char*)p - sizeof(memory_block_t));
	memory_block_t* forChange = NULL;
	memory_block_t* nearestBlockBefore = NULL;
	int togFlag = BLOCK_NO_TOG;
	
	if ((char*)ptr > (char*)g_allMemory && (char*)ptr < (char*)g_allMemory + g_allMemory->size && ptr->magicKey == MAGIC_KEY
		&& *((int*)((char*)ptr + sizeof(memory_block_t) + ptr->size)) == -(ptr->size)) {
		if (g_allMemory->startFree == NULL) {
			//Случай когда нет свободных блоков
			g_allMemory->startFree = ptr;
			(g_allMemory->startFree)->prev = NULL;
			(g_allMemory->startFree)->next = NULL;
			AddEnder(g_allMemory->startFree, FREEBLOCK);

		}
		else {
			//Находим ближайший свободный блок перед *p
			if (g_allMemory->startFree < ptr) {
				nearestBlockBefore = g_allMemory->startFree;
				while (nearestBlockBefore->next != NULL) {
					if (ptr < nearestBlockBefore->next)
						break;
					nearestBlockBefore = nearestBlockBefore->next;
				}
				togFlag = insertBlock(nearestBlockBefore, ptr);
				//Если блоки вплотную к друг-другу склеиваем их
				glueBlocks(togFlag, ptr);
			}
			else {
				forChange = ptr;
				ptr = g_allMemory->startFree;
				g_allMemory->startFree = forChange;

				togFlag = insertBlock(g_allMemory->startFree, ptr);
				glueBlocks(togFlag, ptr);
			}

		}
	}
}


void memdone() {
	g_allMemory = NULL;
}




