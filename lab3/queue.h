#pragma once

typedef struct list {
	int data;
	struct list* next;
} list_t;

typedef struct queue {
	list_t* head;
	list_t* tail;
} queue_t;


queue_t* QueueCreate();

int Push(queue_t* queue, int data);

int Pop(queue_t* queue);

void QueueDelete(queue_t* queue);