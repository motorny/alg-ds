#pragma once
#ifndef AVL_H
#define AVL_H

#include <stdio.h>

typedef struct Node 
{
    int value;
    struct Node* left;
    struct Node* right;
    int height;
} Node_t;

int height(Node_t* node);
int max(int a, int b);
Node_t* newNode(int val);
Node_t* rightRotate(Node_t* y);
Node_t* leftRotate(Node_t* y);
Node_t* findNode(Node_t* node, int val);
int getBalance(Node_t* node);
Node_t* insertNode(Node_t* node, int val);
Node_t* minNodeValue(Node_t* node);
Node_t* deleteNode(Node_t* node, int val);
void printPreOrder(Node_t* node);
void freeTree(Node_t* node);

#endif // AVL_H
