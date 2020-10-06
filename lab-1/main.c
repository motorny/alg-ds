#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define _CRTDBG_MAP_ALLOC 
#ifdef _CRTDBG_MAP_ALLOC 
#include <crtdbg.h> 
#endif

double* CompareStack(void) { // sry for copy & paste
	int i = 0, N = 1000;
	double* time = (double*)malloc(4*sizeof(double)), buf;
	stackList_t* head;
	stack_t* stack = CreateStack(1);
	LARGE_INTEGER freq;
	LARGE_INTEGER count, count1;
	QueryPerformanceCounter(&count);
	QueryPerformanceFrequency(&freq);
	for (i = 0; i < N; i++) {
		Push(stack, i);
	}
	QueryPerformanceCounter(&count1);
	time[0] = ((double)count1.QuadPart - (double)count.QuadPart) / (double)freq.QuadPart; //  push

	QueryPerformanceCounter(&count);
	QueryPerformanceFrequency(&freq);
	for (i = 0; i < N; i++) {
		buf = Pop(stack);
	}
	QueryPerformanceCounter(&count1);
	time[1] = ((double)count1.QuadPart - (double)count.QuadPart) / (double)freq.QuadPart; // pop

	QueryPerformanceCounter(&count);
	QueryPerformanceFrequency(&freq);
	for (i = 0; i < N; i++) {
		PushList(&head, i);
	}
	QueryPerformanceCounter(&count1);
	time[2] = ((double)count1.QuadPart - (double)count.QuadPart) / (double)freq.QuadPart; // push list

	QueryPerformanceCounter(&count);
	QueryPerformanceFrequency(&freq);
	for (i = 0; i < N; i++) {
		buf = PopList(&head);
	}
	QueryPerformanceCounter(&count1);
	time[3] = ((double)count1.QuadPart - (double)count.QuadPart) / (double)freq.QuadPart; // pop list

	return time;
}


int main(void) {
	type_t a = 3;
	stackList_t* head;
	stack_t *stack = CreateStack(10);
	printf("Push Array: %lf\nPop Array: %lf\n", CompareStack()[0], CompareStack()[1]);
	printf("Push List: %lf\nPop List: %lf\n", CompareStack()[2], CompareStack()[3]);
	// Push faster on the list, pop faster on the array
#ifdef _CRTDBG_MAP_ALLOC
 _CrtDumpMemoryLeaks();
#endif 
	return 0;
}