#ifndef QUEUE_H_INCLUDED__
#define QUEUE_H_INCLUDED__
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#pragma warning (disable: 4996)

//typedef struct {
//	int number;
//}data_t;

typedef struct node_t {
	int number;
	int priority;
	struct node_t* next;
} node_t;

typedef struct {
	node_t* tail;
	node_t* head;
}queue_t;

typedef enum {
	TRUE = 0,
	FALSE = 1
}bool_t;

typedef enum {
	FINISHED  = 0,
	NO_MEMORY_ALLOCATED,
	IMPOSSIBLE_TO_COMPLETE
}error_t;

void PriorityIncrease(node_t* current);//priority removal +1
void PriorityDecrease(node_t* current);//priority removal -1
node_t* NewNode(node_t* previous);
node_t* GoToNode(node_t* head, int newpriority);
void EnqueueByPriority(queue_t* queue, int newdata, int newpriority);
void InsertTail(queue_t* queue, int newdata);
void DeleteMax(queue_t* queue);
int ExtractMax(queue_t* queue);
bool_t IsEmpty(queue_t* queue);
queue_t* QueueCreate(int* mass, int N);
void QueueDestroy(queue_t* queue);
void PrintQueue(queue_t* queue);

#endif HEADER_H_INCLUDED
