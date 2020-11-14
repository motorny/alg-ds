#include<stdio.h>
#include"list.h"
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#pragma warning(disable:4996)


void ListDestroy(list_t* list) {
	list_t* tmp = list;

	while (tmp->next != NULL) {
		list = tmp->next;
		free(tmp);
		tmp = list;
	}
	free(list);
}

char* Merge(list_t* list, int n) {
	int k = 0;
	int mem = maxLength * n;
	if (!list)
		return NULL;
	char* str = malloc(mem * sizeof(char));
	assert(str);
	while (list) {
		k += sprintf(str + k, "%s", list->str);

		list = list->next;

	}
	return str;
}

list_t* InsertNode(char word[]) {

	list_t* elem = (list_t*)malloc(sizeof(list_t));
	assert(elem);

	elem->str = word;
	elem->next = NULL;
	return elem;
}

list_t* Insert(char s[][maxLength], int n) {
	int i = 0;
	list_t* list = NULL;
	
	list = InsertNode(s[i]);
	assert(list);
	i++;
	list_t* e = list;
	while (i < n) {
		list->next = InsertNode(s[i]);
		list = list->next;
		i++;
	}

	return e;
}



