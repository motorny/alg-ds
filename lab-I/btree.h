#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define FAIL 0
#define SUCCESS 1
#define NOT_ENOUGH_KEYS 2

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	NOT_LEAF,
	LEAF,
}STATUS;

#define T 3

typedef struct btreenode_t {
	STATUS leaf;
	int num_of_keys;
	int values[2 * T - 1];
	struct btreenode_t* children[2 * T];
}BTREE;

BTREE* CreateNode();
int Position(int value, int* values, int num_of_keys);
void Split(BTREE* node, int position);
void InsertIfNotFull(BTREE* node, int value);
void Insert(BTREE** tree, int value);
int Search(BTREE* tree, int value);
int RemovingKey(BTREE* tree, int value);
void Delete(BTREE* tree, int value);
void Print(BTREE* tree, int lvl);
void Clear(BTREE* tree);