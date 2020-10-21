#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"List.h"
UnrolledList* ListCreate() {
	UnrolledList* list = malloc(sizeof(UnrolledList));
	assert(list);
	list->next = NULL;
	list->NumElements = 0;
	return list;
};

void ListDestroy(UnrolledList* list) {
	while (list) {
		UnrolledList* tmp = list;
		list = list->next;
		free(tmp);
	}
}

Bool AddElem(UnrolledList* list, int elem) {

	if (!list) {
		return FAILED;
	}
	while (list->next) {
		list = list->next;
	}
	if (list->NumElements == MAX_ELEMENTS) {
		UnrolledList* tmp = malloc(sizeof(UnrolledList));
		assert(tmp);
		list->next = tmp;
		tmp->NumElements = 0;
		tmp->next = NULL;
		list = list->next;
	}
	list->array[list->NumElements++] = elem;
	return SUCCESS;
}

int* FindElem(UnrolledList* list, int num) {
	int k = 0;
	assert(list);
	assert(num >= 0);
	for (int i = 0; (i < num) && (list); i++) {
		if (k >= list->NumElements - 1) {
			list = list->next;
			k = 0;
		}
		else
			k++;
	}
	if ((!list) ||(k >= list->NumElements))
		return NULL;
	return list->array + k;
}

Bool DeleteElem(UnrolledList* list, int num) {
	assert(list);
	assert(num >= 0);
	int array[MAX_ELEMENTS - 1] = { 0 }, countNum = 0;
	for (int i = 0; (i < num) && (list); i++) {
		if (countNum >= list->NumElements - 1) {
			list = list->next;
			countNum = 0;
		}
		else
			countNum++;
	}
	if ((!list) || (countNum >= list->NumElements))
		return FAILED;
	for (int i = 0, k = 0; i < list->NumElements; i++) {
		if (i != (countNum)) {
			array[k++] = list->array[i];
		}
		else {
			list->array[i] = 0;
		}
	}
	list->NumElements--;

	for (int i = 0; i < list->NumElements; i++) {
		list->array[i] = array[i];
	}
	return SUCCESS;
}

int FindSize(UnrolledList* list) {
	int k = 0, i;
	for (i = 0;list; i++) {
		if (k >= list->NumElements - 1) {
			list = list->next;
			k = 0;
		}
		else
			k++;
	}
	return i;
}

int* FindNextElem(UnrolledList* list, int compareNum) {
	int size = FindSize(list), k = 0;
	while (list) {
		for (int i = 0; i < list->NumElements; i++, k++) {
			if ((compareNum == list->array[i]) && ((k + 1) != size)) {
				if ((i + 1) == list->NumElements) {
					list = list->next;
					return list->array;
				}
				else
				{
					return list->array + i + 1;
				}

			}
		}
		list = list->next;
	}
	return NULL;
}

int FindByKey(UnrolledList* list, int compareNum) {
	int k = 0;
	while (list) {
		for (int i = 0; i < list->NumElements; i++, k++) {
			if (compareNum == list->array[i])
				return k;
		}
		list = list->next;
	}
	return -1;
}