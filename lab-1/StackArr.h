#pragma once
#pragma warning(disable: 4996)

typedef struct {
	int last;
	int size;
	int* array;
	int delta;
}stackArr_t;

stackArr_t* CreateStackArr(void);

void DestroyStackArr(stackArr_t* stack);

void ResizeStackArr(stackArr_t* stack);

void PushArr(stackArr_t* stack, int data);

int PopArr(stackArr_t* stack);

int LastArr(stackArr_t* stack);

void PrintStackArr(stackArr_t* stack);
