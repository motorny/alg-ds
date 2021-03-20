#pragma once
#include<stdio.h>
#define t 4 //degree
typedef enum bool_t {
	FALSE,
	TRUE
}bool_t;

typedef struct node {
	bool_t leaf;
	int  key_num;
	int key[2 * t];
	struct node* parent;
	struct node* child[2 * t + 1];
	struct node* left;
	struct node* right;
}node;

typedef struct BPtree {
	node* root;
}BPtree;

BPtree* init();
void destroyNode(node* node);
void destroy(BPtree* tree);
node* findNode(BPtree* tree, int key);
bool_t insert(BPtree* tree, int key);
void split(BPtree* tree, node* cnode);
void printTree(node* tree, char* dir, int level);
bool_t deleteEl(BPtree* tree, int key);
void deleteInNode(BPtree* tree, node* tec, int key);

int min_key(node* nodec);
void update(BPtree* tree, node* tec, int key);
bool_t findEl(BPtree* tree, int key);
void merge(BPtree* tree, node* tec, int key);
