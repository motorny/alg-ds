#pragma once
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LETTER_COUNT 100
#define SAME_LENGTH_WITH_HEAD -2
#define SAME_LENGTH -1
#define NEW_HEAD 0
#define ADD_AFTER_SELECTED_LIST 1

typedef struct list {
	char word[MAX_LETTER_COUNT];
	struct list* next;
	unsigned CountOfLet;
}list;

unsigned int getcount(char* word);
list* ReadWord(FILE* f);
int FindCount(list** mylist, unsigned int contofnew);
int FindLetter(list** mylist, list* newlist, int i);
int FindRightPlace(list** mylist, list* newlist);
void AddtoList(list** head, list* newlist);
void PrintN(list* mylist,unsigned int N);
void PrintMoreN(list* mylist,unsigned int N);
void FreeList(list** mylist);
