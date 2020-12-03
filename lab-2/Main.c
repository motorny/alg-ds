#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "memallocator.h"

#define MEMORY_SIZE 1000

int main(void) {
	int i = 0;
	int blockSize = MEMORY_SIZE + memgetminimumsize() + (MEMORY_SIZE - 1) * memgetblocksize();
	char* memoryBlock = (char*)malloc(blockSize);
	LARGE_INTEGER freq;
	LARGE_INTEGER tcountBefore, tcountAfter;
	char** arrPtr = malloc(MEMORY_SIZE * sizeof(char*));
	QueryPerformanceFrequency(&freq);
	if (!memoryBlock || !arrPtr)
		return 1;

	meminit(memoryBlock, blockSize);
	
	//default memory manager
	QueryPerformanceCounter(&tcountBefore);
	for (i = 0; i < MEMORY_SIZE; i++) {
		arrPtr[i] = (char*)malloc(1);
	}
	QueryPerformanceCounter(&tcountAfter);
	printf("Time to allocate %d bytes that needed by default function: %.10f\n", MEMORY_SIZE, ((double)tcountAfter.QuadPart - (double)tcountBefore.QuadPart) / (double)freq.QuadPart);

	QueryPerformanceCounter(&tcountBefore);
	for (i = 0; i < MEMORY_SIZE; i++) {
		free(arrPtr[i]);
	}
	QueryPerformanceCounter(&tcountAfter);
	printf("Time to free %d bytes that needed by default function: %.10f\n", MEMORY_SIZE, ((double)tcountAfter.QuadPart - (double)tcountBefore.QuadPart) / (double)freq.QuadPart);
	

	//my memory manager
	meminit(memoryBlock, blockSize);
	QueryPerformanceCounter(&tcountBefore);
	for (i = 0; i < MEMORY_SIZE; i++) {
		arrPtr[i] = (char*)memalloc(1);
	}
	QueryPerformanceCounter(&tcountAfter);
	printf("Time to allocate %d bytes that needed by my memory manager: %.10f\n", MEMORY_SIZE, ((double)tcountAfter.QuadPart - (double)tcountBefore.QuadPart) / (double)freq.QuadPart);

	QueryPerformanceCounter(&tcountBefore);
	for (i = 0; i < MEMORY_SIZE; i++) {
		memfree(arrPtr[i]);
	}
	QueryPerformanceCounter(&tcountAfter);
	printf("Time to free %d bytes that needed by my memory manager: %.10f\n", MEMORY_SIZE, ((double)tcountAfter.QuadPart - (double)tcountBefore.QuadPart) / (double)freq.QuadPart);
	memdone();

	free(arrPtr);
	free(memoryBlock);
	return 0;
}