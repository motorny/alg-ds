#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "memallocator.h"

#define NUM_OF_MEM_ELEMS 5000

int main(void) {
	int i;
	const int memorySize = NUM_OF_MEM_ELEMS + memgetminimumsize() + (NUM_OF_MEM_ELEMS - 1) * memgetblocksize();
	LARGE_INTEGER timeBefore, timeAfter, freq;
	char* Memory = (char*)malloc(memorySize);
	char** ptr = (char**)malloc(NUM_OF_MEM_ELEMS * sizeof(char*));
	if (Memory == NULL || ptr == NULL)
		return 1;

	QueryPerformanceFrequency(&freq);

	//my memory manager
	meminit(Memory, memorySize);

	QueryPerformanceCounter(&timeBefore);
	for (i = 0; i < NUM_OF_MEM_ELEMS; i++) {
		ptr[i] = (char*) memalloc(1);
	}
	QueryPerformanceCounter(&timeAfter);
	printf("Time required by my memory manager for %i allocations: %lf\n", (int)NUM_OF_MEM_ELEMS, ((double)timeAfter.QuadPart - (double)timeBefore.QuadPart) / (double)freq.QuadPart);

	QueryPerformanceCounter(&timeBefore);
	for (i = 0; i < NUM_OF_MEM_ELEMS; i++) {
		memfree(ptr[i]);
	}
	QueryPerformanceCounter(&timeAfter);
	printf("Time required by my memory manager for %i free: %lf\n", (int)NUM_OF_MEM_ELEMS, ((double)timeAfter.QuadPart - (double)timeBefore.QuadPart) / (double)freq.QuadPart);

	memdone();

	//default functions
	QueryPerformanceCounter(&timeBefore);
	for (i = 0; i < NUM_OF_MEM_ELEMS; i++) {
		ptr[i] = (char*)malloc(1);
	}
	QueryPerformanceCounter(&timeAfter);
	printf("Time required by defaul function for %i allocations: %lf\n", (int)NUM_OF_MEM_ELEMS, ((double)timeAfter.QuadPart - (double)timeBefore.QuadPart) / (double)freq.QuadPart);

	QueryPerformanceCounter(&timeBefore);
	for (i = 0; i < NUM_OF_MEM_ELEMS; i++) {
		free(ptr[i]);
	}
	QueryPerformanceCounter(&timeAfter);
	printf("Time required by defaul function for %i free: %lf\n", (int)NUM_OF_MEM_ELEMS, ((double)timeAfter.QuadPart - (double)timeBefore.QuadPart) / (double)freq.QuadPart);


	free(ptr);
	free(Memory);
	return 0;
}