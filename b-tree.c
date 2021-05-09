#include <stdio.h>
#include <stdlib.h>

#include "b-tree.h"

#pragma warning(disable: 4996)

node_t* FindNode(node_t* tree, int key) {
	int i;
	if (!tree)
		return NULL;
	node_t* node = tree;
	while (1) {
		i = 0;
		while (i < node->num && key > node->keys[i])
			i++;

		if (i < node->num && key == node->keys[i]) //key is found
			return node;
		else if (node->isLeaf) //key is not in the tree
			return NULL;

		node = node->children[i];
		if (!node)
			return NULL;
	};
}

node_t* CreateNode() { //auxiliary function
	int i;
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (!newNode)
		return NULL;
	newNode->num = 0;
	newNode->isLeaf = TRUE;

	for (i = 0; i < 2 * DEGREE; i++)
		newNode->children[i] = NULL;

	return newNode;
}

int SplitChild(node_t* node, int index) { //auxiliary function
	int i;
	node_t* childNode = node->children[index];
	node_t* newNode;

	if (node == NULL || index > 2 * DEGREE - 1)
		return B_FAIL;

	newNode = CreateNode();
	if (!newNode)
		return B_FAIL;
	newNode->num = DEGREE - 1;
	newNode->isLeaf = childNode->isLeaf;
	for (i = 0; i < DEGREE - 1; i++) {  //moving keys
		newNode->keys[i] = childNode->keys[i + DEGREE];
	}
	if (childNode->isLeaf == FALSE) {
		for (int i = 0; i < DEGREE; i++) { //moving children if there are any
			newNode->children[i] = childNode->children[i + DEGREE];
			childNode->children[i + DEGREE] = NULL;
		}
	}
	childNode->num = DEGREE - 1;

	if (node->children[index + 1] != NULL) {
		i = index + 1;
		while (node->children[i] != NULL)
			i++;

		for (i; i > index + 1; i--) {  //freeing up space in our node
			node->children[i] = node->children[i - 1];
			node->keys[i - 1] = node->keys[i - 2];
		}
	}
	node->children[index + 1] = newNode;
	node->keys[index] = childNode->keys[DEGREE - 1];
	node->num++;

	return B_SUCCESS;
}

int InsertInIncomplete(node_t* node, int key) { //auxiliary function
	int i = node->num - 1;
	if (node->isLeaf == TRUE) { //insert in leaf
		while (i >= 0 && key < node->keys[i]) {
			node->keys[i + 1] = node->keys[i];
			i--;
		}
		node->num++;
		node->keys[i + 1] = key;
	}

	else { //if is not leaf, go to children
		while (i >= 0 && key < node->keys[i])
			i--;
		i++;

		if (node->children[i]->num == 2 * DEGREE - 1) {
			if (!SplitChild(node, i))
				return B_FAIL;
			if (node->keys[i] < key)
				i++;
		}
		InsertInIncomplete(node->children[i], key);
	}
	return B_SUCCESS;
}

int AddKey(node_t** tree, int key) {
	node_t* addNode = (*tree);
	node_t* supNode = NULL;

	if (FindNode(*tree, key) != NULL) //the key is already in tree
		return B_FAIL;

	if ((*tree) == NULL) { //if tree is empty
		(*tree) = CreateNode();
		if ((*tree) == NULL)
			return B_FAIL;
		(*tree)->keys[0] = key;
		(*tree)->num = 1;
		return B_SUCCESS;
	}

	if (addNode->num < 2 * DEGREE - 1) {
		if (!InsertInIncomplete(addNode, key))
			return B_FAIL;
	}
	else {
		supNode = CreateNode();
		if (supNode == NULL)
			return B_FAIL;
		(*tree) = supNode;
		supNode->isLeaf = FALSE;
		supNode->num = 0;
		supNode->children[0] = addNode;
		if (!SplitChild(supNode, 0))
			return B_FAIL;
		if (!InsertInIncomplete(supNode, key))
			return B_FAIL;
	}
	return B_SUCCESS;
}

int FindIndexInNode(int key, int* array, int n) { //auxiliary function
	int index = 0;
	while (index < n && key > array[index])
		index++;
	return index;
}

int RemoveFromNode(node_t* tree, node_t* node, int key) {
	node_t** children;
	node_t* left, * right, * supNode, * supNode1;
	int index, i, num, minElem, num1, status;
	int* keysArr;

	if (!node)
		return B_FAIL;

	minElem = (DEGREE - 1) / 2;
	num = node->num;
	keysArr = node->keys;
	children = node->children;

	index = FindIndexInNode(key, keysArr, num);

	if (children[0] == NULL) { //if child is a leaf
		if (key < keysArr[index] || index == num)
			return B_FAIL;
		for (i = index + 1; i < num; i++) {
			keysArr[i - 1] = keysArr[i];
			children[i] = children[i + 1];
		}
		node->num--;

		if (node == tree)
			minElem = 1;

		if (node->num >= minElem)
			return B_SUCCESS;
		else
			return NOT_ENOUGH_KEYS;
	}

	if (index < num && key == keysArr[index]) { //if children is not a leaf
		supNode = children[index];
		while (1) {
			num1 = supNode->num;
			supNode1 = supNode->children[num1];
			if (supNode1 == NULL)
				break;
			supNode = supNode1;
		}
		keysArr[index] = supNode->keys[num1 - 1];
		supNode->keys[num1 - 1] = key;
	}
	status = RemoveFromNode(tree, children[index], key);
	if (status != NOT_ENOUGH_KEYS)
		return status;

	if (index > 0 && children[index - 1]->num > minElem) { //add keys if there is not enough in the node
		left = children[index - 1];
		right = children[index];
		right->children[right->num + 1] = right->children[right->num];
		for (i = right->num; i > 0; i--) {
			right->keys[i] = right->keys[i - 1];
			right->children[i] = right->children[i - 1];
		}
		right->num++;
		right->keys[0] = keysArr[index - 1];
		right->children[0] = left->children[left->num];
		keysArr[index - 1] = left->keys[--left->num];
		return B_SUCCESS;
	}

	if (index < num && children[index + 1]->num > minElem) {
		left = children[index];
		right = children[index + 1];
		left->keys[left->num] = keysArr[index];
		left->children[left->num + 1] = right->children[0];
		keysArr[index] = right->keys[0];
		left->num++;
		right->num--;
		for (i = 0; i < right->num; i++) {
			right->keys[i] = right->keys[i + 1];
			right->children[i] = right->children[i + 1];
		}
		right->children[right->num] = right->children[right->num + 1];
		return B_SUCCESS;
	}

	if (index == num) {
		left = children[index - 1];
		right = children[index];
		left->keys[left->num] = keysArr[index - 1];
	}
	else {
		left = children[index];
		right = children[index + 1];
		left->keys[left->num] = keysArr[index];
	}

	left->children[left->num + 1] = right->children[0];
	for (i = 0; i < right->num; i++) {
		left->keys[left->num + i + 1] = right->keys[i];
		left->children[left->num + i + 2] = right->children[i + 1];
	}
	left->num = left->num + right->num + 1;

	free(right);
	for (i = index + 1; i < num; i++) {
		keysArr[i - 1] = keysArr[i];
		children[i] = children[i + 1];
	}
	if (node == tree)
		minElem = 1;
	node->num--;
	if (node->num >= minElem)
		return B_SUCCESS;
	else 
		return NOT_ENOUGH_KEYS;
}

int RemoveKey(node_t** tree, int key) {
	node_t* node;
	if (!(*tree))
		return B_FAIL;
	int status = RemoveFromNode(*tree, *tree, key);
	if (status == NOT_ENOUGH_KEYS) {
		node = (*tree);
		(*tree) = (*tree)->children[0];
		free(node);
		status = B_SUCCESS;
	}
	return status;
}

int DestroyTree(node_t* tree) {
	int i;
	if (!tree)
		return B_FAIL;
	if (tree->isLeaf == FALSE) {
		for (i = 0; i <= tree->num; i++)
			DestroyTree(tree->children[i]);
	}
	free(tree);
	return B_SUCCESS;
}

void PrintTree(node_t* tree, int level) {
	int i, j;
	if (tree == NULL || level < 0)
		return;

	for (i = 0; i <= tree->num - 1; i++) {
		PrintTree(tree->children[i], level + 1);
		for (j = 0; j <= level; j++)
			printf("   ");
		printf("%d\n", tree->keys[i]);
	}
	PrintTree(tree->children[i], level + 1);
}

void ManageTree(node_t* tree) {
	int key;
	char action;
	while (TRUE) {
		action = getchar();
		if (action == EOF || action == '\n')
			break;

		scanf("%i", &key);

		if (action == 'a')
			AddKey(&tree, key);
		else if (action == 'r')
			RemoveKey(&tree, key);
		else if (action == 'f') {
			if (FindNode(tree, key) != NULL)
				printf("yes\n");
			else
				printf("no\n");
		}
		action = getchar();
	}
	PrintTree(tree, 0);
}

int main() {
	node_t* tree = NULL;
	ManageTree(tree);
	DestroyTree(tree);
	return 0;
}