#include <stdio.h>
#include <stdlib.h>

#include "BinTree.h"

int ntol(int number) {
    int len;
    if (len = (number < 0))
        number = ~number + 1;

    while (number) {
        number /= 10;
        len++;
    }
    return len;
}

Node_t* newNode(Node_t* node, int val) {
    node = (Node_t*) malloc(sizeof(Node_t));
//    *node = (Node_t) {.left = NULL, .right = NULL, .val = val, .len = ntol(0)};
    node->left = NULL;
    node->right = NULL;
    node->val = val;
    node->len = ntol(0);
    return node;
}

void fixLen(Node_t* node) {
    int len = 0;
    if (node->right != NULL)
        len += node->right->len + ntol(node->right->val);
    if (node->left != NULL)
        len += node->left->len + ntol(node->left->val);
    node->len = len;
}

Node_t* insertNode(Node_t* node, int val) {
    if (node == NULL)
        return newNode(node, val);

    if (val > node->val) {
        node->right = insertNode(node->right, val);
        fixLen(node->right);
    } else if (val < node->val) {
        node->left = insertNode(node->left, val);
        fixLen(node->left);
    }
    return node;
}

Node_t* deleteNode(Node_t* node, int val) {

}

Node_t* findNode(Node_t* node, int val) {

}

void freeTree(Node_t* node) {

}

void printPreOrder(Node_t* node) {

}