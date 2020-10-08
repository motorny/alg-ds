#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lid_2020.h"

struct LIST
{
	char *str;
	struct LIST *next;
	struct LIST* prev;
};

void Split(LIST_T* head, LIST_T** first, LIST_T** second)
{
	LIST_T * front, *back;
	if (head == NULL || head->next == NULL) 
	{
		(*first) = NULL;
		(*second) = NULL;
		return;
	}
	front = head->next;
	back = head;
	while (front != NULL)
	{
		front = front->next;
		if (front != NULL)
		{
			back = back->next;
			front = front->next;
		}
	}
	(*second) = back->next;
	(*second)->prev = NULL;
	(*first) = head;
	back->next = NULL;
}
LIST_T * Merge(LIST_T *A, LIST_T *B)
{
	LIST_T *C = NULL;
	if (A == NULL && B == NULL)
		return C;
	else if (A == NULL)
		return B;
	else if (B == NULL)
		return A;

	if ((strcmp(A->str, B->str) <= 0) ? 1 : 0)
	{
		C = A;
		C->next = Merge(A->next, B);
		C->next->prev = C;
	}
	else
	{
		C = B;
		C->next = Merge(A, B->next);
		C->next->prev = C;
	}
	return C;
}

void Sort(LIST_T **head)
{
	LIST_T *ref=*head;
	LIST_T * first = NULL, *second = NULL;
	if (ref == NULL || ref->next == NULL)
	{
		return;
	}
	Split(ref, &first, &second);
	Sort(&first);
	Sort(&second);
	*head = Merge(first, second);
}
