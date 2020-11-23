#include <stdio.h>
#include <malloc.h>
#include "memallocator.h"

#define MEMORY_INITIALIZE_SUCCESS 1
#define MEMORY_INITIALIZE_FAILED -1
#define COULD_NOT_FIND_SUITABLE_BLOCK NULL

typedef enum
{
	FALSE,
	TRUE
} Bool;

typedef struct list
{
	int blockSize;
	struct list* nextBlock;
} LIST;

Bool memInitialized = FALSE;
LIST* systemBlocks;
LIST* firstBlock;
void* endBlock;

int memgetminimumsize()
{
	return sizeof(LIST) + sizeof(int);
}

int memgetblocksize()
{
	return sizeof(LIST) + sizeof(int);
}

int meminit(void* pMemory, int size)
{
	int minSize = memgetminimumsize()
		, blockSize = memgetblocksize();
	int* endDescriptor;

	if (size < minSize || pMemory == NULL || memInitialized == TRUE)
	{
		return MEMORY_INITIALIZE_FAILED;
	}
	systemBlocks = (LIST*)pMemory;
	systemBlocks->nextBlock = NULL;
	systemBlocks->blockSize = size - blockSize;
	memInitialized = TRUE;
	endDescriptor = (int*)((char*)pMemory + size - sizeof(int));
	*endDescriptor = -systemBlocks->blockSize;
	firstBlock = systemBlocks;
	endBlock = (void*)((char*)pMemory + size);

	return MEMORY_INITIALIZE_SUCCESS;
}

void* memalloc(int size)
{
	int* endDescriptor;
	LIST* suitableBlock = systemBlocks,
		* previousBlock = NULL;
	int blockSize = memgetblocksize();
	if (memInitialized == FALSE || size <= 0)
	{
		return NULL;
	}
	while (suitableBlock != NULL)
	{
		if (suitableBlock->blockSize >= size)
		{
			break;
		}
		previousBlock = suitableBlock;
		suitableBlock = suitableBlock->nextBlock;
	}
	if (suitableBlock == NULL)
	{
		return NULL;
	}
	if (suitableBlock->blockSize >= blockSize + size)
	{
		if (previousBlock == NULL)
		{
			systemBlocks = (LIST*)((char*)suitableBlock + size + blockSize);
			systemBlocks->nextBlock = suitableBlock->nextBlock;
			systemBlocks->blockSize = suitableBlock->blockSize - size - blockSize;
			endDescriptor = (int*)((char*)systemBlocks + blockSize + systemBlocks->blockSize - sizeof(int));
			*endDescriptor = -systemBlocks->blockSize;
		}
		else
		{
			previousBlock->nextBlock = (LIST*)((char*)suitableBlock + size + blockSize);
			previousBlock->nextBlock->nextBlock = suitableBlock->nextBlock;
			previousBlock->nextBlock->blockSize = suitableBlock->blockSize - size - blockSize;
			endDescriptor = (int*)((char*)previousBlock->nextBlock + blockSize + previousBlock->nextBlock->blockSize - sizeof(int));
			*endDescriptor = -previousBlock->nextBlock->blockSize;
		}
		suitableBlock->blockSize = size;
		endDescriptor = (int*)((char*)suitableBlock + blockSize + size - sizeof(int));
		*endDescriptor = size;
	}
	else
	{
		endDescriptor = (int*)((char*)suitableBlock + suitableBlock->blockSize + sizeof(LIST));
		*endDescriptor = suitableBlock->blockSize;
		if (previousBlock == NULL)
		{
			systemBlocks = suitableBlock->nextBlock;
		}
		else
		{
			previousBlock->nextBlock = suitableBlock->nextBlock;
		}
	}
	suitableBlock->nextBlock = NULL;
	return (void*)((char*)suitableBlock + sizeof(LIST));
}

void memfree(void* p)
{
	int* leftEndDescriptor,
	   * rightEndDescriptor,
	   * endDescriptor;
	int blockSize = memgetblocksize();
	LIST* newFreeBlock,
		* rightBlock,
		* leftBlock;
	LIST* tmp;
	if (p == NULL)
	{
		return;
	}
	newFreeBlock = (LIST*)((char*)p - sizeof(LIST));
	newFreeBlock->nextBlock = systemBlocks;
	systemBlocks = newFreeBlock;
	endDescriptor = (int*)((char*)newFreeBlock + sizeof(LIST) + newFreeBlock->blockSize);
	*endDescriptor = -newFreeBlock->blockSize;

	if (newFreeBlock == firstBlock)
	{
		leftEndDescriptor = NULL;
	}
	else
	{
		leftEndDescriptor = (int*)((char*)newFreeBlock - sizeof(int));
	}
	if ((void*)((char*)newFreeBlock + newFreeBlock->blockSize + blockSize) == endBlock)
	{
		rightEndDescriptor = NULL;
	}
	else
	{
		rightEndDescriptor = (int*)((char*)newFreeBlock + newFreeBlock->blockSize + blockSize);
		rightEndDescriptor = (int*)((char*)rightEndDescriptor + ((LIST*)rightEndDescriptor)->blockSize + sizeof(LIST));
	}
	if (leftEndDescriptor != NULL && *leftEndDescriptor <= 0)
	{
		leftBlock = (LIST*)((char*)newFreeBlock - blockSize + *leftEndDescriptor);
		leftBlock->blockSize += (newFreeBlock->blockSize + blockSize);
		tmp = systemBlocks;
		while (tmp != NULL)
		{
			if (tmp->nextBlock == leftBlock)
			{
				break;
			}
			tmp = tmp->nextBlock;
		}
		if (tmp == NULL)
		{
			return;
		}
		tmp->nextBlock = leftBlock->nextBlock;
		leftBlock->nextBlock = systemBlocks->nextBlock;
		systemBlocks = leftBlock;
		newFreeBlock = systemBlocks;
		endDescriptor = (int*)((char*)leftBlock + sizeof(LIST) + leftBlock->blockSize);
		*endDescriptor = -leftBlock->blockSize;
	}
	if (rightEndDescriptor != NULL && *rightEndDescriptor <= 0)
	{
		rightBlock = (LIST*)((char*)rightEndDescriptor + *rightEndDescriptor - sizeof(LIST));
		tmp = systemBlocks;
		while (tmp != NULL)
		{
			if (tmp->nextBlock == rightBlock)
			{
				break;
			}
			tmp = tmp->nextBlock;
		}
		if (tmp == NULL)
		{
			return;
		}
		tmp->nextBlock = rightBlock->nextBlock;
		newFreeBlock->blockSize += (rightBlock->blockSize + blockSize);
		endDescriptor = (int*)((char*)newFreeBlock + sizeof(LIST) + newFreeBlock->blockSize);
		*endDescriptor = -newFreeBlock->blockSize;
	}
}

void memdone()
{
	memInitialized = FALSE;
	systemBlocks = NULL;
	firstBlock = NULL;
	endBlock = NULL;
}
