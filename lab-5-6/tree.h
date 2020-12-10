#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    int numOfLeavesBelow;
    int orderAscending;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node* getMinNode(Node *root);

Node* getMaxNode(Node *root);

Node* getFreeNode(int value, Node *parent);

Node* getNodeByValue(Node *root, int value);

void insert(Node **head, int value);

void deleteValue(Node *root, int value);

void printTree(Node *root, const char *dir, int level);

void destroyTree(Node *root);

int getNumOfLeavesBelow(Node *root);

void printKsmall(Node *root, int k);

void setOrder(Node *node, int *number);


#endif // TREE_H
