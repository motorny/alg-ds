#pragma once

#include <stdbool.h>

#define T 5
#define SPCS 4
#define MAX_LENGTH 100

typedef struct node_t {
    bool leaf;
    int key_num;
    int key[2 * T];
    struct node_t* parent;
    struct node_t* left;
    struct node_t* right;
    struct node_t* child[2 * T + 1];
} node_t;

typedef struct tree_t {
    node_t* root;
}tree_t;

tree_t* InitTree();

void DestroyNode(node_t* node);

void DestroyTree(tree_t* tree);

int WhatHeight(tree_t* tree);

int FindMinKey(node_t* node);

node_t* FindNode(node_t* node, int key);

bool FindTree(const tree_t* tree, int key);

void Update(node_t* node, int key);

bool Split(tree_t* tree, node_t* node);

bool InsertTree(tree_t* tree, const int key);

tree_t* Merge(tree_t* tree1, tree_t* tree2);

void SplitTree(tree_t* tree, int key, tree_t* tree1, tree_t* tree2);

void DeleteInNode(tree_t* tree, node_t* node, int key);

bool DeleteTree(tree_t* tree, const int key);

void PrintTree(node_t* tree, char* dr, int level);

void WhatToDo();