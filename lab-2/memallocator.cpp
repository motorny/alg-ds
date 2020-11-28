#include "memallocator.h"
#include <stdlib.h>
#include <stdio.h>
#define FALSE 1
#define TRUE 0

#define BLOCK_DESCRIPTOR_SIZE (int)(sizeof(descriptor_t) + sizeof(block_end_t))

typedef struct descriptor_t { //part of description in the beggining of the memory block
	int size;
	descriptor_t* previous;
	descriptor_t* next;
} descriptor_t;

typedef struct block_end_t {  //part of description in the end of the memory block
	int size;
} block_end_t;

typedef struct myMemory_t { //contains auxiliary information about memory system
	int totalSize;
	char* memoryBeginning;
	descriptor_t* firstFreeMemDescriptor;
	descriptor_t* nextForLastAllocatedBlock; //for "the next appropriate" strategy

} my_memory_t;

my_memory_t myMemory = { 0, NULL, NULL, NULL };

int memgetminimumsize() {
	return BLOCK_DESCRIPTOR_SIZE;
}

int memgetblocksize() {
	return BLOCK_DESCRIPTOR_SIZE;
}

int meminit(void* pMemory, int size) {
	descriptor_t firstDescriptor;

	if (pMemory == NULL || size <= BLOCK_DESCRIPTOR_SIZE)
		return FALSE;

	firstDescriptor.size = size - BLOCK_DESCRIPTOR_SIZE;
	firstDescriptor.next = NULL;
	firstDescriptor.previous = NULL;


	*((descriptor_t*)pMemory) = firstDescriptor;
	((block_end_t*)((char*)pMemory + sizeof(descriptor_t) + firstDescriptor.size))->size = -firstDescriptor.size;
	myMemory.memoryBeginning = (char*)pMemory;
	myMemory.firstFreeMemDescriptor = (descriptor_t*)pMemory;
	myMemory.totalSize = size;

	return TRUE;
}

void memdone() {
	myMemory.memoryBeginning = NULL;
	myMemory.firstFreeMemDescriptor = NULL;
	myMemory.nextForLastAllocatedBlock = NULL;
	myMemory.totalSize = 0;
}

void* memalloc(int size) {
	void* ptrOnAllocMem = NULL;
	descriptor_t* checkingBlock = NULL, * newBlock = NULL;
	if (size <= 0 || myMemory.firstFreeMemDescriptor == NULL || myMemory.memoryBeginning == NULL)
		return NULL;

	if (!myMemory.nextForLastAllocatedBlock) //if it's first allocation or list ended
		checkingBlock = myMemory.firstFreeMemDescriptor;
	else
		checkingBlock = myMemory.nextForLastAllocatedBlock; //start the search from the block that follows one allocated the previous time

	while (checkingBlock != NULL) {
		if (checkingBlock->size < size)
			checkingBlock = checkingBlock->next;
		else {
			if (checkingBlock->size - size < BLOCK_DESCRIPTOR_SIZE + 1) { //if there is not enough memory to create new block
				if (checkingBlock->previous != NULL)
					checkingBlock->previous->next = checkingBlock->next;
				else
					myMemory.firstFreeMemDescriptor = checkingBlock->next;
				if (checkingBlock->next != NULL)
					checkingBlock->next->previous = checkingBlock->previous;
				myMemory.nextForLastAllocatedBlock = checkingBlock->next; //remember pointer on the block after allocated
				checkingBlock->next = NULL;
				checkingBlock->previous = NULL;
				ptrOnAllocMem = checkingBlock + 1;
				((block_end_t*)((char*)ptrOnAllocMem + checkingBlock->size))->size = checkingBlock->size;
				return ptrOnAllocMem;
			}
			else { //allocation with splitting
				newBlock = (descriptor_t*)((char*)checkingBlock + size + BLOCK_DESCRIPTOR_SIZE);
				newBlock->previous = checkingBlock->previous;
				newBlock->next = checkingBlock->next;
				if (newBlock->previous != NULL)
					newBlock->previous->next = newBlock;
				else
					myMemory.firstFreeMemDescriptor = newBlock;
				if (newBlock->next != NULL)
					newBlock->next->previous = newBlock;
				newBlock->size = checkingBlock->size - size - BLOCK_DESCRIPTOR_SIZE;
				((block_end_t*)((char*)(newBlock + 1) + newBlock->size))->size = -newBlock->size;
				myMemory.nextForLastAllocatedBlock = newBlock; //remember pointer on created node
				checkingBlock->next = NULL;
				checkingBlock->previous = NULL;
				checkingBlock->size = size;
				ptrOnAllocMem = checkingBlock + 1;
				((block_end_t*)((char*)ptrOnAllocMem + checkingBlock->size))->size = checkingBlock->size;
				return ptrOnAllocMem;
			}

		}

	}
	return NULL;
}

void memfree(void* p) {
	descriptor_t* blockToFree;
	descriptor_t* nextBlock;
	descriptor_t* previousBlock;
	block_end_t* endOfPrevBlock;
	int sizeOfNext = 0;
	int sizeOfPrevious = 0;

	if (p == NULL || myMemory.memoryBeginning == NULL || p < myMemory.memoryBeginning + sizeof(descriptor_t) || p > myMemory.memoryBeginning + myMemory.totalSize)
		return;
	blockToFree = (descriptor_t*)((char*)p - sizeof(descriptor_t));

	//if the size at the end of the block isn't equal to the size in the beggining of the block, either block is already empty or pointer is invalid
	if (((block_end_t*)((char*)blockToFree + sizeof(descriptor_t) + blockToFree->size))->size != blockToFree->size)
		return;

	nextBlock = (descriptor_t*)((char*)p + blockToFree->size + sizeof(block_end_t));
	if ((char*)nextBlock == myMemory.memoryBeginning + myMemory.totalSize)
		nextBlock = NULL;
	else
		sizeOfNext = ((block_end_t*)((char*)nextBlock + sizeof(descriptor_t) + nextBlock->size))->size;

	endOfPrevBlock = (block_end_t*)((char*)p - BLOCK_DESCRIPTOR_SIZE);
	if ((char*)endOfPrevBlock < myMemory.memoryBeginning)
		previousBlock = NULL;
	else {
		previousBlock = (descriptor_t*)((char*)p - BLOCK_DESCRIPTOR_SIZE - abs((int)(endOfPrevBlock->size)) - sizeof(descriptor_t));
		sizeOfPrevious = ((block_end_t*)((char*)previousBlock + sizeof(descriptor_t) + previousBlock->size))->size;
	}

	if ((nextBlock != NULL && sizeOfNext < 0) || (previousBlock != NULL && sizeOfPrevious < 0)) { //if there is possibility to merge

		if (nextBlock != NULL && sizeOfNext < 0) { //merging with next block if it's empty and adding to list
			blockToFree->size += nextBlock->size + BLOCK_DESCRIPTOR_SIZE;
			((block_end_t*)((char*)blockToFree + sizeof(descriptor_t) + blockToFree->size))->size = -blockToFree->size;
			if (myMemory.nextForLastAllocatedBlock == nextBlock) //if next block was next for last allocated
				myMemory.nextForLastAllocatedBlock = blockToFree;
			blockToFree->next = nextBlock->next;
			blockToFree->previous = nextBlock->previous;
			if (blockToFree->previous != NULL)
				blockToFree->previous->next = blockToFree;
			else
				myMemory.firstFreeMemDescriptor = blockToFree;
			if (blockToFree->next != NULL)
				blockToFree->next->previous = blockToFree;
		}

		if (previousBlock != NULL && sizeOfPrevious < 0) { //merging with previous block if it's empty and adding to list
			previousBlock->size += blockToFree->size + BLOCK_DESCRIPTOR_SIZE;
			((block_end_t*)((char*)previousBlock + sizeof(descriptor_t) + previousBlock->size))->size = -previousBlock->size;

			if (nextBlock != NULL && sizeOfNext < 0) { //if merge in both directions
				if (blockToFree->previous != NULL)
					blockToFree->previous->next = blockToFree->next;
				else
					(myMemory.firstFreeMemDescriptor = blockToFree->next);
				if (blockToFree->next != NULL)
					blockToFree->next->previous = blockToFree->previous;
				if (myMemory.nextForLastAllocatedBlock == blockToFree)
					myMemory.nextForLastAllocatedBlock = previousBlock;
			}
		}
	}

	else { //adding to list without merging
		((block_end_t*)((char*)blockToFree + sizeof(descriptor_t) + blockToFree->size))->size = -blockToFree->size;
		if (myMemory.firstFreeMemDescriptor == NULL) //if block is the only empty in memory
			myMemory.firstFreeMemDescriptor = blockToFree;
		else { //add after the first empty block
			blockToFree->next = myMemory.firstFreeMemDescriptor->next;
			blockToFree->previous = myMemory.firstFreeMemDescriptor;
			myMemory.firstFreeMemDescriptor->next = blockToFree;
			if (blockToFree->next != NULL)
				blockToFree->next->previous = blockToFree;
		}
	}
}
