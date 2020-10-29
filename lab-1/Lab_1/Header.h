#pragma once

typedef struct node {
	char* data;
	struct node* next;
} node_t;

typedef struct list {
	struct node* head;
} list_t;

typedef enum comp {
	less = -1,
	equal = 0,
	more = 1
} comp_t;

list_t* CreateList(void);

void DestroyList(list_t* list);

void PrintLine(char* str);

void PrintList(list_t* list);

int Length(char* str);

char* CopyStr(char* from);

void AddToList(list_t* list, char data[]);

list_t* SortList(list_t* list);



