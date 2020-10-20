#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NOT_ENOUGH_MEMORY  1
#define CANNOT_OPEN_FILE   2
#define INCORRECT_START    3

typedef struct _EmployerInfo
{
	struct tm mytime;
	char firstName[255];
	char secondName[255];
	int payload;
}EmployerInfo;

typedef struct node
{
	void* data;
	struct node* next;
}node;

#ifdef __cplusplus
extern "C" {
#endif

	int ReadFromFile(char* FileName, node** head);

	void DestroyList(node** head);

	bool EmployersPredicate(void* old, void* next);

	void InsertNodeInList(node** head, node* ptr, bool(*predicate)(void*, void*));

	void PrintList(node** list, int N);

#ifdef __cplusplus
}
#endif

#endif