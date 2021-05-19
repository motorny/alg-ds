#pragma once
#ifndef __btree_h__
#define __btree_h__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#pragma warning(disable:4996)

#define TRUE 1
#define FALSE 0
#define SIZE 3

typedef struct node_t node_t;
struct node_t {
    int size;
    int values[SIZE - 1];
    node_t* child[SIZE];
};


typedef struct {
    int t;
    node_t* root;
} tree_t;

node_t* createNode(int value);
int addElem(tree_t* root, int value);
int deleteElem(tree_t* Tree, int value);
int searchElem(tree_t root, int value);
void printTree(node_t* tree, int lvl);
void funcTree(tree_t tree);


#endif // !__btree_h__