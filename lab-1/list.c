#include "list.h"


int list_init_data(Node** head, int data)
{
	(*head) = (Node*)malloc(sizeof(Node));
	if (head == NULL)
		return NULL;
	(*head)->data = data;
	(*head)->next = NULL;
}

void list_push(Node* head, int data)
{
	Node* current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	current->next = (Node*)malloc(sizeof(Node));
	if (current->next == NULL)
		return NULL;
	current->next->data = data;
	current->next->next = NULL;
}

int list_pop(Node** head)
{
	Node* p = *head;
	int v = p->data;
	(*head) = (*head)->next;

	free(p);
	return v;
}

int list_get(Node* head, int n)
{
	Node* c = head;
	for (int i = 0; i < n; i++)
		c = c->next;
	int v = c->data;
	free(c);
	return v;
}