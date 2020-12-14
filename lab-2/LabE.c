#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

typedef struct tree_t{

	int key;
	int leaf;
	struct tree_t* left;
	struct tree_t* right;

} tree_t;



tree_t* Max(tree_t* tree){

	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	return tree;

}

void Add(tree_t** tree, int key) {

	if ((*tree) == NULL)
	{
		(*tree) = (tree_t*)malloc(sizeof(tree_t));
		if ((*tree) == NULL)
		{
			return;
		}
		(*tree)->right = NULL;
		(*tree)->left = NULL;
		(*tree)->leaf = 0;
		(*tree)->key = key;
	}
	else
	{
		if (key > (*tree)->key)
		{
			Add(&((*tree)->right), key);
		}
		else
		{
			if (key < (*tree)->key)
			{
				Add(&((*tree)->left), key);
			}
		}
	}

}

void Delete(tree_t** tree, int key){

	if ((*tree) == NULL)
	{
		return;
	}
	if (key < (*tree)->key)
	{
		Delete(&((*tree)->left), key);
	}
	else
	{
		if (key > (*tree)->key)
		{
			Delete(&((*tree)->right), key);
		}
		else
		{
			if ((*tree)->left == NULL && (*tree)->right == NULL)
			{
				(*tree) = NULL;
			}
			else
			{
				if ((*tree)->left != NULL && (*tree)->right == NULL)
				{
					(*tree) = (*tree)->left;
				}
				else
				{
					if ((*tree)->left == NULL && (*tree)->right != NULL)
					{
						(*tree) = (*tree)->right;
					}
					else
					{
						tree_t* max = Max((*tree)->left);
						(*tree)->key = max->key;
						Delete(&((*tree)->left), max->key);
					}
				}
			}
		}
	}

}


int FindInTree(tree_t* tree, int key){

	while (tree != NULL)
	{
		if (key < tree->key)
		{
			tree = tree->left;
		}
		else
		{
			if (key > tree->key)
			{
				tree = tree->right;
			}
			else
			{
				return 1;
			}
		}

	}

	return 0;

}

void Start(tree_t** tree){

	char tmp, op, number[100];
	int i = 0, key;

	tmp = getchar();
	while (tmp != EOF)
	{
		op = tmp;
		tmp = getchar();
		while (isspace(tmp))
		{
			tmp = getchar();
		}
		while (isdigit(tmp))
		{
			number[i++] = tmp;
			tmp = getchar();
		}
		number[i] = '\0';
		key = atoi(number);
		i = 0;
		switch (op)
		{
		case 'a':
		{
			Add(tree, key);
			break;
		}
		case 'r':
		{
			Delete(tree, key);
			break;
		}
		case 'f':
		{
			if (FindInTree(*tree, key))
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
			break;
		}
		}
		if (tmp == '\n')
		{
			tmp = getchar();
		}
	}

}


int CountLeaf(tree_t** tree){

	if (tree == NULL)
		return 0;
	if ((*tree)->left == NULL && (*tree)->right == NULL)
	{
		(*tree)->leaf = 0;
		return 1;
	}
	if ((*tree)->left == NULL) {
		(*tree)->leaf = CountLeaf(&(*tree)->right);
		return (*tree)->leaf;
	}
	if ((*tree)->right == NULL) {
		(*tree)->leaf = CountLeaf(&(*tree)->left);
		return (*tree)->leaf;
	}
	(*tree)->leaf = CountLeaf(&(*tree)->left) + CountLeaf(&(*tree)->right);
	return (*tree)->leaf;

}

void ClearTree(tree_t* tree) {

	if (tree != NULL)
	{
		ClearTree(tree->right);
		ClearTree(tree->left);
		
		free(tree);
	}

}

void PrintTree(tree_t* tree){
	if (tree)
	{
		PrintTree(tree->left);
		printf("%d ", tree->key);
		PrintTree(tree->right);
	}
}

