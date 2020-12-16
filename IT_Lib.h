#pragma once

#ifndef _IT_LIB_188246413975643
#define _IT_LIB_188246413975643

#define BST_ERROR 0
#define BST_OK 1

typedef struct _TreeItem
{
  int leftX;
  int rightX;
  int rightMax;
  int id;
  int printX;
  struct _TreeItem* parent_p;
  struct _TreeItem* childL_p;
  struct _TreeItem* childR_p;
} TreeItem;

typedef struct _Tree
{
  int count;
  struct _TreeItem* root_p;
} Tree;

Tree* TreeGet(void);

int TreeFree(Tree* tree_p);

int TreeIntersect(Tree* tree_p, int leftX, int rightX, int* outputArray, int maxCount);

TreeItem* TreeAdd(Tree* tree_p, int leftX, int rightX, int id);

int TreeFind(Tree* tree_p, int leftX, int rightX);

int TreeRemove(Tree* tree_p, int leftX, int rightX);

int TreePrintIntervals(Tree* tree_p, int itemTextSize);

#endif // !_IT_LIB_188246413975643