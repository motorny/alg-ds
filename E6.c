#include <stdio.h>
#include <string.h>
#include "E6.h"

#pragma warning(disable: 4996)
#define MAX_LENGTH 1000

static int parser(node** mytree, char *string, int start, int brackets) {
	int i = start, save = 0, recursive;
	char empty[SIZE] = "\0", leftchild = 0, rightchild = 0;
	node* next = (node*)malloc(sizeof(node));
	if (next == NULL)
		return 0;
	strncpy(next->key, empty, SIZE);
	next->left = next->right = NULL;
	while (string[i] != 0) {
		if (string[i] == '(') {
			brackets++;
			if (leftchild == 0) {
				recursive = parser(&(next->left), string, i + 1, brackets);
				if (recursive == 0) {
					free(next);
					return 0;
				}
				i = recursive;
				leftchild = 1;
			}
			else if (rightchild == 0) {
				recursive = parser(&(next->right), string, i + 1, brackets);
				if (recursive == 0) {
					free(next);
					return 0;
				}
				i = recursive;
				rightchild = 1;
			}
			else {
				free(next);
				return 0;
			}
		}
		else if (string[i] == ')') {
			brackets--;
			if (brackets < 0) {
				free(next);
				return 0;
			}
			if (leftchild == 1 && rightchild == 1) {
				free(next);
				return 0;
			}
			(next->key)[save] = 0;
			if (strcmp(next->key, empty) == 0) {
				*mytree = NULL;
				free(next);
			}
			else
				*mytree = next;
			return i;
		}
		else if (i >= 1 && string[i - 1] == ')' && string[i] != '(') {
			free(next);
			return 0;
		}
		else {
			if (save < SIZE - 1)
				(next->key)[save++] = string[i];
		}
		i++;
	}
	if (string[i] == 0 && start != 0) {
		free(next);
		return 0;
	}
	*mytree = next;
	return i;
}

int ReadFile(node** mytree, char* filename) {
	char read[MAX_LENGTH] = "\0";
	int res;
	FILE* file = fopen(filename, "rt");
	*mytree = NULL;
	if (file == NULL)
		return 0;
	fgets(read, MAX_LENGTH, file);
	res = parser(mytree, read, 0, 0);
	if (!res) {
		*mytree = NULL;
		return 0;
	}
	fclose(file);
	return 1;
}

void Print(node* mytree) {
	if (mytree == NULL)
		return;
	if (mytree->left == NULL && mytree->right == NULL) {
		printf("%s()()\n", mytree->key);
	}
	else if (mytree->left == NULL && mytree->right != NULL) {
		printf("%s()(%s)\n", mytree->key, mytree->right->key);
		Print(mytree->right);
	}
	else if (mytree->left != NULL && mytree->right == NULL) {
		printf("%s(%s)()\n", mytree->key, mytree->left->key);
		Print(mytree->left);
	}
	else if (mytree->left != NULL && mytree->right != NULL) {
		printf("%s(%s)(%s)\n", mytree->key, mytree->left->key, mytree->right->key);
		Print(mytree->left);
		Print(mytree->right);
	}
}

static void Delete(node** mytree) {
	node* save = *mytree;
	node** temp;
	if ((*mytree)->left == NULL && (*mytree)->right == NULL)
		(*mytree) = NULL;
	else if ((*mytree)->left == NULL)
		(*mytree) = (*mytree)->right;
	else if ((*mytree)->right == NULL)
		(*mytree) = (*mytree)->left;
	else {
		temp = &(*mytree)->left;
		while ((*temp)->right != NULL)
			temp = &(*temp)->right;
		strncpy((*mytree)->key, (*temp)->key, SIZE);
		save = *temp;
		(*temp) = (*temp)->left;
	}
	free(save);
}

void DeleteAll(node** mytree) {
	while ((*mytree) != NULL)
		Delete(mytree);
}