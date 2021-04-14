#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct tree_t {
    int isLeaf;
    int value, maxValue;
    struct tree_t* left, * middle, * right;
    int leftNum, rightNum, countChild;

    struct tree_t* parent;
}tree_t;

typedef struct stackTree_t {
    tree_t* curTree;
    struct stackTree_t* nextTree;
}stackTree_t;

bool Insert(tree_t** tree, int newEl);

bool Delete(tree_t** tree, int element);

bool Find(tree_t* tree, int element);

bool Merge(tree_t** tree, tree_t* tree1, tree_t* tree2);

bool Split(tree_t* tree, tree_t** tree1, tree_t** tree2, int elementToSplit);