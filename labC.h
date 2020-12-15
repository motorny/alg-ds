#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#pragma once

#define SUCCESS 0
#define FAILING 1

typedef struct {
	int* arr;
	int size;
	int head;//голова
	int tail;//хвост
} queue_t;

typedef struct {
	int number;
	int* edges;
}node_t;

typedef struct {
	int vertex;
	node_t* nodes;
} tree_t;

int CreateQueue(queue_t* q, int size);
int PutToQueue(queue_t* q, int element);
int GetFromQueue(queue_t* q, int* element);
void DeleteQueue(queue_t* q);
int Partition(int array[], int size);
int IsNotSorted(int array[], int size);
void QuickSort(int array[], int size);
int BFS(tree_t* graph, int n, queue_t* q);
void ReadGraph(tree_t* graph, int n);
int Function(void);
