#pragma once

#define TRUE 1
#define FALSE 0
#define NULL_PTR NULL

typedef int T;

typedef struct tree_t {
    T value;
    struct tree_t *left, *right;
} tree_t;



tree_t* GetNewNode(T value);

int Insert(tree_t** head, int value);

int FindByValue(tree_t* root, T value, tree_t** outputPtr);

int RemoveByValue(tree_t** tree, T value);

void printTree(tree_t* root, int lvl);

void RemoveTree(tree_t* tree);
