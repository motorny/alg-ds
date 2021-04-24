#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEGREE 4
#pragma warning(disable: 4996)

typedef enum bool_t {
	FALSE,
	TRUE
}bool_t;

typedef struct Btree {
	bool_t leaf;
	int key_count;
	int key[2 * DEGREE];
	struct Btree* parent;
	struct Btree* child[2 * DEGREE + 1];
	struct Btree* left;
	struct Btree* right;
} Btree;

Btree* tree_create();
void tree_delete(Btree** root);
void tree_update(Btree* node, int key);
void tree_print(Btree** root, int level);

void split(Btree** root, Btree* node);
void merge(Btree** root, Btree* node, int key);

Btree* leaf_find(Btree* root, int key);

bool_t elem_insert(Btree** root, int key);
bool_t elem_delete(Btree** root, int key);
bool_t elem_find(Btree** root, int key);

int minimum(Btree* node);
void del_from_node(Btree** root, Btree* node, int key);