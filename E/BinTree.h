#ifndef BINTREE_H
#define BINTREE_H

typedef struct Node {
    struct Node* left;
    struct Node* right;
    int val;
    int len;
} Node_t;

int ntol(int number);
Node_t* newNode(Node_t* node, int val);
void fixLen(Node_t* node);
Node_t* insertNode(Node_t* node, int val);
Node_t* deleteNode(Node_t* node, int val);
Node_t* findNode(Node_t* node, int val);
void freeTree(Node_t* node);
void printPreOrder(Node_t* node);

#endif // BINTREE_H