#pragma once
#ifndef __TREE_H_
#define __TREE_H_

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define TRUE 1
#define FALSE 0

#define MAX_STR 100

typedef struct Node Node;
struct Node {
	int key;
	int numberOfNodes;

	Node* left, * right;
	Node* father;
};

int AtT(Node** tree, Node* father, int key);
Node* FKLT(Node* tree, int key, int k);
void ClearTree(Node** tree);

#endif
