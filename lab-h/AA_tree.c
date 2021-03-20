#include "AA_tree.h"
#include <stdio.h>
#include <malloc.h>


// Устранение левой связи на одном уровне
void Skew(aatree_t** head) {
	aatree_t* tmpNode1;
	aatree_t* tmpNode2;
	if ((*head) == NULL || (*head)->left == NULL) {
		return;
	}
	if ((*head)->left->level == (*head)->level) {
		tmpNode1 = (*head);
		tmpNode2 = (*head)->left->right;
		(*head) = (*head)->left;
		(*head)->right = tmpNode1;
		(*head)->right->left = tmpNode2;
	}
}

// Устранение двух правых связей на одном уровне
void Split(aatree_t** head) {
	aatree_t* tmpNode1;
	aatree_t* tmpNode2;
	if ((*head) == NULL || (*head)->right == NULL || (*head)->right->right == NULL) {
		return;
	}
	if ((*head)->level == (*head)->right->right->level) {
		tmpNode1 = (*head);
		(*head)->right->level += 1;
		(*head) = (*head)->right;
		tmpNode2 = (*head)->left;
		(*head)->left = tmpNode1;
		(*head)->left->right = tmpNode2;
	}
}

// Вставка узла в дерево
int Insert(aatree_t** head, const int elemToInsert) {
	// Если дерево пустое
	if ((*head) == NULL) {
		aatree_t* newElem = (aatree_t*)malloc(sizeof(aatree_t));
		if (newElem == NULL) {
			return NO_MEMORY_ALLOCATED;
		}
		newElem->data = elemToInsert;
		newElem->level = 1;
		newElem->left = NULL;
		newElem->right = NULL;
		(*head) = newElem;
		return NO_ERRORS;
	}
	// Если не пустое
	if (elemToInsert < (*head)->data) 
		Insert(&((*head)->left), elemToInsert);
	else if (elemToInsert > (*head)->data)
		Insert(&((*head)->right), elemToInsert);
	// Балансировка
	Skew(head);
	Split(head);

	return NO_ERRORS;
};

// Поиск узла
int FindNode(aatree_t* head, const int elemToFind) {
	bool_t ifExists = FALSE;
	if (head == NULL) {
		ifExists = FALSE;
		return FALSE;
	}
	if (elemToFind < head->data)
		ifExists = FindNode(head->left, elemToFind);
	else if (elemToFind > head->data)
		ifExists = FindNode(head->right, elemToFind);
	else
		ifExists = TRUE;
	return ifExists;
};

// Удаление узла
void DeleteNode(aatree_t** head, int elemToDelete) {
	aatree_t** tmpNode1;
	aatree_t* tmpNode2;
	int tmpData;

	if ((*head) == NULL)
		return;
	if ((*head)->data < elemToDelete)
		DeleteNode(&((*head)->right), elemToDelete);
	else if ((*head)->data > elemToDelete)
		DeleteNode(&((*head)->left), elemToDelete);
	else if ((*head)->left == NULL && (*head)->right == NULL) {
		free((*head));
		(*head) = NULL;
		return;
	}
	else if ((*head)->left == NULL) {
		tmpNode2 = (*head);
		(*head) = (*head)->right;
		free(tmpNode2);
		return;
	}
	else if ((*head)->right == NULL) {
		tmpNode2 = (*head);
		(*head) = (*head)->left;
		free(tmpNode2);
		return;
	}
	else {
		tmpNode1 = &((*head)->left);
		while ((*tmpNode1)->right != NULL)
			tmpNode1 = &(*tmpNode1)->right;
		tmpData = (*tmpNode1)->data;
		(*tmpNode1)->data = (*head)->data;
		(*head)->data = tmpData;
		DeleteNode(&((*head)->left), elemToDelete);
	}
	// Уровень
	int leftNodeLvl = 0;
	int rightNodeLvl = 0;
	int newLvl = 1;
	if ((*head)->left)
		leftNodeLvl = (*head)->left->level;
	if ((*head)->right)
		rightNodeLvl = (*head)->right->level;
	if (leftNodeLvl < rightNodeLvl)
		newLvl += leftNodeLvl;
	else
		newLvl += rightNodeLvl;
	if (newLvl < (*head)->level) {
		(*head)->level = newLvl;
		if (newLvl < rightNodeLvl)
			(*head)->right->level = newLvl;
	}
	// Балансировка
	Skew(head);
	Skew(&((*head)->right));
	if ((*head)->right)
		Skew(&((*head)->right->right));
	Split(head);
	Split(&((*head)->right));

};

void FreeTree(aatree_t* head) {
	if (head == NULL)
		return;
	FreeTree(head->left);
	FreeTree(head->right);
	free(head);
}

void PrintTree(aatree_t** head) {
	if ((*head)) {
		if ((*head)->left && (*head)->right)
			printf("%d lvl: %d, left: %d, right: %d\n", (*head)->data, (*head)->level, (*head)->left->data, (*head)->right->data);
		else if ((*head)->left && (*head)->right == NULL)
			printf("%d lvl: %d, left: %d, right: -\n", (*head)->data, (*head)->level, (*head)->left->data);
		else if ((*head)->left == NULL && (*head)->right)
			printf("%d lvl: %d, left: -, right: %d\n", (*head)->data, (*head)->level, (*head)->right->data);
		else if ((*head)->left == NULL && (*head)->right == NULL)
			printf("%d lvl: %d, left: -, right: -\n", (*head)->data, (*head)->level);
		PrintTree(&(*head)->right);
		PrintTree(&(*head)->left);
	}
}