#pragma once
#include <stdio.h>

#define N 2

int flagSort;
int flagSameLength;

typedef struct list {
    struct list* previous;
    char string[100];
} list;

int ReadList(list* mylist, FILE* F);

list* SortSubstitution(list* word);

void ListPrint(list* word);

void ListCountMore(list* word);

void ListCountSame(list* word, int number);

void SortList(list* mylist);
