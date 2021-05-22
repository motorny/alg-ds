#ifndef BPLSTREE_H_INCLUDED__
#define BPLSTREE_H_INCLUDED__
#pragma once

#include<stdio.h>
#include<stdlib.h>
#define T 4
#define NOT_FOUND NULL
#pragma warning(disable: 4996)

enum {
    NOT_FINISHED = 0,
    FINISHED,
    LEAF,
    NOTLEAF,
    ERROR,
};

typedef struct tree_t {
	int isLeaf;
	int keysNum;
	int keys[2 * T];
	struct tree_t* parent;
	struct tree_t* left;
	struct tree_t* right;
	struct tree_t* childs[2 * T + 1];
} tree_t;

void NodeSplit(tree_t** root, tree_t* node);
int FindMin(tree_t* node);
void UpdateKeys(tree_t* node, int key);
void MergeNodes(tree_t* tree, tree_t* node, int key);
void DeleteByKeyFromNode(tree_t* tree, tree_t* node, int key);

tree_t* CreateTree(void);
tree_t* FindNodeByKey(tree_t* tree, int key);
int FindByKey(tree_t* tree, int key);
int InsertKey(tree_t** root, int key);
int DeleteByKey(tree_t* tree, int key);
int DestroyTree(tree_t* tree);
void PrintTree(tree_t* tree, int index, int child);

#endif BPLSTREE_H_INCLUDED