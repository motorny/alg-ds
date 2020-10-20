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
void* firstPointer;
void* endPointer;
int amountOfUsedMemory = 0;

int memgetminimumsize()
{
	return 2 * (sizeof(LIST) + sizeof(int));
}

int memgetblocksize()
{
	return sizeof(LIST) + sizeof(int);
}

int meminit(void* pMemory, int size)
{
	int minSizeBlock = memgetminimumsize()
		, descriptorBlockSize = memgetblocksize();
	int* endDescriptor;
	if (size < minSizeBlock || pMemory == NULL || memInitialized == TRUE)
	{
		return MEMORY_INITIALIZE_FAILED;
	}
	systemBlocks = (LIST*)((char*)pMemory + sizeof(LIST));
	memInitialized = TRUE;
	systemBlocks->nextBlock = NULL;
	systemBlocks->blockSize = size - descriptorBlockSize;
	firstPointer = (void*)((char*)pMemory + sizeof(LIST));
	endPointer = (void*)((char*)pMemory + size);
	endDescriptor = (int*)((char*)pMemory + size - sizeof(int));
	*endDescriptor = -size;

	return MEMORY_INITIALIZE_SUCCESS;
}

void* memalloc(int size)
{
	int* endDescriptor;
	int descriptorBlockSize = memgetblocksize();
	LIST* suitableBlock = systemBlocks
		, * previousBlock = NULL
		, * tempList;

	if (memInitialized == FALSE || size <= 0)
	{
		return NULL;
	}

	while (suitableBlock != NULL)
	{
		if (suitableBlock->blockSize >= size + descriptorBlockSize)
		{
			break;
		}
		previousBlock = suitableBlock;
		suitableBlock = suitableBlock->nextBlock;
	}

	if (suitableBlock == NULL)
	{
		return COULD_NOT_FIND_SUITABLE_BLOCK;
	}

	if (suitableBlock->blockSize >= size + 2 * descriptorBlockSize)
	{
		
		if (previousBlock != NULL)
		{
			previousBlock->nextBlock = (LIST*)((char*)suitableBlock + size + descriptorBlockSize);
			previousBlock->nextBlock->blockSize = suitableBlock->blockSize - size - descriptorBlockSize;
			previousBlock->nextBlock->nextBlock = suitableBlock->nextBlock;
		}
		else
		{
			tempList = systemBlocks;
			systemBlocks = (LIST*)((char*)suitableBlock + size + descriptorBlockSize);
			systemBlocks->blockSize = suitableBlock->blockSize - size - descriptorBlockSize;
			systemBlocks->nextBlock = tempList->nextBlock;
			endDescriptor = (int*)((char*)systemBlocks + systemBlocks->blockSize - sizeof(int));
			*endDescriptor = -(systemBlocks->blockSize);
		}
		suitableBlock->blockSize = size + descriptorBlockSize;
		endDescriptor = (int*)((char*)suitableBlock + size + descriptorBlockSize - sizeof(int));
		*endDescriptor = size + descriptorBlockSize;
	}
	else
	{
		endDescriptor = (int*)((char*)suitableBlock + suitableBlock->blockSize - sizeof(int));
		*endDescriptor = suitableBlock->blockSize;
		if (previousBlock != NULL)
		{
			previousBlock->nextBlock = suitableBlock->nextBlock;
		}
		else
		{
			systemBlocks = suitableBlock->nextBlock;
		}
	}
	amountOfUsedMemory += suitableBlock->blockSize;
	return (void*)((char*)suitableBlock + sizeof(LIST));
}

void memfree(void* pBlock)
{
	int* leftBlockEndDescriptor
		, * rightBlockEndDescriptor
		, * endDescriptor;
	int descriptorBlockSize = memgetblocksize()
		, tmp = 0;
	LIST* newFreeBlock
		, * leftBlock
		, * rightBlock
		, * tempList;

	if (pBlock == NULL)
	{
		return;
	}
	
	newFreeBlock = (LIST*)((char*)pBlock - sizeof(LIST));
	newFreeBlock->nextBlock = systemBlocks;
	systemBlocks = newFreeBlock;
	amountOfUsedMemory -= newFreeBlock->blockSize;
	endDescriptor = (int*)((char*)newFreeBlock + newFreeBlock->blockSize - sizeof(int));
	*endDescriptor = -newFreeBlock->blockSize;

	if (newFreeBlock == firstPointer)
	{
		leftBlockEndDescriptor = NULL;
	}
	else
	{
		leftBlockEndDescriptor = (int*)((char*)newFreeBlock - sizeof(int));
	}
	if ((void*)((char*)newFreeBlock + newFreeBlock->blockSize) == endPointer)
	{
		rightBlockEndDescriptor = NULL;
	}
	else
	{
		rightBlockEndDescriptor = (int*)((char*)newFreeBlock + newFreeBlock->blockSize);
		rightBlockEndDescriptor = (int*)((char*)rightBlockEndDescriptor + ((LIST*)rightBlockEndDescriptor)->blockSize - sizeof(int));
	}
	if (leftBlockEndDescriptor != NULL && *leftBlockEndDescriptor < 0)
	{
		leftBlock = (LIST*)((char*)leftBlockEndDescriptor + sizeof(int) + *leftBlockEndDescriptor);
		tempList = systemBlocks;
		while (tempList != NULL)
		{
			if (tempList->nextBlock == leftBlock)
			{
				break;
			}
			tempList = tempList->nextBlock;
		}
		if (tempList == NULL)
		{
			return;
		}
		tempList->nextBlock = leftBlock->nextBlock;
		leftBlock->blockSize += newFreeBlock->blockSize;
		leftBlock->nextBlock = systemBlocks->nextBlock;
		systemBlocks = leftBlock;
		newFreeBlock = systemBlocks;
		endDescriptor = (int*)((char*)leftBlock + leftBlock->blockSize - sizeof(int));
		*endDescriptor = -leftBlock->blockSize;
	}
	if (rightBlockEndDescriptor != NULL && *rightBlockEndDescriptor < 0)
	{
		rightBlock = (LIST*)((char*)rightBlockEndDescriptor + sizeof(int) + *rightBlockEndDescriptor);
		tempList = systemBlocks;
		while (tempList != NULL)
		{
			if (tempList->nextBlock == rightBlock)
			{
				break;
			}
			tempList = tempList->nextBlock;
		}
		if (tempList == NULL)
		{
			return;
		}
		tempList->nextBlock = rightBlock->nextBlock;
		newFreeBlock->blockSize += rightBlock->blockSize;
		endDescriptor = (int*)((char*)newFreeBlock + newFreeBlock->blockSize - sizeof(int));
		*endDescriptor = -newFreeBlock->blockSize;
	}
}

void memdone()
{
	if (amountOfUsedMemory != 0)
	{

	}
	systemBlocks = NULL;
	firstPointer = NULL;
	memInitialized = FALSE;
}
