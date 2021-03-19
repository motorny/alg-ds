#pragma once

typedef struct tree_t {
	int key;
	int level;
	struct tree_t* left;
	struct tree_t* right;
}tree_t;

tree_t* Find(tree_t* t, int key);
tree_t* Add(tree_t* t, int key);
void Del(tree_t** t, int key);
void PrintTree(tree_t* tree);
void DestroyTree(tree_t* t);