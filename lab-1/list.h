#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct Node_t
{
	int data;
	struct Node_t* next;
} Node;

int list_init_data(Node** head, int data);

void list_push(Node* head, int data);
int list_pop(Node** head);
int list_get(Node* head, int n);

#endif