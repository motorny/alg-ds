#include"AAtree.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>


void Skew(Node** head)
{
	Node* tmp, * tmp1;
	if ((*head) == NULL || (*head)->l == NULL)
	{
		return;
	}

	int tmpElem;
	if ((*head)->l->level == (*head)->level)
	{
		tmp = (*head);
		tmp1 = (*head)->l->r;
		(*head) = (*head)->l;
		(*head)->r = tmp;
		(*head)->r->l = tmp1;
	}
}

void Split(Node** head)
{
	Node* tmp, * tmp1;
	if ((*head) == NULL || (*head)->r == NULL || (*head)->r->r == NULL)
	{
		return;
	}

	if ((*head)->level == (*head)->r->r->level)
	{
		tmp = (*head);
		(*head)->r->level += 1;
		(*head) = (*head)->r;
		tmp1 = (*head)->l;
		(*head)->l = tmp;
		(*head)->l->r = tmp1;
	}
}

int insert(Node** head, int elem)
{
	if ((*head) == NULL)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));

		if (newNode == NULL)
		{
			return FAIL;
		}

		newNode->data = elem;
		newNode->level = 1;
		newNode->l = NULL;
		newNode->r = NULL;

		(*head) = newNode;
		return SUCCESS;
	}

	if (elem < (*head)->data)
	{
		insert(&((*head)->l), elem);
	}
	else
	{
		if (elem > (*head)->data)
		{
			insert(&((*head)->r), elem);
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
		itExist = findNode(head->l, elem);
	}
	else
	{
		if (elem > head->data)
		{
			itExist = findNode(head->r, elem);
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

	if ((*head)->l != NULL)
	{
		leftNodeLevel = (*head)->l->level;
	}
	if ((*head)->r != NULL)
	{
		rightNodeLevel = (*head)->r->level;
	}

	newLevel += Min(leftNodeLevel, rightNodeLevel);

	if (newLevel < (*head)->level)
	{
		(*head)->level = newLevel;
		if (newLevel < rightNodeLevel)
		{
			(*head)->r->level = newLevel;
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
		removeNode(&((*head)->r), elem);
	}
	else
	{
		if ((*head)->data > elem)
		{
			removeNode(&((*head)->l), elem);
		}
		else
		{
			if ((*head)->l == NULL && (*head)->r == NULL)
			{
				free((*head));
				(*head) = NULL;
				return;
			}
			if ((*head)->l == NULL)
			{
				tmpNode2 = (*head);
				(*head) = (*head)->r;
				free(tmpNode2);
				return;
			}
			if ((*head)->r == NULL)
			{
				tmpNode2 = (*head);
				(*head) = (*head)->l;
				free(tmpNode2);
				return;
			}
			else
			{
				tmpNode1 = &((*head)->l);
				while ((*tmpNode1)->r != NULL)
				{
					tmpNode1 = &(*tmpNode1)->r;
				}
				tmpVal = (*tmpNode1)->data;
				(*tmpNode1)->data = (*head)->data;
				(*head)->data = tmpVal;
				removeNode(&((*head)->l), elem);
			}
		}
	}

	changeLevel(head);
	Skew(head);
	Skew(&((*head)->r));
	if ((*head)->r != NULL)
	{
		Skew(&((*head)->r->r));
	}
	Split(head);
	Split(&((*head)->r));
}

void Print(Node** head)
{
	if ((*head) != NULL)
	{
		if ((*head)->l != NULL && (*head)->r != NULL)
		{
			printf("%d level:%d left:%d right:%d\n", (*head)->data, (*head)->level, (*head)->l->data, (*head)->r->data);
		}
		else
		{
			if ((*head)->l != NULL && (*head)->r == NULL)
			{
				printf("%d level:%d left:%d right:\n", (*head)->data, (*head)->level, (*head)->l->data);
			}
			if ((*head)->l == NULL && (*head)->r != NULL)
			{
				printf("%d level:%d left: right:%d\n", (*head)->data, (*head)->level, (*head)->r->data);
			}
			if ((*head)->l == NULL && (*head)->r == NULL)
			{
				printf("%d level:%d left: right:\n", (*head)->data, (*head)->level);
			}
		}
		Print(&(*head)->r);
		Print(&(*head)->l);

	}
}

void treeFree(Node* head)
{
	if (head == NULL)
	{
		return;
	}
	treeFree(head->l);
	treeFree(head->r);
	free(head);
}
