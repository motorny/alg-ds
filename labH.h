#pragma once
#define NO_ERRORS 0
#define NOT_ENOUGH_MEMORY 1
#define NO_ELEMENTS 2

typedef struct node_t{
    int key;
    int priority;
    struct node_t* left;
    struct node_t* right;
}node_t;

node_t* CreateTree(int key, int priority, node_t* left, node_t* right, int* error);
node_t* Merge(node_t* left, node_t* right, int* error);
void Split(int x, node_t* tree, node_t** left, node_t** right, int* error);
void Add(int x, node_t** tree, int* error);
void Delete(int x, node_t** tree, int* error);
int Search(int x, node_t* tree, int* error);
void DeleteTree(node_t* tree);
