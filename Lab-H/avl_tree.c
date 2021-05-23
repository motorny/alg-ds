#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl_tree.h"
#pragma warning(disable:4996)

unsigned int Height(node_t* p) {
	if (p == NULL) return 0;
	return p->height;
}

void ChangeHeight(node_t* p) {
	int left = Height(p->left);
	int right = Height(p->right);
	if (left > right)
		p->height = left + 1;
	else p->height = right + 1;
}

int ChildrenDifference(node_t* tree) {
	return Height(tree->right) - Height(tree->left);
}

node_t* RotateRight(node_t* t) {
	node_t* p = t->left;
	t->left = p->right;
	p->right = t;
	ChangeHeight(t);
	ChangeHeight(p);
	return p;
}

node_t* RotateLeft(node_t* t) {
	node_t* p = t->right;
	t->right = p->left;
	p->left = t;
	ChangeHeight(t);
	ChangeHeight(p);
	return p;
}

node_t* Balance(node_t* p) {
	ChangeHeight(p);
	if (ChildrenDifference(p) == 2) {
		if (ChildrenDifference(p->right) < 0)
			p->right = RotateRight(p->right);
		return RotateLeft(p);
	}
	if (ChildrenDifference(p) == -2) {
		if (ChildrenDifference(p->left) > 0)
			p->left = RotateLeft(p->left);
		return RotateRight(p);
	}
	return p;
}

node_t* FindNode(node_t* p, int k) {
	if (p == NULL)
		return NULL;
	while (p != NULL) {
		if (p->key == k)
			return p;
		else if (p->key < k) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return NULL;
}

node_t* AddNode(node_t* p, int k) {
	if (p == NULL) {
		p = (node_t*)malloc(sizeof(node_t));
		if (!p)
			return NULL;
		p->key = k;
		p->left = 0;
		p->right = 0;
		p->height = 1;
		return p;
	}
	if (k < p->key)
		p->left = AddNode(p->left, k);
	if (k > p->key)
		p->right = AddNode(p->right, k);
	return Balance(p);
}

node_t* FindMin(node_t* p) {
	if (p->left == NULL) {
		return p;
	}
	return FindMin(p->left);
}

node_t* RemoveMin(node_t* p) {
	if (p->left == 0)
		return p->right;
	p->left = RemoveMin(p->left);
	return Balance(p);
}

node_t* DeleteNode(node_t* p, int k) {
	if (p == NULL) {
		return NULL;
	}
	if (k < p->key)
		p->left = DeleteNode(p->left, k);
	if (k > p->key)
		p->right = DeleteNode(p->right, k);
	if (k == p->key) {
		node_t* q = p->left;
		node_t* r = p->right;
		free(p);
		if (r == NULL)
			return q;
		node_t* min = FindMin(r);
		min->right = RemoveMin(r);
		min->left = q;
		return Balance(min);
	}
	return Balance(p);
}

void DestroyTree(node_t* p) {
	if (p == NULL) {
		return;
	}
	DestroyTree(p->left);
	DestroyTree(p->right);
	free(p);
}