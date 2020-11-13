#ifndef QUEUEPRIORITY_H_INCLUDED__
#define QUEUEPRIORITY_H_INCLUDED__
#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include <crtdbg.h>
#pragma warning (disable: 4996)

typedef struct node_t {
	int data, priority;
	struct node_t* next;
} node_t;

typedef struct {
	node_t* head, * tail;
} queuePrior_t;

typedef enum {
	NONE = 0,
	NO_MEMORY,
	NO_DATA
} error_t;

queuePrior_t* InitQueuePriority(int* arr, int N, error_t* error);
void PrintQueue(queuePrior_t* queue, int N);
void DeleteQueue(queuePrior_t* queue, int N, error_t* error);
int IsEmptyQueue(queuePrior_t* queue, error_t* error);
void InsertEl(queuePrior_t* queue, queuePrior_t* queue1, queuePrior_t* queue2, int N, int newEl, int priority, error_t* error);
void InsertEnd(queuePrior_t* queue, int newEl, error_t* error);
int FindMax(queuePrior_t* queue, error_t* error);
int FindMin(queuePrior_t* queue, error_t* error);
void DeleteMax(queuePrior_t* queue, error_t* error);
int FindEl(queuePrior_t* queue, int N, int el, error_t* error);
void SplitQueue(queuePrior_t* queue, queuePrior_t* queue1, queuePrior_t* queue2, int N, int priority, error_t* error);
queuePrior_t* MergeQueue(queuePrior_t* q1, queuePrior_t* q2, int newEl, int priority, error_t* error);

#endif HEADER_H_INCLUDED
