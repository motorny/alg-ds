//
// Created by ikuzin on 12.04.2021.
//

#ifndef LH_NODE_H
#define LH_NODE_H
typedef struct _node {
    int n;
    int keys[2];
    struct _node *p[3];
} node;

node *root = NULL;

typedef enum KeyStatus {
    Duplicate, SearchFailure, Success, InsertIt, LessKeys,
} KeyStatus;

void insert(int key);

void display(node *root, int);

void DelNode(int x);

void search(int x);

KeyStatus ins(node *r, int x, int *y, node **u);

int searchPos(int x, int *key_arr, int n);

KeyStatus del(node *r, int x);

void inorder(node *ptr);

#endif //LH_NODE_H
