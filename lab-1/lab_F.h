#pragma once
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node_t {
    int key;
    int number;
    struct node_t* left;
    struct node_t* right;
    struct node_t* father;
}node_t;

node_t* FindTreeLowerOnK(node_t* t, int key, int k);
int Add(node_t** t, node_t* father, int key);
node_t* Find(node_t* t, int key);
void Del(node_t** t, int key);
void FreeTree(node_t* t);