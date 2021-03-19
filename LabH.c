#include <stdio.h>
#include <stdlib.h>
#include "labH.h"
#pragma warning (disable: 4996)
#pragma once
#define NO_ERRORS 0
#define NOT_ENOUGH_MEMORY 1

node_t* CreateTree(int key, int priority, node_t* left, node_t* right, int* error) {
    node_t* tree;

    tree = (node_t*)malloc(sizeof(node_t));
    if (!tree) {
        *error = NOT_ENOUGH_MEMORY;
        return NULL;
    }
    
    tree->key = key;
    tree->priority = priority;
    tree->left = left;
    tree->right = right;

    return tree;
}

node_t* Merge(node_t* left, node_t* right, int *error){

    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (left->priority > right->priority) {
        left->right = Merge(left->right, right, error);
        return left;
    }
    else {
        right->left = Merge(left, right->left, error);
        return right;

    }

}

void Split(int x, node_t* tree, node_t** left, node_t** right, int *error){
    
    if (tree == NULL) {
        (*left) = NULL;
        (*right) = NULL;
        return;
    }

    if (tree->key <= x) {
        Split(x, tree->right, &(tree->right), right, error);
        (*left) = tree;
    }
    else {
        Split(x, tree->left, left, &(tree->left), error);
        (*right) = tree;
    }

}

void Add (int x, node_t** tree, int *error){
    
    node_t* left, *right, *xTree;
    left = NULL;
    right = NULL;
    xTree = CreateTree(x, rand(), NULL, NULL, error);

    if (!error) {
        return;
    }

    if (!(*tree)) {
        *tree = CreateTree(x, rand(), NULL, NULL, error);
        return;
    }

    Split(x, *tree, &left, &right, error);

    if (!error) {
        return;
    }

    (*tree) = Merge(Merge(left, xTree, error), right, error);
    return;

}

void Delete(int x, node_t** tree, int *error){
    
    node_t* left, *right, *newTree, *secondRight;
    left = NULL;
    right = NULL;
    newTree = NULL;
    secondRight = NULL;

    if (!(*tree)) {
        *error = NO_ELEMENTS;
        return;
    }

    Split(x - 1, *tree, &left, &secondRight, error);
    Split(x, secondRight, &newTree, &right, error);

    if (!error) {
        return;
    }

    free(newTree);

    (*tree) = Merge(left, right, error);

}

int Search(int x, node_t* tree, int* error) {
    
    node_t* left, * right, * newTree, * secondRight;
    int result;

    left = NULL;
    right = NULL;
    newTree = NULL;
    secondRight = NULL;

    if (!error) {
        result = 0;
        return result;
    }

    Split(x - 1, tree, &left, &secondRight, error);
    Split(x, secondRight, &newTree, &right, error);

    tree = Merge(Merge(left, newTree, error), right, error);

    if (!error) {
        result = 0;
        return result;
    }

    if (newTree) {
        result = 1;
    }
    else {
        result = 0;
    }

    return result;
}

void DeleteTree(node_t* tree) {
    if (tree) {
        DeleteTree(tree->left);
        DeleteTree(tree->right);
        free(tree);
    }
}

