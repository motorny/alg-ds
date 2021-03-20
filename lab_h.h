#pragma once

#define FOUND 3
#define NOT_FOUND 4
#define MEM_ERROR 5
#define TREE_ERROR 6

typedef struct node {
	int num;
	int height;
	struct node* right;
	struct node* left;
} node_t;

int HeightOfTree(node_t* tree);

void CorrectHeight(node_t* tree);

int BalancedFactor(node_t* tree);

node_t* RotateRight(node_t* tree);

node_t* RotateLeft(node_t* tree);

node_t* BalanceTree(node_t* tree);

int SearchInTree(node_t* tree, int num);

node_t* AddInTree(node_t* tree, int num);

node_t* FindMin(node_t* tree);

node_t* RemoveMin(node_t* tree);

node_t* RemoveNode(node_t* tree, int num);

void DestroyTree(node_t* tree);

void WhatToDo(node_t* tree);
