#include<stdio.h>
#include<stdlib.h>
#include "labH.h"
#pragma warning(disable : 4996)


treap* Merge(treap* left, treap* right) {
	if (left == NULL)
		return right;
	else if (right == NULL)
		return left;
	else if (left->priority > right->priority) {
		left->right = Merge(left->right, right);
		return left;
	}
	else {
		right->left = Merge(left, right->left);
		return right;
	}
}

void Split(treap* tree, int key, treap** left, treap** right) {
	if (tree == NULL)
		(*left) = (*right) = NULL;
	else if (tree->key < key) {
		Split(tree->right, key, &(tree->right), right);
		(*left) = tree;
	}
	else {
		Split(tree->left, key, left, &(tree->left));
		(*right) = tree;
	}
}


int Find(treap* tree, int key) {
	treap* left = NULL;
	treap* right = NULL;

	Split(tree, key, &left, &right);
	treap* f = NULL;
	Split(right, key + 1, &f, &right);
	treap* p = NULL;
	p = Merge(left, f);
	tree = Merge(p, right);
	if (f)
		return FOUND;
	else return NOTFOUND;
}

void Add(treap** tree, int key) {
	treap* treed = (treap*)malloc(sizeof(treap));
	if (treed) {
		treed->left = treed->right = NULL;
		treed->key = key;
		treed->priority = rand();
	}
	if (!(*tree))
		(*tree) = treed;
	else {
		treap* left = NULL, * right = NULL;
		Split(*tree, key, &left, &right);
		treap* p = Merge(left, treed);
		(*tree) = Merge(p, right);
	}
}

void Delete(treap** tree, int key) {
	treap* left = NULL;
	treap* right = NULL;

	Split(*tree, key, &left, &right);
	treap* f = NULL;
	Split(right, key + 1, &f, &right);

	if (f)
		free(f);
	(*tree) = Merge(left, right);
}

void TreapOff(treap* tree) {
	if (tree) {
		TreapOff(tree->left);
		TreapOff(tree->right);
		free(tree);
	}
}

int main(void) {
	int key;
	treap* t = NULL;
	int operation = getchar();
	while (operation != EOF) {
		scanf("%i", &key);
		if (operation == 'a')
			Add(&t, key);
		else if (operation == 'r')
			Delete(&t, key);
		else if (operation == 'f')
			if (Find(t, key) == FOUND)
				printf("yes\n");
			else printf("no\n");
		else {
			TreapOff(t);
			return 0;
		}
		operation = getchar();
		if (operation == '\n')
			operation = getchar();
	}
	TreapOff(t);
	return 0;
}