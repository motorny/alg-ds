#pragma once
#define ERROR -1;
#define SUCCESS 0

typedef enum
{
	TRUE,
	FALSE
} bool;

typedef struct node node;

struct node
{
	int count;
	int key[3];
	node* parent;
	node* son[4];
};

void InsertToNode(node** leaf, int elem);

node* CreateNode(int key, node* first, node* second, node* third, node* fourth, node* parent);

int Split(node** tree);

int Insert(node** tree, int elem);

bool IsItFind(node* tree, int elem);

void PrintNode(node n);

void PrintTree(node* tree);

node* GetNode(node* tree, int elem);

node* GetMinNode(node* tree);

void DelKeyFromNode(node** tree, int elem);

node* Redistribute(node* leaf);

node* Fix(node* leaf);

node* DelKey(node* tree, int elem);

void FreeTree(node* tree);