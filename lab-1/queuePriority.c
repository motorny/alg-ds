
#include "queuePriority.h"


queuePrior_t* InitQueuePriority(int* arr, int N, error_t* error) {
	queuePrior_t* queue = NULL;
	node_t* el1 = NULL, * el2 = NULL, * el3 = NULL;
	int i = 0;

	if (arr == NULL && N == 0) {
		IsEmptyQueue(queue, error);
		return queue;
	}
	queue = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	if (queue != NULL) {
		el1 = (node_t*)malloc(sizeof(node_t));
		if (!el1) {
			*error = NO_MEMORY;
			free(queue);
			return NULL;
		}
		queue->head = el1;
		queue->tail = el2;
		for (i = 0; i < N - 1; i++) {
			el1->data = arr[i];
			el1->priority = i;
			el2 = (node_t*)malloc(sizeof(node_t));
			if (!el2) {
				*error = NO_MEMORY;
				queue->tail = el1;
				el1->next = NULL;
				DeleteQueue(queue, N, error);
				return NULL;
			}
			el1->next = el2;
			el1 = el2;
		}
		el1->data = arr[i];
		el1->priority = i;
		el2 = NULL;
		el1->next = el2;
		queue->tail = el1;
		return queue;
	}
	else {
		*error = NO_MEMORY;
		return NULL;
	}
}

void DeleteQueue(queuePrior_t* queue, int N, error_t* error) {
	if (IsEmptyQueue(queue, error))
		return;
	else {
		node_t* el1 = queue->head, * el2 = NULL;
		int i;
		for (i = N; i > 0; i--) {
			el2 = el1->next;
			free(el1);
			if (el2 == NULL)
				break;
			el1 = el2;
		}
		free(queue);
	}
}

void PrintQueue(queuePrior_t* queue, int N) {
	node_t* el1 = queue->head, * el2 = NULL;
	int i;
	for (i = N; i > 0; i--) {
		printf("%d(%d) | ", el1->data, el1->priority);
		el2 = el1->next;
		if (el2 == NULL)
			break;
		el1 = el2;
	}
	printf("\n\n");
}


int IsEmptyQueue(queuePrior_t* queue, error_t* error) {
	if (queue == NULL) {
		*error = NO_DATA;
		return 1;
	}
	else
		return 0;
}

void InsertEl(queuePrior_t* queue, queuePrior_t* queue1, queuePrior_t* queue2, int newEl, int N, int priority, error_t* error) {
	if (!IsEmptyQueue(queue, error)) {
		node_t* el1 = queue->head, * el2 = NULL;
		int i, oldEl = 0;
		for (i = 0; i < N; i++) {
			el2 = el1->next;
			if (el2 == NULL)
				break;
			el1 = el2;
		}
		if (priority != N) {
			SplitQueue(queue, queue1, queue2, N, priority, error);
			queue = MergeQueue(queue1, queue2, newEl, priority, error);
		}
		else
			InsertEnd(queue, newEl, error);
	}
}

queuePrior_t* MergeQueue(queuePrior_t* queue1, queuePrior_t* queue2, int newEl, int priority, error_t* error) {
	node_t* el1 = NULL, * el2 = NULL;
	InsertEnd(queue1, newEl, error);
	el1 = queue2->head, el1->priority=queue2->head->priority+1, el2 = NULL;
	queue1->tail->next = el1;
	while (1) {
		el2 = el1->next;
		queue1->tail = el2;
		if (el2 == NULL)
			break;
		queue1->tail->priority++;
		el1 = el2;
	}
	return queue1;
}

void SplitQueue(queuePrior_t* queue, queuePrior_t* queue1, queuePrior_t* queue2, int N, int priority, error_t* error) {
	node_t* el1 = queue->head, * el2 = NULL;
	int i, N1 = 1, N2 = 1;

	if (priority == 0) {
		queue1->head = queue1->tail = NULL;
		queue2->head = el1;;
		for (i = priority + 1; i < N; i++) {
			el2 = el1->next;
			queue2->tail = el2;
			if (el2 == NULL)
				break;
			el1 = el2;
			N2++;
		}
	}
	else {
		queue1->head = el1;;
		for (i = 0; i < priority - 1; i++) {
			el2 = el1->next;
			queue1->tail = el2;
			el1 = el2;
			N1++;
		}

		if (priority == 1)
			queue1->tail = queue1->head;

		queue2->head = el1->next;
		for (i = priority + 1; i < N + 1; i++) {
			el2 = el1->next;
			queue2->tail = el2;
			if (el2 == NULL)
					break;
			el1 = el2;
			N2++;
		}
	}
}


int FindMax(queuePrior_t* queue, error_t* error) {
	node_t* el = NULL;
	if (!IsEmptyQueue(queue, error)) {
		el = queue->head;
	}
	else
		return 0;
	return el->data;
}


int FindMin(queuePrior_t* queue, error_t* error) {
	node_t* el = NULL;
	if (!IsEmptyQueue(queue, error)) {
		el = queue->tail;
	}
	else
		return 0;
	return el->data;
}

void DeleteMax(queuePrior_t* queue, error_t* error) {
	node_t* data = NULL;
	if (!IsEmptyQueue(queue, error)) {
		data = queue->head;
		queue->head = queue->head->next;
		free(data);
	}
	else
		return;
}

int FindEl(queuePrior_t* queue, int N, int el, error_t* error) {
	int i = 0, priority = 0;
	if (!IsEmptyQueue(queue, error)) {
		node_t* el1 = queue->head, * el2 = NULL;
		for (i = 0; i < N; i++) {
			while (el1->data < el) {
				el2 = el1->next;
				el1 = el2;
				priority++;
			}
			if (el1->data != el) {
				*error = NO_DATA;
				return 0;
			}
		}
	}
	else
		return 0;
	return priority;
}


void InsertEnd(queuePrior_t* queue, int newEl, error_t* error) {
	if (!IsEmptyQueue(queue, error)) {
		node_t* newData = (node_t*)malloc(sizeof(node_t));
		if (!newData) {
			*error = NO_MEMORY;
			free(queue);
			return NULL;
		}
		newData->data = newEl;
		int tailPriority;
		if (queue->head == NULL) {
			newData->priority = 0;
			newData->next = NULL;
			queue->head = queue->tail = newData;
			tailPriority = 0;
		}
		else {
			tailPriority = queue->tail->priority;
			newData->priority = tailPriority + 1;
			newData->next = NULL;
			queue->tail->next = newData;
			queue->tail = newData;
		}
	}
}
