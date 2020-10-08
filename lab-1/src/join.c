#include "join.h"
#include <stdlib.h>
#include <string.h>
static void GenerateString(char* string, int length) {
	int i = 0;
	length = rand() % (length - 1) + 1;
	for (i=0; i < length; i++) {
		string[i] = (char)(rand() % 94 + 32);
	}
	string[length] = '\0';
}

struct Data GenerateOne(struct Data* prev) {
	int begin = 0;
	if (prev != NULL) {
		begin = prev->int_field;
	}
	struct Data newfunc;
	newfunc.int_field = begin + rand() % 20 + 1;
	GenerateString(newfunc.str_field1, SIZE);
	GenerateString(newfunc.str_field2, SIZE);
	return newfunc;
}

void WriteToFile(FILE* f, int n) {
	struct Data t1;
	struct Data t2;
	int i = 1;
	if (n == 0) {
		return;
	}
	t1 = GenerateOne(NULL);
	fwrite(&t1, sizeof(struct Data), 1, f);
	for (i = 1; i < n; i++) {
		t2 = GenerateOne(&t1);
		t1 = t2;
		fwrite(&t1, sizeof(struct Data), 1, f);
	}
}

void Add(struct List* list, struct Data* data) {
	struct Node* node;
	struct Node* node1;
	if (data == NULL) {
		return;
	}
	if (list->size == 0) {
		list->first = malloc(sizeof(struct Node));
		list->first->data = *data;
		list->first->next = NULL;
		list->size++;
		return;
	}
	node = list->first;
	if (node->data.int_field > data->int_field) {
		list->first = malloc(sizeof(struct Node));
		list->first->data = *data;
		list->first->next = node;
		list->size++;
		return;
	}
	while (node->next != NULL) {
		if (node->next->data.int_field > data->int_field) {
			break;
		}
		else {
			node = node->next;
		}
	}
	node1 = malloc(sizeof(struct Node));
	node1->data = *data;
	node1->next = node->next;
	node->next = node1;
	list->size++;
}

struct Data Get(struct List* list,int number) {
	int i = 0;
	struct Node* elem = list->first;
	struct Data error;
	if (number >= list->size) {
		strcpy(error.str_field1, "Error");
		return error;
	}
	while (i<number){
		elem = elem->next;
		i++;
	}
	return elem->data;
}

static struct Node* AddLast(struct List* list, struct Node* elem_last, struct Data* data) {
	if (list->first == NULL) {
		list->first=malloc(sizeof(struct Node));
		list->first->data = *data;
		list->first->next = NULL;
		list->size++;
		return list->first;
	}
	else {
		elem_last->next = malloc(sizeof(struct Node));
		elem_last->next->data = *data;
		elem_last->next->next = NULL;
		list->size++;
		return elem_last->next;
	}
}

struct List Join(struct List* list1, struct List* list2) {
	struct Node* elem1 = list1->first;
	struct Node* elem2 = list2->first;
	struct Node* elem_final = NULL;
	struct List list_final;
	list_final.first = NULL;
	list_final.size = 0;
	while (elem1 != NULL || elem2 != NULL) {
		if (elem1 == NULL) {
			elem_final = AddLast(&list_final, elem_final,&(elem2->data));
			elem2 = elem2->next;
		}
		else if (elem2 == NULL) {
			elem_final = AddLast(&list_final, elem_final, &(elem1->data));
			elem1 = elem1->next;
		}
		else {
			if (elem1->data.int_field > elem2->data.int_field) {
				elem_final = AddLast(&list_final, elem_final, &(elem2->data));
				elem2 = elem2->next;
			}
			else {
				elem_final = AddLast(&list_final, elem_final, &(elem1->data));
				elem1 = elem1->next;
			}
		}
	}
	return list_final;
}

void Free(struct List* list) {
	struct Node* t;
	struct Node* t2;
	if (!list || !list->first) {
		return ;
	}
	t = list->first;
	t2 = t;
	while (t->next) {
		t = t->next;
		free(t2);
		t2 = t;
	}
}


