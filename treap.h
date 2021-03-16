#pragma once

#define TRUE 1
#define FALSE 0

typedef struct node_t {
	int key, priority;
	struct node_t* left;
	struct node_t* right;
} node_t;

node_t* MergeTrees(node_t* leftTree, node_t* rightTree);
void SplitTree(node_t* tree, int key, node_t** leftTree, node_t** rightTree);

int AddNode(node_t** tree, int key);
int RemoveNode(node_t** tree, int key);
int FindNode(node_t* tree, int key);

void ManageTree(node_t** tree);
void PrintTree(node_t* tree, int level);

int DestroyTree(node_t* tree);

