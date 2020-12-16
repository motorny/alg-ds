#pragma once

#ifndef TREE_H
#define TREE_H

#define MAX_SIZE 5

typedef struct node_t {
	int key;
	struct node_t* parent;
	struct node_t* left;
	struct node_t* right;
} node_t;

typedef enum {
	FALSE,
	TRUE,
}bool_t;

int AddToTree(node_t** tree, int key);

int DeleteFromTree(node_t** tree, int key);

void DestroyTree(node_t** tree);

node_t* FindInTree(node_t* tree, int key);

void PrintLevels(node_t* tree, int level, char* state);

void PrintTree(node_t* tree, int level);

void PrintNodes(node_t* tree);


#endif // !TREE_H
