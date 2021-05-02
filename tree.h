#ifndef TREE_H_INCLUDED__
#define TREE_H_INCLUDED__
#pragma once

#include<stdio.h>
#include<stdlib.h>

#define NOTENOUGHNODES 0
#define FOUND 1
#define NOTFOUND -1
#define ORDER 4
#define LEAF 4
#define NOTLEAF -4

//B-tree
typedef struct tree {
  int keys[2 * ORDER - 1];
  struct tree* nodes[2 * ORDER];
  int numOfNode;
  int isLeaf;
} tree_t;

tree_t* findKey(tree_t* tree, int key);
void insertKey(tree_t** tree, int key);
void deleteKey(tree_t** root, int key);
void deleteTree(tree_t* tree);

#endif