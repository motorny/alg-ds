#include <stdlib.h>
#include "queue.h"

int InitQ(queue_t* q, int n) {
	if (n <= 0)
		return FALSE;

	q->arr = (int*)malloc(n * sizeof(int));
	if (q->arr == NULL)
		return FALSE;
	q->head = 0;
	q->last = 0;
	q->size = n;
	return TRUE;
}

int push(queue_t* q, int x) {
	if (q->last >= q->size || !q->arr) {
		return FALSE;
	}
	q->arr[q->last++] = x;
	return TRUE;
}

int pop(queue_t* q, int* x) {
	if (q == NULL || q->head >= q->last)
		return FALSE;
	*x = q->arr[q->head];
	q->head++;
	return TRUE;
}

int RemoveQ(queue_t* q) {
	if (q == NULL || q->arr == NULL)
		return FALSE;
	free(q->arr);
	q->head = 0;
	q->last = 0;
	q->size = 0;
	return TRUE;
}