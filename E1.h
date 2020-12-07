#ifndef E1_H_INCLUDED__
#define E1_H_INCLUDED__
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

#define FOUND 1
#define NOTFOUND -1

typedef struct tree {
  int key;
  int height;
  struct tree* left;
  struct tree* right;
} tree_t;

tree_t* addTree(tree_t* tree, int key);
tree_t* delTree(tree_t* tree, int key);
int findTree(tree_t* tree, int key);
void printTree(tree_t* tree, int index);
void freeTree(tree_t* tree);
tree_t* readString(tree_t* tree);

#endif