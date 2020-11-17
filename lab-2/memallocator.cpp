#include <stdlib.h>
#include <stdio.h>
#include "memallocator.h"

#define TRUE 1
#define FALSE 0
#define ERROR NULL
#define NOTAVAILABLE -1
#define KEY 14

typedef struct desc_t {
	int size;
	int key;
	struct desc_t* Next;
}NodeHead_t;

typedef struct end { 
	int size;
}NodeEnd_t;

NodeHead_t* freeList = NULL;
char* start = NULL;
int memSize = 0; 

int memgetminimumsize() {
	return sizeof(NodeHead_t) + sizeof(NodeEnd_t);
}

int meminit(void* pMemory, int size) {
	if (pMemory == NULL)
		return FALSE;

	start = (char*)pMemory;
	memSize = size;
	freeList = (NodeHead_t*)pMemory;
	freeList->size = size - memgetminimumsize();
	freeList->key = KEY;
	freeList->Next = NULL;
	((NodeEnd_t*)((char*)freeList + sizeof(NodeHead_t) + freeList->size))->size = freeList->size;

	return TRUE;
}

int memgetblocksize() {
	return sizeof(NodeHead_t) + sizeof(NodeEnd_t);
} 

void memdone() {
	freeList = NULL;
	memSize = 0;
	start = NULL;
}

void* memalloc(int size) {
	int bestSize = -13; // for 1 iteration 
	NodeHead_t** tmp = &freeList;
	NodeHead_t** bestPtr = NULL;
	NodeHead_t* newBlock = NULL;

	if (freeList == NULL || size <= 0)
		return ERROR;

	// find the best fit
	while ((*tmp) != NULL) {
		if ((*tmp)->size >= size && ((*tmp)->size < bestSize || bestSize == -13)) {
			bestSize = (*tmp)->size;
			bestPtr = tmp;
		}
		tmp = &(*tmp)->Next;
	}

	if (bestPtr == NULL)
		return ERROR;

	newBlock = *bestPtr;
	// delete from freeList
	if (bestSize - size <= memgetminimumsize()) {
		*bestPtr = (*bestPtr)->Next;
		newBlock->Next = NULL;
		((NodeEnd_t*)((char*)newBlock + newBlock->size + sizeof(NodeHead_t)))->size = NOTAVAILABLE;
		return (char*)newBlock + sizeof(NodeHead_t);
	}
	
	(*bestPtr) = (NodeHead_t*)(size + memgetminimumsize() + (char*)newBlock);
	(*bestPtr)->size = newBlock->size - memgetminimumsize() - size;
	(*bestPtr)->key = KEY;
	(*bestPtr)->Next = newBlock->Next;
	((NodeEnd_t*)((char*)newBlock + newBlock->size + sizeof(NodeHead_t)))->size = (*bestPtr)->size;

	newBlock->size = size;
	newBlock->key = KEY;
	newBlock->Next = NULL;
	((NodeEnd_t*)((char*)newBlock + newBlock->size + sizeof(NodeHead_t)))->size = NOTAVAILABLE;

	return (char*)newBlock + sizeof(NodeHead_t);
}

void memfree(void* p) {
	NodeHead_t* head;
	NodeEnd_t* end;  
	// for defragmentation
	NodeHead_t *prevHead, * nextHead, *tmp;
	NodeEnd_t *prevEnd, *nextEnd;

	if (p == NULL || (char*)p < (char*)start || (char*)p >= (char*)start + memSize)
		return;

	head = (NodeHead_t*)((char*)p - sizeof(NodeHead_t));
	if (head->key != KEY)
		return;
	end = (NodeEnd_t*)((char*)p + head->size);
	
	// try to unite with left block 
	prevEnd = (NodeEnd_t*)((char*)p - memgetblocksize());
	prevHead = (NodeHead_t*)((char*)p - memgetblocksize() - prevEnd->size - sizeof(NodeHead_t));
	if ((char*)prevEnd < (char*)start || prevEnd->size == NOTAVAILABLE) {
		head->Next = freeList;
		end->size = head->size;
		freeList = head;
	}
	else {
		prevHead->size = head->size + prevHead->size + memgetblocksize();
		end->size = prevHead->size;
		head = prevHead;
	}

	//try to unite with right block
	nextHead = (NodeHead_t*)((char*)end + sizeof(NodeEnd_t));
	nextEnd = (NodeEnd_t*)((char*)nextHead + nextHead->size + sizeof(NodeHead_t));
	if ((char*)nextHead >= (char*)(start + memSize) || nextHead->key != KEY)
		return;

	if (nextEnd->size != NOTAVAILABLE) {
		head->size = nextHead->size + head->size + memgetblocksize();
		nextHead->key = FALSE;
		nextEnd->size = head->size;
		tmp = &freeList;
		while (*tmp != NULL && (*tmp) != nextHead) {
			tmp = &(*tmp)->Next;
		}

		if (*tmp == nextHead) {
			*tmp = (*tmp)->Next;
		}
	}
}



