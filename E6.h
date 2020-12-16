#ifndef __TREE_H_
#define __TREE_H_

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
#define SIZE 100

typedef struct node {
	char key[SIZE];
	struct node* left;
	struct node* right;
}node;

int  ReadFile(node **mytree, char *filename);
void Print(node* mytree);
void DeleteAll(node** mytree);

#endif