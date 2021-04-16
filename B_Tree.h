#pragma once
#include<stdlib.h>
#include<string.h>
#include<stdio.h>


#define t 4 
typedef enum bool_t
{
	FALSE,
	TRUE
}bool_t;

typedef struct node_t
{
	bool_t leaf;
	int  key_num;
	int key[2 * t];
	struct node_t* parent;
	struct node_t* child[2 * t + 1];
	struct node_t* left;
	struct node_t* right;
}node_t;

typedef struct tree_t
{
	node_t* root;
}tree_t;

tree_t* InitTree();
void DestroyNode(node_t* node);
void DestroyTree(tree_t* tree);
node_t* FindNode(tree_t* tree, int key);
bool_t InsertTree(tree_t* tree, int key);
void Split(tree_t* tree, node_t* cnode);
void PrintTree(node_t* tree, char* dir, int level);
bool_t DeleteTree(tree_t* tree, int key);
void DeleteInNode(tree_t* tree, node_t* tec, int key);

int MinKey(node_t* nodec);
void Update(tree_t* tree, node_t* tec, int key);
bool_t FindTree(tree_t* tree, int key);
void Merge(tree_t* tree, node_t* tec, int key);