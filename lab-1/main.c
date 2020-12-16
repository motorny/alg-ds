#include <stdio.h>
#include <assert.h>
#include "list.h"
#include "queue_list.h"
#include "queue_array.h"

void print_queue(Queue* q)
{
	for (int i = 0; i < q->real_size; i++)
		printf("%d ", q->data[i]);
	printf("\n");
}

void print_queuel(QueueL* q)
{
	Node* new_el = q->head;
	while (new_el != NULL)
	{
		printf("%d ", new_el->data);
		new_el = new_el->next;
	}
	printf("\n");
	free(new_el);
}


int main()
{
	Queue* q = NULL;
	QueueL* ql = NULL;

	queue_init(&q, 5);

	queue_push(q, 23);
	queue_push(q, 45);
	queue_push(q, 687);
	queue_push(q, -345);

	printf("Current queue: ");
	print_queue(q);


	queuel_init(&ql);

	queuel_push(&ql, -34);
	queuel_push(&ql, 445);
	queuel_push(&ql, 12);
	queuel_push(&ql, 55);

	printf("Current queueL: ");
	print_queuel(ql);

}