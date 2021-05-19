#pragma once

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define NOERROR 1
#define NOKEYS 101
#define NOTFOUND 10
#define FOUND 11
#define T 3


typedef enum {
	NOTLEAF,
	LEAF,
}ISLEAF;


typedef struct btree_t {
	ISLEAF leaf;
	int count;
	int vals[2 * T - 1];
	struct btree_t* children[2 * T];
}BTREE;

BTREE* InitNode();

void DestroyTree(BTREE* tree, int val);

int FindPos(int val, int* vals, int count);

void Split(BTREE* node, int pos);

void InsertToFull(BTREE* node, int val);

void Insert(BTREE** tree, int val);

int Search(BTREE* tree, int val);

int DeleteKey(BTREE* tree, int val);

void PrintTree(BTREE* tree, int lvl);

void Clear(BTREE* tree);