#pragma once

typedef enum {
	ERROR_NO,
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	OUT_OF_MEMORY,
	STACK_IS_EMPTY
} error_t;

typedef struct ArrayStack {
	int* data;
	int top;
	int size;
} ArrayStack_t;

ArrayStack_t* CreateArrayStack(error_t* err);

int PopArrayStack(ArrayStack_t* stack, error_t* err);

void PushArrayStack(ArrayStack_t* stack, int elem, error_t* err);

void DestroyArrayStack(ArrayStack_t* stack);



typedef struct ListStack {
	int data;
	struct ListStack* prev;
} ListStack_t;

struct ListStack* CreateListStack(error_t* err);

struct ListStack* CreateLinkedListStack(error_t* err);

void PushListStack(ListStack_t** stack, int newData, error_t*err);

int PopListStack(ListStack_t** stack, error_t* err);

void DestroyListStack(ListStack_t** stack, error_t* err);
