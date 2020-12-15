#pragma once
#pragma warning(disable: 4996)

typedef struct node {
	int data;
	struct node* next;
} node_t;

typedef struct stackList {
	struct node* head;
} stackList_t;

stackList_t* CreateStackList(void);

void DestroyStackList(stackList_t* stack);

void PushList(stackList_t* stack, int data);

int PopList(stackList_t* stack);

int LastList(stackList_t* stack);

void PrintStackList(stackList_t* stack);