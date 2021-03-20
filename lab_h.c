#include <stdio.h>
#include <stdlib.h>
#include "lab_h.h"

#pragma warning(disable:4996)

int HeightOfTree(node_t* tree) {
	if (tree != NULL)
		return tree->height;
	else return 0;
}

void CorrectHeight(node_t* tree) {
	int hl = HeightOfTree(tree->left);
	int hr = HeightOfTree(tree->right);
	if (hl > hr)
		tree->height = hl + 1;
	else tree->height = hr + 1;                     
}

int BalancedFactor(node_t* tree) {
	return HeightOfTree(tree->right) - HeightOfTree(tree->left);
}

node_t* RotateRight(node_t* tree) {
	node_t* p = tree->left;
	tree->left = p->right;
	p->right = tree;
	CorrectHeight(tree);
	CorrectHeight(p);
	return p;
}

node_t* RotateLeft(node_t* tree) {
	node_t* p = tree->right;
	tree->right = p->left;
	p->left = tree;
	CorrectHeight(tree);
	CorrectHeight(p);
	return p;
}

node_t* BalanceTree(node_t* tree) {
	CorrectHeight(tree);
	if (BalancedFactor(tree) == 2) {
		if (BalancedFactor(tree->right) < 0)
			tree->right = RotateRight(tree->right);
		return RotateLeft(tree);
	}
	if (BalancedFactor(tree) == -2) {
		if (BalancedFactor(tree->left) > 0)
			tree->left = RotateLeft(tree->left);
		return RotateRight(tree);
	}
	return tree;
}

int SearchInTree(node_t* tree, int num) {
	if (tree == NULL)
		return TREE_ERROR;
	while (tree != NULL) {
		if (tree->num == num)
			return FOUND;
		else if (tree->num < num) {
			tree = tree->right;
		}
		else {
			tree = tree->left;
		}
	}
	return NOT_FOUND;
}

node_t* AddInTree(node_t* tree, int num) {
	if (tree == NULL) {
		tree = (node_t*)malloc(sizeof(node_t));
		tree->num = num;
		tree->left = 0;
		tree->right = 0;
		tree->height = 1;
		return tree;
	}
	if (num < tree->num)
		tree->left = AddInTree(tree->left, num);
	if (num > tree->num)
		tree->right = AddInTree(tree->right, num);
	return BalanceTree(tree);
}

node_t* FindMin(node_t* tree) {
	if (tree->left != NULL)
		return FindMin(tree->left);
	else return tree;
}

node_t* RemoveMin(node_t* tree) {
	if (tree->left == 0)
		return tree->right;
	tree->left = RemoveMin(tree->left);
	return BalanceTree(tree);
}
 
node_t* RemoveNode(node_t* tree, int num) {
	if (tree == NULL)
		return NULL;
	if (num < tree->num)
		tree->left = RemoveNode(tree->left, num);
	if (num > tree->num)
		tree->right = RemoveNode(tree->right, num);
	if (num == tree->num) {
		node_t* q = tree->left;
		node_t* r = tree->right;
		free(tree);
		if (r == NULL)
			return q;
		node_t* min = FindMin(r);
		min->right = RemoveMin(r);
		min->left = q;
		return BalanceTree(min);
	}
	return BalanceTree(tree);
}

void DestroyTree(node_t* tree) {
	if (tree == NULL)
		return;
	DestroyTree(tree->left);
	DestroyTree(tree->right);
	free(tree);
}

void WhatToDo(node_t* tree) {
	int num = 0;
	int founder = 0;
	char c = getchar();
	while (c != EOF) {
		scanf("%d", &num);
		if (c == 'a') {
			tree = AddInTree(tree, num);
		}
		else if (c == 'r') {
			tree = RemoveNode(tree, num);
		}
		else if (c == 'f') {
			founder = SearchInTree(tree, num);
			if (founder == FOUND)
				printf("yes\n");
			else
				printf("no\n");
		}
		else {
			printf("Incorrect input");
			return;
		}
		c = getchar();
		if (c == '\r')
			c = getchar();
		if (c == '\n')
			c = getchar();
	}
	return;
}