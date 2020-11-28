// created by Serdyukov Dmitriy
// all copyrights are protected, although who needs it
//
// I don't want to write allocators ever again :(

#ifdef __cplusplus
extern "C" {
#endif

#include "memallocator.h"
#include <stdio.h>
#include <assert.h>

#define NULL ((void*)0)   //zero for returns
#define DIMON_NULL ((memblock_t*)0)   //zero for static use

#define FREE 1   //block status
#define	BUSY 0   //block status
#define BUSY_SPECIAL(x) (-1*x)   //block status

#define SIZE_FULL_BLOCK memgetblocksize()   //size of full block
#define SIZE_PART_BLOCK (memgetblocksize() - sizeof(int))   //size of construction at the begining

#define FREE_BLOCK_MARKER -35
	
//LIST AND HELP BLOCK STRUCTURES
typedef struct memblock_t {
	int size;
	int status;
	struct memblock_t* next;
	struct memblock_t* prev;
} memblock_t;
typedef struct {
	memblock_t* head;
	int freeSize;
	int startSize;
} memcontrol_t;


//GLOBAL VARIABLES
memcontrol_t* MemoryStart = (memcontrol_t*)0;   //for main values control
memblock_t* lastReturnedPointer;   //for more faster finding block


//SIZE FUNCTIONS
int memgetblocksize(void) {
	return sizeof(memblock_t) + sizeof(int);
}
int memgetminimumsize(void) {
	return memgetblocksize() + sizeof(memcontrol_t);
}


//HELPER FUNCTIONS 
static void SetControlSize(memblock_t* dataptr, int status) {
	assert(dataptr->size >= 0);

	int* p = (int*)((char*)dataptr + SIZE_PART_BLOCK + dataptr->size);

	switch (status) {
	case FREE:
		*p = dataptr->size;
		break;
	case BUSY:
		*p = (int)dataptr->size * (-1);
		break;
	default:
		break;
	}
}
static int SeeControlSize(memblock_t* dataptr) {
	return *((int*)((char*)dataptr + SIZE_PART_BLOCK + dataptr->size));
}
static void SetFreeBytes(void* start, void* end) {
	if (start == end)
		return;

	char* p = (char*)start;
	do {
		*p = FREE_BLOCK_MARKER;
		p++;
	} while (p != (char*)end);
}
static int IsCorrupted(void) {
	memblock_t* ptr = MemoryStart->head;
	do {
		if (ptr->status == FREE) {
			if (SeeControlSize(ptr) < 0)
				return 1;
		}
		else {
			if (SeeControlSize(ptr) > 0)
				return 1;
		}
		ptr = ptr->next;
	} while (ptr != DIMON_NULL);
	return 0;
}
static memblock_t* FindFirstSuitBlock(int size, memblock_t* lastPtr) {
	memblock_t* best = DIMON_NULL;
	memblock_t* ptrPrev = lastPtr, *ptrNext = lastPtr;
	memblock_t* temp;

	if (lastPtr == DIMON_NULL) //if something was wrong last time.. you can always start over ;) 
		lastPtr = MemoryStart->head;

	//search in both directions
	while (best == DIMON_NULL) {
		if (lastPtr->size >= size && lastPtr->status == FREE) {
			best = lastPtr;
			break;
		}
		if (ptrNext->next == DIMON_NULL && ptrPrev->prev == DIMON_NULL) {
			if (ptrNext->size >= size && ptrNext->status == FREE) {
				best = ptrNext;
				break;
			}
			else
				return DIMON_NULL;
		}

		if (ptrPrev->prev != DIMON_NULL) {
			if (ptrPrev->prev->size >= size && ptrPrev->prev->status == FREE) {
				best = ptrPrev->prev;
				break;
			}
			else
				ptrPrev = ptrPrev->prev;
		}
		if (ptrNext->next != DIMON_NULL) {
			if (ptrNext->next->size >= size && ptrNext->next->status == FREE) {
				best = ptrNext->next;
				break;
			}
			else
				ptrNext = ptrNext->next;
		}

	}

	//make everything ideal
	temp = best->next;
	if (best->size - (size + SIZE_FULL_BLOCK) > 0) {
		best->next = (memblock_t*)((char*)best + SIZE_FULL_BLOCK + size);
		best->next->prev = best;
		if (best->next == DIMON_NULL)
			best->next->next = DIMON_NULL;
		else {
			best->next->next = temp;
			if(best->next->next != DIMON_NULL) 
				best->next->next->prev = best->next;
		}
		best->next->status = FREE;
		best->next->size = best->size - (size + SIZE_FULL_BLOCK);
		SetControlSize(best->next, FREE);
		best->status = BUSY;
	}
	else {
		best->status = BUSY_SPECIAL((best->size - size));
		SetControlSize(best, BUSY);
	}

	return best;
}	


//GENERAL FUCTIONS
int meminit(void* pMemory, int size) {
	//checks
	assert(pMemory != 0);
	assert(size >= 0);
	if (size < memgetminimumsize())
		return -1;

	//put first block in memory
	memblock_t* firstBlock = (memblock_t*) (sizeof(memcontrol_t) + (char*)pMemory);
	MemoryStart = (memcontrol_t*)pMemory;

	//values filling
	MemoryStart->head = firstBlock;
	MemoryStart->freeSize = size - memgetminimumsize();
	MemoryStart->startSize = size;

	//I was fixing something with it
	lastReturnedPointer = MemoryStart->head;

	//values filling 2
	firstBlock->size = size - memgetminimumsize();
	firstBlock->status = FREE;
	firstBlock->next = DIMON_NULL;
	firstBlock->prev = DIMON_NULL;
	SetControlSize(firstBlock, FREE);
	return 0;
}
void* memalloc(int size) {
	//checks
	assert(size >= 0);
	if (IsCorrupted())
		assert(-1 > 0);
	if (MemoryStart == (memcontrol_t*)0 || MemoryStart->freeSize < size)
		return NULL;

	//finding block
	memblock_t* ptr = FindFirstSuitBlock(size, lastReturnedPointer);
	if (ptr == DIMON_NULL)
		return NULL;
	
	//freeSize changing
	if (ptr->size < (size + SIZE_FULL_BLOCK)) {
		MemoryStart->freeSize -= ptr->size;
	}
	else 
		MemoryStart->freeSize -= (size + SIZE_FULL_BLOCK);
	
	if (MemoryStart->freeSize < 0)
		MemoryStart->freeSize = 0;
	
	//two main lines
	ptr->size = size;
	SetControlSize(ptr, BUSY);

	//returns
	lastReturnedPointer = (memblock_t*)(ptr);
	return (void*)((char*)ptr + SIZE_PART_BLOCK);
}
void memfree(void* p) {
	assert(p != 0);

	memblock_t* ptr = (memblock_t*)((char*)p - SIZE_PART_BLOCK);
	int controlSize = *((int*)((char*)ptr + SIZE_PART_BLOCK + ptr->size));
	assert(controlSize <= 0);
	int sizeLeft = -1;
	int freeSize = 0;

	//if block is not full (BUSY_SPECIAL mode)
	if (ptr->status != BUSY)
		ptr->size += ptr->status * (-1);

	freeSize = ptr->size;

	//merge with left block
	if (ptr != MemoryStart->head) {
		sizeLeft = *(int*)((char*)ptr - sizeof(int));
		if (sizeLeft > 0) {
			if (lastReturnedPointer == ptr) 
				lastReturnedPointer = ptr->prev;

			ptr->prev->size += ptr->size + SIZE_FULL_BLOCK;
			ptr->prev->next = ptr->next;
			
			if (ptr->next != DIMON_NULL) {
				ptr->next->prev = ptr->prev;
			}
			ptr = ptr->prev;

			freeSize += SIZE_FULL_BLOCK;
		}
	}
	//merge with right block
	if (ptr->next != NULL && ptr->next->status == FREE) {
		if (lastReturnedPointer == ptr->next)
			lastReturnedPointer = ptr;

		ptr->size += ptr->next->size + SIZE_FULL_BLOCK;
		ptr->next = ptr->next->next;
		if (ptr->next != DIMON_NULL) {
			ptr->next->prev = ptr;
		}

		freeSize += SIZE_FULL_BLOCK;
	}

	SetControlSize(ptr, FREE);
	SetFreeBytes((char*)ptr + SIZE_PART_BLOCK, (char*)ptr + SIZE_PART_BLOCK + ptr->size);
	ptr->status = FREE;

	MemoryStart->freeSize += freeSize;
}
void memdone(void) {
	// "there won't be any leaks, either if you check them out or if you keep them hidden"
	// (C) Serdyukov Dmitriy
	SetFreeBytes(
		(void*)((char*)MemoryStart->head - sizeof(memcontrol_t)),
		(void*)((char*)MemoryStart->head - sizeof(memcontrol_t) + MemoryStart->startSize)
	);
}


#ifdef __cplusplus
}
#endif
