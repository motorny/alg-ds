#ifndef TREE_H_INCLUDED__
#define TREE_H_INCLUDED__
#pragma once

#include<stdio.h>
#include<stdlib.h>

#define FOUND 1
#define NOTFOUND -1
#define ORDER 4
#define LEAF 4
#define NOTLEAF -4

//B+-tree
typedef struct tree {
  int keys[2 * ORDER];
  struct tree* nodes[2 * ORDER + 1];
  struct tree* parent;
  struct tree* left, *right;
  int numOfNode;
  int isLeaf;
} tree_t;

tree_t* createTree(void);
int findKey(tree_t* tree, int key);
void insertKey(tree_t** root, int key);
void deleteKey(tree_t* tree, int key);
void deleteTree(tree_t* tree);
void printTree(tree_t* tree, int index, int child);

#endif