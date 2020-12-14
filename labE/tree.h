#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOUND_ELEMENT 1
#define NO_ELEMENT 0

typedef struct tree_node_t {
	struct tree_node_t* left;
	struct tree_node_t* right;
	int number;
}TREE_NODE;

void Insert(TREE_NODE** tree, int value);
int Search(TREE_NODE* tree, int value);
TREE_NODE* MinValueNode(TREE_NODE* tree);
void Delete(TREE_NODE** tree, int value);
void NormalPrint(TREE_NODE* tree, int lvl, const char* status);
void SpecialPrint(TREE_NODE* tree);
void PrintAsTree(TREE_NODE* tree, int lvl);
void Clear(TREE_NODE* tree);

