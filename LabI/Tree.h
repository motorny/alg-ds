#pragma once

#include <stdbool.h>
#define T 5 // min deg of B-tree

typedef struct node_t {
    bool leaf;
    int keyNum;
    int key[2 * T];
    struct node_t* parent;
    struct node_t* child[2 * T + 1];
    struct node_t* left;
    struct node_t* right;
} node_t;

typedef struct tree_t {
    node_t* root;
}tree_t;

tree_t* CreateTree();
bool InsertTree(tree_t* tree, const int key);
bool SearchTree(const tree_t* tree, const int key);
bool DeleteTree(tree_t* tree, const int key);
void FreeTree(tree_t* tree);
tree_t* Merge(tree_t* t1, tree_t* t2);
void SplitTree(tree_t* tree, int key, tree_t* t1, tree_t* t2);
void PrintTree(tree_t* tree);
