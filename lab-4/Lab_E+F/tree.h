#ifndef TREE
#define TREE

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef int data_t;

typedef struct node_t {
  data_t data;
  int numOfNode;
  int key;
  struct node_t* left;
  struct node_t* right;
  struct node_t* p;
} node_t;

typedef struct {
  node_t* root;
} tree_t;

node_t* CreateNode(int key);

node_t* Find(tree_t* tree, int key);

int Add(tree_t* tree, int key);

void Transplant(tree_t* tree, node_t* u, node_t* v);

void Delete(tree_t* tree, int key);

void CountLeaves(tree_t* tree);

void Print(tree_t* tree);

int FindShiftK(tree_t* tree, int k, int key);

void ClearTree(tree_t* tree);

#ifdef __cplusplus
}
#endif

#endif