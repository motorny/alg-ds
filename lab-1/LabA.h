#pragma once
#define N 4
#define NO_ERRORS 0
#define NOT_ENOUGH_MEMORY 1
#define ARRAY_IS_FULL 2
#define QUEUE_IS_FREE 3

typedef struct {
	int data[N];
	int head;
	int tail;
}queue_array_t;

typedef struct element_tag {
	int data;
	struct element_tag* next;
} element_t;

typedef struct {
	int size;
	element_t* head;
	element_t* tail;
}queue_list_t;

void CreateList(queue_list_t* queue, int* error);
int IsFilledList(queue_list_t* queue);
void AddToList(queue_list_t* queue, int data, int* error);
int DeleteFromList(queue_list_t* queue, int* error);
void DeleteAllList(queue_list_t* queue);
int SizeOfList(queue_list_t* queue);

void CreateArray(queue_array_t* queue);
int IsFilledArray(queue_array_t* queue);
void AddToArray(queue_array_t* queue, int element, int* error);
int DeleteFromArray(queue_array_t * queue, int* error);
int SizeOfArray(queue_array_t * queue);
void DeleteAllArray(queue_array_t * queue);
