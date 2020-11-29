#include "ULL.h"
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

ull_t* CreateHead() {
	ull_t* head;
	head = (ull_t*)malloc(sizeof(ull_t));
	if (head) {
		head->arrSize = 0;
		head->arrSize = NULL;
		return head;
	}
	else {
		return NULL;
	}
}
ull_t* CreateNewNode(ull_t* prev) {
	ull_t* node = (ull_t*)malloc(sizeof(ull_t));
	if (node) {
		node->arrSize = 0;
		node->nextBlock = NULL;
		prev->nextBlock = node;
		return node;
	}
	else {
		return NULL;
	}
}
ull_t* GetCurrentNode(ull_t* head) {
	ull_t* current;
	if (head->nextBlock != NULL) {
		current = head->nextBlock;
		while (current->nextBlock) {
			current = current->nextBlock;
		}
		return current;
	}
	else {
		return head;
	}
}
void AddElement(ull_t* head, int elem) {
	ull_t* current;
	ull_t* node;
	current = GetCurrentNode(head);
	if (current == NULL) {
		return;
	}
	if (current->arrSize == SIZE) {
		node = CreateNewNode(current);
		node->arr[0] = elem;
		node->arrSize = 1;
	}
	else {
		current->arr[current->arrSize] = elem;
		current->arrSize++;
	}
}
void DeleteElement(ull_t* head, int num) {
	int i, n = 0, j;
	ull_t* buf;
	buf = head;
	while (buf) {
		for (i = 0; i < buf->arrSize; i++) {
			n++;
			if (n == num) {
				for (j = i; j < buf->arrSize - i - 1; j++) {
					buf->arr[j] = buf->arr[j + 1];
				}
				buf->arrSize--;
				return;
			}
		}
		buf = buf->nextBlock;
	}
}
int GetElementNum(ull_t* head, int num) {
	int i, n = 0;
	ull_t* buf;
	buf = head;
	while (buf) {
		for (i = 0; i < buf->arrSize; i++) {
			n++;
			if (n == num) {
				return buf->arr[i];
			}
		}
		buf = buf->nextBlock;
	}
	return ERROR;
}
int GetNumKey(ull_t* head, int key) {
	int i, n = 0;
	ull_t* buf;
	buf = head;
	while (buf) {
		for (i = 0; i < buf->arrSize; i++) {
			if (buf->arr[i] == key) {
				n++;
				return n;
			}
			n++;
		}
		buf = buf->nextBlock;
	}
	return ERROR;
}
int GetNextElementKey(ull_t* head, int key) {
	int i, n = 0;
	ull_t* buf;
	buf = head;
	while (buf) {
		for (i = 0; i < buf->arrSize; i++) {
			if (buf->arr[i] == key) {
				if (i == (buf->arrSize - 1)) {
					return buf->nextBlock->arr[0];
				}
				else {
					return buf->arr[i + 1];
				}
			}
			n++;
		}
		buf = buf->nextBlock;
	}
	return ERROR;
}
int GetCountElements(ull_t* head) {
	int i, n = 0;
	ull_t* buf;
	buf = head;
	while (buf) {
		for (i = 0; i < buf->arrSize; i++) {
			n++;
		}
		buf = buf->nextBlock;
	}
	return n;
}