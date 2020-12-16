#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tree.h"


int AddToTree(node_t** tree, int key) {
	node_t* node = (node_t*)malloc(sizeof(node_t));

	if (node == NULL)
		return FALSE;

	node_t* tmp = NULL;
	node->key = key;
	node->left = NULL;
	node->right = NULL;

	// Если дерево пустое
	if (*tree == NULL) {
		*tree = node;
		node->parent = NULL;
	}
	// Если корень уже есть
	else {
		while (*tree != NULL) {
			tmp = *tree;
			// Спускаемся
			if ((*tree)->key < key)
				tree = &((*tree)->right);
			else if ((*tree)->key > key)
				tree = &((*tree)->left);
			// Если такой уже есть
			else {
				free(node);
				return FALSE;
			}
		}
		*tree = node;
		node->parent = tmp;
	}
	while (node->parent != NULL)
		node = node->parent;

	return TRUE;

};

node_t* FindInTree(node_t* tree, int key) {
	while (tree != NULL) {
		// Спускаемся в дерево
		if (tree->key > key)
			tree = tree->left;
		else if (tree->key < key)
			tree = tree->right;
		// Искомое найдено
		else
			return tree;
	}
	// Если ничего не нашлось
	return NULL;
};

static node_t* Maximum(node_t* tree) {
	if (tree == NULL)
		return NULL;
	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}

int DeleteFromTree(node_t** tree, int key) {
	node_t* node = NULL;
	node_t* tmp = NULL;
	// Если дерево не пустое
	if (*tree != NULL) {
		node = FindInTree(*tree, key);
		// Если такой нашелся
		if (node != NULL) {
			// Если это лист 
			if (node->left == NULL && node->right == NULL){
				// С родителем
				if (node->parent != NULL) {
					// Если он левый
					if (node == node->parent->left)
						node->parent->left = NULL;
					// Если правый
					else
						node->parent->right = NULL;
				}
				// Если есть только корень, и он искомый
				else
					*tree = NULL;
			}
			// Если есть потомок только слева
			else if (node->left != NULL && node->right == NULL) {
				// Если с родителем, то подсоединим к родителю потомок
				if (node->parent != NULL) {
					node->left->parent = node->parent;
					// Если он левый
					if (node == node->parent->left)
						node->parent->left = node->left;
					// Если правый
					else
						node->parent->right = node->left;
				}
				// Это корень, сделаем потомок корнем
				else {
					*tree = node->left;
					(*tree)->parent = NULL;
				}
			}
			// Если есть потомок только справа
			else if (node->left == NULL && node->right != NULL) {
				// Если с родителем, то подсоединим к родителю потомок
				if (node->parent != NULL) {
					node->right->parent = node->parent;
					// Если он левый
					if (node == node->parent->left)
						node->parent->left = node->right;
					// Если правый
					else
						node->parent->right = node->right;
				}
				// Это корень, сделаем потомок корнем
				else {
					*tree = node->right;
					(*tree)->parent = NULL;
				}
			}
			// Если у удаляемого узла два потомка
			else {
				// Найдем среди всех потомков больший
				tmp = Maximum(node->left);
				node->key = tmp->key;
				// Удаляем максимум левого поддерева
				DeleteFromTree(&(node->left), tmp->key);
				return TRUE;
			}
			tmp = node;
			while (tmp->parent != NULL)
				tmp = tmp->parent;
			// Освободим память из-под нашего элемента
			free(node);
			return TRUE;
		}
	}
	return FALSE;
};

void DestroyTree(node_t** tree) {
	while ((*tree) != NULL)
		DeleteFromTree(tree, (*tree)->key);
};

void PrintLevels(node_t* tree, int level, char* state) {
	if (tree) {
		printf("level = %i, %s, key = %i\n", level, state, tree->key);
		PrintLevels(tree->left, level + 1, "left");
		PrintLevels(tree->right, level + 1, "right");
	}
};
// Печатает слева направо
void PrintTree(node_t* tree, int level) {
	int i = 0;
	if (tree) {
		PrintTree(tree->right, level + 1);
		for (i = 0; i < level; i++)
			putchar('   ');
		printf("%i\n", tree->key);
		PrintTree(tree->left, level + 1);
	}
}


void PrintNodes(node_t* tree) {
	if (tree) {
		if (tree->left || tree->right) {
			printf("%i (", tree->key);
			PrintNodes(tree->left);
			printf(") (");
			PrintNodes(tree->right);
			printf(")");
		}
		else {
			printf("%i", tree->key);
		}
	}
};

