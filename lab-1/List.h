#pragma once

typedef enum
{
	FALSE,
	TRUE
} Bool;

typedef struct list
{
	int data;
	struct list* next;
} LIST;

LIST* initList();
void delList(LIST* head);
LIST* insertInList(LIST* head, int data);
LIST* deleteItem(LIST* head, int data);
Bool searchItemInList(LIST* head, int data);
LIST* intersection(LIST* head1, LIST* head2);
LIST* unionOfSets(LIST* head1, LIST* head2);
void printList(LIST* head);