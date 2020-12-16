#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"

#pragma warning(disable : 4996)

//Функция, которая инициализирует дерево
void InitTree(node_t** tree, int num, int* error) {
	(*tree) = (node_t*)malloc(sizeof(node_t));
	if ((*tree) == NULL) {
		*error = MEM_ERROR;
		return;
	}
	(*tree)->num = num;
	(*tree)->left = NULL;
	(*tree)->right = NULL;
}

//Функция, которая добавляет элемент в дерево
void AddInTree(node_t** tree, int num) {
	int error = 0;
	if ((*tree) == NULL) {
		InitTree(tree, num, &error);
		if (error == MEM_ERROR)
			return;
	}
	if ((*tree)->num == num)
		return;
	if ((*tree)->num < num)
		AddInTree(&((*tree)->right), num);
	if ((*tree)->num > num)
		AddInTree(&((*tree)->left), num);
}

//Функция, которая удаляет элемент из дерева
void RemoveFromTree(node_t** tree, int num) {
	if ((*tree) == NULL) {
		return;
	}
	if ((*tree)->num > num) {
		RemoveFromTree(&((*tree)->left), num);
		return;
	}
	if ((*tree)->num < num) {
		RemoveFromTree(&((*tree)->right), num);
		return;
	}
	if ((*tree)->num == num) {
		if ((*tree)->left != NULL && (*tree)->right != NULL) {
			node_t** temp = &(*tree)->left;
			while ((*temp)->right) {
				temp = &((*temp)->right);
			}
			(*tree)->num = (*temp)->num;
			(*temp) = (*temp)->left;
			return;
		}
		if ((*tree)->left != NULL && (*tree)->right == NULL) {
			(*tree) = (*tree)->left;
			return;
		}
		if ((*tree)->left == NULL && (*tree)->right != NULL) {
			(*tree) = (*tree)->right;
			return;
		}
		if ((*tree)->left == NULL && (*tree)->right == NULL) {
			free(*tree);
			(*tree) = NULL;
			return;
		}

	}
}

//Функция, которая уничтожает дерево
void DestroyTree(node_t* tree) {
	if (tree == NULL)
		return;
	DestroyTree(tree->left);
	DestroyTree(tree->right);
	free(tree);
}

//Функция, которая выполняет поиск элемента по дереву
int SearchInTree(node_t* tree, int num) {
	if (tree == NULL)
		return TREE_ERROR;
	while (tree != NULL) {
		if (tree->num == num)
			return FOUND;
		else if (tree->num < num) {
			tree = tree->right;
		}
		else {
			tree = tree->left;
		}
	}
	return NOT_FOUND;
}

//Функция, которая печатает дерево в виде дерева с задающимся отступом
void PrintTree(node_t* tree, int n) {
	if (tree == NULL)
		return;
	int i = 0;
	PrintTree(tree->left, n + tree->num);
	for (i = 0; i < n; i++)
		printf("  ");
	printf("%d\n", tree->num);
	PrintTree(tree->right, n + tree->num);
}

//Функция, которая печатает дерево по заданию
void TaskPrint(node_t* tree) {
	if (tree == NULL)
		return;
	if (tree->left != NULL || tree->right != NULL) {
		printf("%d (", tree->num);
		TaskPrint(tree->left);
		printf(") (");
		TaskPrint(tree->right);
		printf(")");
	}
	else {
		printf("%d", tree->num);
	}	
}

//Функция, которая распоряжается командами, отданными пользователем
void WhatToDo(node_t** tree) {
	if (tree == NULL)
		return;
	int num = 0;
	int founder = 0;
	char c = getchar();
	while (c != EOF) {
		scanf("%d", &num);
		if (c == 'a') {
			AddInTree(tree, num);
		}
		else if (c == 'r') {
			RemoveFromTree(tree, num);
		}
		else if (c == 'f') {
			founder = SearchInTree(*tree, num);
			if (founder == FOUND)
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

int main(void) {
	node_t* tree = NULL;
	WhatToDo(&tree);
	PrintTree(tree, 2);
	printf("\n");
	TaskPrint(tree);
	DestroyTree(tree);
	return 0;
}
