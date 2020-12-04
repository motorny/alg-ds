#include <malloc.h>
#include <stdio.h>

#define FIND 1
#define NOT_FIND 0

typedef struct tree
{
	int leftBorder;
	int rightBorder;
	struct tree* left;
	struct tree* right;
} TREESEGM;

typedef struct
{
	int lBorder;
	int rBorder;
} INTERSECTING_SEGM;

int index = 0;
INTERSECTING_SEGM answer[100];

void addSegment(TREESEGM** tree, int lBorder, int rBorder)
{
	if (lBorder > rBorder)
	{
		return;
	}
	if ((*tree) == NULL)
	{
		(*tree) = (TREESEGM*)malloc(sizeof(TREESEGM));
		if ((*tree) == NULL)
		{
			return;
		}
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->leftBorder = lBorder;
		(*tree)->rightBorder = rBorder;
	}
	else
	{
		if (lBorder < (*tree)->leftBorder)
		{
			addSegment(&((*tree)->left), lBorder, rBorder);
		}
		else
		{
			if (rBorder != (*tree)->rightBorder || lBorder > (*tree)->leftBorder)
			{
				addSegment(&((*tree)->right), lBorder, rBorder);
			}
		}
	}
}

int findSegmention(TREESEGM* tree, int lBorder, int rBorder)
{
	while (tree != NULL)
	{
		if (lBorder < tree->leftBorder)
		{
			tree = tree->left;
		}
		else
		{
			if (rBorder != tree->rightBorder || lBorder > tree->leftBorder)
			{
				tree = tree->right;
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

TREESEGM* getMaxLeftBord(TREESEGM* tree)
{
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	return tree;
}

void delSegment(TREESEGM** tree, int lBorder, int rBorder)
{
	if ((*tree) == NULL)
	{
		return;
	}
	if (lBorder < (*tree)->leftBorder)
	{
		delSegment(&((*tree)->left), lBorder, rBorder);
	}
	else
	{
		if (rBorder != (*tree)->rightBorder || lBorder > (*tree)->leftBorder)
		{
			delSegment(&((*tree)->right), lBorder, rBorder);
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
						TREESEGM* max = getMaxLeftBord((*tree)->left);
						(*tree)->leftBorder = max->leftBorder;
						delSegment(&((*tree)->left), max->leftBorder, max->rightBorder);
					}
				}
			}
		}
	}
}

void destroyTreeSegm(TREESEGM* tree)
{
	if (tree != NULL)
	{
		destroyTreeSegm(tree->left);
		destroyTreeSegm(tree->right);
		free(tree);
	}
}

void printTreeSegm(TREESEGM* tree, int index)
{
	if (tree != NULL)
	{
		printf("%d: [%d ; %d]\n", index, tree->leftBorder, tree->rightBorder);
		printTreeSegm(tree->left, index + 1);
		printTreeSegm(tree->right, index + 1);
	}
}

void interSegm(TREESEGM* tree, int lBorder, int rBorder)
{
	if (tree != NULL)
	{
		if (rBorder >= tree->leftBorder && lBorder <= tree->rightBorder)
		{
			answer[index].lBorder = tree->leftBorder;
			answer[index++].rBorder = tree->rightBorder;
			//printf("[%d %d]\n", tree->leftBorder, tree->rightBorder);
		}
		interSegm(tree->left, lBorder, rBorder);
		interSegm(tree->right, lBorder, rBorder);
	}
}