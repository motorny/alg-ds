#include "avl.h"

int getHeight(node_t* tree) {
	if (tree)
		return tree->height;
	else return 0;
}

void CorrectHeight(node_t* tree) {
	int hl = getHeight(tree->left);
	int hr = getHeight(tree->right);
	if (hl > hr)
		tree->height = hl + 1;
	else tree->height = hr + 1;
}

int BalancedFactor(node_t* tree) {
	return getHeight(tree->right) - getHeight(tree->left);
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

int FindNode(node_t* tree, int num) {
	if (!tree)
		return 0;
	while (tree) {
		if (tree->num == num)
			return 1;
		else if (tree->num < num)
			tree = tree->right;
		else
			tree = tree->left;
	}
	return 0;
}

node_t* AddNode(node_t* tree, int num) {
	if (!tree) {
		tree = (node_t*)malloc(sizeof(node_t));
		tree->num = num;
		tree->left = 0;
		tree->right = 0;
		tree->height = 1;
		return tree;
	}
	if (num < tree->num)
		tree->left = AddNode(tree->left, num);
	if (num > tree->num)
		tree->right = AddNode(tree->right, num);
	return BalanceTree(tree);
}

node_t* FindMin(node_t* tree) {
	if (tree->left)
		return FindMin(tree->left);
	else return tree;
}

node_t* RemoveMin(node_t* tree) {
	if (!tree->left)
		return tree->right;
	tree->left = RemoveMin(tree->left);
	return BalanceTree(tree);
}

node_t* RemoveNode(node_t* tree, int num) {
	if (!tree)
		return NULL;
	if (num < tree->num)
		tree->left = RemoveNode(tree->left, num);
	if (num > tree->num)
		tree->right = RemoveNode(tree->right, num);
	if (num == tree->num) {
		node_t* q = tree->left;
		node_t* r = tree->right;
		free(tree);
		if (!r)
			return q;
		node_t* min = FindMin(r);
		min->right = RemoveMin(r);
		min->left = q;
		return BalanceTree(min);
	}
	return BalanceTree(tree);
}

void DestroyTree(node_t* tree) {
	if (!tree)
		return;
	DestroyTree(tree->left);
	DestroyTree(tree->right);
	free(tree);
}