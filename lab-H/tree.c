#include "tree.h"
#include <stdio.h>
#include <malloc.h>

void Skew(Node** head)
{
	Node* tmp, *tmp1;
	if ((*head) == NULL || (*head)->left == NULL)
	{
		return;
	}

	int tmpElem;
	if ((*head)->left->level == (*head)->level)
	{
		tmp = (*head);
		tmp1 = (*head)->left->right;
		(*head) = (*head)->left;
		(*head)->right = tmp;
		(*head)->right->left = tmp1;
	}
}

void Split(Node** head)
{
	Node* tmp, *tmp1;
	if ((*head) == NULL || (*head)->right == NULL || (*head)->right->right == NULL)
	{
		return;
	}

	if ((*head)->level == (*head)->right->right->level)
	{
		tmp = (*head);
		(*head)->right->level += 1;
		(*head) = (*head)->right;
		tmp1 = (*head)->left;
		(*head)->left = tmp;
		(*head)->left->right = tmp1;
	}
}

int insert(Node** head, int elem)
{
	if ((*head) == NULL)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));

		if (newNode == NULL)
		{
			return FAILED_TO_ALLOCATE_MEMORY;
		}

		newNode->data = elem;
		newNode->level = 1;
		newNode->left = NULL;
		newNode->right = NULL;

		(*head) = newNode;
		return SUCCESS;
	}
	
	if (elem < (*head)->data)
	{
		insert(&((*head)->left), elem);
	}
	else
	{
		if (elem > (*head)->data)
		{
			insert(&((*head)->right), elem);
		}
	}

	Skew(head);
	Split(head);

	return SUCCESS;
}

int findNode(Node* head, const int elem)
{
	int itExist = False;
	if (head == NULL)
	{
		itExist = False;
		return itExist;
	}

	if (elem < head->data)
	{
		itExist = findNode(head->left, elem);
	}
	else
	{
		if (elem > head->data)
		{
			itExist = findNode(head->right, elem);
		}
		else
		{
			itExist = True;
		}
	}

	return itExist;
	
}

void changeLevel(Node** head)
{
	int newLevel = 1,
		leftNodeLevel = 0,
		rightNodeLevel = 0;

	if ((*head)->left != NULL)
	{
		leftNodeLevel = (*head)->left->level;
	}
	if ((*head)->right != NULL)
	{
		rightNodeLevel = (*head)->right->level;
	}
	
	newLevel += Min(leftNodeLevel, rightNodeLevel);

	if (newLevel < (*head)->level)
	{
		(*head)->level = newLevel;
		if (newLevel < rightNodeLevel)
		{
			(*head)->right->level = newLevel;
		}
	}
}

void removeNode(Node** head, int elem)
{
	Node** tmpNode1,
		* tmpNode2;
	int tmpVal;

	if ((*head) == NULL)
		return;
	if ((*head)->data < elem)
	{
		removeNode(&((*head)->right), elem);
	}
	else
	{
		if ((*head)->data > elem)
		{
			removeNode(&((*head)->left), elem);
		}
		else
		{
			if ((*head)->left == NULL && (*head)->right == NULL)
			{
				free((*head));
				(*head) = NULL;
				return;
			}
			if ((*head)->left == NULL)
			{
				tmpNode2 = (*head);
				(*head) = (*head)->right;
				free(tmpNode2);
				return;
			}
			if ((*head)->right == NULL)
			{
				tmpNode2 = (*head);
				(*head) = (*head)->left;
				free(tmpNode2);
				return;
			}
			else
			{
				tmpNode1 = &((*head)->left);
				while ((*tmpNode1)->right != NULL)
				{
					tmpNode1 = &(*tmpNode1)->right;
				}
				tmpVal = (*tmpNode1)->data;
				(*tmpNode1)->data = (*head)->data;
				(*head)->data = tmpVal;
				removeNode(&((*head)->left), elem);
			}
		}
	}

	changeLevel(head);
	Skew(head);
	Skew(&((*head)->right));
	if ((*head)->right != NULL)
	{
		Skew(&((*head)->right->right));
	}
	Split(head);
	Split(&((*head)->right));
}

void printTree(Node** head)
{
	if ((*head) != NULL)
	{
		if ((*head)->left != NULL && (*head)->right != NULL)
		{
			printf("%d level:%d left:%d right:%d\n", (*head)->data, (*head)->level, (*head)->left->data, (*head)->right->data);
		}
		else
		{
			if ((*head)->left != NULL && (*head)->right == NULL)
			{
				printf("%d level:%d left:%d right:\n", (*head)->data, (*head)->level, (*head)->left->data);
			}
			if ((*head)->left == NULL && (*head)->right != NULL)
			{
				printf("%d level:%d left: right:%d\n", (*head)->data, (*head)->level, (*head)->right->data);
			}
			if ((*head)->left == NULL && (*head)->right == NULL)
			{
				printf("%d level:%d left: right:\n", (*head)->data, (*head)->level);
			}
		}
		printTree(&(*head)->right);
		printTree(&(*head)->left);
		
	}
}

void treeFree(Node* head)
{
	if (head == NULL)
	{
		return;
	}
	treeFree(head->left);
	treeFree(head->right);
	free(head);
}