#pragma once

typedef struct node{
	char* cont;
	struct node* next;
	struct node* prev;
}Node;

typedef struct list{
	Node* head;
	Node* tail;
}List;

typedef enum {
	FALSE = 0,
	TRUE = 1,
}Bool;


List* createList();
Bool addNode(List* pList, const char* str, int n);
void destroyList(List* pList);
void printList(List* pList);