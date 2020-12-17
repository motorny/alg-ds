#pragma once

struct queueitem {
	int vertex;
	struct queueitem* next;
};


struct queue {
	int count;
	struct queueitem* head;
	struct queueitem* current;
	struct queueitem* tail;
};


struct queue* initQueue();
int appendQueueItem(struct queue* q,int v);
int getCurrentQueueItem(struct queue* q);
int shiftCurrentQueueItem(struct queue* q);
int destroyQueue(struct queue* q);

