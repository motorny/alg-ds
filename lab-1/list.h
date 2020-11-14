#pragma once

#define maxLength 15

typedef struct list_t {
	char* str;
	struct list_t* next;
}list_t;



void ListDestroy(list_t* list);

char* Merge(list_t* list, int n);

list_t* InsertNode(char word[]);

list_t* Insert(char s[][maxLength], int n);

