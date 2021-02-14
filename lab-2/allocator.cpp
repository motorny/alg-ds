#include <stdio.h>
#include <stdlib.h>
#include "memallocator.h"

#define NULL_INPUT 1
#define NOT_ENOUGHT_SIZE 2
#define CHECK_NUMBER 1747

char* memory = NULL;
int memsize = 0;

typedef struct Head {
	int size;
	int check;
	struct Head* next;
}Head;

typedef struct {
	int size;
}End;

Head* firstHead = NULL;

int memgetminimumsize() {
	return (sizeof(Head) + sizeof(End));
}

int memgetblocksize() {
	return (sizeof(Head) + sizeof(End));
}


int meminit(void* pMemory, int size) {
	if (!pMemory) {
		return NULL_INPUT;
	}
	if (size <= memgetblocksize()) {
		return NOT_ENOUGHT_SIZE;
	}

	memory = (char*)pMemory;
	memsize = size;

	firstHead = (Head*)pMemory;
	firstHead->size = size - memgetminimumsize();
	firstHead->next = NULL;
	((End*)((char*)firstHead + sizeof(Head) + firstHead->size))->size = firstHead->size;

	return 0;
}

void* memalloc(int size) {
	Head** tmp = &firstHead;
	Head** currentNodeHead = NULL;
	Head* newNode = NULL;
	int i = 0;

	if (memory == NULL || size + memgetminimumsize() > memsize || size < 0) {
		return NULL;
	}

	while (*tmp) {
		if ((*tmp)->size >= size) {
			currentNodeHead = tmp;
			i++;
			if (i == 2) {
				break;
			}
		}
		tmp = &(*tmp)->next;
	}

	if (currentNodeHead == NULL) {
		return NULL;
	}

	newNode = *currentNodeHead;

	if (newNode->size <= size + memgetminimumsize()) {
		*currentNodeHead = (*currentNodeHead)->next;
		((End*)((char*)newNode + newNode->size + sizeof(Head)))->size = -1;
		newNode->next = NULL;
		newNode->check = CHECK_NUMBER;
		return (char*)newNode + sizeof(Head);
	}

	(*currentNodeHead) = (Head*)((char*)newNode + memgetminimumsize() + size);
	(*currentNodeHead)->size = newNode->size - memgetminimumsize() - size;
	(*currentNodeHead)->next = newNode->next;
	((End*)((char*)newNode + newNode->size + sizeof(Head)))->size = (*currentNodeHead)->size;

	newNode->size = size;
	newNode->next = NULL;
	newNode->check = CHECK_NUMBER;
	((End*)((char*)newNode + newNode->size + sizeof(Head)))->size = -1;

	return (char*)newNode + sizeof(Head);
}

void memfree(void* p) {
	Head* currentNodeHead = (Head*)((char*)p - sizeof(Head));
	Head* head = NULL;
	End* end = NULL;
	Head** tmp = NULL;
	int checkOnUni = 0;

	if (p == NULL || memory == NULL) {
		return;
	}
	if (((char*)p + sizeof(End) > (char*)memory + memsize) || (char*)p - sizeof(Head) < memory) {
		return;
	}
	if (currentNodeHead->check != CHECK_NUMBER) {
		return;
	}
	if (((End*)((char*)currentNodeHead + currentNodeHead->size + sizeof(Head)))->size > 0) {
		return;
	}

	end = (End*)((char*)currentNodeHead - sizeof(End));

	if (end->size != -1 && (char*)end > memory) {
		head = (Head*)((char*)end - end->size - sizeof(Head));
		if ((char*)head >= memory) {
			head->size = head->size + currentNodeHead->size + memgetminimumsize();
			currentNodeHead->check = 0;
			((End*)((char*)head + head->size + sizeof(Head)))->size = head->size;
			currentNodeHead = head;
			checkOnUni = 1;
		}
	}

	head = (Head*)((char*)currentNodeHead + currentNodeHead->size + memgetminimumsize());

	if ((char*)head - memsize < memory) {
		end = (End*)((char*)head + head->size + sizeof(Head));
		if (end->size != -1 && (char*)end - memsize < memory) {
			currentNodeHead->size = currentNodeHead->size + head->size + memgetminimumsize();
			end->size = currentNodeHead->size;

			tmp = &firstHead;
			while ((*tmp) != NULL && (*tmp) != head) {
				tmp = &(*tmp)->next;
			}
			*tmp = currentNodeHead;

			if (checkOnUni) {
				if (head->next != currentNodeHead) {
					if (currentNodeHead->next == head) {
						currentNodeHead->next = head->next;
					}
					else {
						*tmp = head->next;
					}
				}
			}
			else {
				currentNodeHead->next = head->next;
			}
			checkOnUni = 1;
		}
	}

	if (checkOnUni) {
		return;
	}
	else {
		currentNodeHead->next = firstHead;
		firstHead = currentNodeHead;
		((End*)((char*)currentNodeHead + currentNodeHead->size + sizeof(Head)))->size = currentNodeHead->size;
	}
}

void memdone() {
	memory = NULL;
	memsize = 0;
}
