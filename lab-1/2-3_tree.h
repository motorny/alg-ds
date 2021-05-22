#pragma once

typedef struct tree_t {
	int keys[3]; //array of keys
	int count; //count of keys
	struct tree_t* child[4]; //array of children
	struct tree_t* parent; //pointer on parent
}tree_t;

tree_t* Find(tree_t* t, int keys);
tree_t* Add(tree_t* t, int keys);
tree_t* Del(tree_t* t, int keys);
void PrintTree(tree_t* tree);