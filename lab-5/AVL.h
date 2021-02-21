#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct node {
	int key;
	unsigned int height;
	struct node* right;
	struct node* left;
} node_t;

// is tree balanced?
int bFactor(node_t* p);

// if the height is incorrect we fix it
void FixHeight(node_t* p);

// returns the height of node
unsigned int Height(node_t* p);

// right rotation
node_t* RotateRight(node_t* p);

// left rotation
node_t* RotateLeft(node_t* q);

// tries to balance tree if it is not balanced
node_t* Balance(node_t* p);

// inserting where "k" is key, returns a root of tree
node_t* Insert(node_t* p, int k);

// searching a node with minimal key
node_t* FindMin(node_t* p);

// removing a node with minimal key
node_t* RemoveMin(node_t* p);

// removing a node 
node_t* RemoveNode(node_t* p, int k);

// finding a node by key, returns node
node_t* FindNodeByKey(node_t* p, int k);

// reading string
char* ReadStr(void);

// prints data about node
void PrintTree(node_t *p);

// destroying tree
void DestroyTree(node_t* tree);