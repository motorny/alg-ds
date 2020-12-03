#include <stdio.h>
#include <stdlib.h>
#include "memallocator.h"
#define NO_FIT_BLOCK_TO_ALLOCATE NULL
#define NEGATIVE_WHILE_IS_NOT_FOUND -1

typedef enum {
	SUCCESS = 0,
	CANNOT_INITIALIZE_THE_LIST = 1,
	DETECTED_MEMORY_LEAKS = 2,
}error_t;

typedef struct descriptor_t {
	int size;
	descriptor_t* next;
}descriptor_t;

typedef struct {
	int fullness;
}end_of_block_t;

typedef struct {
	char* wholeBlockPtr;
	descriptor_t* head;
	int blockSize;
}list_t;

// Return minimum size in bytes of the memory pool to allocate 0-bytes block
int memgetminimumsize() {
	return sizeof(descriptor_t) + sizeof(end_of_block_t);
}

// Returns size in bytes of additional information per allocation
int memgetblocksize() {
	return sizeof(descriptor_t) + sizeof(end_of_block_t);
}

list_t list = { NULL, (descriptor_t*)NULL, 0 };

// Init memory system with memory block pMemory.
int meminit(void* pMemory, int size) {
	int descriptSize = memgetminimumsize();

	if (!pMemory || size <= descriptSize)
		return CANNOT_INITIALIZE_THE_LIST;
	list.blockSize = size;
	descriptor_t headDiscriptor;
	headDiscriptor.size = size - descriptSize;
	headDiscriptor.next = NULL;
	*((descriptor_t*)pMemory) = headDiscriptor;

	list.wholeBlockPtr = (char*)pMemory;
	list.head = (descriptor_t*)pMemory;
	((end_of_block_t*)((char*)pMemory + sizeof(descriptor_t) + headDiscriptor.size))->fullness = -headDiscriptor.size; //put fullness to the end of the block

	return SUCCESS;
}

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, 0 otherwise
void* memalloc(int size) {
	if (size <= 0 || list.head == NULL)
		return NULL;

	descriptor_t* bestFitDescript = NULL;
	descriptor_t* newDescript = NULL, * prevDescript = NULL;
	int deltacur = 0;
	int deltamin = NEGATIVE_WHILE_IS_NOT_FOUND; // >= 0 if there is the best fit block
	descriptor_t* start = list.head;
	descriptor_t* current = start;

	//finding the best fit
	while (current != NULL) {
		if (size <= current->size) { //there is enough memory in the block
			deltacur = current->size - size;
			if (deltacur == 0) {
				deltamin = 0;
				bestFitDescript = current;
				break;
			}
			else {
				if (deltamin == -1 || deltacur < deltamin) { //the first discriptor or current block is better than previous fit
					deltamin = deltacur;
					bestFitDescript = current;
				}
				else { ; } //current block does is not the best
			}
		}
		current = current->next;
	}
	if (deltamin == -1) {
		return NO_FIT_BLOCK_TO_ALLOCATE;
	}

	//finding the pointer to the previous descriptor
	prevDescript = start;
	while (prevDescript->next != bestFitDescript && bestFitDescript != start)//if the best fit is not the first
		prevDescript = prevDescript->next;

	if (bestFitDescript->size - size <= memgetblocksize()) { //not enough memory to create a new block
		if (bestFitDescript == start) {
			list.head = bestFitDescript->next;
		}
		else
			prevDescript->next = bestFitDescript->next;
		((end_of_block_t*)((char*)bestFitDescript + sizeof(descriptor_t) + bestFitDescript->size))->fullness = bestFitDescript->size;
	}

	else { //allocate memory and create new block 
		newDescript = (descriptor_t*)((char*)bestFitDescript + memgetblocksize() + size);
		newDescript->size = bestFitDescript->size - size - memgetblocksize();
		((end_of_block_t*)((char*)newDescript + sizeof(descriptor_t) + newDescript->size))->fullness = -newDescript->size; //new block is free

		if (bestFitDescript == start) {
			list.head = newDescript;
		}
		else
			prevDescript->next = newDescript;

		newDescript->next = bestFitDescript->next;
		bestFitDescript->size = size;
		((end_of_block_t*)((char*)bestFitDescript + sizeof(descriptor_t) + size))->fullness = size; //fit block is full
	}
	return (descriptor_t*)bestFitDescript + 1;
}

// Free memory previously allocated by memalloc
void memfree(void* p) {
	if (p == NULL)
		return;
	int size = 0, fullnessPrev = 0, fullnessNext = 0;
	descriptor_t* currentDescript = (descriptor_t*)((char*)p - sizeof(descriptor_t));
	//if block is already empty or pointer is invalid
	if (((end_of_block_t*)((char*)currentDescript + sizeof(descriptor_t) + currentDescript->size))->fullness != currentDescript->size)
		return;

	descriptor_t* prevDescript = NULL, * nextDescript = NULL;
	descriptor_t* current = list.head;

	if (list.head != NULL) {
		//merge with the block on the left
		if ((char*)currentDescript != list.wholeBlockPtr) { //current is not the first block in the whole memory
			fullnessPrev = ((end_of_block_t*)((char*)currentDescript - sizeof(end_of_block_t)))->fullness;
			if (fullnessPrev < 0) { //previous block is free
				size = -fullnessPrev; //of previous block
				prevDescript = (descriptor_t*)((char*)currentDescript - size - memgetblocksize());
				while (current->next != prevDescript && prevDescript != list.head) //finding the pointer on the previous if it is not the first
					current = current->next;
				if (prevDescript != list.head) {
					current->next = prevDescript->next;
					prevDescript->next = list.head;
					list.head = prevDescript;
					current = list.head;
				}
				else { ; } //previous is already the head of the list
				prevDescript->size = size + currentDescript->size + memgetblocksize();
				((end_of_block_t*)((char*)currentDescript + sizeof(descriptor_t) + currentDescript->size))->fullness = -prevDescript->size; //merged block  is free
			}
		}

		//merge with the block on the right
		if (((char*)currentDescript + currentDescript->size + memgetblocksize()) != ((char*)list.wholeBlockPtr + list.blockSize)) { //checking that currentDiscript is not the last in the whole block
			if (fullnessPrev < 0) { //currentDescript is merged with block on the left
				currentDescript = prevDescript; //this is needed to merge on the right too
			}
			nextDescript = (descriptor_t*)((char*)currentDescript + currentDescript->size + memgetblocksize());
			fullnessNext = ((end_of_block_t*)((char*)nextDescript + sizeof(descriptor_t) + nextDescript->size))->fullness;
			if (fullnessNext < 0) { //next block is free
				size = -fullnessNext; //of next block
				while (current->next != nextDescript && nextDescript != list.head) //finding ptr on the next if it is not the first
					current = current->next;
				if (nextDescript != list.head) {
					current->next = nextDescript->next;
				}
				if (currentDescript != list.head) { //there was merging on the left
					if (nextDescript == list.head)
						currentDescript->next = nextDescript->next; //merging with the previous head without putting the pointer on the previous head
					else
						currentDescript->next = list.head;
					list.head = currentDescript;
				}
				currentDescript->size = size + currentDescript->size + memgetblocksize();
				((end_of_block_t*)((char*)nextDescript + sizeof(descriptor_t) + size))->fullness = -currentDescript->size;
			}
		}
	}

	if (fullnessPrev >= 0 && fullnessNext >= 0) { //free without merging
		((end_of_block_t*)((char*)currentDescript + sizeof(descriptor_t) + currentDescript->size))->fullness = -currentDescript->size;//block is free
		currentDescript->next = list.head;
		list.head = currentDescript;
	}
	return;
}

// You can implement memory leak checks here
void memdone() {
	int leaks = 0;
	descriptor_t* descriptor = (descriptor_t*)list.wholeBlockPtr;
	while (((char*)descriptor + memgetblocksize() + descriptor->size) <= ((char*)list.wholeBlockPtr + list.blockSize)) {
		if (((end_of_block_t*)((char*)descriptor + sizeof(descriptor_t) + descriptor->size))->fullness > 0) {//some memory is not empty
			if (leaks == 0) {
				leaks = DETECTED_MEMORY_LEAKS;
				printf("\nDetected memory leaks :(\n");
				printf("at %p, %i bytes long\n", descriptor, descriptor->size);
			}
			else //leaks == DETECTED_MEMORY_LEAKS
				printf("at %p, %i bytes long\n", descriptor, descriptor->size);
		}
		descriptor = (descriptor_t*)((char*)descriptor + memgetblocksize() + descriptor->size);
	}
	if (leaks == 0)
		printf("\nThere is no memory leaks :)\n");
	return;
}