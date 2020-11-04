

#pragma once
#define INIT_SIZE 4

typedef enum Bool {
	FAILED,
	SUCCESS
}Bool_t;


typedef struct StackList {
	int value;
	struct StackList *next;
}StackList_t;

StackList_t* CreateStackList();

Bool_t PushStackList(StackList_t **head, int value);

int PopStackList(StackList_t **head);

void DestroyStackList(StackList_t** head);


typedef struct StackArray {
	int* value;
	size_t size;
	size_t top;
}StackArray_t;

StackArray_t* CreateStackArray();

Bool_t PushStackArray(StackArray_t *stack, int value);

int PopStackArray(StackArray_t *stack);

void DestroyStackArray(StackArray_t* stack);
