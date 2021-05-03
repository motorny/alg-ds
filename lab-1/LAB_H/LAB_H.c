#include <stdio.h>                                              
#include <stdlib.h>
#include "DekartTree.h"

typedef struct node_t {
    int val;
    int size;
    int prior;
    struct node_t* left;
    struct node_t* right;
} node_t;

int GetSize(node_t* tree) {
    if (tree == NULL) return 0;
    return tree->size;
}

void PrintTree(node_t* tree) {
    if (tree == NULL) return;
    PrintTree(tree->left);
    printf("%i ", tree->val);
    PrintTree(tree->right);
}

void DestroyTree(node_t* tree) {
    if (tree) {
        DestroyTree(tree->left);
        DestroyTree(tree->right);
        free(tree);
    }
}

node_t* Insert(int val) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) return NULL;
    new_node->val = val;
    new_node->size = 1;
    new_node->prior = rand();
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void ChangeSize(node_t* tree) {
    if (tree == NULL) return;
    tree->size = 1 + GetSize(tree->left) + GetSize(tree->right);
}

node_t* Merge(node_t* treeA, node_t* treeB) {
    if (treeA == NULL) {
        ChangeSize(treeB);
        return treeB;
    }
    else if (treeB == NULL) {
        ChangeSize(treeA);
        return treeA;
    }
    else if (treeA->prior > treeB->prior) {
        treeA->right = Merge(treeA->right, treeB);
        ChangeSize(treeA);
        return treeA;
    }
    else {
        treeB->left = Merge(treeA, treeB->left);
        ChangeSize(treeB);
        return treeB;
    }
}

void Split(int n, int val, node_t* tree, node_t** treeA, node_t** treeB) {
    if (tree == NULL) {
        *treeA = NULL;
        *treeB = NULL;
        return;
    }
    if (val <= GetSize(tree->left) + n) {
        Split(n, val, tree->left, treeA, &(tree->left));
        *treeB = tree;
    }
    else {
        Split(n + 1 + GetSize(tree->left), val, tree->right, &(tree->right), treeB);
        *treeA = tree;
    }
    ChangeSize(tree);
}

void AddNode(int n, int val, node_t** tree) {
    node_t* new_tree = Insert(val);
    node_t* treeA = NULL;
    node_t* treeB = NULL;
    if (n < 0 || new_tree == NULL) return;
    Split(0, n, *tree, &treeA, &treeB);
    *tree = Merge(Merge(treeA, new_tree), treeB);
}

void DeleteNode(int n, node_t** tree) {
    node_t* treeA = NULL;
    node_t* treeB = NULL;
    node_t* treeC = NULL;
    node_t* treeD = NULL;
    if (n < 0) return;
    Split(0, n, *tree, &treeA, &treeB);
    Split(0, 1, treeB, &treeC, &treeD);
    if (treeC)
        free(treeC);
    *tree = Merge(treeA, treeD);
}

void DeleteVal(int val, node_t** tree) {
    if (*tree == NULL) return;
    if ((*tree)->val == val) {
        node_t* treeA = (*tree)->left;
        node_t* treeB = (*tree)->right;
        free(*tree);
        *tree = Merge(treeA, treeB);
        return;
    }
    DeleteVal(&((*tree)->left), val);
    DeleteVal(&((*tree)->right), val);
}

void IsItFind(node_t* tree, int val, int* find) {
    if (tree == NULL) return;
    if (tree->val == val)
        *find = 1;
    IsItFind(tree->left, val, find);
    IsItFind(tree->right, val, find);
}
