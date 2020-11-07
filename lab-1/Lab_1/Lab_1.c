
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Header.h"
#pragma warning(disable: 4996)

list_t* CreateList(void) {
	list_t* list = malloc(sizeof(list));
	if (list == NULL)
		return NULL;
	list->head = NULL;
	return list;
}

list_t* DestroyList(list_t* list) {
	while (list->head != NULL) {
		node_t* p = list->head;
		list->head = list->head->next;
		free(p);
	}
	return list->head;
}

void PrintLine(char* str) {
	while ((*str) != 0) {
		printf("%c", *str);
		str++;
	}
}

void PrintList(list_t* list) {
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
	if (to == NULL)
		return NULL;
	for (i = 0; i <= length; i++) {
		to[i] = from[i];
	}
	return to;
}

void AddToList(list_t* list, char data[]) {
	node_t* newNode = malloc(sizeof(node_t));
	if (newNode == NULL)
		list == NULL;
	newNode->data = CopyStr(data);
	newNode->next = list->head;
	list->head = newNode;
}

list_t* SortList(list_t* list) {
	node_t* startlist = (node_t*)malloc(sizeof(node_t)), * current = (node_t*)malloc(sizeof(node_t)), * listprev = (node_t*)malloc(sizeof(node_t)), * listnext = (node_t*)malloc(sizeof(node_t)), * newlist = (node_t*)malloc(sizeof(node_t));
	list_t* newhead = (list_t*)malloc(sizeof(list_t));
	char* maxdata = (char*)malloc(sizeof(char));
	if (maxdata == NULL)
		return NULL;
	comp_t iscompare;
	int count = 0;
	if (startlist == NULL)
		return NULL;
	if (listnext == NULL)
		return NULL;
	if (newhead == NULL)
		return NULL;
	if (current == NULL)
		return NULL;
	if (listprev == NULL)
		return NULL;
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

//int main(void) {
//	list_t* list = CreateList();
//	AddToList(list, "cck flk");
//	AddToList(list, "-4u4");
//	AddToList(list, "42kf ngp0");
//	AddToList(list, "42kf deffn gp0");
//	AddToList(list, "&3298 328u31/fwef12./,");
//	AddToList(list, "u *%");
//	AddToList(list, "-_-");
//
//	PrintList(list);
//	list = SortList(list);
//	printf("\n");
//	PrintList(list);
//	DestroyList(list);
//	return 0;
//}

