#pragma once

typedef struct Tree23 {
	int leftValue;
	int rightValue;
	int maxSon;
	struct Tree23* left;
	struct Tree23* middle;
	struct Tree23* right;
	struct Tree23* leftone;
	struct Tree23* rightone;
} Tree23;

Tree23* Update(Tree23* tree, Tree23* left, Tree23* mid, Tree23* right);

Tree23* Merge(Tree23* tree, Tree23* left, Tree23* mid, Tree23* right, Tree23* del);

Tree23* Split(Tree23* tree1, Tree23* node, Tree23* tree2, Tree23* tree11, Tree23* tree12, Tree23* tree21, Tree23* tree22, Tree23* del);

Tree23* AddNumber(int number);

Tree23* InsertNumber(Tree23* tree, int number);

Tree23* DeleteNumber(Tree23* tree, int number);

Tree23* FindNumber(Tree23* tree, int number);

void Print(Tree23* tree);

void DeleteNode(Tree23* node);

void DestroyTree(Tree23* tree);
