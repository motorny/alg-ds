#pragma once

#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#define FAILED 0
#define SUCCESS 1
#define GIVE_MORE_KEYS 2



#define T 3

typedef struct btree_t {
	int flag;
	int keys;
	int value[2 * T - 1];
	struct btree_t* kids[2 * T];
}btree_t;

btree_t* CreateTree();

void Split(btree_t* node, int position);

void InsertPlace(btree_t* node, int value);

void Insert(btree_t** tree, int value);

int Search(btree_t* tree, int value);

int Remove(btree_t* tree, int value);

void DeleteEl(btree_t* tree, int value);

void Print(btree_t* tree, int lvl);

void DeleteTree(btree_t* tree);