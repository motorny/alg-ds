#include "StackArr.h"
#include "StackList.h"
#include <stdio.h>
#include <assert.h>
#include <Windows.h>

void CompareTime(stackArr_t* stackA, stackList_t* stackL, int iterations) {
	int i;
	double timeA_Push, timeL_Push, timeA_Pop, timeL_Pop;
	LARGE_INTEGER t1, t2, fr;
	assert(stackA);
	assert(stackL);
	QueryPerformanceFrequency(&fr);

	QueryPerformanceCounter(&t1);
	for (i = 0; i < iterations; i++) {
		PushArr(stackA, 1);
	}
	QueryPerformanceCounter(&t2);
	timeA_Push = (double)(t2.QuadPart - t1.QuadPart);
	
	QueryPerformanceCounter(&t1);
	for (i = 0; i < iterations; i++) {
		PushList(stackL, 1);
	}
	QueryPerformanceCounter(&t2);
	timeL_Push = (double)(t2.QuadPart - t1.QuadPart);

	QueryPerformanceCounter(&t1);
	for (i = 0; i < iterations; i++) {
		PopArr(stackA);
	}
	QueryPerformanceCounter(&t2);
	timeA_Pop = (double)(t2.QuadPart - t1.QuadPart);

	QueryPerformanceCounter(&t1);
	for (i = 0; i < iterations; i++) {
		PopList(stackL);
	}
	QueryPerformanceCounter(&t2);
	timeL_Pop = (double)(t2.QuadPart - t1.QuadPart);

	printf("Time for %d iterations:\n", iterations);
	printf("Pust to array - %g, push to list - %g\n", timeA_Push, timeL_Push);
	printf("Pop from array - %g, pop from list - %g\n", timeA_Pop, timeL_Pop);
}

int main(void) {
	stackArr_t* stackA = CreateStackArr();
	stackList_t* stackL = CreateStackList();
	CompareTime(stackA, stackL, 1000);
	DestroyStackArr(stackA);
	DestroyStackList(stackL);
	return 0;
}