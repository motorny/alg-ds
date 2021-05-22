#pragma once
#include <stdio.h>
#include <stdlib.h>

#define FAIL 0
#define SUCCESS 1
#define NOT_ENOUGH_KEYS 2



typedef enum {
	NOT_LEAF,
	LEAF,
} STATUS;

#define DEGREE 2

typedef struct btreenode_t {
	STATUS leaf;
	int n;
	int values[2 * DEGREE - 1];
	struct btreenode_t* children[2 * DEGREE];
} Btree;

Btree* newnode_init();

int get_position(int value, int* values, int n);

void split(Btree* node, int position);

void notfull_insert(Btree* node, int value);

void insert(Btree** tree, int value);

int search(Btree* tree, int value);

int remove(Btree* tree, int value);

void delete(Btree* tree, int value);

void print(Btree* tree, int lvl);

void clear(Btree* tree);