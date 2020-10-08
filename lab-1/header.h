#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct node_t{
	int day;
	int month;
	int year;
	int temperature;
	struct node_t* next;
} NODE;

typedef struct {
	NODE* first;
} LIST;

LIST* InitList(void);
void ReadFile(FILE* f, LIST* list);
void AddToList(LIST* list, int dd, int mm, int yy, int temp);
void Print(LIST* list);
int Search(LIST* list, int temp);
void FreeList(LIST* list);
