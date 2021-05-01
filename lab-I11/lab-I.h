#ifndef LAB_I_INCLUDED
#define LAB_I_INCLUDED
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma warning (disable: 4996)

typedef struct tree_t {
  bool isLeaf;
  int value, maxValue;
  struct tree_t* lc, * mc, * rc;
  int ln, rn, amountChildren; //2 or 3 children
  struct tree_t* parent;
}tree_t;

//for extra operations
typedef struct stack_t {
  tree_t* tree;
  struct stack_t* next;
}stack_t;

bool Insert(tree_t** tree, int key);
bool Find(tree_t* tree, int key);
bool Delete(tree_t** tree, int key);

bool Merge(tree_t** tree, tree_t* tree1, tree_t* tree2);
bool Split(tree_t* tree, tree_t** tree1, tree_t** tree2, int key); //return trees from pointer

#endif //LAB_I_INCLUDED