#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable: 4996)
#include "Bplus.h"


bplus_t* TreeInit() {
	bplus_t* root = (bplus_t*)malloc(sizeof(bplus_t));
	if (root) {
		root->leaf = 1;
		root->keyCount = 0;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		for (int i = 0; i < 2 * 4 + 1; i++)
			root->child[i] = NULL;
	}
	return root;
}
void Destroy(bplus_t** root) {
	if (!(*root)->leaf) {
		for (int i = 0; i < (*root)->keyCount; i++)
			Destroy(&((*root)->child[i]));
	}
	free(*root);
	*root = NULL;
}

void Split(bplus_t** root, bplus_t* node) {
	int i, key, pos;
	bplus_t* newnode = malloc(sizeof(bplus_t));
	newnode->leaf = 0;
	newnode->keyCount = 0;
	newnode->left = NULL;
	newnode->right = NULL;
	for (i = 0; i < 2 * 4 + 1; i++)
		newnode->child[i] = NULL;
	if (node->right) {
		newnode->right = node->right;
		node->right->left = newnode;
		node->right = newnode;
		newnode->left = node;
	}
	else {
		newnode->right = node->right;
		node->right = newnode;
		newnode->left = node;
	}

	key = node->key[4];
	newnode->keyCount = 4 - 1;
	node->keyCount = 4;
	for (i = 0; i < newnode->keyCount; i++) {
		newnode->key[i] = node->key[i + 4 + 1];
		newnode->child[i] = node->child[i + 4 + 1];
		node->child[i + 4 + 1] = NULL;
	}
	newnode->child[newnode->keyCount] = node->child[2 * 4];
	node->child[2 * 4] = NULL;

	if (node->leaf) {
		newnode->keyCount++;
		newnode->leaf = 1;
		for (i = newnode->keyCount - 1; i >= 1; i--)
			newnode->key[i] = newnode->key[i - 1];
		newnode->key[0] = node->key[4];
	}

	if (node == (*root)) {
		(*root) = malloc(sizeof(bplus_t));
		if (*root) {
			(*root)->key[0] = key;
			(*root)->child[0] = node;
			(*root)->child[1] = newnode;

			for (i = 0; i < 2 * 4 + 1; i++) {
				if (newnode->child[i])
					newnode->child[i]->parent = newnode;
				if (node->child[i])
					node->child[i]->parent = node;
			}
			(*root)->leaf = 0;
			(*root)->parent = NULL;
			(*root)->left = NULL;
			(*root)->right = NULL;
			for (i = 2; i < 2 * 4 + 1; i++)
				(*root)->child[i] = NULL;
			(*root)->keyCount = 1;
			node->parent = (*root);
			newnode->parent = (*root);
		}
	}
	else {
		newnode->parent = node->parent;
		bplus_t* parent = node->parent;

		pos = 0;
		while (pos < parent->keyCount && (parent->key[pos] < key))
			pos++;

		for (i = parent->keyCount; i >= pos + 1; i--)
			parent->key[i] = parent->key[i - 1];

		for (i = parent->keyCount + 1; i >= pos + 2; i--)
			parent->child[i] = parent->child[i - 1];

		for (i = 0; i < 2 * 4; i++) {
			if (newnode->child[i])
				newnode->child[i]->parent = newnode;
		}
		parent->key[pos] = key;
		parent->child[pos + 1] = newnode;
		parent->keyCount++;

		if (parent->keyCount == 2 * 4)
			Split(root, parent);
	}
}

bplus_t* FindLeaf(bplus_t* root, int key) {
	bplus_t* cur = NULL;
	if (root) {
		cur = root;
		while (cur->leaf != 1) {
			for (int i = 0; i <= cur->keyCount; i++) {
				if (i == cur->keyCount || key < cur->key[i]) {
					cur = cur->child[i];
					break;
				}
			}
		}
	}
	return cur;
}

int AddElement(bplus_t** root, int key) {
	int i, pos = 0;
	bplus_t* leaf = FindLeaf(*root, key);
	if (!leaf)
		return 0;
	for (i = 0; i < leaf->keyCount; i++) {
		if (leaf->key[i] == key)
			return 0;
	}
	while ((pos < leaf->keyCount) && (leaf->key[pos] < key))
		pos++;
	for (i = leaf->keyCount; i >= pos + 1; i--)
		leaf->key[i] = leaf->key[i - 1];

	leaf->key[pos] = key;
	leaf->keyCount++;
	if (leaf->keyCount == 2 * 4)
		Split(root, leaf);
	return 1;
}

int MinKey(bplus_t* node) {
	for (int i = 0; i < 2 * 4; i++) {
		if (node->child[i])
			return MinKey(node->child[i]);
	}
	return node->key[0];
}

void Update(bplus_t* node, int key) {
	bplus_t* tmp = node->parent;
	int pos = 0;

	while (tmp) {
		while ((pos < tmp->keyCount) && (tmp->key[pos] < key))
			pos++;
		if (pos < tmp->keyCount) {
			if (tmp->key[pos] != MinKey(tmp->child[pos + 1]))
				tmp->key[pos] = MinKey(tmp->child[pos + 1]);
		}
		tmp = tmp->parent;
	}
}


int RemoveElem(bplus_t** root, int key) {
	int i, pos = 0, flag = 0;
	bplus_t* leaf = FindLeaf(*root, key);
	for (i = 0; i < leaf->keyCount; i++) {
		if (leaf->key[i] == key) {
			flag = 1;
			break;
		}
	}
	if (!flag)
		return 0;

	DeleteInNode(root, leaf, key);
	return 1;
}

void Merge(bplus_t** root, bplus_t* node, int key) {
	bplus_t* parent = node->parent;
	bplus_t* rightBro = node->right;
	bplus_t* leftBro = node->left;
	int i, pos = 0;
	bplus_t* tmp = NULL;
	if (rightBro && (rightBro->parent == node->parent)) {
		for (i = 0; i < rightBro->keyCount; i++) {
			node->key[node->keyCount] = rightBro->key[i];
			node->child[node->keyCount + 1] = rightBro->child[i];
			if (rightBro->child[i])
				rightBro->child[i]->parent = node;
			node->keyCount++;
		}
		node->child[node->keyCount + 1] = rightBro->child[rightBro->keyCount];
		if (rightBro->child[rightBro->keyCount])
			rightBro->child[rightBro->keyCount]->parent = node;
		if (rightBro->right)
			rightBro->right->left = node;
		node->right = rightBro->right;
		DeleteInNode(root, node->parent, MinKey(rightBro));
		Update(node, key);
	}
	else {
		for (i = 0; i < node->keyCount; i++) {
			leftBro->key[leftBro->keyCount] = node->key[i];
			leftBro->child[leftBro->keyCount + 1] = node->child[i];
			if (node->child[i])
				node->child[i]->parent = leftBro;

			leftBro->keyCount++;
		}
		leftBro->child[leftBro->keyCount + 1] = node->child[node->keyCount];
		if (node->child[node->keyCount])
			node->child[node->keyCount]->parent = leftBro;

		leftBro->right = node->right;
		if (node->right)
			node->right->left = leftBro;

		DeleteInNode(root, leftBro->parent, MinKey(node));
		Update(leftBro, key);
	}
}

int FindElement(bplus_t** root, int key) {
	bplus_t* leaf = FindLeaf(*root, key);
	for (int i = 0; i < leaf->keyCount; i++) {
		if (leaf->key[i] == key)
			return 1;
	}
	return 0;
}

void PrintTree(bplus_t** root, int level) {
	int i;
	for (i = 0; i < (*root)->keyCount; i++)
		printf("lvl %d key = %d\n", level, (*root)->key[i]);

	for (int i = 0; i < 2 * 4; i++) {
		if ((*root)->child[i]) {
			printf("child %d\n", i);
			PrintTree(&((*root)->child[i]), level + 1);
		}
	}
}

void DeleteInNode(bplus_t** root, bplus_t* node, int key) {
	int i, pos = 0, flag = 0;
	bplus_t* rightBro;
	bplus_t* leftBro;
	while ((pos < node->keyCount) && (node->key[pos] < key))
		pos++;

	for (i = pos; i < node->keyCount; i++)
		node->key[i] = node->key[i + 1];

	for (i = pos + 1; i <= node->keyCount; i++)
		node->child[i] = node->child[i + 1];

	for (i = node->keyCount + 1; i < 2 * 4 + 1; i++)
		*(node->child + i) = NULL;

	node->keyCount--;
	if (node == (*root)) {
		for (i = 0; i < 2 * 4 + 1; i++) {
			if (node->child[i]) {
				if (node->child[i]->keyCount == 0)
					node->child[i] = NULL;

			}
		}
		if ((*root)->keyCount == 0 && (*root)->child[0])
			(*root) = (*root)->child[0];

		return;
	}
	if (node->keyCount >= 4 / 2 - 1)
		Update(node, key);

	else {
		rightBro = node->right;
		leftBro = node->left;
		if (leftBro && leftBro->keyCount > 4 - 1 && (leftBro->parent == node->parent)) {
			leftBro->keyCount--;
			node->keyCount++;
			for (i = 1; i < node->keyCount; i++) {
				node->key[i] = node->key[i - 1];
				node->child[i] = node->child[i - 1];
			}
			node->child[node->keyCount] = node->child[node->keyCount - 1];
			node->key[0] = leftBro->key[leftBro->keyCount];
			node->child[0] = leftBro->child[leftBro->keyCount + 1];
			leftBro->child[leftBro->keyCount + 1] = NULL;
			if (node->child[0])
				node->child[0]->parent = node;

			Update(node, key);
		}
		else if (rightBro && rightBro->keyCount > 4 - 1 && (rightBro->parent == node->parent)) {
			node->keyCount++;
			node->key[node->keyCount - 1] = rightBro->key[0];
			node->child[node->keyCount] = rightBro->child[0];
			if (node->child[node->keyCount])
				node->child[node->keyCount]->parent = node;

			for (i = 0; i < rightBro->keyCount; i++) {
				rightBro->key[i] = rightBro->key[i + 1];
				rightBro->child[i] = rightBro->child[i + 1];
			}
			for (i = 0; i < 2 * 4; i++) {
				if (rightBro->child[i] == rightBro->child[i + 1] && rightBro->child[i] != NULL) {
					rightBro->child[i + 1] = NULL;
					break;
				}
			}
			rightBro->keyCount--;
			Update(node, key);
		}
		else
			Merge(root, node, key);
	}
}


void MainFun(bplus_t** root) {
	int value;
	int check = 1;
	char buffer = getchar();
	while (buffer != EOF) {
		scanf("%d", &value);
		if (buffer == 'a')
			check = AddElement(root, value);
		else if (buffer == 'r')
			check = RemoveElem(root, value);
		else if (buffer == 'f') {
			if (FindElement(root, value))
				printf("yes\n");
			else
				printf("no\n");
		}
		else {
			printf("Incorrect input");
			return;
		}
		buffer = getchar();
		if (buffer == '\r' || buffer == '\n')
			buffer = getchar();
	}
	return;
}

int main(void) {
	bplus_t* tree;
	tree = TreeInit();
	MainFun(&tree);
	Destroy(&tree);
	return 0;
}