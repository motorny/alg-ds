#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct tree
{
	int data;
	struct tree* left;
	struct tree* right;
} TREE;

void addToTree(TREE** tree, int data);
void delByData(TREE** tree, int data);
int findByValue(TREE* tree, int data);
void workingWithTree(TREE** tree);
TREE* subtreeHeightDif(TREE* tree);
void printTree(TREE* tree, int index);

#endif // !TREE_H
