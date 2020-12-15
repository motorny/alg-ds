#pragma once
#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#define GO_ON 1
#define FREE_FLAG 0 

#define PUSH_NODE(where_you_want) \
push_node(&((*t)->where_you_want), key);\
(*t)->where_you_want->parent = (*t);\

typedef struct node_t {
    int key;
    struct node_t* left;
    struct node_t* right;
    struct node_t* parent;
    int width;
    int flag;
}node_t;

void push_node(node_t** t, int key);
void del_node(node_t** t, int key);
void print_tree(node_t* t);

int find_node(node_t* t, int key);
node_t* find_elem(node_t* T, int key);
node_t* find_elem_k_lower(node_t* T, int k);