#include "List.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

LIST* initList()
{
	LIST* head = NULL;
	return head;
}

void delList(LIST* head)
{
	LIST* a;
	for (; head != NULL; )
	{
		a = head;
		head = head->next;
		free(a);
	}
}

LIST* insertInList(LIST* head, int data)
{
	LIST* current = head
		, * previous = NULL
		, * temp;

	temp = (LIST*)malloc(sizeof(LIST));
	if (temp == NULL)
	{
		printf_s("failed add item");
		return NULL;
	}
	temp->data = data;

	if (current == NULL)
	{
		head = temp;
		head->next = NULL;
		return head;
	}

	for (; current != NULL; )
	{
		if (current->data == data)
		{
			break;
		}
		if (current->data > data)
		{
			if (previous == NULL)
			{
				temp->next = current;
				head = temp;
				break;
			}
			if (current->next == NULL)
			{
				previous->next = temp;
				temp->next = current;
			}
			else
			{
				previous->next = temp;
				temp->next = current;
			}
			break;
		}
		previous = current;
		current = current->next;
		if (current == NULL)
		{
			previous->next = temp;
			temp->next = NULL;
		}
	}

	return head;
}

LIST* deleteItem(LIST* head, int data)
{
	LIST* a = head;
	LIST* tmp = head;
	if (a->data == data)
	{
		head = a->next;
		free(a);
	}
	else
	{
		for (; a != NULL; )
		{
			if (a->data == data)
			{
				tmp->next = a->next;
				free(a);
				break;
			}
			tmp = a;
			a = a->next;
		}

		a = tmp;
	}


	return head;
}

Bool searchItemInList(LIST* head, int data)
{
	LIST* a = head;
	Bool itFound = FALSE;
	for (; a != NULL; )
	{
		if (a->data == data)
		{
			itFound = TRUE;
			break;
		}
		a = a->next;
	}
	return itFound;
}

LIST* intersection(LIST* head1, LIST* head2)
{
	LIST* a1 = head1, * a2;
	LIST* temp = initList();

	for (; a1 != NULL; )
	{
		a2 = head2;
		for (; a2 != NULL; )
		{
			if (a1->data == a2->data)
			{
				temp = insertInList(temp, a1->data);
				break;
			}
			a2 = a2->next;
		}
		a1 = a1->next;
	}

	return temp;
}

LIST* unionOfSets(LIST* head1, LIST* head2)
{
	LIST* a1 = head1, * a2 = head2;
	LIST* temp = initList();

	for (; a1 != NULL; )
	{
		temp = insertInList(temp, a1->data);
		a1 = a1->next;
	}
	for (; a2 != NULL; )
	{
		temp = insertInList(temp, a2->data);
		a2 = a2->next;
	}
	return temp;
}

void printList(LIST* head)
{
	LIST* a = head;

	printf_s("Address         Data         Next item\n");
	for (; a != NULL; )
	{
		printf_s("%p         ", a);
		printf_s("%d           ", a->data);
		printf_s("%p\n", a->next);

		a = a->next;
	}
}