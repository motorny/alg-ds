#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include"queue.h"






queue_t* QueueCreate() {
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));

	if (!queue)
		return NULL;
	queue->head = NULL;
	queue->tail = NULL;

	return queue;
}

int Push(queue_t* queue, int data) {
	if (!queue)
		return -1;
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	if (!tmp)
		return -1;
	tmp->data = data;
	tmp->next = NULL;
	if (!queue->tail) {
		queue->head = tmp;
		queue->tail = tmp;
		return 1;
	}
	queue->tail->next = tmp;
	queue->tail = tmp;

	return 1;
}

int Pop(queue_t* queue) {
	int result;
	list_t* tmp;

	if (!queue || !queue->head)
		return -1;
	tmp = queue->head;
	result = tmp->data;
	queue->head = queue->head->next;
	free(tmp);
	if (!queue->head)
		queue->tail = NULL;

	return result;
}
void QueueDelete(queue_t* queue) {
	list_t* tmp;
	list_t* next;
	if (!queue)
		return;

	tmp = queue->head;
	while (tmp != NULL) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(queue);
}
