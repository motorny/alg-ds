#include <stdlib.h>

typedef struct Queue_t
{
	int* data;
	int real_size;
} Queue;

void queue_init(Queue** p, int size);
void queue_push(Queue* p, int data);
int queue_pop(Queue* p);