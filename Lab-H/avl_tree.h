#pragma once

typedef struct node {
	int key;
	unsigned int height;
	struct node* right;
	struct node* left;
} node_t;

int ChildrenDifference(node_t* p);

void ChangeHeight(node_t* p);

unsigned int Height(node_t* p);

node_t* RotateRight(node_t* p);

node_t* RotateLeft(node_t* q);

node_t* Balance(node_t* p);

node_t* AddNode(node_t* p, int k);

node_t* FindMin(node_t* p);

node_t* RemoveMin(node_t* p);

node_t* DeleteNode(node_t* p, int k);

node_t* FindNode(node_t* p, int k);

void DestroyTree(node_t* p);
