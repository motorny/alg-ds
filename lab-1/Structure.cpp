#include "Structure.h"

ListNode* InitList()
{
	ListNode* head;
	ListNode* tail;
	head = (ListNode*)malloc(sizeof(ListNode));
	tail = (ListNode*)malloc(sizeof(ListNode));
	if (head == NULL || tail == NULL) return NULL;
	else
	{
		head->name = "Head";
		head->date = 0;
		head->next = tail;
		tail->name = "Tail";
		tail->date = INT_MAX;
		tail->next = NULL;
	}
	return head;
}

void DestroyList(ListNode* head)
{
	ListNode* headFixed = head;
	while (head->next != NULL)
	{
		while (head->next->next != NULL)
			head = head->next;
		free(head->next);
		head->next = NULL;
		head = headFixed;
	}
	free(head);
}

void PushNode(ListNode* p, ListNode* q)
{
	q->next = p->next;
	p->next = q;
}

ListNode* InitListNode(char* name, int date)
{
	ListNode* ptr;
	ptr = (ListNode*)malloc(sizeof(ListNode));
	if (ptr == NULL) return NULL;
	else
	{
		ptr->date = date;
		ptr->name = name;
	}
	return ptr;
}

ListNode* FindPlaceToPush(ListNode* head,int date)
{
	while (date >= head->next->date)
		head = head->next;
	return head;
}

int CountNodes(ListNode* head) //without 2 fictitous elems
{
	int count = 1;
	while (head->next != NULL)
	{
		head = head->next;
		count++;
	}
	return count - 2;
}

ListNodePtrArray FindByDate(ListNode* head, int date, int* count) //write down in count amount of finded persons
{
	ListNodePtrArray Array;
	int MaxSize = CountNodes(head);
	if (MaxSize > 0)
	{
		Array = (ListNodePtrArray)malloc(sizeof(ListNodePtr) * MaxSize);
		if (Array == NULL) return NULL;
		else
		{
			while (head->date <= date)
			{
				if (head->date == date)
				{
					Array[*count] = head;
					(*count)++;
				}
				head = head->next;
			}
		}
	}
	else return NULL;
	return Array;
}