#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct node
{
	int leftBorder;
	int rightBorder;
	struct node* parent;
	struct node* left;
	struct node* right;
} TREE;

#define FIND 1
#define NOT_FIND 0

void add(TREE** node, int lBorder, int rBorder)
{
	TREE* tmp;
	if (lBorder > rBorder)
	{
		return;
	}
	if ((*node) == NULL)
	{
		(*node) = (TREE*)malloc(sizeof(TREE));
		if ((*node) == NULL)
		{
			return;
		}
		(*node)->left = NULL;
		(*node)->right = NULL;
		(*node)->leftBorder = lBorder;
		(*node)->rightBorder = rBorder;
	}
	else
	{
		tmp = (*node);
		while (tmp)
		{
			if (lBorder < (*node)->leftBorder)
			{
				if (tmp->left)
				{
					tmp = tmp->left;
					continue;
				}
				else
				{
					tmp = (TREE*)malloc(sizeof(TREE));
					if (tmp == NULL)
					{
						return;
					}
					tmp->left = NULL;
					tmp->right = NULL;
					tmp->leftBorder = lBorder;
					tmp->rightBorder = rBorder;
					return;
				}
			}
			else
			{
				if (rBorder != (*node)->rightBorder || lBorder > (*node)->leftBorder)
				{
					if (tmp->right)
					{
						tmp = tmp->right;
						continue;
					}
					else
					{
						tmp = (TREE*)malloc(sizeof(TREE));
						if (tmp == NULL)
						{
							return;
						}
						tmp->left = NULL;
						tmp->right = NULL;
						tmp->leftBorder = lBorder;
						tmp->rightBorder = rBorder;
						return;
					}
				}
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

void del(TREE** node, int lBorder, int rBorder)
{
	if ((*node) == NULL)
	{
		return;
	}
	if (lBorder < (*node)->leftBorder)
	{
		delSegment(&((*node)->left), lBorder, rBorder);
	}
	else
	{
		if (rBorder != (*node)->rightBorder || lBorder > (*node)->leftBorder)
		{
			delSegment(&((*node)->right), lBorder, rBorder);
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
						(*node)->leftBorder = max->leftBorder;
						delSegment(&((*node)->left), max->leftBorder, max->rightBorder);
					}
				}
			}
		}
	}
}

int findByValue(TREE* node, int lBorder, int rBorder)
{
	while (node != NULL)
	{
		if (lBorder < node->leftBorder)
		{
			node = node->left;
		}
		else
		{
			if (rBorder != node->rightBorder || lBorder > node->leftBorder)
			{
				node = node->right;
				continue;
			}
			else
			{
				return FIND;
			}
		}

	}
	return NOT_FIND;
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

void printTree(TREE* node, int index)
{
	if (node != NULL)
	{
		printf("%d: [%d ; %d]\n", index, node->leftBorder, node->rightBorder);
		printTreeSegm(node->left, index + 1);
		printTreeSegm(node->right, index + 1);
	}
}

typedef struct
{
	int lBorder;
	int rBorder;
} INTERSECTING_SEGM;

int index = 0;
INTERSECTING_SEGM answer[100];

void interSegm(TREE* node, int lBorder, int rBorder)
{
	if (node != NULL)
	{
		if (rBorder >= node->leftBorder && lBorder <= node->rightBorder)
		{
			answer[index].lBorder = node->leftBorder;
			answer[index++].rBorder = node->rightBorder;
		}
		interSegm(node->left, lBorder, rBorder);
		interSegm(node->right, lBorder, rBorder);
	}
}