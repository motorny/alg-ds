#ifndef E3_H_INCLUDED__
#define E3_H_INCLUDED__

#pragma once

typedef struct tree_t {
  int key;
  int lH, rH;
  int minH, maxH;
  struct tree_t* left;
  struct tree_t* right;
} tree_t;

typedef struct {
  int data;
  int flagFilled;
} cell_t;

void DestroyTree(tree_t* t);

tree_t* AddNode(tree_t* t, int keyNew, int* flagDone);

tree_t* DelNode(tree_t* t, int keyNew, int* flagDone);

tree_t* FindNode(tree_t* t, int key, int* flagDone);

void FillCells(tree_t* t, cell_t* a, int m, int* x, int y);

// print function -> no tests needed
void PrintTree(tree_t *t);

// interface function -> no tests needed
void Run(void);

#endif