#pragma once

typedef struct node_t {
        int data;
        int key;
        int width;
        struct node_t* left;
        struct node_t* right;
        struct node_t* parent;
}node_t;

typedef struct start_t {
        node_t* node;
}start_t;

int WhatWidth(int key);

void UpdateWidth(node_t* start, int value);

node_t** PlaceToAdd(int key, node_t** start);

node_t* Addnode(int key, int data);

node_t** FindNode(int key);

void DeleteNode(int key);

void Printree(node_t* tree, int n);

void DestroyTree(node_t* tree);
