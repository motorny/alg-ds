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
	LIST* currentDelLink;
	while (head != NULL)
	{
		currentDelLink = head;
		head = head->next;
		free(currentDelLink);
	}
}

LIST* insertInList(LIST* head, int data)
{
	LIST* current = head
		, * previous = NULL
		, * linkToAdd;

	linkToAdd = (LIST*)malloc(sizeof(LIST));
	if (linkToAdd == NULL)
	{
		printf_s("failed add item");
		return NULL;
	}
	linkToAdd->data = data;

	if (current == NULL)
	{
		head = linkToAdd;
		head->next = NULL;
		return head;
	}

	while (current != NULL)
	{
		if (current->data == data)
		{
			break;
		}
		if (current->data > data)
		{
			if (previous == NULL)
			{
				linkToAdd->next = current;
				head = linkToAdd;
				break;
			}
			if (current->next == NULL)
			{
				previous->next = linkToAdd;
				linkToAdd->next = current;
			}
			else
			{
				previous->next = linkToAdd;
				linkToAdd->next = current;
			}
			break;
		}
		previous = current;
		current = current->next;
		if (current == NULL)
		{
			previous->next = linkToAdd;
			linkToAdd->next = NULL;
		}
	}

	return head;
}

LIST* deleteItem(LIST* head, int data)
{
	LIST* removedLink = head;
	LIST* tmp = head;
	if (removedLink->data == data)
	{
		head = removedLink->next;
		free(removedLink);
	}
	else
	{
		while (removedLink != NULL)
		{
			if (removedLink->data == data)
			{
				tmp->next = removedLink->next;
				free(removedLink);
				break;
			}
			tmp = removedLink;
			removedLink = removedLink->next;
		}

		removedLink = tmp;
	}


	return head;
}

Bool searchItemInList(LIST* head, int data)
{
	LIST* mainList = head;
	Bool itFound = FALSE;
	while (mainList != NULL)
	{
		if (mainList->data == data)
		{
			itFound = TRUE;
			break;
		}
		mainList = mainList->next;
	}
	return itFound;
}

LIST* intersection(LIST* head1, LIST* head2)
{
	LIST* firstList = head1, * secondList;
	LIST* intersectionList = initList();

	while (firstList != NULL)
	{
		secondList = head2;
		while (secondList != NULL)
		{
			if (firstList->data == secondList->data)
			{
				intersectionList = insertInList(intersectionList, firstList->data);
				break;
			}
			secondList = secondList->next;
		}
		firstList = firstList->next;
	}

	return intersectionList;
}

//helper function for union
LIST* insertInEndOfList(LIST* head, int data)
{
	LIST* lastLink = head;
	if (head == NULL)
	{
		lastLink = (LIST*)malloc(sizeof(LIST));
		lastLink->data = data;
		lastLink->next = NULL;
		head = lastLink;
	}
	else
	{
		while (lastLink->next != NULL)
		{
			lastLink = lastLink->next;
		}
		lastLink->next = (LIST*)malloc(sizeof(LIST));
		lastLink->next->data = data;
		lastLink->next->next = NULL;
	}

	return head;
}

LIST* unionOfSets(LIST* head1, LIST* head2)
{
	LIST* firstList = head1, * secondList = head2;
	LIST* unionList = initList();

	while (firstList != NULL || secondList != NULL)
	{
		if (firstList == NULL)
		{
			unionList = insertInEndOfList(unionList, secondList->data);
			secondList = secondList->next;
			continue;
		}
		if (secondList == NULL)
		{
			unionList = insertInEndOfList(unionList, firstList->data);
			firstList = firstList->next;
			continue;
		}
		if (firstList->data < secondList->data)
		{
			if (firstList != NULL)
			{
				unionList = insertInEndOfList(unionList, firstList->data);
				firstList = firstList->next;
				continue;
			}
		}
		if (firstList->data == secondList->data)
		{
			unionList = insertInEndOfList(unionList, firstList->data);
			firstList = firstList->next;
			secondList = secondList->next;
			continue;
		}
		unionList = insertInEndOfList(unionList, secondList->data);
		secondList = secondList->next;
	}
	return unionList;
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