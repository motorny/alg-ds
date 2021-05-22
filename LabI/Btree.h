#pragma once

#ifndef __BTREE_H_INCLUDED
#define __BTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define T 2
#define MEM_ERR -1
#define IND_ERR -2
#define MFAIL 0
#define SUCCESS 1

typedef enum {
	FALSE,
	TRUE,
} bool_t;

typedef struct b_tree_node_t {
	bool_t leaf;
	int count;
	int key[2 * T - 1];
	struct b_tree_node_t* children[2 * T];
} b_tree_node_t;

typedef struct b_tree_t {
	b_tree_node_t* root;
} b_tree_t;

void BTreeInit(b_tree_t* tree);
int BTreeInsert(b_tree_t* tree, int key);
b_tree_node_t* BTreeFind(b_tree_t* tree, int key);
void BTreeClear(b_tree_t* tree);
void BTreePrint(b_tree_t* tree);
int BTreeRemove(b_tree_t* tree, int key);

#endif //__BTREE_H_INCLUDED 