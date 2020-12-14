#include "tree.h"

#pragma warning (disable : 4996)

void Insert(TREE_NODE** tree, int value) {
	if ((*tree) == NULL) {
		(*tree) = (TREE_NODE*)malloc(sizeof(TREE_NODE));
		if ((*tree) == NULL)
			return;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->number = value;
	}

	if ((*tree)->number < value)
		Insert(&((*tree)->right), value);
	else if ((*tree)->number > value)
		Insert(&((*tree)->left), value);
	else return;
}

int Search(TREE_NODE* tree, int value) {
	while (tree != NULL) {
		if (tree->number == value)
			return FOUND_ELEMENT;
		else if (tree->number < value)
			tree = tree->right;
		else tree = tree->left;
	}
	return NO_ELEMENT;
}

TREE_NODE* MinValueNode(TREE_NODE* tree) {
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

void Delete(TREE_NODE** tree, int value) {
	if ((*tree) == NULL)
		return;
	if ((*tree)->number == value) {
		if ((*tree)->left == NULL && (*tree)->right == NULL)
			(*tree) = NULL;
		else if ((*tree)->left != NULL && (*tree)->right == NULL)
			(*tree) = (*tree)->left;
		else if ((*tree)->left == NULL && (*tree)->right != NULL)
			(*tree) = (*tree)->right;
		else {
			(*tree)->number = MinValueNode((*tree)->right)->number;
			Delete(&((*tree)->right), (*tree)->number);
		}
	}
	else if ((*tree)->number < value)
		Delete(&((*tree)->right), value);
	else Delete(&((*tree)->left), value);
}

void NormalPrint(TREE_NODE* tree, int lvl, const char* status) {
	if (tree != NULL) {
		printf("level = %d, %s, value = %d\n", lvl, status, tree->number);
		NormalPrint(tree->left, lvl + 1, "left");
		NormalPrint(tree->right, lvl + 1, "right");
	}
}
void SpecialPrint(TREE_NODE* tree) {
	if (tree != NULL) {
		if (tree->left != NULL || tree->right != NULL) {
			printf("%d (", tree->number);
			SpecialPrint(tree->left);
			printf(") (");
			SpecialPrint(tree->right);
			printf(")");
		}
		else {
			printf("%d", tree->number);
		}
	}
}

void PrintAsTree(TREE_NODE* tree, int lvl) {
	if (tree != NULL) {
		PrintAsTree(tree->right, lvl + 1);
		for (int i = 0; i < lvl; i++) putchar('    ');
		printf("%d\n", tree->number);
		PrintAsTree(tree->left, lvl + 1);
	}
}

void Clear(TREE_NODE* tree) {
	if (tree != NULL) {
		Clear(tree->left);
		Clear(tree->right);
		free(tree);
	}
}
