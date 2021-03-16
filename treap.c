#include <stdio.h>
#include <stdlib.h>

#include "treap.h"

#pragma warning(disable: 4996)

node_t* MergeTrees(node_t* leftTree, node_t* rightTree) {
	if (!leftTree) 
		return rightTree;
	if (!rightTree) 
		return leftTree;
	if (leftTree->priority > rightTree->priority) {
		leftTree->right = MergeTrees(leftTree->right, rightTree);
		return leftTree;
	}
	else {
		rightTree->left = MergeTrees(leftTree, rightTree->left);
		return rightTree;
	}
}

void SplitTree(node_t* tree, int key, node_t** leftTree, node_t** rightTree) {
	if (!tree) {
		(*leftTree) = NULL;
		(*rightTree) = NULL;
		return;
	}
	if (tree->key <= key) {
		SplitTree(tree->right, key, &(tree->right), rightTree);
		(*leftTree) = tree;
		return;
	} 
	else {
		SplitTree(tree->left, key, leftTree, &(tree->left));
		(*rightTree) = tree;
		return;
	}
}

int AddNode(node_t** tree, int key) {
	node_t* leftTree, * rightTree;
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL)
		return FALSE;

	newNode->key = key;
	newNode->priority = rand();
	newNode->left = NULL;
	newNode->right = NULL;

	if ((*tree) == NULL) { //if tree is empty
		(*tree) = newNode;
		return TRUE;
	}

	SplitTree(*tree, key, &leftTree, &rightTree);
	if (leftTree && leftTree->key == key) { //if key is already in the tree
		(*tree) = MergeTrees(leftTree, rightTree);
		return FALSE;
	}
	(*tree) = MergeTrees(MergeTrees(leftTree, newNode), rightTree);

	return TRUE;
}

int FindNode(node_t* tree, int key) {
	node_t* leftTree, * equalTree, * rightTree;

	SplitTree(tree, key, &leftTree, &rightTree);
	SplitTree(leftTree, key - 1, &leftTree, &equalTree);
	tree = MergeTrees(MergeTrees(leftTree, equalTree), rightTree);

	if (equalTree)
		return TRUE;
	else
		return FALSE;
}

int RemoveNode(node_t** tree, int key) {
	node_t* leftTree, * equalTree, * rightTree;

	SplitTree(*tree, key, &leftTree, &rightTree);
	SplitTree(leftTree, key - 1, &leftTree, &equalTree);
	(*tree) = MergeTrees(leftTree, rightTree);

	if (!equalTree) //if key isn't found
		return FALSE;
	else {
		free(equalTree);
		return TRUE;
	}
}

int DestroyTree(node_t* tree) {
	if (!tree)
		return FALSE;
	else {
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
	return TRUE;
}

void PrintTree(node_t* tree, int level) {
	int i;
	if (tree == NULL)
		return;
	PrintTree(tree->right, level + 1);
	for (i = 0; i < level; i++)
		printf("           ");
	printf("%i(pr %i)\n", tree->key, tree->priority);
	PrintTree(tree->left, level + 1);
}

void ManageTree(node_t** tree) {
	int key;
	char operator;
	while (TRUE) {
		operator = getchar();
		if (operator == EOF || operator == '\n')
			break;

		scanf("%i", &key);

		if (operator == 'a')
			AddNode(tree, key);
		else if (operator == 'r')
			RemoveNode(tree, key);
		else if (operator == 'f') {
			if (FindNode(*tree, key) == TRUE)
				printf("yes\n");
			else
				printf("no\n");
		}

		operator = getchar();
	}
}

int main() {
	node_t* tree = NULL;
	ManageTree(&tree);
	DestroyTree(tree);
	return 0;
}