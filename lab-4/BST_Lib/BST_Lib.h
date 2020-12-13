#pragma once

#ifndef _BST_LIB_188246413975643
#define _BST_LIB_188246413975643

#define BST_ERROR 0
#define BST_OK 1

typedef struct _TreeItem
{
  int key;
  int value;
  int printX;
  struct _TreeItem* childL_p;
  struct _TreeItem* childR_p;
} TreeItem;

typedef struct _Tree
{
  int count;
  struct _TreeItem* root_p;
} Tree;

typedef int TreeItemGetInfo(TreeItem* item_p);

TreeItemGetInfo TreeItemGetValue;

TreeItemGetInfo TreeItemGetKey;

Tree* TreeGet(void);

int TreeFree(Tree* tree_p);

TreeItem* TreeAdd(Tree* tree_p, int key, int value);

TreeItem* TreeFind(Tree* tree_p, int key);

int TreeRemove(Tree* tree_p, int key);

int TreeHightDifToValue(Tree* tree_p);

int TreePrint(Tree* tree_p, int itemTextSize, TreeItemGetInfo info);

#endif // !_BST_LIB_188246413975643