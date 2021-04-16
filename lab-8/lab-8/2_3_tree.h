#pragma once


typedef struct node {
	int size;
	int key[3];
	struct node* first;
	struct node* second;
	struct node* third;
	struct node* fourth;
	struct node* parent;
} node;


void swap(int* a, int* b);
node* InitNode(int key);
void Sort(node* p);
int IsLeaf(node* p);
void InsertKey(node* p, int key); 
node* Split(node* p);
node* Insert(node* root, int key);
node* Search(node* root, int key);
int Find(node* p, int key);
void FreeTree(node* root);
node* Merge(node* leaf);
node* Fix(node* leaf);
node* Remove(node* p, int key);
void PrintLinearly(node* ptr);
void ParseCommand(char command, int key, node** root);
