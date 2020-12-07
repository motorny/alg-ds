#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include"Tree.h"

NODE* CreateNode(int data, NODE* parent) {
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return node;
}

void InsertInTree(NODE** root, int data) {
	NODE* temp = NULL;
	if (*root == NULL) {
		*root = CreateNode(data, NULL);
		return;
	}
	temp = *root;
	while (temp) {
		if (data > temp->data) {
			if (temp->right) {
				temp = temp->right;
				continue;
			}
			else {
				temp->right = CreateNode(data, temp);
				return;
			}
		}
		else if (data < temp->data) {
			if (temp->left) {
				temp = temp->left;
				continue;
			}
			else {
				temp->left = CreateNode(data, temp);
				return;
			}
		}
		return;
	}
}

NODE* GetMinNode(NODE* root) {
	while (root->left)
		root = root->left;
	return root;
}

NODE* GetMaxNode(NODE* root) {
	while (root->right)
		root = root->right;
	return root;
}

NODE* SearchNodeByData(NODE* root, int data) {
	while (root) {
		if (root->data > data) {
			root = root->left;
			continue;
		}
		else if (root->data < data) {
			root = root->right;
			continue;
		}
		return root;
	}
	return NULL;
}

//Рассмотреть случай, когда удаляем корень и ниже ничего нет, нужно чтобы корень стал NULL
void RemoveNodeByPtr(NODE* target) {
	if (target == NULL)
		return;
	if (target->left && target->right) {
		NODE* localMax = GetMaxNode(target->left);
		target->data = localMax->data;
		RemoveNodeByPtr(localMax);
		return;
	}
	else if (target->left) {
		if (target->parent == NULL) {
			NODE* nodeToDel = target->left;
			target->data = nodeToDel->data;
			target->left = nodeToDel->left;
			target->right = nodeToDel->right;
			target = nodeToDel;
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
			NODE* nodeToDel = target->right;
			target->data = nodeToDel->data;
			target->left = nodeToDel->left;
			target->right = nodeToDel->right;
			target = nodeToDel;
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
			if (target == target->parent->left)
				target->parent->left = NULL;
			else
				target->parent->right = NULL;
		}
	}
	free(target);
}

void RemoveNodeByData(NODE* root, int data) {
	NODE* target = SearchNodeByData(root, data);
	RemoveNodeByPtr(target);
}

void printTreePreOrder(NODE* root, const char* dir, int level) {
	if (root) {
		printf("lvl %d %s = %d\n", level, dir, root->data);
		printTreePreOrder(root->left, "left", level + 1);
		printTreePreOrder(root->right, "right", level + 1);
	}
}

void printTreePostOrder(NODE* root)
{
	if (root) {
		if (root->left)
			printTreePostOrder(root->left);
		if (root->right)
			printTreePostOrder(root->right);
		printf("%d ", root->data);
	}
}

void DestroyTree(NODE** root) {
	if (*root) {
		DestroyTree(&((*root)->left));
		DestroyTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

void ConsoleTree(NODE** root) {
	int data;
	char c = getchar();
	while (c != EOF) {
		scanf("%d", &data);
		if (c == 'a') {
			InsertInTree(root, data);
		}
		else if (c == 'r') {
			RemoveNodeByData(*root, data);
		}
		else if (c == 'f') {
			NODE* searNode = SearchNodeByData(*root, data);
			if (searNode != NULL)
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

void WriteInDataMinLeavesHeight(NODE* root) {
	//Write min heights of leaves in subtrees in the nodes of the binary tree.
	if (root) {
		WriteInDataMinLeavesHeight(root->left);
		WriteInDataMinLeavesHeight(root->right);
		if (root->left && root->right)
			root->data = root->left->data < root->right->data ? root->left->data : root->right->data;
		else if (root->left)
			root->data = root->left->data;
		else if (root->right)
			root->data = root->right->data;
		else
			root->data = -1;
		root->data++;
	}
}
