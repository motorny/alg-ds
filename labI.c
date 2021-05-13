#include <stdio.h>
#include <stdlib.h>
#include "labI.h"

#pragma warning (disable:4996)


btree_t* CreateTree() {
	btree_t* tree = (btree_t*)malloc(sizeof(btree_t));
	if (tree == NULL)
		return NULL;

	tree->flag = 1;
	tree->keys = 0;

	for (int i = 0; i < 2 * T; i++)
		tree->kids[i] = NULL;

	return tree;
}



void Split(btree_t* tree, int place) {
	btree_t* dubtree = CreateTree();
	btree_t* kidsin = tree->kids[place];

	dubtree->flag = kidsin->flag;
	dubtree->keys = T - 1;

	for (int i = 0; i < T - 1; i++)
		dubtree->value[i] = kidsin->value[i + T];
	if (kidsin->flag == 0) {
		for (int i = 0; i < T; i++) {
			dubtree->kids[i] = kidsin->kids[i + T];
			kidsin->kids[i + T] = NULL;
		}
	}

	kidsin->keys = T - 1;
	if (tree->kids[place + 1] != NULL) {
		int counter = place + 1;
		while (tree->kids[counter] != NULL)
			counter++;
		for (counter; counter > place + 1; counter--) {
			tree->value[counter - 1] = tree->value[counter - 2];
			tree->kids[counter] = tree->kids[counter - 1];
		}
	}

	tree->keys = tree->keys + 1;
	tree->kids[place + 1] = dubtree;
	tree->value[place] = kidsin->value[T - 1];

}




void InsertPlace(btree_t* tree, int value) {
	int place = tree->keys - 1;
	if (tree->flag == 1) {
		while (place >= 0 && value < tree->value[place]) {
			tree->value[place + 1] = tree->value[place];
			place--;
		}
		tree->keys++;
		tree->value[place + 1] = value;
	}
	else {
		while (place >= 0 && value < tree->value[place])
			place--;
		if (tree->kids[place + 1]->keys == 2 * T - 1) {
			Split(tree, place + 1);
			if (tree->value[place + 1] < value)
				place = place + 1;
		}
		place = place + 1;
		InsertPlace(tree->kids[place], value);
	}
}

int Search(btree_t* tree, int value) {
	if (tree == NULL)
		return FAILED;
	else {
		int count = 0;
		while (count < tree->keys && value > tree->value[count]) {
			count++;
		}
		if (count < tree->keys && value == tree->value[count])
			return SUCCESS;
		else if (tree->flag == 1)
			return FAILED;
		else return Search(tree->kids[count], value);
	}
}



void Insert(btree_t** tree, int value) {
	if (!(*tree)) {
		(*tree) = CreateTree();
		(*tree)->value[0] = value;
		(*tree)->keys = 1;
		return;
	}
	else {
		if (Search((*tree), value) == SUCCESS)
			return;
		else {
			if ((*tree)->keys < 2 * T - 1) {
				InsertPlace((*tree), value);
			}
			else {
				btree_t* dubtree = CreateTree();
				btree_t* tmp = (*tree);
				(*tree) = dubtree;
				dubtree->flag = 0;
				dubtree->keys = 0;
				dubtree->kids[0] = tmp;
				Split(dubtree, 0);
				InsertPlace(dubtree, value);
			}
		}
	}
}



int Remove(btree_t* tree, int value) {
	if (!tree)
		return FAILED;

	int needs = (T - 1) / 2;

	int treekeys = tree->keys;
	int* treevalue = tree->value;
	btree_t** treekids = tree->kids;

	int place = 0;
	while (place < treekeys && value > treevalue[place])
		place++;

	if (!treekids[0]) {
		if (value < treevalue[place] || place == treekeys)
			return FAILED;
		for (int i = place + 1; i < treekeys; i++) {
			treevalue[i - 1] = treevalue[i];
			treekids[i] = treekids[i + 1];
		}
		tree->keys--;
		if (tree->keys >= needs)
			return SUCCESS;
		else
			return GIVE_MORE_KEYS;
	}

	btree_t* tmp1;
	int keys1;
	btree_t* tmp2;

	if (place < treekeys && value == treevalue[place]) {
		tmp1 = treekids[place];
		for (;;) {
			keys1 = tmp1->keys;
			tmp2 = tmp1->kids[keys1];
			if (!tmp2)
				break;
			tmp1 = tmp2;
		}
		treevalue[place] = tmp1->value[keys1 - 1];
		tmp1->value[keys1 - 1] = value;
	}
	int status = Remove(treekids[place], value);
	if (status != GIVE_MORE_KEYS)
		return status;

	btree_t* left;
	btree_t* right;

	if (place > 0 && treekids[place - 1]->keys > needs) {
		left = treekids[place - 1];
		right = treekids[place];
		right->kids[right->keys + 1] = right->kids[right->keys];
		for (int i = right->keys; i > 0; i--) {
			right->value[i] = right->value[i - 1];
			right->kids[i] = right->kids[i - 1];
		}
		right->keys++;
		right->value[0] = treevalue[place - 1];
		right->kids[0] = left->kids[left->keys];
		treevalue[place - 1] = left->value[--left->keys];
		return SUCCESS;
	}

	if (place < treekeys && treekids[place + 1]->keys > needs) {
		left = treekids[place];
		right = treekids[place + 1];
		left->value[left->keys] = treevalue[place];
		left->kids[left->keys + 1] = right->kids[0];
		treevalue[place] = right->value[0];
		left->keys++;
		right->keys--;
		for (int i = 0; i < right->keys; i++) {
			right->value[i] = right->value[i + 1];
			right->kids[i] = right->kids[i + 1];
		}
		right->kids[right->keys] = right->kids[right->keys + 1];
		return SUCCESS;
	}

	if (place == treekeys) {
		left = treekids[place - 1];
		right = treekids[place];
		left->value[left->keys] = treevalue[place - 1];
	}
	else {
		left = treekids[place];
		right = treekids[place + 1];
		left->value[left->keys] = treevalue[place];
	}
	left->kids[left->keys + 1] = right->kids[0];
	for (int i = 0; i < right->keys; i++) {
		left->value[left->keys + i + 1] = right->value[i];
		left->kids[left->keys + i + 2] = right->kids[i + 1];
	}
	left->keys = left->keys + right->keys + 1;
	free(right);
	for (int i = place + 1; i < treekeys; i++) {
		treevalue[i - 1] = treevalue[i];
		treekids[i] = treekids[i + 1];
	}
	tree->keys--;
	if (tree->keys >= needs)
		return SUCCESS;
	else return GIVE_MORE_KEYS;
}



void DeleteEl(btree_t* tree, int value) {
	if (tree == NULL)
		return;
	int state = Remove(tree, value);
	if (state == GIVE_MORE_KEYS) {
		btree_t* freenode = tree;
		tree = tree->kids[0];
		free(freenode);
	}
}

void Print(btree_t* tree, int lvl) {
	int i;
	if (tree == NULL)
		return;
	for (i = 0; i <= tree->keys - 1; i++) {
		Print(tree->kids[i], lvl + 1);
		for (int j = 0; j <= lvl; j++)
			printf("   ");
		printf("%d\n", tree->value[i]);
	}
	Print(tree->kids[i], lvl + 1);
}

void DeleteTree(btree_t* tree) {
	if (tree == NULL)
		return;
	if (tree->flag == 0) {
		for (int i = 0; i <= tree->keys; i++) {
			DeleteTree(tree->kids[i]);
		}
	}
	free(tree);
}




int main() {
	char command;
	int value;
	btree_t* tree = NULL;

	command = (char)getchar();
	while (command != EOF) {
		scanf("%d", &value);
		switch (command) {
		case 'a':
		{
			Insert(&tree, value);
			break;
		}
		case 'f':
		{
			if (Search(tree, value) == FAILED)
				puts("no");
			else if (Search(tree, value) == SUCCESS)
				puts("yes");
			break;
		}
		case 'r':
		{
			DeleteEl(tree, value);
			break;
		}
		default:
			break;
		}
		command = (char)getchar();
		if (command == '\r' || command == '\n')
			command = (char)getchar();
	}

	DeleteTree(tree);
	return 0;
}