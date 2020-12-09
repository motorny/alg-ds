#define _CRT_SECURE_NO_WARNINGS

#include<malloc.h>
#include<stdio.h>
#include"SectionTree.h"
#include<stdbool.h>

#define FROM_PARENT 1
#define FROM_LEFT_CHILD 2
#define FROM_RIGHT_CHILD 3

static NODE* CreateNode(int leftBorder, int rightBorder, NODE* parent) {
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->leftBorder = leftBorder;
	node->rightBorder = rightBorder;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return node;
}

//Organization by leftBorder
void InsertInTree(NODE** root, int leftBorder, int rightBorder) {
	NODE* temp = NULL;
	if (leftBorder > rightBorder)
		return;
	if (*root == NULL) {
		*root = CreateNode(leftBorder, rightBorder, NULL);
		return;
	}
	temp = *root;
	while (temp) {
		if (leftBorder > temp->leftBorder || (leftBorder == temp->leftBorder && rightBorder != temp->rightBorder)) {
			if (temp->right) {
				temp = temp->right;
				continue;
			}
			else {
				temp->right = CreateNode(leftBorder, rightBorder, temp);
				return;
			}
		}
		else if (leftBorder < temp->leftBorder) {
			if (temp->left) {
				temp = temp->left;
				continue;
			}
			else {
				temp->left = CreateNode(leftBorder, rightBorder, temp);
				return;
			}
		}
		else
			return;
	}
}

static NODE* GetMinLeftBorderNode(NODE* root) {
	while (root->left)
		root = root->left;
	return root;
}

static NODE* GetMaxLeftBorderNode(NODE* root) {
	while (root->right)
		root = root->right;
	return root;
}

static void RemoveNodeByPtr(NODE* target, NODE* root) {
	if (target == NULL)
		return;
	if (target->left && target->right) {
		NODE* localMax = GetMaxLeftBorderNode(target->left);
		target->leftBorder = localMax->leftBorder;
		target->rightBorder = localMax->rightBorder;
		RemoveNodeByPtr(localMax, root);
		return;
	}
	else if (target->left) {
		if (target->parent == NULL) {
			NODE* nodeToDel = target->left;
			target->leftBorder = nodeToDel->leftBorder;
			target->rightBorder = nodeToDel->rightBorder;
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
			target->leftBorder = nodeToDel->leftBorder;
			target->rightBorder = nodeToDel->rightBorder;
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

static NODE* SearchNodeByData(NODE* root, int leftBorder, int rightBorder) {
	if (leftBorder <= rightBorder) {
		while (root) {
			if (root->leftBorder > leftBorder) {
				root = root->left;
				continue;
			}
			else if (root->leftBorder < leftBorder) {
				root = root->right;
				continue;
			}
			else if (root->rightBorder == rightBorder)
				return root;
			else {
				root = root->right;
				continue;
			}

		}
	}
	return NULL;
}

static void RemoveNodeByData(NODE* root, int leftBorder, int rightBorder) {
	NODE* target = SearchNodeByData(root, leftBorder, rightBorder);
	RemoveNodeByPtr(target, root);
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
	int leftBorder, rightBorder;
	char c = getchar();
	while (c != EOF) {
		scanf("%d %d", &leftBorder, &rightBorder);
		if (c == 'a') {
			InsertInTree(root, leftBorder, rightBorder);
		}
		else if (c == 'r') {
			RemoveNodeByData(*root, leftBorder, rightBorder);
		}
		else if (c == 'f') {
			NODE* searNode = SearchNodeByData(*root, leftBorder, rightBorder);
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

void printTreePreOrder(NODE* root, const char* dir, int level) {
	if (root) {
		printf("lvl %d %s = [%d %d]\n", level, dir, root->leftBorder, root->rightBorder);
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
		printf("[%d %d]", root->leftBorder, root->rightBorder);
	}
}

static void GoToParrent(int* wayP, NODE** currentP) {
	NODE* current = *currentP;

	if (current->parent == NULL) {
		*currentP = NULL;
		return;
	}
	*wayP = current == current->parent->left ? FROM_LEFT_CHILD : FROM_RIGHT_CHILD;
	*currentP = current->parent;
}

static void GoLeft(int* wayP, NODE** currentP) {
	*wayP = FROM_PARENT;
	*currentP = (*currentP)->left;
}

static void GoRight(int* wayP, NODE** currentP) {
	*wayP = FROM_PARENT;
	*currentP = (*currentP)->right;
}

void PrintSectMass(NODE** mass) {
	for (int i = 0; mass[i] != NULL; i++) {
		printf("[%d %d]\n", (mass[i])->leftBorder, (mass[i])->rightBorder);
	}
}

bool CheckForCrossing(int leftFinding, int rightFinding, int leftWith, int rightWith) {
	if ((leftFinding >= leftWith && leftFinding <= rightWith) || (rightFinding >= leftWith && rightFinding <= rightWith))
		return true;
	else
		return false;
}

NODE** FindInterSegm(NODE* root, int leftBorder, int rightBorder) {
	NODE** interSegm = NULL;
	int interSegm_C = 0;
	int way = FROM_PARENT;
	NODE* current = root;

	while (current) {
		switch (way) {
		case FROM_PARENT:
			if (CheckForCrossing(leftBorder, rightBorder, current->leftBorder, current->rightBorder)) {
				interSegm = (NODE**)realloc(interSegm, sizeof(NODE*) * (interSegm_C+1));
				interSegm[interSegm_C] = current;
				interSegm_C++;
			}
			if (current->left != NULL)
				GoLeft(&way, &current);
			else
				way = FROM_LEFT_CHILD;
			break;
		case FROM_LEFT_CHILD:
			if (current->right != NULL)
				GoRight(&way, &current);
			else
				way = FROM_RIGHT_CHILD;
			break;
		case FROM_RIGHT_CHILD:
			GoToParrent(&way, &current);
			break;
		}
		
	}

	interSegm = (NODE**)realloc(interSegm, sizeof(NODE*) * (interSegm_C+1));
	interSegm[interSegm_C] = NULL;
	return interSegm;
}