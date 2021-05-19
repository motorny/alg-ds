#pragma once
#include <stdlib.h>
#include "rbtree.h"


void rotateLeft(Node* x, Node** root) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;

    if (y != NIL)
        y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    else {
        (*root) = y;
    }

    y->left = x;
    if (x != NIL)
        x->parent = y;
}

void rotateRight(Node* x, Node** root) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL)
        y->right->parent = x;

    if (y != NIL)
        y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    else {
        (*root) = y;
    }

    y->right = x;
    if (x != NIL)
        x->parent = y;
}

void insertFixup(Node* x, Node** root) {
    while (x != (*root) && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            Node* y = x->parent->parent->right;
            if (y->color == RED) {

                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->right) {

                    x = x->parent;
                    rotateLeft(x, root);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(x->parent->parent, root);
            }
        }
        else {

            Node* y = x->parent->parent->left;
            if (y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x, root);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(x->parent->parent, root);
            }
        }
    }
    (*root)->color = BLACK;
}

Node* insert(T data, Node** root) {
    Node* current, * parent, * x;
    current = (*root);
    parent = NULL;
    if (current == NULL)
        return NULL;
    while (current != NIL) {
        if (data == current->data)
            return current;
        parent = current;
        current = data < current->data ? current->left : current->right;
    }
    x = (Node*)malloc(sizeof(Node));
    if (x == NULL) {
        return ERROR_ALLOC;
    }
    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;

    if (parent) {
        if (data < parent->data)
            parent->left = x;
        else
            parent->right = x;
    }
    else {
        (*root) = x;
    }

    insertFixup(x, root);
    return(x);
}

void deleteFixup(Node* x, Node** root) {
    while (x != (*root) && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent, root);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w, root);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(x->parent, root);
                x = (*root);
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent, root);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w, root);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(x->parent, root);
                x = (*root);
            }
        }
    }
    x->color = BLACK;
}

Node* findNode(T data, Node* root) {
    Node* current = root;
    while (current != NIL)
        if (data == current->data)
            return (current);
        else
            current = data < current->data ? current->left : current->right;
    return NULL;
}

void deleteD(T data, Node** root) {
    Node* x, * y, * z;
    z = findNode(data, (*root));
    if (!z || z == NIL)
        return;

    if (z->left == NIL || z->right == NIL) {
        y = z;
    }
    else {
        y = z->right;
        while (y->left != NIL)
            y = y->left;
    }

    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if (y->parent) {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    else {
        (*root) = x;
    }

    if (y != z)
        z->data = y->data;
    if (y->color == BLACK)
        deleteFixup(x, root);

    free(y);
}