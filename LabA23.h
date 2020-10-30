#pragma once
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct list {
	char word[100];
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
