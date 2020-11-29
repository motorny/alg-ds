#pragma once
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define TRUE 1
#define FALSE 0

typedef struct node node;
struct node {
  int key;
  node* left;
  node* right;
  node* parent;
  int number;   // number of elements
  int width;    // key width
};
typedef struct tree
{
  node *root;
} tree;

int TreeAddElement(tree *T, int key);
int TreeDeleteElement(tree *T, int key);
node * TreeFindElement(tree T, int key);
void TreePrint(tree T);
node * TreeKLower(tree T, int k);
void TreeFree(tree* T);
