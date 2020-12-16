#include "queue_list.h"

void queuel_init(QueueL** p)
{
	(*p) = (QueueL*)malloc(sizeof(QueueL));
	//list_init(&(*p)->head);
	(*p)->rsize = 0;
	//list_pop(&(*p)->head);
}

void queuel_push(QueueL** p, int data)
{
	if ((*p)->rsize == 0)
		list_init_data(&(*p)->head, data);
	else
		list_push((*p)->head, data);
	(*p)->rsize++;
}

int queuel_pop(QueueL* p)
{
	p->rsize--;
	return list_pop(&p->head);
}