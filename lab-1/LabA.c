#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 4 //количество элементов в массиве, служащем основной очереди 

/*#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW*/

typedef struct {
	int data[N];
	int head;
	int tail;
}queue_array_t;

typedef struct element_tag {
	int data;
	struct element_tag* next;
} element_t;

typedef struct{
	int size;
	element_t* head;
	element_t* tail;
}queue_list_t;

void CreateList(queue_list_t* queue) {

	queue->head = malloc(sizeof(element_t));
	queue->head->next = NULL;
	queue->tail = queue->head;
	queue->size = 0;

}

int IsFilledList(queue_list_t* queue) {
	if (queue->size == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void AddToList(queue_list_t* queue, int data, int *error) {

	element_t* temp;

	if (IsFilledList(queue)) {
		temp = malloc(sizeof(element_t));

		if (temp == NULL) {
			*error = 1; //в случае нехватки памяти
		}
		else {
			*error = 0;
			temp->data = data;
			temp->next = NULL;

			queue->tail->next = temp;
			queue->tail = temp;
		}
	}
	else {
		*error = 0;
		queue->head->data = data;
		queue->head->next = NULL;
		queue->tail = queue->head;
	}

	queue->size++;
}

int DeleteFromList(queue_list_t* queue, int *error) {
	int element;
	element_t* first = queue->head->next;

	if (queue->size != 0) {
		element = queue->head->data;
		free(queue->head);
		queue->head = first;
		queue->size--;

		*error = 0;
		return element;
	}
	else {
		*error = 1;
		return 0;
	}

}

void DeleteAllList(queue_list_t* queue) {
	element_t* temp = queue->head;

	while (temp != NULL) {
		temp = queue->head->next;
		free(queue->head);
		queue->head = temp;
	}

	queue->size = 0;
}

int SizeOfList(queue_list_t* queue) {
	return queue->size;
}

void CreateArray(queue_array_t* queue) {

	queue->head = 0;
	queue->tail = 0;

}

int IsFilledArray(queue_array_t* queue) {
	if (queue->head == queue->tail) {
		return 0;
	}
	else {
		return 1;
	}
}

void AddToArray(queue_array_t* queue, int element, int* error) {
	if ((queue->tail + 1) % N == queue->head) {
		*error = 1; //если массив переполнен
	}
	else {
		queue->data[queue->tail] = element;
		queue->tail = (queue->tail + 1) % N;
		*error = 0;
	}
}

int DeleteFromArray(queue_array_t* queue, int* error) {
	int element;

	if (IsFilledArray(queue)) {
		element = queue->data[queue->head];
		queue->head = (queue->head + 1) % N;
		*error = 0;
		return element;
	}
	else {
		*error = 1; //если массив пустой
		return 0;
	}
}

int SizeOfArray(queue_array_t* queue) {
	int size = queue->tail - queue->head;
	if (size == -1) {
		size = N - 1;
	}
	return size;
}

void DeleteAllArray(queue_array_t* queue) {
	int error;

	while (SizeOfArray(queue) != 0) {
		DeleteFromArray(queue, &error);
	}
}

void DeleteAllArray_ArrayIsFree_returnValidVal(void) {
	queue_array_t queue;
	CreateArray(&queue);

	DeleteAllArray(&queue);

	assert(queue.head == queue.tail);
}

void DeleteAllArray_ArrayIsFilled_returnValidVal(void) {
	queue_array_t queue;
	int error;
	CreateArray(&queue);

	AddToArray(&queue, 1, &error);
	AddToArray(&queue, 2, &error);
	DeleteAllArray(&queue);

	assert(queue.head == queue.tail);
}

void CreateArray_NewArray_returnValidVal() {
	queue_array_t queue;
	CreateArray(&queue);

	assert(queue.head == 0);
	assert(queue.tail == 0);
}

void AddToArray_ArrayIsFree_returnValidVal() {
	queue_array_t queue;
	int error, tail;
	CreateArray(&queue);
	tail = queue.tail;

	AddToArray(&queue, 5, &error);

	assert(queue.data[queue.head] == 5);
	assert(error == 0);
	assert(queue.tail - tail == 1);
}

void AddToArray_ArrayIsFull_returnValidVal() {
	queue_array_t queue;
	int error, i, tail;
	CreateArray(&queue);
	tail = queue.tail;

	for (i = 0; i < 4; i++) {
		AddToArray(&queue, i, &error);
	}

	assert(queue.data[queue.tail - 1] == 2);
	assert(error == 1);
	assert(queue.tail - tail == 3);
}

void DeleteFromArray_ArrayIsEmpty_returnError() {
	queue_array_t queue;
	int error, element;
	CreateArray(&queue);

	element = DeleteFromArray(&queue, &error);

	assert(error == 1);
	assert(element == 0);
}

void DeleteFromArray_ArrayIsFiiled_returnValidVal() {
	queue_array_t queue;
	int error, element;
	CreateArray(&queue);

	AddToArray(&queue, 6, &error);
	element = DeleteFromArray(&queue, &error);

	assert(error == 0);
	assert(element == 6);
}

void IsFilledArray_ArrayIsEmpty_return0() {
	queue_array_t queue;
	int state;
	CreateArray(&queue);

	state = IsFilledArray(&queue);

	assert(state == 0);
}

void IsFilledArray_ArrayIsFill_return1() {
	queue_array_t queue;
	int state, error;
	CreateArray(&queue);
	AddToArray(&queue, 5, &error);

	state = IsFilledArray(&queue);

	assert(state == 1);
}

void SizeOfArray_ArrayIsEmpty_return0() {
	queue_array_t queue;
	int size;
	CreateArray(&queue);

	size = SizeOfArray(&queue);

	assert(size == 0);
}

void SizeOfArray_ArrayIsFill_return0() {
	queue_array_t queue;
	int size, error;
	CreateArray(&queue);
	AddToArray(&queue, 1, &error);

	size = SizeOfArray(&queue);

	assert(size == 1);
}

void AddToList_ListIsFree_returnValidVal(void) {
	queue_list_t queue;
	int error;

	CreateList(&queue);
	AddToList(&queue, 5, &error);

	assert(queue.head->data == 5);
	assert(error == 0);
}

void CreateList_ListIsFree_returnValidVal(void) {
	queue_list_t queue;

	CreateList(&queue);

	assert(queue.size == 0);
	assert(queue.head == queue.tail);
}

void DeleteAllList_ListIsFree_returnValidVal(void) {
	queue_list_t queue;

	CreateList(&queue);

	DeleteAllList(&queue);

	assert(queue.size == 0);
	assert(queue.head == NULL);
}

void DeleteAllList_ListIsFilled_returnValidVal(void) {
	queue_list_t queue;
	int error;

	CreateList(&queue);
	AddToList(&queue, 5, &error);
	DeleteAllList(&queue);

	assert(queue.size == 0);
	assert(queue.head == NULL);
}

void DeleteFromList_ListIsFree_returnValidVal(void) {
	queue_list_t queue;
	int element, error;
	CreateList(&queue);

	element = DeleteFromList(&queue, &error);

	assert(element == 0);
	assert(error == 1);
	assert(queue.size == 0);
}


void DeleteFromList_ListIsFilled_returnValidVal(void) {
	queue_list_t queue;
	int element, error;
	CreateList(&queue);

	AddToList(&queue, 6, &error);
	AddToList(&queue, 4, &error);

	element = DeleteFromList(&queue, &error);

	assert(element == 6);
	assert(error == 0);
	assert(queue.size == 1);

}

void IsFilledList_ListIsFree_return0(void) {
	queue_list_t queue;
	int state;
	CreateList(&queue);

	state = IsFilledList(&queue);

	assert(state == 0);
}

void IsFilledList_ListIsFilled_return1(void) {
	queue_list_t queue;
	int state, error;
	CreateList(&queue);

	AddToList(&queue, 1, &error);
	state = IsFilledList(&queue);

	assert(state == 1);
}


void SizeOfList_ListIsFree_return0(void) {
	queue_list_t queue;
	int size;
	CreateList(&queue);

	size = SizeOfList(&queue);

	assert(size == 0);
}

void SizeOfList_ListIsFilled_return2(void) {
	queue_list_t queue;
	int size, error;
	CreateList(&queue);

	AddToList(&queue, 1, &error);
	AddToList(&queue, 2, &error);
	
	size = SizeOfList(&queue);

	assert(size == 2);
}

int main(void) {
	DeleteAllArray_ArrayIsFilled_returnValidVal();
	//_CrtDumpMemoryLeaks();

	return 0;
}