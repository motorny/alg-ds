#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	int leaf;
	struct node* left;
	struct node* right;
} TREE;

#define FIND 1
#define NOT_FIND 0

void add(TREE** node, int key)
{
	if ((*node) == NULL)
	{
		(*node) = (TREE*)malloc(sizeof(TREE));
		if ((*node) == NULL)
		{
			return;
		}
		(*node)->left = NULL;
		(*node)->right = NULL;
		(*node)->key = key;
		(*node)->leaf = 0;
	}
	else
	{
		if (key < (*node)->key)
		{
			add(&((*node)->left), key);
		}
		else
		{
			if (key > (*node)->key)
			{
				add(&((*node)->right), key);
			}
		}
	}
}

TREE* getMax(TREE* node)
{
	while (node->right != NULL)
	{
		node = node->right;
	}
	return node;
}

void del(TREE** node, int key)
{
	if ((*node) == NULL)
	{
		return;
	}
	if (key < (*node)->key)
	{
		del(&((*node)->left), key);
	}
	else
	{
		if (key > (*node)->key)
		{
			del(&((*node)->right), key);
		}
		else
		{
			if ((*node)->left == NULL && (*node)->right == NULL)
			{
				(*node) = NULL;
			}
			else
			{
				if ((*node)->left != NULL && (*node)->right == NULL)
				{
					(*node) = (*node)->left;
				}
				else
				{
					if ((*node)->left == NULL && (*node)->right != NULL)
					{
						(*node) = (*node)->right;
					}
					else
					{
						TREE* max = getMax((*node)->left);
						(*node)->key = max->key;
						del(&((*node)->left), max->key);
					}
				}
			}
		}
	}
}

int findByValue(TREE* node, int key)
{
	while (node != NULL)
	{
		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			if (key > node->key)
			{
				node = node->right;
			}
			else
			{
				return FIND;
			}
		}

	}
	return NOT_FIND;
}

void workingWithTree(TREE** node)
{
	char c, operation, number[255];
	int index = 0, key;

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
		key = atoi(number);
		index = 0;
		switch (operation)
		{
		case 'a':
		{
			add(node, key);
			break;
		}
		case 'r':
		{
			del(node, key);
			break;
		}
		case 'f':
		{
			if (findByValue(*node, key))
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

void destroyTree(TREE* node)
{
	if (node != NULL)
	{
		destroyTree(node->left);
		destroyTree(node->right);
		free(node);
	}
}

int countLeaf(TREE** node)
{
	if (node == NULL)
		return 0;
	if ((*node)->left == NULL && (*node)->right == NULL)
	{
		(*node)->leaf = 0;
		return 1;
	}
	(*node)->leaf = countLeaf((*node)->left) + countLeaf((*node)->right);
	return (*node)->leaf;
}

void printTree(TREE* node, int index)
{
	if (node)
	{
		printf("%d: %d\n", index, node->leaf);
		printTree(node->left, index + 1);
		printTree(node->right, index + 1);
	}
}

//int main()
//{
//	TREE* node = NULL;
//	workingWithTree(&node);
//	countLeaf(node);
//	printTree(node, 0);
//	destroyTree(node);
//	return 0;
//}