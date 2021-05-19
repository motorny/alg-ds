#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define deg 4
#pragma warning(disable: 4996)

typedef enum bool_t
{
	FALSE,
	TRUE
}bool_t;

typedef struct Bplus
{
	bool_t leaf;
	int key_count;
	int key[2 * deg];
	//int* data;//if is leaf
	struct Bplus* parent;
	struct Bplus* child[2 * deg + 1];
	struct Bplus* left;
	struct Bplus* right;
} Tree;

Tree* Init();
void Destroy(Tree** root);
void Split(Tree** root, Tree* node);
Tree* FindLeaf(Tree* root, int key);
bool_t Insert(Tree** root, int key);
int MinKey(Tree* node);
void Update(Tree* node, int key);
void Merge(Tree** root, Tree* node, int key);
void DeleteInNode(Tree** root, Tree* node, int key);
bool_t Delete(Tree** root, int key);
void PrintTree(Tree** root, int level);
bool_t FindElement(Tree** root, int key);
void GetTreeFromConsole(Tree** root);