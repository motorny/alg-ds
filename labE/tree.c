#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

tree_t* GetNewNode(T value) {
    tree_t* tmp = (tree_t*)malloc(sizeof(tree_t));
    if (tmp == NULL)
        return NULL_PTR;

    tmp->left = NULL;
    tmp->right = NULL;
    tmp->value = value;
    return tmp;
}

int Insert(tree_t** head, int value) {
    tree_t* tmp = NULL;
    if (*head == NULL) {
        *head = GetNewNode(value);
        return TRUE;
    }

    tmp = *head;
    while (tmp) {
        if (value > tmp->value) {
            if (tmp->right != NULL) {
                tmp = tmp->right;
                continue;
            }
            else {
                tmp->right = GetNewNode(value);
                return TRUE;
            }
        }
        else if (value < tmp->value) {
            if (tmp->left != NULL) {
                tmp = tmp->left;
                continue;
            }
            else {
                tmp->left = GetNewNode(value);
                return TRUE;
            }
        }
        else {
            return FALSE;
        }
    }
    return FALSE;
}


int FindByValue(tree_t* root, T value, tree_t** outputPtr) {
    while (root) {
        if (root->value > value) {
            root = root->left;
            continue;
        }
        else if (root->value < value) {
            root = root->right;
            continue;
        }
        else {
            (*outputPtr) = root;
            return TRUE;
        }
    }
    (*outputPtr) = NULL_PTR;
    return FALSE;
}

int RemoveByValue(tree_t** tree, T value) {
    tree_t* root;
    if ((*tree) == NULL) {
        return FALSE;
    }
    if ((*tree)->value > value) {
        RemoveByValue(&((*tree)->left), value);
        return TRUE;
    }
    else if ((*tree)->value < value) {
        RemoveByValue(&((*tree)->right), value);
        return TRUE;
    }
    else {
        if ((*tree)->left && (*tree)->right) {
            tree_t** tmp = &(*tree)->left;
            while ((*tmp)->right) { // find the max
                tmp = &((*tmp)->right);
            }
            (*tree)->value = (*tmp)->value;
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
}

void printTree(tree_t* root, int lvl) {
    if (root) {
        printf("lvl_%i  %i\n", lvl, root->value);
        printTree(root->left, lvl + 1);
        printTree(root->right, lvl + 1);
    }
}

void RemoveTree(tree_t* tree) {
    if (tree != NULL) {
        RemoveTree(tree->left);
        RemoveTree(tree->right);
        free(tree);
    }
}