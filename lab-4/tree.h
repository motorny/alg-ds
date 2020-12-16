#pragma once

#define FOUND 3
#define NOT_FOUND 4
#define MEM_ERROR 5
#define TREE_ERROR 6

typedef struct node_t {
	int num;
	struct node_t* left;
	struct node_t* right;
} node_t;

void InitTree(node_t** tree, int num, int* error);
void AddInTree(node_t** tree, int num);
void RemoveFromTree(node_t** tree, int num);
void DestroyTree(node_t* tree);
int SearchInTree(node_t* tree, int num);
void PrintTree(node_t* tree, int n);
void TaskPrint(node_t* tree);
void WhatToDo(node_t** tree);
