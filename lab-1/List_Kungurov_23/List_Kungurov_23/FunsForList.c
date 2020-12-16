#include <stdio.h>
#include "FunsForList.h"
#include <stdlib.h>
#include <string.h>
#define OUT_OF_MEM -1
#define SUCCESS 0
int PutOnTheRightPlace(char* word, DoubleLinkedList* list) {
	Node* begin = NULL;
	Node* tmp = NULL;
	int RESULT;

	if (list->size == 0 /*||(Compare(word, list->head->value) == 0) */) {
			RESULT = PushFront(list, word);
			return RESULT;
	}
	if (list->size == 1 /* || (Compare(word, list->tail->value) == 1)*/ ) {
			RESULT = PushBack(list, word);
			return RESULT;
	}
	if (list->size > 1) {
		if ((Compare(word, list->tail->value) == 1)) {
			RESULT = PushBack(list, word);
			return RESULT;
		}
		if ((Compare(word, list->head->value) == 0)) {
			RESULT = PushFront(list, word);
			return RESULT;
		}
		else {
			begin = list->head;
			while (Compare(word, begin->value) == 1) {
				if (Compare(word, begin->next->value) == 0) {
					PutBeforeElement(list, begin->next, word);
					return SUCCESS;
				}
				begin = begin->next;
			}
		}
	}
	return SUCCESS;
}
DoubleLinkedList* CreateDoubleLinkedList(int RESULT) {
	DoubleLinkedList* tmp = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
	if (tmp == NULL) {
		RESULT = OUT_OF_MEM;
		return NULL;
	}
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;
	RESULT = SUCCESS;
	return tmp;
}
void DeleteDoubleLinkedList(DoubleLinkedList** list) {
	Node* now = (*list)->head;
	Node* next = NULL;
	while (now) {
		next = now->next;
		free(now);
		now = next;
	}
	free(*list);
	(*list) = NULL;
}

int PushFront(DoubleLinkedList* list, char* data) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	if(tmp == NULL) {
		return OUT_OF_MEM;
	}
	tmp->value = data;
	if (list->size == 0) {
		list->tail = NULL;
		list->head = tmp;
		list->head->prev = NULL;
		list->head->next = list->tail;
		list->size++; 
		return SUCCESS;
	}
	tmp->next = list->head;
	tmp->prev = NULL;
	list->head->prev = tmp;
	list->head = tmp;
	list->size++;
	return SUCCESS;

}
int PushBack(DoubleLinkedList* list, char* data) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		return OUT_OF_MEM;
	}
	tmp->value = data;
	if (list->size == 1) {
		if (Compare(data, list->head->value) == 0) {
			list->tail = list->head;
			list->tail->next = NULL;
			tmp->next = list->tail;
			tmp->prev = NULL;
			list->tail->prev = tmp;
			list->head = tmp;
			list->size++;
			return SUCCESS;
		}
		if (Compare(data, list->head->value) == 1) {
			tmp->next = NULL;
			tmp->prev = list->head;
			list->head->next = tmp;
			list->head->prev = NULL;
			list->tail = tmp;
			list->size++;
			return SUCCESS;
		}
	}
	tmp->next = NULL;
	tmp->prev = list->tail;
	list->tail->next = tmp;
	list->tail = tmp;
	list->size++;
	return SUCCESS;
}
void PrintDoubleLinkedListMoreThanN(DoubleLinkedList* list, int N) {
	Node* now = list->head;
	while (now!= NULL) {
		if (strlen(now->value) > N) {
			printf("%s ", now->value);
		}
		now = now->next;
	}
	printf("\n");
}
void PrintDoubleLinkedListTheN(DoubleLinkedList* list, int N) {
	Node* now = list->head;
	while (now != NULL) {
		if (strlen(now->value) == N) {
			printf("%s ", now->value);
		}
		now = now->next;
	}
	printf("\n");
}
int Compare(char* Word, char* WordFromList) {
	if (strlen(Word) > strlen(WordFromList)) {
		return 1;
	}
	if (strlen(Word) == strlen(WordFromList)) {
		if (strcmp(Word, WordFromList) < 0) {
			return 0;
		}
		if (strcmp(Word, WordFromList) > 0) {
			return 1;
		}
		else {
			return 1;
		}
	}
	else {
		return 0;
	}
}
int PutBeforeElement(DoubleLinkedList* list, Node* element, char* value) {
	Node* putting = NULL;
	putting = (Node*)malloc(sizeof(Node));
	if (putting == NULL) {
		return OUT_OF_MEM;
	}
	putting->value = value;
	putting->prev = element->prev;
	element->prev->next = putting;
	element->prev = putting;
	putting->next = element;
	list->size++;
	return SUCCESS;
}