#ifndef QUEUE
#define QUEUE

#pragma once

typedef int elem_t;

//Очередь на списке
typedef struct node_t {
	elem_t data;
	struct node_t* next;
} node_t;

typedef struct {
	node_t* head;
	node_t* tail;
	int size;
} queueList_t;

//Очередь на массиве
typedef struct {
	elem_t* data;
	int size;
	int head, tail;
} queueArr_t;

#ifdef __cplusplus
	extern "C" {
#endif

		int EmptyQueueArr(queueArr_t queue);

		int SizeQueueArr(queueArr_t queue);

		void PushQueueArr(elem_t newElem, queueArr_t* queue);

		elem_t* PopQueueArr(queueArr_t* queue);

		int EmptyQueueList(queueList_t queue);

		void PushQueueList(elem_t elem, queueList_t* queue);

		elem_t* PopQueueList(queueList_t* queue);

#ifdef __cplusplus
	}
#endif

#endif