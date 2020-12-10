#ifndef QUEUE_H_INCLUDED__
#define QUEUE_H_INCLUDED__
#pragma once

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)
#define IS_NUMBER(ch) ( ch >= '0' && ch <= '9')
#define ZERO_CODE 48
#define FACTOR 10

enum {
	FINISHED = 0,
	FAILED
};

enum {
	NOT_VISITED = 0,
	VISITED
};

typedef struct queue_t {
	int* arr;
	int size;
	int head;
	int tail;
} queue_t;

typedef struct {
	int number;
	int flag;
	int neighborsQuantity;
	int* neighbors;
}vertex_t;

typedef struct {
	int vertexQuantity;
	vertex_t* vertexes;
}adjacencyList_t;

int CreateQueue(queue_t* queue, int size);
int DestroyQueue(queue_t* queue);
int Push(queue_t* queue, int num);
int Pop(queue_t* queue, int* num);

#endif HEADER_H_INCLUDED