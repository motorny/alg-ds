#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define size 50

typedef struct tree {
    int l, r;
    struct tree* left;
    struct tree* right;
}intTree_t;

typedef struct {
    int r, l;
}interval_t;

void Add(intTree_t** tree, int left, int right) {
    if ((*tree) == NULL) {
        (*tree) = (intTree_t*)malloc(sizeof(intTree_t));
        if (!(*tree))
            return;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->l = left;
        (*tree)->r = right;
        return;
    }

    if (left < (*tree)->l) {
        Add(&(*tree)->left, left, right);
    }
    else if (left > (*tree)->l || right > (*tree)->r) {
        Add(&(*tree)->right, left, right);
    }
}

void RemoveTree(intTree_t* tree) {
    if (tree) {
        RemoveTree(tree->left);
        RemoveTree(tree->right);
        free(tree);
    }
}

int RemoveInter(intTree_t** tree, int left, int right) {
    intTree_t* root;
    if ((*tree) == NULL) {
        return FALSE;
    }
    if ((*tree)->l > left) {
        RemoveInter(&((*tree)->left), left, right);
        return TRUE;
    }
    else if ((*tree)->l < left || (*tree)->r != right) {
        RemoveInter(&((*tree)->right), left, right);
        return TRUE;
    }
    else {
        if ((*tree)->left && (*tree)->right) {
            intTree_t** tmp = &(*tree)->left;
            while ((*tmp)->right) { // find the max
                tmp = &((*tmp)->right);
            }
            (*tree)->l = (*tmp)->l;
            root = (*tmp);
            (*tmp) = (*tmp)->left;
            free(root);
            return TRUE;
        }
        else if ((*tree)->left) {
            root = (*tree);
            (*tree) = (*tree)->left;
            free(root);
            return TRUE;
        }
        else if ((*tree)->right) {
            root = (*tree);
            (*tree) = (*tree)->right;
            free(root);
            return TRUE;
        }
        else {
            free(*tree);
            (*tree) = NULL;
            return TRUE;
        }
    }
    return FALSE;
}

int Find(intTree_t* tree, int left, int right) {
    while (tree) {
        if (tree->l == left && tree->r == right) {
            return TRUE;
        }
        else if (left < tree->l) {
            tree = tree->left;
            continue;
        }
        else if (left > tree->l || right != tree->r) {
            tree = tree->right;
            continue;
        }
    }

    return FALSE;
}

void printTree(intTree_t* tree, int lvl) {
    if (tree) {
        printf("lvl_%i  (%i, %i) \n", lvl, tree->l, tree->r);
        printTree(tree->left, lvl + 1);
        printTree(tree->right, lvl + 1);
    }
}

void Intersect(intTree_t* tree, int left, int right, interval_t (*arr)[size], int* lvl) {
    if (tree) {
        if (tree->l <= right && tree->r >= left) {
            (*arr)[(*lvl)].l = tree->l;
            (*arr)[(*lvl)].r = tree->r;
            (*lvl)++;
        }
        Intersect(tree->left, left, right, arr, lvl);
        Intersect(tree->right, left, right, arr, lvl);
    }
}

