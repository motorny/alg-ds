

#pragma once
#define MAX_ELEMENTS 4

typedef struct UnrolledList {
	struct UnrolledList* next;
	int NumElements;
	int array[MAX_ELEMENTS];
}UnrolledList;

typedef enum Bool {
	FAILED,
	SUCCESS
}Bool;

UnrolledList* ListCreate();

void ListDestroy(UnrolledList* list);

Bool AddElem(UnrolledList* list, int elem);

int* FindElem(UnrolledList* list, int num);

Bool DeleteElem(UnrolledList* list, int num);

int FindSize(UnrolledList* list);

int* FindNextElem(UnrolledList* list, int compareNum);

int FindByKey(UnrolledList* list, int compareNum);
