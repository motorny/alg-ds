#ifndef F21_H_INCLUDED__
#define F21_H_INCLUDED__

#pragma once

typedef struct tree_t {
  int key;
  int subnodesQ;
  struct tree_t* left;
  struct tree_t* right;
  struct tree_t* father;
} tree_t;

typedef struct {
  int data;
  int flagFilled;
} cell_t;

void DestroyTree(tree_t* t);

tree_t* AddNode(tree_t* t, int keyNew, int* flagDone);

tree_t* DelNode(tree_t* t, int keyNew, int* flagDone);

tree_t* FindNode(tree_t* t, int key, tree_t** ans);

tree_t* FindNodeSmallerByK(tree_t* t, int key, int k);

// interface function -> no tests needed
void Run(void);

#endif