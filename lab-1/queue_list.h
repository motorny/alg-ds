#include <stdlib.h>
#include "list.h"

typedef struct QueueL_t
{
	Node* head;
	int rsize;
} QueueL;

void queuel_init(QueueL** p);
void queuel_push(QueueL** p, int data);
int queuel_pop(QueueL* p);