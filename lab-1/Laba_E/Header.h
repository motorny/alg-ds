#pragma once

typedef struct node_t {
    int key;
    struct node_t* parent;
    struct node_t* left;
    struct node_t* right;
    int data;
    int width;
}node_t;

node_t* Addnode(int key, int data);

void Deletenode(int key);

void DestroyTree(node_t* tree);

node_t** FindPlaceAdd(int key, node_t** start);

node_t** Findnode(int key);

int Getwidth(int key);

void Printree(node_t* tree, int n);

void UpdateWidth(node_t* start, int value);


