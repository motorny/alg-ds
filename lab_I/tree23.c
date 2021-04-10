#include "tree23.h"
#include <malloc.h>
#include <stdio.h>

#define is_leaf(x) (x->son[0] == NULL && x->son[1] == NULL && x->son[2] == NULL)

void insertToNode(node** leaf, int elem)
{
	if ((*leaf)->countKey == 0)
	{
		(*leaf)->countKey = 1;
		(*leaf)->key[0] = elem;
		return;
	}
	if ((*leaf)->countKey == 1)
	{
		(*leaf)->countKey = 2;
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
	if ((*leaf)->countKey == 2)
	{
		(*leaf)->countKey = 3;
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

node* createNode(int key, node* firstSon, node* secondSon, node* thirdSon, node* fourthSon, node* parrent)
{
	node* newNode = malloc(sizeof(node));
	if (newNode == NULL)
	{
		return NULL;
	};

	newNode->countKey = 1;
	newNode->key[0] = key;
	newNode->son[0] = firstSon;
	newNode->son[1] = secondSon;
	newNode->son[2] = thirdSon;
	newNode->son[3] = fourthSon;
	newNode->parent = parrent;

	return newNode;
}

int split(node** tree)
{
	if ((*tree)->countKey < 3)
		return 1;

	node* x = createNode((*tree)->key[0], (*tree)->son[0], (*tree)->son[1], NULL, NULL, (*tree)->parent);
	if (x == NULL)
	{
		return MEMORY_ALLOCATED_ERROR;
	}

	node* y = createNode((*tree)->key[2], (*tree)->son[2], (*tree)->son[3], NULL, NULL, (*tree)->parent);
	if (y == NULL)
	{
		return MEMORY_ALLOCATED_ERROR;
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
		insertToNode(&((*tree)->parent), (*tree)->key[1]); 

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
		(*tree)->countKey = 1;
		(*tree)->parent = NULL;
		(*tree)->son[0] = x;
		(*tree)->son[1] = y;
		(*tree)->son[2] = NULL;
		(*tree)->son[3] = NULL;
	}
}

int insert(node** tree, int elem)
{
	if ((*tree) == NULL)
	{
		(*tree) = createNode(elem, NULL, NULL, NULL, NULL, NULL);
		if ((*tree) == NULL)
		{
			return MEMORY_ALLOCATED_ERROR;
		}
	}
	else
	{
		for (int i = 0; i < (*tree)->countKey; i++)
		{
			if ((*tree)->key[i] == elem)
				return SUCCESS;
		}
		if (is_leaf((*tree)))
			insertToNode(tree, elem);
		else if (elem < (*tree)->key[0]) insert(&((*tree)->son[0]), elem);
		else if ((*tree)->countKey == 1 || (*tree)->countKey == 2 && elem < (*tree)->key[1]) insert(&((*tree)->son[1]), elem);
		else insert(&((*tree)->son[2]), elem);
	}

	split(tree);

	return SUCCESS;
}

BOOL find(node* tree, int elem)
{
	BOOL itFind = FALSE;
	if (tree == NULL)
		return itFind;

	for (int i = 0; i < tree->countKey; i++)
	{
		if (tree->key[i] == elem)
			itFind = TRUE;
	}

	if (itFind == FALSE)
	{
		if (elem < tree->key[0])
			itFind = find(tree->son[0], elem);
		else if (tree->countKey == 2 && elem < tree->key[1] || tree->countKey == 1)
			itFind = find(tree->son[1], elem);
		else if (tree->countKey == 2)
			itFind = find(tree->son[2], elem);
	}

	return itFind;
}

void printNode(node n)
{
	if (n.parent != NULL)
	{
		for (int i = 0; i < n.parent->countKey; i++)
			printf("%d ", n.parent->key[i]);
	}
	else printf("-1 ");

	printf(":");

	for (int i = 0; i < n.countKey; i++)
		printf(" %d", n.key[i]);

	printf("\n");
}

void printTree(node* tree)
{
	if (tree->son[0] != NULL)
		printTree(tree->son[0]);

	if (tree->son[1] != NULL)
		printTree(tree->son[1]);

	if (tree->son[2] != NULL)
		printTree(tree->son[2]);

	printNode(*tree);
}

node* getNode(node* tree, int elem)
{
	if (tree == NULL)
		return NULL;

	while (tree != NULL)
	{
		for (int i = 0; i < tree->countKey; i++)
		{
			if (tree->key[i] == elem)
				return tree;
		}

		if (elem < tree->key[0])
			tree = tree->son[0];
		else if (tree->countKey == 2 && elem < tree->key[1] || tree->countKey == 1)
			tree = tree->son[1];
		else if (tree->countKey == 2)
			tree = tree->son[2];
	}

	return tree;
}

node* getMinNode(node* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->son[0] != NULL)
	{
		tree = tree->son[0];
	}

	return tree;
}

void delKeyFromNode(node** tree, int elem)
{
	if ((*tree)->countKey >= 1 && (*tree)->key[0] == elem)
	{
		(*tree)->key[0] = (*tree)->key[1];
		(*tree)->key[1] = (*tree)->key[2];
		(*tree)->countKey--;
	}
	else if ((*tree)->countKey == 2 && (*tree)->key[1] == elem)
	{
		(*tree)->key[1] = (*tree)->key[2];
		(*tree)->countKey--;
	}
}

node* redistribute(node* leaf) {
	node* parent = leaf->parent;
	node* first = parent->son[0];
	node* second = parent->son[1];
	node* third = parent->son[2];

	if ((parent->countKey == 2) && (first->countKey < 2) && (second->countKey < 2) && (third->countKey < 2)) {
		if (first == leaf) {
			parent->son[0] = parent->son[1];
			parent->son[1] = parent->son[2];
			parent->son[2] = NULL;
			insertToNode(&(parent->son[0]), parent->key[0]);
			parent->son[0]->son[2] = parent->son[0]->son[1];
			parent->son[0]->son[1] = parent->son[0]->son[0];

			if (leaf->son[0] != NULL) parent->son[0]->son[0] = leaf->son[0];
			else if (leaf->son[1] != NULL) parent->son[0]->son[0] = leaf->son[1];

			if (parent->son[0]->son[0] != NULL) parent->son[0]->son[0]->parent = parent->son[0];

			delKeyFromNode(&parent, parent->key[0]);
			free(first);
		}
		else if (second == leaf) {
			insertToNode(&(first), parent->key[0]);
			delKeyFromNode(&parent, parent->key[0]);
			if (leaf->son[0] != NULL) first->son[2] = leaf->son[0];
			else if (leaf->son[1] != NULL) first->son[2] = leaf->son[1];

			if (first->son[2] != NULL) first->son[2]->parent = first;

			parent->son[1] = parent->son[2];
			parent->son[2] = NULL;

			free(second);
		}
		else if (third == leaf) {
			insertToNode(&(second), parent->key[1]);
			parent->son[2] = NULL;
			delKeyFromNode(&parent, parent->key[1]);
			if (leaf->son[0] != NULL) second->son[2] = leaf->son[0];
			else if (leaf->son[1] != NULL) second->son[2] = leaf->son[1];

			if (second->son[2] != NULL)  second->son[2]->parent = second;

			free(third);
		}
	}
	else if ((parent->countKey == 2) && ((first->countKey == 2) || (second->countKey == 2) || (third->countKey == 2))) {
		if (third == leaf) {
			if (leaf->son[0] != NULL) {
				leaf->son[1] = leaf->son[0];
				leaf->son[0] = NULL;
			}

			insertToNode(&(leaf), parent->key[1]);
			if (second->countKey == 2) {
				parent->key[1] = second->key[1];
				delKeyFromNode(&second, second->key[1]);
				leaf->son[0] = second->son[2];
				second->son[2] = NULL;
				if (leaf->son[0] != NULL) leaf->son[0]->parent = leaf;
			}
			else if (first->countKey == 2) {
				parent->key[1] = second->key[0];
				leaf->son[0] = second->son[1];
				second->son[1] = second->son[0];
				if (leaf->son[0] != NULL) leaf->son[0]->parent = leaf;

				second->key[0] = parent->key[0];
				parent->key[0] = first->key[1];
				delKeyFromNode(&first, first->key[1]);
				second->son[0] = first->son[2];
				if (second->son[0] != NULL) second->son[0]->parent = second;
				first->son[2] = NULL;
			}
		}
		else if (second == leaf) {
			if (third->countKey == 2) {
				if (leaf->son[0] == NULL) {
					leaf->son[0] = leaf->son[1];
					leaf->son[1] = NULL;
				}
				insertToNode(&(second), parent->key[1]);
				parent->key[1] = third->key[0];
				delKeyFromNode(&third, third->key[0]);
				second->son[1] = third->son[0];
				if (second->son[1] != NULL) second->son[1]->parent = second;
				third->son[0] = third->son[1];
				third->son[1] = third->son[2];
				third->son[2] = NULL;
			}
			else if (first->countKey == 2) {
				if (leaf->son[1] == NULL) {
					leaf->son[1] = leaf->son[0];
					leaf->son[0] = NULL;
				}
				insertToNode(&(second), parent->key[0]);
				parent->key[0] = first->key[1];
				delKeyFromNode(&first, first->key[1]);
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
			insertToNode(&(first), parent->key[0]);
			if (second->countKey == 2) {
				parent->key[0] = second->key[0];
				delKeyFromNode(&second, second->key[0]);
				first->son[1] = second->son[0];
				if (first->son[1] != NULL) first->son[1]->parent = first;
				second->son[0] = second->son[1];
				second->son[1] = second->son[2];
				second->son[2] = NULL;
			}
			else if (third->countKey == 2) {
				parent->key[0] = second->key[0];
				second->key[0] = parent->key[1];
				parent->key[1] = third->key[0];
				delKeyFromNode(&third, third->key[0]);
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
	else if (parent->countKey == 1) {
		insertToNode(&(leaf), parent->key[0]);

		if (first == leaf && second->countKey == 2) {
			parent->key[0] = second->key[0];
			delKeyFromNode(&second, second->key[0]);

			if (leaf->son[0] == NULL) leaf->son[0] = leaf->son[1];

			leaf->son[1] = second->son[0];
			second->son[0] = second->son[1];
			second->son[1] = second->son[2];
			second->son[2] = NULL;
			if (leaf->son[1] != NULL) leaf->son[1]->parent = leaf;
		}
		else if (second == leaf && first->countKey == 2) {
			parent->key[0] = first->key[1];
			delKeyFromNode(&first, first->key[1]);

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
		insertToNode(&(parent->son[1]), parent->key[0]);
		parent->son[1]->son[2] = parent->son[1]->son[1];
		parent->son[1]->son[1] = parent->son[1]->son[0];

		if (leaf->son[0] != NULL) 
			parent->son[1]->son[0] = leaf->son[0];
		else if (leaf->son[1] != NULL) 
			parent->son[1]->son[0] = leaf->son[1];

		if (parent->son[1]->son[0] != NULL) 
			parent->son[1]->son[0]->parent = parent->son[1];

		delKeyFromNode(&parent, parent->key[0]);
		free(parent->son[0]);
		parent->son[0] = NULL;
	}
	else if (parent->son[1] == leaf) {
		insertToNode(&(parent->son[0]), parent->key[0]);

		if (leaf->son[0] != NULL) 
			parent->son[0]->son[2] = leaf->son[0];
		else if (leaf->son[1] != NULL) 
			parent->son[0]->son[2] = leaf->son[1];

		if (parent->son[0]->son[2] != NULL) 
			parent->son[0]->son[2]->parent = parent->son[0];

		delKeyFromNode(&parent, parent->key[0]);
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

node* fix(node* leaf)
{
	if (leaf->countKey == 0 && leaf->parent == NULL)
	{
		free(leaf);
		return NULL;
	}

	if (leaf->countKey != 0)
	{
		if (leaf->parent != NULL)
		{
			return fix(leaf->parent);
		}
		else
		{
			return leaf;
		}
	}

	if (leaf->parent->son[0]->countKey == 2 || leaf->parent->son[1]->countKey == 2
		|| leaf->parent->countKey == 2 && leaf->parent->son[2]->countKey == 2)
	{
		leaf = redistribute(leaf);
	}
	else
	{
		leaf = merge(leaf);
	}

	return fix(leaf);
}

node* delKey(node* tree, int elem)
{
	node* delNode = getNode(tree, elem);
	node* min = NULL;

	if (delNode == NULL)
	{
		return tree;
	}

	if (delNode->key[0] == elem)
	{
		min = getMinNode(delNode->son[1]);
	}
	else
	{
		min = getMinNode(delNode->son[2]);
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

	delKeyFromNode(&delNode, elem);

	return fix(delNode);
}

void treeFree(node* tree)
{
	if (tree == NULL)
	{
		return;
	}
	treeFree(tree->son[0]);
	treeFree(tree->son[1]);
	treeFree(tree->son[2]);
	free(tree);
}