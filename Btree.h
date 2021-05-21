#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define T 2
#define ERROR_MEM -1
#define ERROR_IND -2
#define MFAIL 0
#define SUCCESS 1

typedef enum {
	FALSE,
	TRUE,
} bool;

typedef struct node_t {
	bool leaf;
	int count;
	int key[2 * T - 1];
	struct node_t* children[2 * T];
} node_t;

typedef struct btree_t {
	node_t* root;
} btree_t;

void BTreeInit(btree_t* tree);

void BTreePrint(btree_t* tree);

int BTreeInsert(btree_t* tree, int key);

int BTreeRemove(btree_t* tree, int key);

node_t* BTreeFind(btree_t* tree, int key);
void BTreeClear(btree_t* tree);



