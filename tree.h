#pragma once

typedef struct node_t {
	int elem;
	struct node_t* left;
	struct node_t* right;
	struct node_t* parent;
	int ordNumb;
}node_t;

char* readString();

int nodeAdd(node_t** root, int elem);

node_t* findNode(node_t* root, int elem);

node_t* getNode(node_t* parent, int elem);

void deleteNodeByElem(node_t** root, int elem);

void printTree(node_t* root, char* dir, int level);

void treeDestroy(node_t* root);

int height(node_t* node);

void heightTree(node_t* root);

void printKsmall(node_t* root, int k);

void setOrder(node_t* node, int* number);
node_t* findK(node_t* root, int k);

void printLow(node_t* root, char* dir, int level, int k);