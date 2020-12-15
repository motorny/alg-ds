#include <stdio.h>
#include <stdlib.h>
#include "labC.h"
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


int CreateQueue(queue_t* q, int size) {
	q->arr = NULL;

	if (size > 0) {
		q->arr = (int*)calloc(size, sizeof(int));
	}

	if (q->arr) {
		q->size = size;
		q->head = 0;
		q->tail = 0;

		return SUCCESS;
	}

	return FAILING;
}

int PutToQueue(queue_t* q, int element) {
	if (q->arr != NULL && q->size > q->tail) {
		q->arr[q->tail++] = element;
		return SUCCESS;
	}
	return FAILING;
}

int GetFromQueue(queue_t* q, int* element) {
	if (q != NULL && q->head != q->tail) {
		*element = q->arr[q->head++];
		return SUCCESS;
	}
	return FAILING;
}

void DeleteQueue(queue_t* q) {
	free(q->arr);
	q->arr = NULL;
	q->size = 0;
	q->head = 0;
	q->tail = 0;
}

int Partition(int array[], int size) {
	int pivot = array[size / 2], i = -1, j = size, t;

	while (1) {
		do {
			i++;
		} while (array[i] < pivot);

		do {
			j--;
		} while (array[j] > pivot);

		if (i >= j) {
			return j;
		}

		t = array[i];
		array[i] = array[j];
		array[j] = t;

	}

}

int IsNotSorted(int array[], int size) {
	int i;
	for (i = 1; i < size; i++) {
		if (array[i] < array[i - 1]) {
			return 1;
		}
	}

	return 0;
}


void QuickSort(int array[], int size) {
	int p = 0, i;
	int* array1;
	if (IsNotSorted(array, size)) {
		p = Partition(array, size);

		array1 = (int*)malloc(sizeof(int) * (size - p));

		for (i = 1; i < (size - p); i++) {
			array1[i - 1] = array[p + i];
		}

		QuickSort(array, p + 1);
		QuickSort(array1, size - p - 1);

		for (i = 0; i < (size - p - 1); i++) {
			array[p + i + 1] = array1[i];
		}
	}
}

int BFS(tree_t* graph, int n, queue_t* q) {
	int vertex, i;
	int* nodes;
	
	nodes = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		nodes[i] = 0;
	}

	if (n != 0 && graph->nodes != NULL && nodes != NULL) {
		PutToQueue(q, 0);
		nodes[0] = 1;

		while (!GetFromQueue(q, &vertex)) {
			for (i = 0; i < graph->nodes[vertex].number; i++) {

				if (!nodes[graph->nodes[vertex].edges[i]]) {
					PutToQueue(q, graph->nodes[vertex].edges[i]);
					nodes[graph->nodes[vertex].edges[i]] = 1;
				}

			}

		}

		return SUCCESS;
	}
	free(nodes);
	return FAILING;
}

void ReadGraph(tree_t* graph, int n) {
	int i, f = 2, point1, point2;
	while (f > 1) {
		f = scanf("%i %i", &point1, &point2);
		graph->nodes[point1].edges[graph->nodes[point1].number++] = point2;
		graph->nodes[point2].edges[graph->nodes[point2].number++] = point1;
	}

	for (i = 0; i < n; i++) {
		QuickSort(graph->nodes[i].edges, graph->nodes[i].number);
	}
}

int Function(void) {
	queue_t q;
	tree_t graph;
	int error = 0;
	int i, f = 2, n;
	char ch = '\n', ch1 = '1';

	scanf("%i", &n);

	CreateQueue(&q, n);
	graph.nodes = (node_t*)malloc(n * sizeof(node_t));

	for (i = 0; i < n; i++) {
		graph.nodes[i].edges = (int*)malloc(n * sizeof(int));
	}

	for (i = 0; i < n; i++) {
		graph.nodes[i].number = 0;
	}

	ReadGraph(&graph, n);

	error = BFS(&graph, n, &q);

	if (error) {
		free(graph.nodes);
		DeleteQueue(&q);
		return FAILING;
	}

	for (i = 0; i < q.tail; i++) {
		printf("%i ", q.arr[i]);
	}

	for (i = 0; i < n; i++) {
		free(graph.nodes[i].edges);
	}
	
	free(graph.nodes);
	DeleteQueue(&q);
   
    return 0;
}      