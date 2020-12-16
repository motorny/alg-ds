#pragma once

#define TRUE 1
#define FALSE 0
#define NULL_DATA 0

typedef struct node_t {
	struct node_t* parent;
	struct node_t* left;
	struct node_t* right;
	int key;
	int data;
} node_t;

void MinSubtreeHeigh(node_t* tree);

int AddNode(node_t** tree, int key);
int RemoveNode(node_t** tree, int key);
node_t* FindNode(node_t* tree, int key);
void ManageTree(node_t** tree);

void PrintTree(node_t* tree, int level);

void DestroyTree(node_t** tree);

