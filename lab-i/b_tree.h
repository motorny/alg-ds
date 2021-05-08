#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FACTOR 2

typedef enum {
	MEM_ERR = -1,
	IND_ERR = -2,
	MY_FAIL =  0,
	SUCCESS = 1,
} error_t;

typedef enum {
	FALSE,
	TRUE,
} bool_t;

typedef struct Btree_node_t {
	bool_t ifLeaf;
	int numKeys;
	int key[2 * FACTOR - 1];
	struct Btree_node_t* children[2 * FACTOR];
} Btree_node_t;

typedef struct b_tree_t {
	Btree_node_t* root;
} Btree_t;

void InitBtree(Btree_t* tree);

int AddToBtree(Btree_t* tree, int key);

Btree_node_t* FindInBtree(Btree_t* tree, int key);

int DeleteFromBtree(Btree_t* tree, int key);

void DestroyBtree(Btree_t* tree);

void PrintBtree(Btree_t* tree);



