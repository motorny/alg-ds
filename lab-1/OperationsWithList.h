#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define NOTSAME 1
#define SAME 0
#define ERROR_OPENING_FILE -1
#define SUCCESS_ADD 0
#define ADDED 2

typedef struct List {
  char surname[SIZE];
  char name[SIZE];
  char father[SIZE];
  struct List* next;
} List;

void GetStr(List* person, char* surname, char* name, char* scndname);

List* TransformToList(char* tmp);

int AddToList(List** top, List* person);

int Compare(List* person_l, List* info);

int PrintRequest(List** top, List* input);

void PrintList(List** top);

void FreeList(List** top);