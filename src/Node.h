//
// Created by ikuzin on 26.02.2021.
//

#ifndef LH_NODE_H
#define LH_NODE_H


typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node_t;

Node_t *Add(Node_t *, int);

Node_t *Find(Node_t *, int);

Node_t *MinNodeByKey(Node_t *);

Node_t *Del(Node_t *, int);

void DestroyTree(Node_t *);

void RotateLeft(Node_t &);

void RotateRight(Node_t &);

Node_t *Splay(Node_t *&);

#endif //LH_NODE_H
