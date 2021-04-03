#pragma once

#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#define SUCCESS 1
#define FAIL 0

#define T 5 // minimum degree of B-tree

typedef struct tree_t tree_t;

tree_t* TreeCreate();
int TreeInsert(tree_t* tree, const int key);
int TreeSearch(const tree_t* tree, const int key);
int TreeDelete(tree_t* tree, const int key);
void TreeFree(tree_t* tree);
tree_t* TreeMerge(tree_t* t1, tree_t* t2);
void TreeSplit(tree_t* tree, int key, tree_t* t1, tree_t* t2);
void TreePrint(tree_t* tree);

#endif // TREE_H_INCLUDED