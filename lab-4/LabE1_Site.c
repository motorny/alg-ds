#include "Tree.h"

#define FIND 1
#define NOT_FIND 0

void addToTree(TREE** tree, int data)
{
	if ((*tree) == NULL)
	{
		(*tree) = (TREE*)malloc(sizeof(TREE));
		if ((*tree) == NULL)
		{
			return;
		}
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->data = data;
	}
	else
	{
		if (data < (*tree)->data)
		{
			addToTree(&((*tree)->left), data);
		}
		else
		{
			if (data > (*tree)->data)
			{
				addToTree(&((*tree)->right), data);
			}
		}
	}
}

TREE* getMax(TREE* tree)
{
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	return tree;
}

void delByData(TREE** tree, int data)
{
	if ((*tree) == NULL)
	{
		return;
	}
	if (data < (*tree)->data)
	{
		delByData(&((*tree)->left), data);
	}
	else
	{
		if (data > (*tree)->data)
		{
			delByData(&((*tree)->right), data);
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
						TREE* max = getMax((*tree)->left);
						(*tree)->data = max->data;
						delByData(&((*tree)->left), max->data);
					}
				}
			}
		}
	}
}

int findByValue(TREE* tree, int data)
{
	while (tree != NULL)
	{
		if (data < tree->data)
		{
			tree = tree->left;
		}
		else
		{
			if (data > tree->data)
			{
				tree = tree->right;
			}
			else
			{
				return FIND;
			}
		}

	}
	return NOT_FIND;
}

void workingWithTree(TREE** tree)
{
	char c, operation, number[255];
	int index = 0, data;

	c = getchar();
	while (c != EOF)
	{
		operation = c;
		c = getchar();
		while (isspace(c))
		{
			c = getchar();
		}
		while (isdigit(c))
		{
			number[index++] = c;
			c = getchar();
		}
		number[index] = '\0';
		data = atoi(number);
		index = 0;
		switch (operation)
		{
		case 'a':
		{
			addToTree(tree, data);
			break;
		}
		case 'r':
		{
			delByData(tree, data);
			break;
		}
		case 'f':
		{
			if (findByValue(*tree, data))
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
		if (c == '\n')
		{
			c = getchar();
		}
	}
}

void destroyTree(TREE* tree)
{
	if (tree != NULL)
	{
		destroyTree(tree->left);
		destroyTree(tree->right);
		free(tree);
	}
}

void printTree(TREE* tree, int index)
{
	if (tree != NULL)
	{
		printf("%d %d\n", index, tree->data);
		printTree(tree->left, index + 1);
		printTree(tree->right, index + 1);
	}
}

int treeHeight(TREE* tree)
{
	int heightLeft = 0, heightRight = 0;
	if (tree == NULL)
	{
		return 0;
	}
	if (tree->left != NULL)
	{
		heightLeft = treeHeight(tree->left);
	}
	if (tree->right != NULL)
	{
		heightRight = treeHeight(tree->right);
	}
	if (heightLeft > heightRight)
	{
		return heightLeft + 1;
	}
	else
	{
		return heightRight + 1;
	}
}

TREE* subtreeHeightDif(TREE* tree)
{
	int heightLeft = 0, heightRight = 0;
	if (tree != NULL)
	{
		if (tree->left != NULL)
		{
			heightLeft = treeHeight(tree->left) + 1;
			subtreeHeightDif(tree->left);
		}
		if (tree->right != NULL)
		{
			heightRight = treeHeight(tree->right) + 1;
			subtreeHeightDif(tree->right);
		}
		tree->data = abs(heightLeft - heightRight);
	}
	return tree;
}