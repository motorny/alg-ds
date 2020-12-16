#include <stdio.h>
#include <stdlib.h>

#include "treeofintervals.h"
#pragma warning(disable: 4996)

int AddNode(node_t** tree, int leftBorderValue, int rightBorderValue) {
	node_t* treeNode = NULL;
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL)
		return FALSE;
	newNode->leftBorder = leftBorderValue;
	newNode->rightBorder = rightBorderValue;
	newNode->left = NULL;
	newNode->right = NULL;


	if (leftBorderValue > rightBorderValue)
		return FALSE;
	if (*tree == NULL) {
		newNode->parent = NULL;
		(*tree) = newNode;
		return TRUE;
	}
	else {
		treeNode = (*tree);
		while (treeNode) {
			if (leftBorderValue > treeNode->leftBorder || (leftBorderValue == treeNode->leftBorder && rightBorderValue != treeNode->rightBorder)) {
				if (treeNode->right)
					treeNode = treeNode->right;
				else {
					treeNode->right = newNode;
					newNode->parent = treeNode;
					return TRUE;
				}
			}
			else if (leftBorderValue < treeNode->leftBorder) {
				if (treeNode->left)
					treeNode = treeNode->left;
				else {
					treeNode->left = newNode;
					newNode->parent = treeNode;
					return TRUE;
				}
			}
			else if (leftBorderValue == treeNode->leftBorder && rightBorderValue == treeNode->rightBorder) 
				return FALSE;
		}
		return FALSE;
	}
}

//auxiliary function, finds the biggest key in subtree
node_t* FindMaxLeftBorderNode(node_t* tree) {
	node_t* maxNode = tree;
	while (maxNode->right)
		maxNode = maxNode->right;
	return maxNode;
}

node_t* FindNode(node_t* tree, int leftBorderValue, int rightBorderValue) {
	node_t* treeNode = tree;
	if (tree == NULL || (leftBorderValue > rightBorderValue))
		return NULL;

	while (treeNode) {
		if (treeNode->leftBorder > leftBorderValue)
			treeNode = treeNode->left;
		else if (treeNode->leftBorder < leftBorderValue)
			treeNode = treeNode->right;
		else if (treeNode->rightBorder == rightBorderValue)
			return treeNode;
		else
			treeNode = treeNode->right;
	}
	return NULL;
}

int RemoveNode(node_t** tree, int leftBorderValue, int rightBorderValue) {
	node_t* delNode;
	node_t* delNodeNew;

	if (*tree == NULL)
		return FALSE;
	delNode = FindNode(*tree, leftBorderValue, rightBorderValue);
	if (delNode == NULL)
		return FALSE;

	if (delNode->left && delNode->right) { //if node has both childs
		delNodeNew = FindMaxLeftBorderNode(delNode->left); //finding the biggest key in the left subtree
		delNode->leftBorder = delNodeNew->leftBorder;  //replace data in the deliting node
		delNode->rightBorder = delNodeNew->rightBorder;

		//deleting node
		delNode = FindNode(delNode->left, delNodeNew->leftBorder, delNodeNew->rightBorder);

		if (delNodeNew->left) { //if node has child
			if (delNodeNew == delNodeNew->parent->left) {
				delNodeNew->parent->left = delNodeNew->left;
				delNodeNew->left->parent = delNodeNew->parent;
			}
			else {
				delNodeNew->parent->right = delNodeNew->left;
				delNodeNew->left->parent = delNodeNew->parent;
			}
		}
		else {
			if (delNodeNew == delNodeNew->parent->right)
				delNodeNew->parent->right = NULL;
			else if (delNodeNew == delNodeNew->parent->left)
				delNodeNew->parent->left = NULL;
		}
		free(delNodeNew);
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

void DestroyTree(node_t** tree) {
	node_t* delNode;
	while (*tree != NULL) {
		delNode = FindMaxLeftBorderNode(*tree);
		RemoveNode(tree, delNode->leftBorder, delNode->rightBorder);
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
	printf("[%i %i]\n", tree->leftBorder, tree->rightBorder);
	PrintTree(tree->left, level + 1);
}

//auxiliary function, checks if cuts cross
int CheckCrossing(int leftFinding, int rightFinding, int leftWith, int rightWith) {
	if ((leftFinding >= leftWith && leftFinding <= rightWith) || (rightFinding >= leftWith && rightFinding <= rightWith))
		return TRUE;
	else
		return FALSE;
}

//auxiliary function for FindIntersections
node_t* Parent(int* direction, node_t* subtree) {
	node_t* subtreeNode = subtree;

	if (subtreeNode->parent == NULL) {
		subtree = NULL;
		return subtree;
	}

	if (subtreeNode == subtreeNode->parent->left)
		*direction = FROM_LEFT;
	else
		*direction = FROM_RIGHT;
	return subtreeNode->parent;
}

//auxiliary function for FindIntersections
node_t* LeftChild(int* direction, node_t* subtree) {
	*direction = FROM_PARENT;
	return subtree->left;
}

//auxiliary function for FindIntersections
node_t* RightChild(int* direction, node_t* subtree) {
	*direction = FROM_PARENT;
	return subtree->right;
}

node_t** FindIntersections(node_t* tree, int leftBorder, int rightBorder) {
	node_t** intersections = NULL;
	int  intersectionsCount = 0;
	node_t** newMemory;
	node_t* treeNode = tree;
	int direction = FROM_PARENT;

	while (treeNode) {
		if (direction == FROM_PARENT) {
			if (CheckCrossing(leftBorder, rightBorder, treeNode->leftBorder, treeNode->rightBorder)) {
				newMemory = (node_t**)realloc(intersections, sizeof(node_t*) * (intersectionsCount + 1));
				if (newMemory == NULL) {
					free(intersections);
					return NULL;
				}
				else
					intersections = newMemory;
				intersections[intersectionsCount] = treeNode;
				intersectionsCount++;
			}
			if (treeNode->left != NULL)
				treeNode = LeftChild(&direction, treeNode);
			else
				direction = FROM_LEFT;
		}
		else if (direction == FROM_LEFT) {
			if (treeNode->right != NULL)
				treeNode = RightChild(&direction, treeNode);
			else
				direction = FROM_RIGHT;
		}
		else if (direction == FROM_RIGHT)
			treeNode = Parent(&direction, treeNode);
	}

	if (intersections) {
		newMemory = (node_t**)realloc(intersections, sizeof(node_t*) * (intersectionsCount + 1));
		if (newMemory == NULL) {
			free(intersections);
			return NULL;
		}
		else
			intersections = newMemory;
		intersections[intersectionsCount] = NULL;
	}
	return intersections;
}


void ManageTreeOfIntervals(node_t** tree) {
	int leftBorder, rightBorder, numOfIntersec = 0;
	char operator;
	node_t** intersections;
	while (TRUE) {
		operator = getchar();
		if (operator == EOF || operator == '\n')
			break;

		scanf("%i %i", &leftBorder, &rightBorder);

		if (operator == 'a') {
			if (!AddNode(tree, leftBorder, rightBorder))
				printf("add error\n");
		}
		else if (operator == 'r')
			RemoveNode(tree, leftBorder, rightBorder);
		else if (operator == 'f') {
			if (FindNode(*tree, leftBorder, rightBorder) != NULL)
				printf("yes\n");
			else
				printf("no\n");
		}
		else if (operator == 'i') { //operator for finding intersections
			intersections = FindIntersections(*tree, leftBorder, rightBorder);
			while (intersections && intersections[numOfIntersec]) {
				printf("%i %i    ", intersections[numOfIntersec]->leftBorder, intersections[numOfIntersec]->rightBorder);
				numOfIntersec++;
			}
			if(numOfIntersec == 0)
				printf("no intersections found");
			printf("\n");
			numOfIntersec = 0;
		}
		else
			printf("Incorrect input\n");

		operator = getchar();
	}
}