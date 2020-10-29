
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Header.h"
#pragma warning(disable: 4996)

list_t* CreateList(void) {
	list_t* list = malloc(sizeof(list));
	assert(list);
	list->head = NULL;
	return list;
}

void DestroyList(list_t* list) {
	node_t* tmp;
	if (list == NULL) return;
	while (list->head != NULL) {
		tmp = list->head;
		list->head = tmp->next;
		free(tmp->data);
		free(tmp);
	}
	free(list);
}

void PrintLine(char* str) {
	while ((*str) != 0) {
		printf("%c", *str);
		str++;
	}
}

void PrintList(list_t* list) {
	assert(list);
	node_t* tmp = list->head;
	while (tmp != NULL) {
		PrintLine(tmp->data);
		printf("\n");
		tmp = tmp->next;
	}
}

int Length(char* str) {
	int len = 0;
	while (str[len++]);
	return len;
}

char* CopyStr(char* from) {
	int length = Length(from), i;
	char* to = malloc((length + 1) * sizeof(char));
	for (i = 0; i <= length; i++) {
		to[i] = from[i];
	}
	return to;
}

void AddToList(list_t* list, char data[]) {
	node_t* newNode = malloc(sizeof(node_t));
	assert(newNode);
	newNode->data = CopyStr(data);
	newNode->next = list->head;
	list->head = newNode;
}

list_t* SortList(list_t* list) {
	node_t* startlist = (node_t*)malloc(sizeof(node_t)), * current = (node_t*)malloc(sizeof(node_t)), * listprev = (node_t*)malloc(sizeof(node_t)), * listnext = (node_t*)malloc(sizeof(node_t)), * newlist = (node_t*)malloc(sizeof(node_t));
	list_t* newhead = (list_t*)malloc(sizeof(list_t));
	char* maxdata = (char*)malloc(sizeof(char));
	comp_t iscompare;
	int count = 0;
	assert(startlist);
	assert(listnext);
	assert(newhead);
	assert(current);
	assert(listprev);
	newlist = list->head;
	newhead->head = NULL;
	current = list->head;
	while (list->head != NULL) {
		current = list->head;
		maxdata = list->head->data;
		listprev = current;
		newlist = list->head;
		while (list->head->next != NULL) {
			startlist = list->head;
			listnext = list->head->next;
			iscompare = strcmp(maxdata, listnext->data);
			if (iscompare == less) {
				maxdata = listnext->data;
				current = listnext;
				listprev = startlist;
			}
			list->head = list->head->next;
		}
		if (newlist->data == maxdata) {
			list->head = current->next;
			current->next = newhead->head;
			newhead->head = current;
		}
		else {
			listprev->next = current->next;
			list->head = newlist;
			current->data = maxdata;
			current->next = newhead->head;
			newhead->head = current;
		}
	}
	return newhead;
}

int main(void) {
	list_t* list = CreateList();
	AddToList(list, "cck flk");
	AddToList(list, "-4u4");
	AddToList(list, "42kf ngp0");
	AddToList(list, "42kf deffn gp0");
	AddToList(list, "&3298 328u31/fwef12./,");
	AddToList(list, "u *%");
	AddToList(list, "-_-");

	PrintList(list);
	list = SortList(list);
	printf("\n");
	PrintList(list);
	DestroyList(list);
	return 0;
}

