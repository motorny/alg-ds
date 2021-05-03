#pragma once

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	int val;
	int height;
	struct node* right;
	struct node* left;
} node_t;

int getHeight(node_t* tree);
void CorrectHeight(node_t* tree);
int BalancedFactor(node_t* tree);
node_t* RotateRight(node_t* tree);
node_t* RotateLeft(node_t* tree);
node_t* BalanceTree(node_t* tree);
int FindNode(node_t* tree, int num);
node_t* AddNode(node_t* tree, int num);
node_t* FindMin(node_t* tree);
node_t* RemoveMin(node_t* tree);
node_t* RemoveNode(node_t* tree, int num);
void DestroyTree(node_t* tree);