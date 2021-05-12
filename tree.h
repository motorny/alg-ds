#pragma once
#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable:4996)

typedef struct node_t {
	int size;
	int key[3];
	struct node_t* first;
	struct node_t* second;
	struct node_t* third;
	struct node_t* fourth;
	struct node_t* parent;
} node_t;

node_t* InitNode(int key);
int IsLeaf(node_t* p);
void Swap(int* a, int* b);
void Sort(node_t* p);
void InsertKey(node_t* p, int key);
node_t* Split(node_t* p);
node_t* AddElem(node_t* root, int key);
int Find(node_t* p, int key);
node_t* FindElem(node_t* p, int key);
node_t* FindMin(node_t* p);
void Remove(node_t* p, int key);
node_t* Redistribute(node_t* leaf);
node_t* Merge(node_t* leaf);
node_t* Fix(node_t* leaf);
node_t* RemoveNode(node_t* p, int key);
void FreeTree(node_t* root);
void MainFunc(char command, int key, node_t** root);