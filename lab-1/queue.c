#include "queue.h"

//extern int error;

void PriorityIncrease(node_t* current) {
	node_t* ptr = current;
	node_t* ptr1 = NULL;
	while (ptr->next != NULL) {
		ptr1 = ptr->next;
		ptr1->priority++;
		ptr = ptr1;
	}
}

void PriorityDecrease(node_t* current) {
	node_t* ptr = current;
	node_t* ptr1 = NULL;
	while (ptr->next != NULL) {
		ptr1 = ptr->next;
		ptr1->priority--;
		ptr = ptr1;
	}
}

node_t* NewNode(node_t* previous, bool_t* flag) {//adding between nodes
	node_t* newnode = (node_t*)malloc(sizeof(node_t));
	if (!newnode) {
		//error = NO_MEMORY_ALLOCATED;
		*flag = FALSE;
		return NULL;
	}
	node_t* pointer = NULL;
	pointer = previous->next;
	previous->next = newnode;
	newnode->next = pointer;
	return newnode;
}

node_t* GoToNode(node_t* node, int newpriority) {
	node_t* node1 = NULL;

	while (node->priority < newpriority) {
		node1 = node->next;
		node = node1;
	}

	return node;
}

void EnqueueByPriority(queue_t* queue, int newdata, int newpriority, bool_t* flag) {
	if (IsEmpty(queue) == TRUE) {//is empty
		//error = IMPOSSIBLE_TO_COMPLETE;
		*flag = FALSE;
		return;
	}

	node_t* node = queue->head;
	node_t* newnode = NULL;

	if (newpriority == node->priority) {//add by zero priority
		newnode = (node_t*)malloc(sizeof(node_t));
		if (!newnode) {
			//error = NO_MEMORY_ALLOCATED;
			*flag = FALSE;
			return;
		}

		newnode->next = node;
		newnode->number = newdata;
		newnode->priority = 0;
		queue->head = newnode;
		PriorityIncrease(newnode);
		return;
	}
	node = GoToNode(node, newpriority - 1);
	newnode = NewNode(node, flag);
	if (*flag != TRUE)
		return;
	newnode->number = newdata;
	newnode->priority = newpriority;
	PriorityIncrease(newnode);
}

void InsertTail(queue_t* queue, int newdata, bool_t* flag) {
	if (IsEmpty(queue) == TRUE) {//is empty
		//error = IMPOSSIBLE_TO_COMPLETE;
		*flag = FALSE;
		return;
	}

	int tailpriority = queue->tail->priority;
	node_t* newnode = (node_t*)malloc(sizeof(node_t));
	if (!newnode) {
		//error = NO_MEMORY_ALLOCATED;
		*flag = FALSE;
		return;
	}

	queue->tail->next = newnode;
	newnode->number = newdata;
	newnode->priority = tailpriority + 1;
	newnode->next = NULL;
	queue->tail = newnode;
}

void DeleteMax(queue_t* queue, bool_t* flag) {
	if (IsEmpty(queue) == TRUE) {//is empty
		//error = IMPOSSIBLE_TO_COMPLETE;
		*flag = FALSE;
		return;
	}
	
	node_t* node = queue->head->next;
	node->priority--;
	free(queue->head);
	queue->head = node;
	PriorityDecrease(queue->head);

	return;
}

int ExtractMax(queue_t* queue, bool_t* flag) {
	if (IsEmpty(queue) == TRUE) {//is empty
		//error = IMPOSSIBLE_TO_COMPLETE;
		*flag = FALSE;
		return 0;
	}

	int extracted = queue->head->number;
	DeleteMax(queue, flag);
	return extracted;
}

queue_t* QueueCreate(int* mass, int N, bool_t* flag) {
	queue_t* queue = NULL;

	if (N == 0 && mass == NULL) {
		return queue;
	}

	queue = (queue_t*)malloc(sizeof(queue_t));
	if (!queue) {
		//error = NO_MEMORY_ALLOCATED;
		*flag = FALSE;
		return NULL;
	}

	node_t* head = (node_t*)malloc(sizeof(node_t));
	if (!head) {
		//error = NO_MEMORY_ALLOCATED;
		*flag = FALSE;
		free(queue);
		return NULL;
	}
	node_t* tail = NULL;
	queue->head = head;
	queue->tail = tail;
	node_t* node = head;
	node_t* node1 = NULL;
	int i = 0;

	for (i = 0; i < N ; i++) {
		node->number = mass[i];
		node->priority = i;
		if (i == N - 1) {
			node1 = NULL;
			node->next = node1;
			break;
		}
		node1 = (node_t*)malloc(sizeof(node_t));
		//node1 = NULL;
		if (!node1) {
			//error = NO_MEMORY_ALLOCATED;
			*flag = FALSE;
			queue->tail = node;
			node->next = NULL;
			QueueDestroy(queue);
			return NULL;
		}
		node->next = node1;
		node = node1;		
	}
	queue->tail = node;

	return queue;
}

void QueueDestroy(queue_t* queue) {
	node_t* node = queue->head;
	node_t* node1 = NULL;

	while (1) {
		node1 = node->next;
		free(node);
		if (node1 == NULL)
			break;
		node = node1;
	}
	free(queue);
}

void PrintQueue(queue_t* queue) {
	node_t* node = queue->head;
	node_t* node1 = NULL;

	while(1) {
		printf("-> (%d)[%d] ", node->priority, node->number);
		node1 = node->next;
		if (node1 == NULL)
			break;
		node = node1;
	}
	printf("\n\n");
}

bool_t IsEmpty(queue_t* queue) {
	if (queue == NULL)
		return TRUE;// is empty
	else
		return FALSE;// is full
}
