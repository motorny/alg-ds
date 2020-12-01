#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>


char* memory = NULL;
int memSize = 0;

#define ALL_IS_OK 0
#define KEY 777
#define NULL_MEM 2
#define TOO_SMALL_SIZE 3


typedef struct NodeHeader {
	int size;
	int num; // for checking validness of pointer
	struct NodeHeader* next;
} nodeHeader_t;

typedef struct NodeEnder {
	int size;
} nodeEnder_t;

nodeHeader_t* theFirst;

int memgetminimumsize() {
	return sizeof(nodeHeader_t) + sizeof(nodeEnder_t);
}

int memgetblocksize() {
	return sizeof(nodeHeader_t) + sizeof(nodeEnder_t);
}



int meminit(void* pMemory, int size) {
	if (pMemory == NULL) {
		return NULL_MEM;
	}
	if (size < memgetminimumsize()) {
		return TOO_SMALL_SIZE;
	}

	memory = (char*)pMemory;
	memSize = size;

	theFirst = (nodeHeader_t*)memory;
	theFirst->size = memSize - memgetminimumsize();
	theFirst->next = NULL;
	theFirst->num = 88;
	((nodeEnder_t*)((char*)theFirst + sizeof(nodeHeader_t) + theFirst->size))->size = theFirst->size;
	return ALL_IS_OK;
}

void* memalloc(int size) {
	if (memory == NULL || size <= 0)
		return NULL;
	nodeHeader_t** tmp = &theFirst;
	nodeHeader_t* newBlock = NULL;
	nodeHeader_t** ptr = NULL;
	int minSize = -1, blockSize;
	while ((*tmp) != NULL) {
		if (((*tmp)->size >= size) && ((minSize == -1) || ((*tmp)->size < minSize))) {
			ptr = tmp;
			minSize = (*tmp)->size;
		}
		tmp = &(*tmp)->next;


	}
	
	if (ptr == NULL)
		
		return NULL;
	blockSize = (*ptr)->size;
	newBlock = (*ptr);	
	
	newBlock->num = KEY;	
	if (minSize <= size + memgetminimumsize()) {
		(*ptr) = (*ptr)->next;
		newBlock->next = NULL;
		((nodeEnder_t*)((char*)newBlock + newBlock->size + sizeof(nodeHeader_t)))->size = -1;
		return (char*)newBlock + sizeof(nodeHeader_t);
	}

	(*ptr) = (nodeHeader_t*)(size + memgetminimumsize() + (char*)newBlock);
	(*ptr)->size = blockSize - memgetminimumsize() - size;
	(*ptr)->num = KEY;
	(*ptr)->next = newBlock->next;
	((nodeEnder_t*)((char*)newBlock + newBlock->size + sizeof(nodeHeader_t)))->size = (*ptr)->size;

	newBlock->size = size;
	newBlock->num = KEY;
	newBlock->next = NULL;
	((nodeEnder_t*)((char*)newBlock + newBlock->size + sizeof(nodeHeader_t)))->size = -1;

	return (char*)newBlock + sizeof(nodeHeader_t);
}

void memfree(void* p) {
	nodeHeader_t* head;
	nodeEnder_t* end;
	nodeHeader_t* prevHead, * nextHead, ** tmp;
	nodeEnder_t* prevEnd, * nextEnd;

	if (p == NULL || (char*)p < (char*)memory || (char*)p >= (char*)memory + memSize)
		return;

	head = (nodeHeader_t*)((char*)p - sizeof(nodeHeader_t));
	if (head->num != KEY)
		return;
	end = (nodeEnder_t*)((char*)p + head->size);

	prevEnd = (nodeEnder_t*)((char*)p - memgetminimumsize());
	prevHead = (nodeHeader_t*)((char*)p - memgetminimumsize() - prevEnd->size - sizeof(nodeHeader_t));
	if ((char*)prevEnd < (char*)memory || prevEnd->size == -1) {
		head->next = theFirst;
		end->size = head->size;
		theFirst = head;
	}
	else {
		prevHead->size = head->size + prevHead->size + memgetminimumsize();
		end->size = prevHead->size;
		head = prevHead;
	}

	nextHead = (nodeHeader_t*)((char*)end + sizeof(nodeEnder_t));
	nextEnd = (nodeEnder_t*)((char*)nextHead + nextHead->size + sizeof(nodeHeader_t));
	if ((char*)nextHead >= (char*)(memory + memSize) || nextHead->num != KEY)
		return;

	if (nextEnd->size != -1) {
		head->size = nextHead->size + head->size + memgetminimumsize();
		nextHead->num = -1;
		nextEnd->size = head->size;
		tmp = &theFirst;
		while (*tmp != NULL && (*tmp) != nextHead) {
			tmp = &(*tmp)->next;
		}

		if (*tmp == nextHead) {
			*tmp = (*tmp)->next;
		}
	}
}
void memdone()
{
	theFirst = NULL;
	memSize = 0;
	memory = NULL;
}


