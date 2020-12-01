#ifndef __TREE_H_
#define __TREE_H_

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define TRUE 1
#define FALSE 0

#define MAX_STR 100

typedef struct node_t node_t;
struct node_t {
  char keyStr[MAX_STR];
  node_t* left, *right;
};

int ReadTreeFromFile(node_t **tree, char *filename);
void PrintTree(node_t* tree);
void ClearTree(node_t** tree);

#endif
