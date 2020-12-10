#include "queue.h"

int CreateQueue(queue_t* queue, int size) {
	if (!queue || size <= 0)
		return FAILED;
	queue->arr = (int*)malloc(size * sizeof(int));
	if (!queue->arr)
		return FAILED;
	queue->size = size;
	queue->head = 0;
	queue->tail = 0;
	return FINISHED;
}

int DestroyQueue(queue_t* queue) {
	if (!queue || !queue->arr)
		return FAILED;
	free(queue->arr);
	queue->head = 0;
	queue->size = 0;
	queue->tail = 0;
	return FINISHED;
}

int Push(queue_t* queue, int num) {
	if (!queue || !queue->arr || queue->tail >= queue->size)
		return FAILED;
	queue->arr[queue->tail++] = num;
	return FINISHED;
}

int Pop(queue_t* queue, int* num) {
	if (!queue || !num || !queue->arr || queue->head >= queue->tail)
		return FAILED;
	*num = queue->arr[queue->head];
	queue->head++;
	return FINISHED;
}