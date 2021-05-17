#include"pch.h"
#include "Header.h"
#include <malloc.h>
#include <stdio.h>

#define isleaf(x) (x->son[0] == NULL && x->son[1] == NULL && x->son[2] == NULL)

void InsertToNode(node **leaf, int elem)
{
	if ((*leaf)->count == 0)
	{
		(*leaf)->count = 1;
		(*leaf)->key[0] = elem;
		return;
	}
	if ((*leaf)->count == 1)
	{
		(*leaf)->count = 2;
		if (elem > (*leaf)->key[0])
		{
			(*leaf)->key[1] = elem;
		}
		else
		{
			(*leaf)->key[1] = (*leaf)->key[0];
			(*leaf)->key[0] = elem;
		}
		return;
	}
	if ((*leaf)->count == 2)
	{
		(*leaf)->count = 3;
		if (elem > (*leaf)->key[1])
		{
			(*leaf)->key[2] = elem;
		}
		else
		{
			if (elem > (*leaf)->key[0])
			{
				(*leaf)->key[2] = (*leaf)->key[1];
				(*leaf)->key[1] = elem;
			}
			else
			{
				(*leaf)->key[2] = (*leaf)->key[1];
				(*leaf)->key[1] = (*leaf)->key[0];
				(*leaf)->key[0] = elem;
			}
		}
		return;
	}
}

node* CreateNode(int key, node* first, node* second, node* third, node* fourth, node* parent)
{
	node* newNode = malloc(sizeof(node));
	if (newNode == NULL)
	{
		return NULL;
	};

	newNode->count = 1;
	newNode->key[0] = key;
	newNode->son[0] = first;
	newNode->son[1] = second;
	newNode->son[2] = third;
	newNode->son[3] = fourth;
	newNode->parent = parent;

	return newNode;
}

int Split(node** tree)
{
	if ((*tree)->count < 3)
		return SUCCESS;

	node* x = CreateNode((*tree)->key[0], (*tree)->son[0], (*tree)->son[1], NULL, NULL, (*tree)->parent);
	if (x == NULL)
	{
		return ERROR;
	}

	node* y = CreateNode((*tree)->key[2], (*tree)->son[2], (*tree)->son[3], NULL, NULL, (*tree)->parent);
	if (y == NULL)
	{
		return ERROR;
	}

	if (x->son[0])
		x->son[0]->parent = x;
	if (x->son[1])
		x->son[1]->parent = x;
	if (y->son[0])
		y->son[0]->parent = y;
	if (y->son[1])
		y->son[1]->parent = y;


	if ((*tree)->parent)
	{
		int tmp = 4;
		InsertToNode(&((*tree)->parent), (*tree)->key[1]);

		if ((*tree)->parent->son[0] == (*tree))
			tmp = 0;
		else if ((*tree)->parent->son[1] == (*tree))
			tmp = 1;
		else if ((*tree)->parent->son[2] == (*tree))
			tmp = 2;

		if (tmp == 0)
		{
			(*tree)->parent->son[3] = (*tree)->parent->son[2];
			(*tree)->parent->son[2] = (*tree)->parent->son[1];
			(*tree)->parent->son[1] = y;
			(*tree)->parent->son[0] = x;
		}
		else if (tmp == 1)
		{
			(*tree)->parent->son[3] = (*tree)->parent->son[2];
			(*tree)->parent->son[2] = y;
			(*tree)->parent->son[1] = x;
		}
		else
		{
			(*tree)->parent->son[3] = y;
			(*tree)->parent->son[2] = x;
		}
	}
	else
	{
		x->parent = (*tree);
		y->parent = (*tree);
		(*tree)->key[0] = (*tree)->key[1];
		(*tree)->key[1] = 0;
		(*tree)->key[2] = 0;
		(*tree)->count = 1;
		(*tree)->parent = NULL;
		(*tree)->son[0] = x;
		(*tree)->son[1] = y;
		(*tree)->son[2] = NULL;
		(*tree)->son[3] = NULL;
	}
	return SUCCESS;
}

int Insert(node** tree, int elem)
{
	if ((*tree) == NULL)
	{
		(*tree) = CreateNode(elem, NULL, NULL, NULL, NULL, NULL);
		if ((*tree) == NULL)
		{
			return ERROR;
		}
	}
	else
	{
		for (int i = 0; i < (*tree)->count; i++)
		{
			if ((*tree)->key[i] == elem)
				return SUCCESS;
		}
		if (isleaf((*tree)))
			InsertToNode(tree, elem);
		else if (elem < (*tree)->key[0]) Insert(&((*tree)->son[0]), elem);
		else if ((*tree)->count == 1 || (*tree)->count == 2 && elem < (*tree)->key[1]) Insert(&((*tree)->son[1]), elem);
		else Insert(&((*tree)->son[2]), elem);
	}

	Split(tree);

	return SUCCESS;
}

bool IsItFind(node* tree, int elem)
{
	bool find = FALSE;
	if (tree == NULL)
		return find;

	for (int i = 0; i < tree->count; i++)
	{
		if (tree->key[i] == elem)
			find = TRUE;
	}

	if (find == FALSE)
	{
		if (elem < tree->key[0])
			find = IsItFind(tree->son[0], elem);
		else if (tree->count == 2 && elem < tree->key[1] || tree->count == 1)
			find = IsItFind(tree->son[1], elem);
		else if (tree->count == 2)
			find = IsItFind(tree->son[2], elem);
	}

	return find;
}

void PrintNode(node n)
{
	if (n.parent != NULL)
	{
		for (int i = 0; i < n.parent->count; i++)
			printf("%d ", n.parent->key[i]);
	}
	else printf("-1 ");

	printf(":");

	for (int i = 0; i < n.count; i++)
		printf(" %d", n.key[i]);

	printf("\n");
}

void PrintTree(node* tree)
{
	if (tree->son[0] != NULL)
		printTree(tree->son[0]);

	if (tree->son[1] != NULL)
		PrintTree(tree->son[1]);

	if (tree->son[2] != NULL)
		PrintTree(tree->son[2]);

	PrintNode(*tree);
}

node* GetNode(node* tree, int elem)
{
	if (tree == NULL)
		return NULL;

	while (tree != NULL)
	{
		for (int i = 0; i < tree->count; i++)
		{
			if (tree->key[i] == elem)
				return tree;
		}

		if (elem < tree->key[0])
			tree = tree->son[0];
		else if (tree->count == 2 && elem < tree->key[1] || tree->count == 1)
			tree = tree->son[1];
		else if (tree->count == 2)
			tree = tree->son[2];
	}

	return tree;
}

node* GetMinNode(node* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->son[0] != NULL)
	{
		tree = tree->son[0];
	}

	return tree;
}

void DelKeyFromNode(node** tree, int elem)
{
	if ((*tree)->count >= 1 && (*tree)->key[0] == elem)
	{
		(*tree)->key[0] = (*tree)->key[1];
		(*tree)->key[1] = (*tree)->key[2];
		(*tree)->count--;
	}
	else if ((*tree)->count == 2 && (*tree)->key[1] == elem)
	{
		(*tree)->key[1] = (*tree)->key[2];
		(*tree)->count--;
	}
}

node* Redistribute(node* leaf) {
	node* parent = leaf->parent;
	node* first = parent->son[0];
	node* second = parent->son[1];
	node* third = parent->son[2];

	if ((parent->count == 2) && (first->count < 2) && (second->count < 2) && (third->count < 2)) {
		if (first == leaf) {
			parent->son[0] = parent->son[1];
			parent->son[1] = parent->son[2];
			parent->son[2] = NULL;
			InsertToNode(&(parent->son[0]), parent->key[0]);
			parent->son[0]->son[2] = parent->son[0]->son[1];
			parent->son[0]->son[1] = parent->son[0]->son[0];

			if (leaf->son[0] != NULL) parent->son[0]->son[0] = leaf->son[0];
			else if (leaf->son[1] != NULL) parent->son[0]->son[0] = leaf->son[1];

			if (parent->son[0]->son[0] != NULL) parent->son[0]->son[0]->parent = parent->son[0];

			DelKeyFromNode(&parent, parent->key[0]);
			free(first);
		}
		else if (second == leaf) {
			InsertToNode(&(first), parent->key[0]);
			DelKeyFromNode(&parent, parent->key[0]);
			if (leaf->son[0] != NULL) first->son[2] = leaf->son[0];
			else if (leaf->son[1] != NULL) first->son[2] = leaf->son[1];

			if (first->son[2] != NULL) first->son[2]->parent = first;

			parent->son[1] = parent->son[2];
			parent->son[2] = NULL;

			free(second);
		}
		else if (third == leaf) {
			InsertToNode(&(second), parent->key[1]);
			parent->son[2] = NULL;
			DelKeyFromNode(&parent, parent->key[1]);
			if (leaf->son[0] != NULL) second->son[2] = leaf->son[0];
			else if (leaf->son[1] != NULL) second->son[2] = leaf->son[1];

			if (second->son[2] != NULL)  second->son[2]->parent = second;

			free(third);
		}
	}
	else if ((parent->count == 2) && ((first->count == 2) || (second->count == 2) || (third->count == 2))) {
		if (third == leaf) {
			if (leaf->son[0] != NULL) {
				leaf->son[1] = leaf->son[0];
				leaf->son[0] = NULL;
			}

			InsertToNode(&(leaf), parent->key[1]);
			if (second->count == 2) {
				parent->key[1] = second->key[1];
				DelKeyFromNode(&second, second->key[1]);
				leaf->son[0] = second->son[2];
				second->son[2] = NULL;
				if (leaf->son[0] != NULL) leaf->son[0]->parent = leaf;
			}
			else if (first->count == 2) {
				parent->key[1] = second->key[0];
				leaf->son[0] = second->son[1];
				second->son[1] = second->son[0];
				if (leaf->son[0] != NULL) leaf->son[0]->parent = leaf;

				second->key[0] = parent->key[0];
				parent->key[0] = first->key[1];
				DelKeyFromNode(&first, first->key[1]);
				second->son[0] = first->son[2];
				if (second->son[0] != NULL) second->son[0]->parent = second;
				first->son[2] = NULL;
			}
		}
		else if (second == leaf) {
			if (third->count == 2) {
				if (leaf->son[0] == NULL) {
					leaf->son[0] = leaf->son[1];
					leaf->son[1] = NULL;
				}
				InsertToNode(&(second), parent->key[1]);
				parent->key[1] = third->key[0];
				DelKeyFromNode(&third, third->key[0]);
				second->son[1] = third->son[0];
				if (second->son[1] != NULL) second->son[1]->parent = second;
				third->son[0] = third->son[1];
				third->son[1] = third->son[2];
				third->son[2] = NULL;
			}
			else if (first->count == 2) {
				if (leaf->son[1] == NULL) {
					leaf->son[1] = leaf->son[0];
					leaf->son[0] = NULL;
				}
				InsertToNode(&(second), parent->key[0]);
				parent->key[0] = first->key[1];
				DelKeyFromNode(&first, first->key[1]);
				second->son[0] = first->son[2];
				if (second->son[0] != NULL) second->son[0]->parent = second;
				first->son[2] = NULL;
			}
		}
		else if (first == leaf) {
			if (leaf->son[0] == NULL) {
				leaf->son[0] = leaf->son[1];
				leaf->son[1] = NULL;
			}
			InsertToNode(&(first), parent->key[0]);
			if (second->count == 2) {
				parent->key[0] = second->key[0];
				DelKeyFromNode(&second, second->key[0]);
				first->son[1] = second->son[0];
				if (first->son[1] != NULL) first->son[1]->parent = first;
				second->son[0] = second->son[1];
				second->son[1] = second->son[2];
				second->son[2] = NULL;
			}
			else if (third->count == 2) {
				parent->key[0] = second->key[0];
				second->key[0] = parent->key[1];
				parent->key[1] = third->key[0];
				DelKeyFromNode(&third, third->key[0]);
				first->son[1] = second->son[0];
				if (first->son[1] != NULL) first->son[1]->parent = first;
				second->son[0] = second->son[1];
				second->son[1] = third->son[0];
				if (second->son[1] != NULL) second->son[1]->parent = second;
				third->son[0] = third->son[1];
				third->son[1] = third->son[2];
				third->son[2] = NULL;
			}
		}
	}
	else if (parent->count == 1) {
		InsertToNode(&(leaf), parent->key[0]);

		if (first == leaf && second->count == 2) {
			parent->key[0] = second->key[0];
			DelKeyFromNode(&second, second->key[0]);

			if (leaf->son[0] == NULL) leaf->son[0] = leaf->son[1];

			leaf->son[1] = second->son[0];
			second->son[0] = second->son[1];
			second->son[1] = second->son[2];
			second->son[2] = NULL;
			if (leaf->son[1] != NULL) leaf->son[1]->parent = leaf;
		}
		else if (second == leaf && first->count == 2) {
			parent->key[0] = first->key[1];
			DelKeyFromNode(&first, first->key[1]);

			if (leaf->son[1] == NULL) leaf->son[1] = leaf->son[0];

			leaf->son[0] = first->son[2];
			first->son[2] = NULL;
			if (leaf->son[0] != NULL) leaf->son[0]->parent = leaf;
		}
	}
	return parent;
}

node* merge(node* leaf) {
	node* parent = leaf->parent;

	if (parent->son[0] == leaf) {
		InsertToNode(&(parent->son[1]), parent->key[0]);
		parent->son[1]->son[2] = parent->son[1]->son[1];
		parent->son[1]->son[1] = parent->son[1]->son[0];

		if (leaf->son[0] != NULL)
			parent->son[1]->son[0] = leaf->son[0];
		else if (leaf->son[1] != NULL)
			parent->son[1]->son[0] = leaf->son[1];

		if (parent->son[1]->son[0] != NULL)
			parent->son[1]->son[0]->parent = parent->son[1];

		DelKeyFromNode(&parent, parent->key[0]);
		free(parent->son[0]);
		parent->son[0] = NULL;
	}
	else if (parent->son[1] == leaf) {
		InsertToNode(&(parent->son[0]), parent->key[0]);

		if (leaf->son[0] != NULL)
			parent->son[0]->son[2] = leaf->son[0];
		else if (leaf->son[1] != NULL)
			parent->son[0]->son[2] = leaf->son[1];

		if (parent->son[0]->son[2] != NULL)
			parent->son[0]->son[2]->parent = parent->son[0];

		DelKeyFromNode(&parent, parent->key[0]);
		free(parent->son[1]);
		parent->son[1] = NULL;
	}

	if (parent->parent == NULL) {
		node* tmp = NULL;
		if (parent->son[0] != NULL)
			tmp = parent->son[0];
		else
			tmp = parent->son[1];
		tmp->parent = NULL;
		free(parent);
		return tmp;
	}
	return parent;
}

node* Fix(node* leaf)
{
	if (leaf->count == 0 && leaf->parent == NULL)
	{
		free(leaf);
		return NULL;
	}

	if (leaf->count != 0)
	{
		if (leaf->parent != NULL)
		{
			return Fix(leaf->parent);
		}
		else
		{
			return leaf;
		}
	}

	if (leaf->parent->son[0]->count == 2 || leaf->parent->son[1]->count == 2
		|| leaf->parent->count == 2 && leaf->parent->son[2]->count == 2)
	{
		leaf = Redistribute(leaf);
	}
	else
	{
		leaf = merge(leaf);
	}

	return Fix(leaf);
}

node* DelKey(node* tree, int elem)
{
	node* delNode = GetNode(tree, elem);
	node* min = NULL;

	if (delNode == NULL)
	{
		return tree;
	}

	if (delNode->key[0] == elem)
	{
		min = GetMinNode(delNode->son[1]);
	}
	else
	{
		min = GetMinNode(delNode->son[2]);
	}

	if (min != NULL)
	{
		if (delNode->key[0] == elem)
		{
			delNode->key[0] = min->key[0];
			min->key[0] = elem;
		}
		else
		{
			delNode->key[1] = min->key[0];
			min->key[0] = elem;
		}

		delNode = min;
	}

	DelKeyFromNode(&delNode, elem);

	return Fix(delNode);
}

void FreeTree(node* tree)
{
	if (tree == NULL)
	{
		return;
	}
	FreeTree(tree->son[0]);
	FreeTree(tree->son[1]);
	FreeTree(tree->son[2]);
	free(tree);
}