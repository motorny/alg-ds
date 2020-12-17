#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

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

int IsNotSorted(int array[], int size) {
	int i;
	for (i = 1; i < size; i++) {
		if (array[i] < array[i - 1]) {
			return FAILING;
		}
	}

	return SUCCESS;
}


void QuickSort(int array[], int start, int end) {
	int pivot;
	int l_hold = start;
	int r_hold = end;
	pivot = array[start];
	while (start < end) {
		while ((array[end] >= pivot) && (start < end)) {
			end--;
		}

		if (start != end) {
			array[start] = array[end];
			start++;
		}

		while ((array[start] <= pivot) && (start < end)) {
			start++;
		}

		if (start != end) {
			array[end] = array[start];
			end--;
		}
	}

	array[start] = pivot;
	pivot = start;
	start = l_hold;
	end = r_hold;
	if (start < pivot) {
		QuickSort(array, start, pivot - 1);
	}
	if (end > pivot) {
		QuickSort(array, pivot + 1, end);
	}

}

int BFS(tree_t* graph, int n, queue_t* q) {
	int vertex, i;
	int* nodes;

	nodes = malloc(sizeof(int) * n);

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
		QuickSort(graph->nodes[i].edges, 0, graph->nodes[i].number);
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
	graph.nodes = malloc(n * sizeof(node_t));

	for (i = 0; i < n; i++) {
		graph.nodes[i].edges = malloc(n * sizeof(int));
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