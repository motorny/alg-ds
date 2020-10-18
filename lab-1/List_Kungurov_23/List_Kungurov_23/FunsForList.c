#include <stdio.h>
#include "FunsForList.h"
#include <stdlib.h>
#include <string.h>
void PutOnTheRightPlace(char* word, DoubleLinkedList* List) {
	Node* Begin = NULL;
	Node* tmp = NULL;
	if (List->size == 0) {
		Push(List, word);
		return;
	}
	if (List->size == 1) {
		tmp = (Node*)malloc(sizeof(Node));

		if (Compare(word, List->head->value) == 1) {
			tmp->value = word;
			List->head->prev = NULL;
			List->tail = tmp;
			List->tail->next = NULL;
			List->tail->prev = List->head;
			List->head->next = List->tail;
			List->size++;
		}
		if (Compare(word, List->head->value) == 0) {
			tmp->value = word;
			List->tail = List->head;
			List->tail->next = NULL;
			List->head = tmp;
			List->head->prev = NULL;
			List->head->next = List->tail;
			List->tail->prev = List->head;
			List->size++;
		}
		return;
	}
	else {
		if (Compare(word, List->head->value) == 0) {
			PushFront(List, word);
			return;
		}
		if (Compare(word, List->tail->value) == 1) {
			PushBack(List, word);
			return;
		}
		else {
			Begin = List->head;
			while (Compare(word, Begin->value) == 1) {
				if (Compare(word, Begin->next->value) == 0) {
					PutBeforeElement(List, Begin->next, word);
					return;
				}
				Begin = Begin->next;
			}
		}
	}
}
void Push(DoubleLinkedList* List, char* value) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->value = value;
	List->head = tmp;
	//List->tail = tmp;
	List->head->prev = NULL;
	//List->tail->next = NULL;
	//List->tail->prev = List->head;
	List->head->next = List->tail;
	List->size++;
}
DoubleLinkedList* CreateDoubleLinkedList() {
	DoubleLinkedList* tmp = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}
void DeleteDoubleLinkedList(DoubleLinkedList** List) {
	Node* tmp = (*List)->head;
	Node* next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*List);
	(*List) = NULL;
}

void PushFront(DoubleLinkedList* list, char* data) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->value = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head) {
		list->head->prev = tmp;
	}
	list->head = tmp;

	if (list->tail == NULL) {
		list->tail = tmp;
	}
	list->size++;
}
void PushBack(DoubleLinkedList* list, char* value) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}
void PrintDoubleLinkedList(DoubleLinkedList* List,void (*fun)(int N,char* value),int N) {
	Node* tmp = List->head;
	while (tmp!= NULL) {
		fun(N, tmp->value);
		tmp = tmp->next;
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
void PutBeforeElement(DoubleLinkedList* List, Node* Element, char* value) {
	Node* Putting = NULL;
	Putting = (Node*)malloc(sizeof(Node));
	Putting->value = value;
	Putting->prev = Element->prev;
	Element->prev->next = Putting;
	Element->prev = Putting;
	Putting->next = Element;
	List->size++;
}
void PrintTheN(int N, char* value) {
	if (strlen(value) == N) {
		printf("%s ", value);
	}
	return;
}
void PrintMoreThanN(int N, char* value) {
	if (strlen(value) > N) {
		printf("%s ", value);
	}
	return;
}