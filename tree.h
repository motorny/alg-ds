#ifndef TREE_H_INCLUDED__
#define TREE_H_INCLUDED__
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#pragma warning (disable: 4996)

#define TRUE 1
#define FALSE 0

typedef struct node node_t;
struct node {
  int key;
  int height;
  node_t* left;
  node_t* right;
};

int minSubtree(node_t* tree);
int addNode(node_t** tree, int elem);
int deleteElem(node_t** tree, int elem);
int findElem(node_t* tree, int elem);
void printHeightTree(node_t* tree, int level);
node_t* funcTree(node_t* tree);
void deleteTree(node_t* tree);

#endif