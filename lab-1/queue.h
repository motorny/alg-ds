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
	FALSE
}bool_t;

void PriorityIncrease(node_t* current);//priority removal +1
void PriorityDecrease(node_t* current);//priority removal -1
node_t* NewNode(node_t* previous);
node_t* GoToNode(node_t* head, int newpriority);
void EnqueueByPriority(queue_t* queue, int date, int priority, bool_t* flag);
void InsertTail(queue_t* queue, int newdata, bool_t* flag);
void DeleteMax(queue_t* queue, bool_t* flag);
int ExtractMax(queue_t* queue, bool_t* flag);
bool_t IsEmpty(queue_t* queue);
queue_t* QueueCreate(int* mass, int N);
void QueueDestroy(queue_t* queue);
void PrintQueue(queue_t* queue);

#endif HEADER_H_INCLUDED
