#pragma once

#include <stdio.h>

#define stsize 20
#define EQUAL_STR 0
#define STR1BIG 1
#define STR2BIG -1

typedef struct list_p {
	struct list_p* next;
	char word[stsize];
}list_p;

void EnterWord (list_p* list, char* word);
list_p* InitList (char* word);
void DeleteList (list_p* list);
void FindPlaceForWord (list_p** list, char word[], list_p** pWord, list_p** nWord);
list_p* AddWord (list_p* nWord, list_p* pWord, char* word);
void Add2List (list_p** list, char word[]);
void PrintList (list_p* list, FILE* file3);
void UnionList (list_p* list2, list_p* list1);
void UnionAndPrintList (list_p* list1, list_p* list2, FILE* file3);