//#include "pch.h"
#include <stdlib.h>
//#include "vld.h"
#include <stdio.h>
#include "stack.h"


const int capacity = 10;

// Creats a stack 
ArrayStack_t* CreateArrayStack(error_t* err) {
	ArrayStack_t* stack = (ArrayStack_t*)malloc(sizeof(ArrayStack_t));
	stack->top = 0;
	stack->size = capacity;
	stack->data = (int*)malloc(sizeof(int) * capacity);
	if (stack->data == NULL) {
		*err = OUT_OF_MEMORY;
		return NULL;
	}
	return stack;
}
// Adds an item in the stack


void PushArrayStack(ArrayStack_t* stack, int elem, error_t* err) {
	int flag = 0;
	if (stack->top == stack->size)
	{
		int* newData = (int*)malloc(sizeof(int) * (stack->size + capacity));
		if (newData == NULL) {
			flag = 1;
			*err = OUT_OF_MEMORY;
		}
		else {
			for (int i = 0; i != stack->top; ++i)
				newData[i] = stack->data[i];
			stack->size += capacity;
			free(stack->data);
			stack->data = newData;
		}
	}
	
	if (flag == 0) {
		stack->data[stack->top] = elem;
		stack->top++;
	}
}

// Removes an item from the stack and returnes removed item
int PopArrayStack(ArrayStack_t* stack, error_t* err) {
	if (stack->top == 0) {
		*err = STACK_UNDERFLOW;
		return 0;
	}
	return stack->data[(stack->top--) - 1];
}
// Destroys a stack
void DestroyArrayStack(ArrayStack_t* stack) {
	free(stack->data);
	free(stack);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

ListStack_t* CreateListStack(error_t* err) {
	ListStack_t* stack = (ListStack_t*)malloc(sizeof(ListStack_t));
	if (stack == NULL) {
		*err = OUT_OF_MEMORY;
		return NULL;
	}
	stack->prev = NULL;
	return stack;
}
void PushListStack(ListStack_t** stack, int elem, error_t* err) {
	ListStack_t* tmp = (ListStack_t*)malloc(sizeof(ListStack_t));
	if (tmp == NULL) {
		*err = OUT_OF_MEMORY;
	}
	else {
		tmp->data = elem;
		tmp->prev = *stack;
		(*stack) = tmp;
	}
}


int PopListStack(ListStack_t** stack, error_t* err) {
	ListStack_t* tmp;
	int elem;
	if ((*stack)->prev == NULL) {
		*err = STACK_UNDERFLOW;
		return *err;
	}
	tmp = *stack;
	elem = (*stack)->data;
	(*stack) = (*stack)->prev;
	free(tmp);
	return elem;
}

void DestroyListStack(ListStack_t** stek, error_t* err) {;
	while ((*stek) != NULL) {
		PopListStack(stek, err);
	}
}

struct ListStack* CreateLinkedListStack(error_t* err)
{
	ListStack_t* stek = (ListStack_t*)malloc(sizeof(ListStack_t));
	if (stek == NULL) {
		*err = OUT_OF_MEMORY;
		return NULL;
	}
	if (stek) {
		stek->data = 0;
		stek->prev = 0;
	}
	return stek;

}
