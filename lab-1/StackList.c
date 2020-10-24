#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "StackList.h"
#pragma warning(disable: 4996)

stackList_t* CreateStackList(void) {
	stackList_t* stack = (stackList_t*)malloc(sizeof(stack));
	assert(stack);
	stack->head = NULL;
	return stack;
}

void DestroyStackList(stackList_t* stack) {
	node_t* tmp;
	if (stack == NULL) return;
	while (stack->head != NULL) {
		tmp = stack->head;
		stack->head = tmp->next;
		free(tmp);
	}
	free(stack);
}

void PushList(stackList_t* stack, int data) {
	node_t* newNode;
	assert(stack);
	newNode = (node_t*)malloc(sizeof(node_t));
	assert(newNode);
	newNode->next = stack->head;
	stack->head = newNode;
	newNode->data = data;
}

int PopList(stackList_t* stack) {
	node_t* top;
	int data;
	assert(stack);
	if (stack->head == NULL) return 0;
	top = stack->head;
	data = top->data;
	stack->head = top->next;
	free(top);
	return data;
}

int LastList(stackList_t* stack) {
	assert(stack);
	return stack->head->data;
}

void PrintStackList(stackList_t* stack) {
	node_t* node;
	if (stack == NULL) {
		printf("NULL\n");
		return;
	}
	node = stack->head;
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}