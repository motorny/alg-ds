#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode {
	struct ListNode* next;
	char* name;
	int date;
} ListNode;

typedef ListNode* ListNodePtr;
typedef ListNodePtr* ListNodePtrArray;

ListNode* InitList(); //init list with 2 fictitous elems
void DestroyList(ListNode* head);
void PushNode(ListNode* p, ListNode* q); //push q after p;
ListNode* InitListNode(char* name, int date);
ListNode* FindPlaceToPush(ListNode* head,int date); //you should push Node before result
int CountNodes(ListNode* head);
ListNodePtrArray FindByDate(ListNode* head, int date, int* count);