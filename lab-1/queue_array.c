#include "queue_array.h"

void queue_init(Queue** p, int size)
{
	(*p) = (Queue*)malloc(sizeof(Queue));
	(*p)->data = (int*)malloc(size * sizeof(int));

	(*p)->real_size = 0;
}

void queue_push(Queue* p, int data)
{
	p->data[p->real_size] = data;
	p->real_size++;
}

int queue_pop(Queue* p)
{
	int val = p->data[0];
	p->data = p->data + 1;
	p->real_size--;

	return val;
}