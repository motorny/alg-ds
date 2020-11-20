    #pragma once

#define maxLength 15

typedef struct list_t {
	char* str;
	struct list_t* next;
}list_t;



void ListDestroy(list_t* list);

int Length(char s[][maxLength], int n);

char* Merge(list_t* list, int n);

list_t* InsertStrToList(char word[]);

list_t* InsertTextToList(char s[][maxLength], int n);


    
