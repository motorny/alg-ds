#pragma once

#ifndef __TREE_H_INCLUDED
#define __TREE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node_t {
  int key;
  int num;
  struct node_t* left;
  struct node_t* right;
  struct node_t* parent;
} node_t;

#define TRUE 1
#define FALSE 0
#define BLOCKSIZE 5

int TreeAdd(node_t** tree, int num);
node_t* TreeFind(node_t* tree, int num);
int TreeDel(node_t** tree, int num);
void TreeClear(node_t** tree);
//lab-F
node_t* FindKLower(node_t* tree, int key, int k);
//lab-E
void TreePrettyPrint(node_t* tree);
void TreePrint(node_t* tree);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TREE_H_INCLUDED */
