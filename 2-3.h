#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


typedef struct tree_t {

    struct tree_t* left;
    int left_val;
    struct tree_t* right;
    int right_val;
    struct tree_t* mid;
    int max_son;
    struct tree_t* left1;
    struct tree_t* right1;
} tree_t;

tree_t* Update(tree_t* tree, tree_t* left, tree_t* mid, tree_t* right);

tree_t* Merge(tree_t* tree, tree_t* left, tree_t* mid, tree_t* right, tree_t* del);

tree_t* Split(tree_t* tree1, tree_t* node, tree_t* tree2, tree_t* tree11, tree_t* tree12, tree_t* tree21, tree_t* tree22, tree_t* del);

tree_t* AddVal(int val);

tree_t* InsertNode(tree_t* tree, int val);

tree_t* DeleteVal(tree_t* tree, int val);

tree_t* FindVal(tree_t* tree, int val);

void PrintTree(tree_t* tree);

void DeleteNode(tree_t* node);

void DestroyTree(tree_t* tree);

char* ReadStr(void);