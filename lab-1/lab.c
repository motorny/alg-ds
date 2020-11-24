#include <stdlib.h>
#include "qu.h"
#include <malloc.h>

int* InitArray(int size) {
	
	return (int*)malloc(sizeof(int) * size);

}

int IsQuArrayEmpty(quArray_t quAr) {

	return quAr.last == quAr.first;

}

int PushQuArray(int data, quArray_t* quAr) {
	
	int* tmp;
	if (quAr->size == 0) {
		tmp = (int*)realloc(quAr->data, sizeof(int));
		if (tmp != NULL) {
			quAr->data = tmp;
		}
		else {
			return 1;
		}
		quAr->last = 0;
		quAr->first = 0;
		quAr->data[quAr->first] = data;
		quAr->size = 1;
	}
	else {
		if (IsQuArrayEmpty(*quAr)) {
			tmp = (int*)realloc(quAr->data, sizeof(int) * 2);
			if (tmp != NULL) {
				quAr->data = tmp;
			}
			else {
				return 1;
			}
			quAr->last = quAr->first++;
			quAr->data[quAr->last] = data;
			quAr->size = 2;
		}
		else {
			tmp = (int*)realloc(quAr->data, sizeof(int) * (quAr->size + 1));
			if (tmp != NULL) {
				quAr->data = tmp;
			}
			else {
				return 1;
			}
			quAr->last++;
			quAr->data[quAr->last] = data;
			quAr->size++;
		}
		
	}


	return 0;
}

int PopQuArray(quArray_t* quAr) {
	
	int tmp;

	if (quAr->size <= 0) {
		return NULL;
	}
	if (quAr->size > 1) {
		quAr->first++;
		return quAr->data[quAr->first - 1];
	}
	else {
		tmp = quAr->first;
		quAr->first = NULL;
		quAr->last = NULL;
		quAr->size = 0;
		return quAr->data[tmp];
	}
}

quList_t InitQuList(int size, int* data) {

	quList_t quLi;
	int i;
	node_t* tmp;

	if (size == 1) {
		quLi.first = (node_t*)malloc(sizeof(node_t*));
		quLi.last = quLi.first;
		quLi.size = 1;
		quLi.first->data = data[0];
	}
	else {
		quLi.last = (node_t*)malloc(sizeof(node_t*));
		quLi.last->data = data[0];
		tmp = quLi.last;
		for (i = 1; i < size-1; i++) {
			tmp->next = (node_t*)malloc(sizeof(node_t*));			
			tmp->next->data = data[i];
			tmp = tmp->next;
		}
		quLi.first = (node_t*)malloc(sizeof(node_t*));
		tmp->next = quLi.last;
		quLi.first->data = data[size - 1];
		quLi.size = size;
	}
	return quLi;

}

int PushQuList(int data, quList_t* quLi) {

	if (quLi->size == 0) {
		quLi->first = (node_t*)malloc(sizeof(node_t*));
		if (quLi->first == NULL) {
			return 1;
		}
		quLi->last = quLi->first;
		quLi->first->data = data;
		quLi->first->next = NULL;
		quLi->size = 1;
	}
	else if (quLi->size == 1) {
		quLi->last = (node_t*)malloc(sizeof(node_t*));
		if (quLi->last == NULL) {
			return 1;
		}
		quLi->last->next = quLi->first;
		quLi->last->data = data;
		quLi->size = 2;
	}
	else {
		node_t* tmp = quLi->last;
		quLi->last = (node_t*)malloc(sizeof(node_t*));
		if (quLi->last == NULL) {
			return 1;
		}
		quLi->last->data = data;
		quLi->last->next = tmp;
	}

	return 0;
}

int PopQuList(quList_t* quLi) {

	int data;
	int i;
	node_t* tmp;

	if (quLi->size == 0) {
		return NULL;
	}
	else if (quLi->size == 1) {
		data = quLi->first->data;
		quLi->first = NULL;
		quLi->last = NULL;
		quLi->size = 0;
		return data;
	}
	else if (quLi->size == 2) {
		data = quLi->first->data;
		quLi->first = quLi->last;
		quLi->size =1;
		return data;
	}
	else {
		data = quLi->first->data;
		tmp = quLi->last;
		for (i = 0; i < quLi->size-2; i++) {
			tmp = tmp->next;
		}
		quLi->first = tmp;
		quLi->size--;
		return data;
	}

}