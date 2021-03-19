#pragma once
#include <stdio.h>

#define N 2

int flagSort;
int flagSameLength;

typedef struct list {
    struct list* previous;
    char string[100];
} list;

void MakeList(list* mylist, FILE* F);

void PutWord(list* old, list* newWord);

void WordToList(list* mylist, list* newWord);

void ListPrint(list* word);

void ListCountMore(list* word);

void ListCountSame(list* word, int number);

