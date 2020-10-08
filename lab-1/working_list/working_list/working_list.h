#pragma once
#ifndef __WORKING_LIST__
#define __WORKING_LIST__

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LE 15
#define NO_MATCH 1
#define MATCH 0
#define ERROR_OPENING_FILE -1
#define EMPTY_ELEMENT 2

typedef struct node {
    char surname[MAX_LE];
    char name[MAX_LE];
    char scndname[MAX_LE];
    struct node* next;
} tnode;

void GetInfo(tnode* person, char* surname, char* name, char* scndname);

tnode* ConvertInputToNode(char* tmp);

tnode* GetPtrLast(tnode* top);

int AddToList(tnode** top, tnode* person);

int Compare(tnode* person_l, tnode* info);

int PrintFilteredList(tnode** top, tnode* input);

void PrintInitialList(tnode** top);

void FreeList(tnode** top);
#endif 

