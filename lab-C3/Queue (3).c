#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"



struct queue* initQueue()
{
	struct queue* q = malloc(sizeof(struct queue));
	q->count = 0;
	q->head = NULL;
	q->current = NULL;
	q->tail = NULL;

	return q;
};
int appendQueueItem(struct queue* q, int v)
{
	struct queueitem* newvertex = (struct queueitem*) malloc(sizeof(struct queueitem));
	newvertex->vertex = v;
	newvertex->next = NULL;
	if (q->head == NULL) {
		q->head = newvertex;
		q->current = newvertex;
		q->tail = newvertex;
	}
	else {
		q->tail->next = newvertex;
		q->tail = q->tail->next;
	}
	q->count++;
};
int getCurrentQueueItem(struct queue* q)
{
	return q->current->vertex;
};
int shiftCurrentQueueItem(struct queue* q)
{
	q->current = q->current->next;
	q->count--;
	if(q->current)	return q->current->vertex;
};



void destroyQList(struct queueitem* qi) {
	if (qi->next) destroyQList(qi->next);
	free(qi);
}


int destroyQueue(struct queue* q)
{
	destroyQList(q->head);
	free(q);
};
