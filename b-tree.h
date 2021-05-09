#pragma once

typedef enum {
	FALSE,
	TRUE,
} bool_t;

#define B_FAIL 0
#define B_SUCCESS 1
#define NOT_ENOUGH_KEYS -1

#define DEGREE 3

typedef struct node_t {
	bool_t isLeaf;
	int num;
	int keys[2 * DEGREE - 1];
	struct node_t* children[2 * DEGREE];
} node_t;

int AddKey(node_t** tree, int key);
int RemoveKey(node_t** tree, int key);
node_t* FindNode(node_t* tree, int key);
void PrintTree(node_t* tree, int level);

void ManageTree(node_t* tree);
int DestroyTree(node_t* tree);

