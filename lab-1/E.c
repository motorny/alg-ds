
#include <stdio.h>
#include <stdlib.h>
#include "labE.h"
//
struct tree* GNN(Tree value) {
    struct tree* t = (struct tree*)malloc(sizeof(struct tree));
    if (t == NULL) {
        return NULL;
    }
    t->left = NULL;
    t->right = NULL;
    t->value = value;
    return t;
}
int Inst(struct tree** head, int value) {
    struct tree* t = NULL;
    if (*head == NULL) {
        *head = GNN(value);
        return TRUE;
    }
    t = *head;
    while (t) {
        if (value > t->value) {
            if (t->right != NULL) {
                t = t->right;
                continue;
            }
            else {
                t->right = GNN(value);
                return TRUE;
            }
        }
        else if (value < t->value) {
            if (t->left != NULL) {
                t = t->left;
                continue;
            }
            else {
                t->left = GNN(value);
                return TRUE;
            }
        }
        else {
            return FALSE;
        }
    }
    return FALSE;
}
int FBV(struct tree* root, Tree value, struct tree** outPtr) {
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
            (*outPtr) = root;
            return TRUE;
        }
    }
    (*outPtr) = NULL;
    return FALSE;
}
int RBV(struct tree** tree, Tree value) {
    struct tree* root;
    if ((*tree) == NULL) {
        return FALSE;
    }
    if ((*tree)->value > value) {
        RBV(&((*tree)->left), value);
        return TRUE;
    }
    else if ((*tree)->value < value) {
        RBV(&((*tree)->right), value);
        return TRUE;
    }
    else {
        if ((*tree)->left && (*tree)->right) {
            struct tree** t = &(*tree)->left;
            while ((*t)->right) {
                t = &((*t)->right);
            }
            (*tree)->value = (*t)->value;
            root = (*t);
            (*t) = (*t)->left;
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
void Print(struct tree* root, int level) {
    if (root) {
        printf("%i  %i\n", level, root->value);
        Print(root->left, level + 1);
        Print(root->right, level + 1);
    }
}
void Delete(struct tree* tree) {
    if (tree != NULL) {
        Delete(tree->left);
        Delete(tree->right);
        free(tree);
    }
}
void Input(struct tree** tree, char action, int value, int** output) {//
    struct tree* buf;
    switch (action) {
    case 'a':
        Inst(tree, value);
        break;
    case 'r':
        RBV(tree, value);
        break;
    case 'f':
        if (FBV(*tree, value, &buf)) {
            printf("Yes");
        }
        else {
            printf("No");
        }
        break;
    default:
        break;
    }
}
void STL(struct tree** tree, int** number, int* level) {
    if (tree != NULL) {
        if ((*tree)->left == NULL && (*tree)->right == NULL) {
            (*tree)->value = 1;
            return;
        }
        else if ((*tree)->left == NULL) {
            STL(&(*tree)->right, number, level);
            (*tree)->value = (*tree)->right->value;
        }
        else if ((*tree)->right == NULL) {
            STL(&(*tree)->left, number, level);
            (*tree)->value = (*tree)->left->value;
        }
        else {
            STL(&(*tree)->left, number, level);
            STL(&(*tree)->right, number, level);
            (*tree)->value = (*tree)->right->value + (*tree)->left->value;
        }
    }
}
