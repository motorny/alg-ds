//
// Created by ikuzin on 26.02.2021.
//



#include "Node.h"
#include <cstdio>
#include <cstdlib>

Node_t *Add(Node_t *t, int key) {
    if (t == NULL) {
        t = (Node_t *) malloc(sizeof(Node_t));
        if (t == NULL)
            return NULL;
        t->key = key;
        t->left = t->right = NULL;
    } else {
        if (key < t->key) {
            t->left = Add(t->left, key);
            t->left->parent = t;
        } else {
            if (key > t->key) {
                t->right = Add(t->right, key);
                t->right->parent = t;
            }
        }
    }
    return t;
}

Node_t *Find(Node_t *t, int key) {
    Node_t *temp = NULL;
    if (t == NULL)
        return NULL;
    if (t->key == key)
        return t;
    else {
        if (key < t->key)
            temp = Find(t->left, key);
        else
            temp = Find(t->right, key);
    }
    return temp;
}

Node_t *MinNodeByKey(Node_t *t) {
    while (t->left != NULL)
        t = t->left;
    return t;
}

Node_t *Del(Node_t *t, int key) {
    if (t == NULL)
        return t;
    if (key < t->key)
        t->left = Del(t->left, key);
    else if (key > t->key)
        t->right = Del(t->right, key);
    else if (t->left != NULL && t->right != NULL) {
        t->key = MinNodeByKey(t->right)->key;
        t->right = Del(t->right, t->key);
    } else {
        Node_t *pPtr = t->parent;
        if (t->left != NULL) {
            t = t->left;
            t->parent = pPtr;
        } else if (t->right != NULL) {
            t = t->right;
            t->parent = pPtr;
        } else
            t = NULL;
    }
    return t;
}

void DestroyTree(Node_t *t) {
    if (t == NULL)
        return;
    DestroyTree(t->left);
    DestroyTree(t->right);
    free(t);
}

void RotateLeft(Node_t &nodePtr) {
    Node_t *pNodePtr = nodePtr.parent;
    Node_t *rNodePtr = nodePtr.right;
    if (pNodePtr != NULL) {
        if (pNodePtr->left == &nodePtr) pNodePtr->left = rNodePtr;
        else pNodePtr->right = rNodePtr;
    }
    Node_t *tmpPtr = rNodePtr->left;
    rNodePtr->left = &nodePtr;
    nodePtr.right = tmpPtr;
    nodePtr.parent = rNodePtr;
    rNodePtr->parent = pNodePtr;
    if (nodePtr.right != NULL) nodePtr.right->parent = &nodePtr;
}

void RotateRight(Node_t &nodePtr) {
    Node_t *pNodePtr = nodePtr.parent;
    Node_t *lNodePtr = nodePtr.left;
    if (pNodePtr != NULL) {
        if (pNodePtr->right == &nodePtr) pNodePtr->right = lNodePtr;
        else pNodePtr->left = lNodePtr;
    }
    Node_t *tmpPtr = lNodePtr->right;
    lNodePtr->right = &nodePtr;
    lNodePtr->parent = pNodePtr;
    nodePtr.left = tmpPtr;
    nodePtr.parent = lNodePtr;
    if (nodePtr.left != NULL) nodePtr.left->parent = &nodePtr;
}

Node_t *Splay(Node_t *&nodePrt) {
    while (nodePrt->parent != NULL) {
        if (nodePrt == nodePrt->parent->left) {
            if (nodePrt->parent->parent == NULL) RotateRight(*nodePrt->parent);
            else if (nodePrt->parent == nodePrt->parent->parent->left) {
                RotateRight(*nodePrt->parent->parent);
                RotateRight(*nodePrt->parent);
            } else {
                RotateRight(*nodePrt->parent);
                RotateLeft(*nodePrt->parent);
            }
        } else {
            if (nodePrt->parent->parent == NULL) RotateLeft(*nodePrt->parent);
            else if (nodePrt->parent == nodePrt->parent->parent->right) {
                RotateLeft(*nodePrt->parent->parent);
                RotateLeft(*nodePrt->parent);
            } else {
                RotateLeft(*nodePrt->parent);
                RotateRight(*nodePrt->parent);
            }
        }
    }
    return nodePrt;
}