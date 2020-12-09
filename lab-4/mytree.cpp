#include<stdio.h>
#include<stdlib.h>
#include"mytree.h"
#pragma warning(disable:4996)

Node* CreateFreeNode(T value, Node* parent) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		return ERRORNULL;
	}
	tmp->right = NULL;
	tmp->left = NULL;
	tmp->value = value;
	tmp->parent = parent;
	return tmp;
}

void InsertInTree(Node** root, T value) {
	Node* tmp = NULL;
	if (*root == NULL) {
		*root = CreateFreeNode(value, NULL);
		return;
	}
	tmp = *root;
	while (tmp) {
		if (value > tmp->value) {
			if (tmp->right) {
				tmp = tmp->right;
				continue;
			}
			else {
				tmp->right = CreateFreeNode(value, tmp);
				return;
			}
		}
		else if (value < tmp->value) {
			if (tmp->left) {
				tmp = tmp->left;
				continue;
			}
			else {
				tmp->left = CreateFreeNode(value, tmp);
				return;
			}
		}
		return;
	}
}

Node* GetMinNode(Node* root) {
	while (root->left)
		root = root->left;
	return root;
}

Node* GetMaxNode(Node* root) {
	while (root->right)
		root = root->right;
	return root;
}

Node* GetNodeByValue(Node* root, T value) {
	while (root) {
		if (root->value > value) {
			root = root->left;
			continue;
		}
		else if (root->value < value) {
			root = root->right;
			continue;
		}
		return root;
	}
	return NULL;
}

void RemoveNodeByPtr(Node* target) {
	if (target == NULL) {
		return;
	}
	if (target->left && target->right) {
		Node* localMax = GetMaxNode(target->left);
		target->value = localMax->value;
		RemoveNodeByPtr(localMax);
		return;
	}
	else if (target->left) {
		if (target->parent == NULL) {
			Node* bufNode = target->left;
			target->value = bufNode->value;
			target->left = bufNode->left;
			target->right = bufNode->right;
			target = bufNode;
		}
		else if (target == target->parent->left) {
			target->parent->left = target->left;
			target->left->parent = target->parent;
		}
		else {
			target->parent->right = target->left;
			target->left->parent = target->parent;
		}
	}
	else if (target->right) {
		if (target->parent == NULL) {
			Node* bufNode = target->right;
			target->value = bufNode->value;
			target->left = bufNode->left;
			target->right = bufNode->right;
			target = bufNode;
		}
		else if (target == target->parent->right) {
			target->parent->right = target->right;
			target->right->parent = target->parent;
		}
		else {
			target->parent->left = target->right;
			target->right->parent = target->parent;
		}
	}
	else {
		if (target->parent != NULL) {
			if (target == target->parent->left) {
				target->parent->left = NULL;
			}
			else {
				target->parent->right = NULL;
			}
		}
	}
	free(target);
}

void DeleteValue(Node* root, T value) {
	Node* target = GetNodeByValue(root, value);
	RemoveNodeByPtr(target);
}

void PrintTree(Node* root, const char* dir, int level) {
	if (root) {
		printf("lvl %d %s = %d\n", level, dir, root->value);
		PrintTree(root->left, "left", level + 1);
		PrintTree(root->right, "right", level + 1);
	}
}

void DestroyTree(Node** root) {
	if (*root) {
		DestroyTree(&((*root)->left));
		DestroyTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

void GetTreeFromConsole(Node** root) {
	int value;
	
	char buffer = getchar();
	while (buffer != EOF) {
		scanf("%d", &value);
		if (buffer == 'a') {
			InsertInTree(root, value);
		}
		else if (buffer == 'r') {
			DeleteValue(*root, value);
		}
		else if (buffer == 'f') {
			Node* checkNode = GetNodeByValue(*root, value);
			if (checkNode != ERRORNULL) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
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

void MinHeightLeaves(Node* root) {
	if (root) {
		MinHeightLeaves(root->left);
		MinHeightLeaves(root->right);
		if (root->left && root->right) {
			if (root->left->value <= root->right->value) {
				root->value = root->left->value + 1;
			}
			else {
				root->value = root->right->value + 1;
			}
		}
		else if (root->left) {
			root->value = root->left->value + 1;
		}
		else if (root->right) {
			root->value = root->right->value + 1;
		}
		else { 
			root->value = 0;
		}
	}
}

