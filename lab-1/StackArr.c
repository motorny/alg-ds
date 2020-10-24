#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "StackArr.h"
#pragma warning(disable: 4996)

stackArr_t* CreateStackArr(void) {
	stackArr_t* stack = (stackArr_t*)malloc(sizeof(stackArr_t));
	if(stack==NULL) return NULL;
	stack->last = -1;
	stack->delta = 10;
	stack->size = stack->delta;
	stack->array = (int*)malloc(stack->size * sizeof(int));
	if (stack->array == NULL) {
		free(stack);
		return NULL;
	}
	return stack;
}
void DestroyStackArr(stackArr_t* stack) {
	if (stack == NULL) return;
	if (stack->array != NULL) free(stack->array);
	free(stack);
}

void ResizeStackArr(stackArr_t* stack) {
	int* p;
	assert(stack);
	stack->size += stack->delta;
	p = (int*)realloc(stack->array, stack->size * sizeof(int));
	assert(p);
	stack->array = p;
}

void PushArr(stackArr_t* stack, int data) {
	assert(stack);
	stack->last++;
	if (stack->last >= stack->size) ResizeStackArr(stack);
	stack->array[stack->last] = data;
}

int PopArr(stackArr_t* stack) {
	assert(stack);
	assert(stack->array);
	if (stack->last < 0) return 0;
	stack->last--;
	return stack->array[stack->last + 1];
}

int LastArr(stackArr_t* stack) {
	assert(stack);
	assert(stack->array);
	if (stack->last < 0) return 0;
	return stack->array[stack->last];
}

void PrintStackArr(stackArr_t* stack) {
	int i;
	if (stack == NULL) {
		printf("NULL\n");
		return;
	}
	i = stack->last;
	while (i >= 0) {
		printf("%d ", stack->array[i]);
		i--;
	}
	printf("\n");
}
