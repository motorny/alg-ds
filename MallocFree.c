#include <stdio.h>
#include <malloc.h>
#include"memallocator.h"

#define InitYes 0
#define InitNo 1

typedef struct block
{
	int size;
	struct block* next;
}block;


block* Blocks;
void* head;
void* tail;
int size;


int memgetblocksize()
{
	return sizeof(block) + sizeof(int);
}

int memgetminimumsize()
{
	return sizeof(block) + sizeof(int);
}

int meminit(void* pMemory, int size)
{

	int* descriptor;

	if (size < memgetminimumsize() || pMemory == NULL)
	{
		return  InitNo;
	}
	Blocks = (block*)pMemory;
	Blocks->next = NULL;
	Blocks->size = size - memgetblocksize();
	head = pMemory;
	tail = (void*)((char*)pMemory + size);
	descriptor = (int*)((char*)pMemory + size - sizeof(int));
	*descriptor = -(size - memgetblocksize());


	return  InitYes;
}

void* memalloc(int size)
{
	int* descriptor;
	block* neededBlock = Blocks;
	block* previousBlock = NULL;
	block* newBlock;
	void* pAllocated = NULL;

	if (size <= 0)
	{
		return NULL;
	}

	while (neededBlock != NULL)
	{
		if (neededBlock->size >= size)
		{
			break;
		}
		previousBlock = neededBlock;
		neededBlock = neededBlock->next;
	}

	if (neededBlock == NULL)
	{
		return NULL;
	}

	pAllocated = (char*)neededBlock + sizeof(block);

	if (neededBlock->size >= size + memgetblocksize())
	{

		if (previousBlock != NULL)
		{
			previousBlock->next = (block*)((char*)neededBlock + size + memgetblocksize());
			previousBlock->next->size = neededBlock->size - size - memgetblocksize();
			previousBlock->next->next = neededBlock->next;
			descriptor = (int*)((char*)previousBlock->next + previousBlock->next->size + memgetblocksize() - sizeof(int));
			*descriptor = -(previousBlock->next->size);
		}
		else
		{
			newBlock = (block*)((char*)neededBlock + size + memgetblocksize());
			newBlock->size = neededBlock->size - size - memgetblocksize();
			newBlock->next = Blocks->next;
			Blocks = newBlock;
			descriptor = (int*)((char*)newBlock + newBlock->size + memgetblocksize() - sizeof(int));
			*descriptor = -(newBlock->size);
		}
		neededBlock->size = size;
		descriptor = (int*)((char*)neededBlock + size + memgetblocksize() - sizeof(int));
		*descriptor = size;


	}


	else
	{
		descriptor = (int*)((char*)neededBlock + neededBlock->size + sizeof(block));
		*descriptor = neededBlock->size;
		if (previousBlock == NULL)
		{
			newBlock = neededBlock->next;
			Blocks = newBlock;
		}
		else
		{
			previousBlock->next = neededBlock->next;
		}
	}

	neededBlock->next = NULL;
	return pAllocated;
}

void memfree(void* pBlock)
{
	int* ldescriptor;
	int* rdescriptor;
	int* descriptor;
	block* newBlock;
	block* leftBlock;
	block* rightBlock;
	block* tempBlock;


	if (pBlock == NULL)
	{
		return;
	}
	newBlock = (block*)((char*)pBlock - sizeof(block));
	newBlock->next = Blocks;
	Blocks = newBlock;
	descriptor = (int*)((char*)newBlock + newBlock->size + sizeof(block));
	*descriptor = -newBlock->size;


	if (newBlock == head)
	{
		ldescriptor = NULL;
	}
	else {
		ldescriptor = (int*)((char*)newBlock - sizeof(int));
	}

	if ((void*)((char*)newBlock + newBlock->size + memgetblocksize()) == tail)
	{
		rdescriptor = NULL;
	}
	else {
		rdescriptor = (int*)((char*)newBlock + newBlock->size + memgetblocksize());
		rdescriptor = (int*)((char*)rdescriptor + ((block*)rdescriptor)->size + sizeof(block));
	}


	if (ldescriptor != NULL && *ldescriptor <= 0)
	{
		leftBlock = (block*)((char*)newBlock - memgetblocksize() + *ldescriptor);
		tempBlock = Blocks;
		while (tempBlock != NULL)
		{
			if (tempBlock->next == leftBlock)
			{
				break;
			}
			tempBlock = tempBlock->next;
		}
		if (tempBlock != NULL)
		{
			leftBlock->size += (newBlock->size + memgetblocksize());
			tempBlock->next = leftBlock->next;
			leftBlock->next = Blocks->next;
			Blocks = leftBlock;
			newBlock = Blocks;
			descriptor = (int*)((char*)leftBlock + leftBlock->size + sizeof(block));
			*descriptor = -leftBlock->size;
		}
		else {
			return;
		}
	}

	if (rdescriptor != NULL && *rdescriptor <= 0)
	{
		rightBlock = (block*)((char*)rdescriptor - sizeof(block) + *rdescriptor);
		tempBlock = Blocks;
		while (tempBlock != NULL)
		{
			if (tempBlock->next == rightBlock)
			{
				break;
			}
			tempBlock = tempBlock->next;
		}
		if (tempBlock != NULL)
		{
			tempBlock->next = rightBlock->next;
			newBlock->size += (rightBlock->size + memgetblocksize());
			descriptor = (int*)((char*)newBlock + newBlock->size + sizeof(block));
			*descriptor = -newBlock->size;

		}
		else {
			return;
		}

	}
}



void memdone()
{
	head = NULL;
	size = 0;
	Blocks = NULL;
	tail = NULL;
}


