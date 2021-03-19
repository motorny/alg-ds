#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct splaytree_t {
	struct splaytree_t* left;
	struct splaytree_t* right;
	struct splaytree_t* parent;
	int number;
}SPLAYTREE;

void Insert(SPLAYTREE** tree, int value);
SPLAYTREE* Search(SPLAYTREE* tree, int value);
SPLAYTREE* MinValueNode(SPLAYTREE* tree);
void Delete(SPLAYTREE** tree, int value);
void TurnLeft(SPLAYTREE* root);
void TurnRight(SPLAYTREE* root);
SPLAYTREE* Splay(SPLAYTREE* ptr);
void Clear(SPLAYTREE* tree);

