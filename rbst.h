#pragma once
#pragma warning(disable:4996)

#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

typedef struct node
{
    int key;
    int size;
    struct node* left;
    struct node* right;
}node;

struct node* node_create(int key);

struct node* node_find(struct node* root, int key);

int node_getsize(struct node* root);

void node_fixsize(struct node* root);

struct node* rot_right(struct node* ptr_node);

struct node* rot_left(struct node* ptr_node);

struct node* insertnode(struct node* ptr_node, int key);

struct node* insert(struct node* ptr_node, int key);

struct node* join(struct node* ptr_node1, struct node* ptr_node2);

struct node* remove_node(struct node* node, int key);
