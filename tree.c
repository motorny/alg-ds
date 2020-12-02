#include<stdio.h>
#include<stdlib.h>
#include"tree.h"

char* readString() {
	char* str = NULL, * ptr = NULL;
	int i = 0;
	str = (char*)malloc(2 * sizeof(char));
	if (!str)
		return NULL;
	while ((str[i] = fgetc(stdin)) != EOF) {
		i++;
		ptr = realloc(str, (i + 1) * sizeof(char));
		if (ptr)
			str = ptr;
		else
			return NULL;
	}
	str[i] = 0;
	return str;
}

node_t* getNode(node_t* parent, int elem) {
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	if (tmp) {
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->parent = parent;
		tmp->elem = elem;
	}
	return tmp;
}
void treeDestroy(node_t* tree) {
	if (tree) {
		treeDestroy(tree->left);
		treeDestroy(tree->right);
		free(tree);
	}
}

int nodeAdd(node_t** root, int elem) {
	int number = 1;
	if ((*root) == NULL) {
		(*root) = getNode(NULL, elem);
		(*root)->ordNumb = 1;
		return 1;
	}
	node_t* tmp = (*root);
	while (tmp) {
		if (elem > tmp->elem) {
			if (tmp->right) {
				tmp = tmp->right;
				continue;
			}
			else {
				tmp->right = getNode(tmp, elem);
				setOrder((*root), &number);
				return 1;
			}
		}
		else if (elem < tmp->elem) {
			if (tmp->left) {
				tmp = tmp->left;
				continue;
			}
			else {
				tmp->left = getNode(tmp, elem);
				setOrder((*root), &number);
				return 1;
			}
		}
		else if (elem == tmp->elem)
			return 0;
	}
	return 0;

}

node_t* findNode(node_t* root, int elem) {
	while (root) {
		if (elem > root->elem) {
			root = root->right;
			continue;
		}
		else if (elem < root->elem) {
			root = root->left;
		}
		else {
			return root;
		}
	}
	return NULL;
}



void deleteNodeByElem(node_t** root, int elem) {
	node_t* tmp = NULL;
	int number = 1;
	node_t** tree = (root);
	node_t** lmx;
	if (root) {
		while (*root) {
			if (elem > (*root)->elem) {
				(root) = &((*root)->right);
			}
			else if (elem < (*root)->elem) {
				(root) = &((*root)->left);
			}
			else {
				tmp = (*root);
				if (!(*root)->left && !(*root)->right)
					(*root) = NULL;
				else if (!(*root)->left)
					(*root) = (*root)->right;
				else if (!(*root)->right)
					(*root) = (*root)->left;
				else {
					lmx = &(*root)->left;
					while ((*lmx)->right)
						lmx = &(*lmx)->right;
					(*root)->elem = (*lmx)->elem;
					tmp = *lmx;
					(*lmx) = (*lmx)->left;
				}

				free(tmp);
				setOrder(*tree, &number);
			}

		}
		
	}
}
void printTree(node_t* root,char* dir, int level) {
	if (root) {
		printf("lvl %d %s = %d  order = %i\n", level, dir, root->elem, root->ordNumb);
		printTree(root->left, "left", level + 1);
		printTree(root->right, "right", level + 1);
	}
}

void setOrder(node_t* node, int* number) {
	if (node) {
		
		setOrder(node->left, number);
		node->ordNumb = (*number);
		(*number)++;
		setOrder(node->right, number);
	}
}

int height(node_t* node) {
	if (node == 0)
		return 0;
	int left, right;
	if (node->left != NULL) {
		left = height(node->left);
	}
	else
		left = -1;
	if (node->right != NULL) {
		right = height(node->right);
	}
	else
		right = -1;
	int max = left > right ? left : right;
	return max + 1;
}

void heightTree(node_t* root) {
	int left = 0, right = 0;
	if (root) {
		
		if (root->left) {
			left = height(root->left) + 1;
			heightTree(root->left);
		}
		else left = 0;

		if (root->right) {
			right = height(root->right) + 1;
			heightTree(root->right);
		}
		else right = 0;

		root->elem = left - right;
		
	}
}

node_t* findK(node_t* root, int k) {
	node_t* number = NULL;
	if (root) {
	
		number = findK(root->right, k);
		if (number)
			return number;
		if (root->ordNumb == k)
			return root;
		number = findK(root->left, k);
		if (number)
			return number;
	}
	return NULL;
}
void printLow(node_t* root,char* dir, int level, int k) {
	if (root) {
		printLow(root->left, "left", level + 1, k);
		if (root->ordNumb < k)
			printf("lvl %d %s = %d  order = %i\n", level, dir, root->elem, root->ordNumb);
		printLow(root->right, "right", level + 1, k);
	}
}

void printKsmall(node_t* root, int k) {
	int number = 1;
	node_t* trgt = findK(root, k);
	if (trgt) {
		printf("\n K: %i  VALUE: %i\n", trgt->ordNumb, trgt->elem);
		if (trgt->elem % 2 == 0)
			printLow(root, "root", 0, k);
	}
	else
		printf("\nNOT FOUND\n");

}