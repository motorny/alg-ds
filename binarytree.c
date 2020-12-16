#include <stdio.h>
#include <stdlib.h>

#include "binarytree.h"
#pragma warning(disable: 4996)

void MinSubtreeHeigh(node_t* tree) {
	if (tree == NULL)
		return;
	MinSubtreeHeigh(tree->left);
	MinSubtreeHeigh(tree->right);
	if (tree->left && tree->right) {
		if (tree->left->data > tree->left->data)
			tree->data = tree->left->data + 1;
		else
			tree->data = tree->right->data + 1;
	}
	else if (tree->left)
		tree->data = tree->left->data + 1;
	else if (tree->right)
		tree->data = tree->right->data + 1;
	else
		tree->data = 0;
}

int AddNode(node_t** tree, int key) {
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	node_t* treeNode = (*tree);

	if (newNode == NULL)
		return FALSE;
	newNode->key = key;
	newNode->data = NULL_DATA;
	newNode->left = NULL;
	newNode->right = NULL;

	if (*tree == NULL) { //if tree is empty
		newNode->parent = NULL;
		(*tree) = newNode;
		return TRUE;
	}

	while (treeNode) {
		if (key < treeNode->key) {
			if (treeNode->left)
				treeNode = treeNode->left;
			else
				break;
		}

		else if (key > treeNode->key) {
			if (treeNode->right)
				treeNode = treeNode->right;
			else
				break;
		}
		else {
			free(newNode);
			return;
		}
	}

	if (key < treeNode->key)
		treeNode->left = newNode;
	else
		treeNode->right = newNode;

	newNode->parent = treeNode;
	return TRUE;
}

node_t* FindNode(node_t* tree, int key) {
	node_t* treeNode = tree;
	if (tree == NULL)
		return FALSE;
	while (treeNode) {
		if (treeNode->key < key)
			treeNode = treeNode->right;
		else if (treeNode->key > key)
			treeNode = treeNode->left;
		else
			return treeNode;
	}
	return NULL;
}

//auxiliary function, finds the smallest key in subtree
node_t* FindMaxNode(node_t* tree) {
	node_t* maxNode = tree;
	while (maxNode->right)
		maxNode = maxNode->right;
	return maxNode;
}

int RemoveNode(node_t** tree, int key) {
	node_t* delNode;
	node_t* delNodeNew;

	if (*tree == NULL)
		return FALSE;
	delNode = FindNode(*tree, key);
	if (delNode == NULL)
		return FALSE;

	if (delNode->left && delNode->right) { //if node has both childs
		delNodeNew = FindMaxNode(delNode->left); //finding the biggest key in the left subtree
		delNode->key = delNodeNew->key;  //replace data in the deliting node
		delNode->data = delNodeNew->data;
		RemoveNode(&(delNode->left), delNodeNew->key);
		return TRUE;
	}
	else if (delNode->left) { //if node has only left childs
		if (delNode->parent == NULL) {
			(*tree) = delNode->left;
			delNode->left->parent = NULL;
		}

		else if (delNode == delNode->parent->left) {
			delNode->parent->left = delNode->left;
			delNode->left->parent = delNode->parent;
		}

		else { //if node is the right child for its parent
			delNode->parent->right = delNode->left;
			delNode->left->parent = delNode->parent;
		}
	}

	else if (delNode->right) { //if node has only right childs
		if (delNode->parent == NULL) {
			(*tree) = delNode->right;
			delNode->right->parent = NULL;
		}
		else if (delNode == delNode->parent->right) {
			delNode->parent->right = delNode->right;
			delNode->right->parent = delNode->parent;
		}
		else { //if node is the left child for its parent
			delNode->parent->left = delNode->right;
			delNode->right->parent = delNode->parent;
		}
	}
	else { //if node doesn't have childs
		if (delNode->parent != NULL) {
			if (delNode == delNode->parent->right)
				delNode->parent->right = NULL;
			else if (delNode == delNode->parent->left)
				delNode->parent->left = NULL;
		}
		else
			*tree = NULL;
	}
	free(delNode);
	return TRUE;
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
			if (FindNode(*tree, key) != NULL)
				printf("yes\n");
			else
				printf("no\n");
		}

		operator = getchar();
	}
}

//prints a tree, rotated to the left
void PrintTree(node_t* tree, int level) {
	int i;
	if (tree == NULL)
		return;
	PrintTree(tree->right, level + 1);
	for (i = 0; i < level; i++)
		printf("     ");
	printf("%i(%i)\n", tree->data, tree->key);
	PrintTree(tree->left, level + 1);
}

void DestroyTree(node_t** tree) { 
	node_t* delNode;
	while (*tree != NULL) {
		delNode = FindMaxNode(*tree);
		RemoveNode(tree, delNode->key);
	}
}

int main() {
	node_t* tree = NULL;
	ManageTree(&tree);
	MinSubtreeHeigh(tree);
	PrintTree(tree, 1);
	DestroyTree(&tree);
	return 0;
}