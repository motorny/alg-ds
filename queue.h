#pragma once

#define TRUE 1
#define FALSE 0
struct queue {
	int size;
	int first;
	int last;
	int* arr;
};

int InitQueue(struct queue* q, int n);
int Push(struct queue* q, int elem);
int Pop(struct queue* q, int* elem);
int RemoveQueue(struct queue* q);