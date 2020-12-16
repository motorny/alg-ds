#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
}node;


node* Add(node* mynode, int number) {
	if (mynode == NULL) {
		mynode = (node*)malloc(sizeof(node));
		if (mynode == NULL)
			return NULL;
		mynode->key = number;
		mynode->left = mynode->right = NULL;
	}
	else {
		if (number < mynode->key)
			mynode->left = Add(mynode->left, number);
		else if (number > mynode->key)
			mynode->right = Add(mynode->right, number);
	}
	return mynode;
}

node* Find(node* mynode, int key) {
	node* returnnode = NULL;
	if (mynode == NULL)
		return NULL;
	if (mynode->key == key)
		return mynode;
	else 
		returnnode = key < mynode->key ? Find(mynode->left, key) : Find(mynode->right, key);
	return returnnode;
}
node* MaxNodeByKey(node* mynode) {
	while (mynode->right != NULL)
		mynode = mynode->right;
	return mynode;
}
void Del(node** mynode, int key) {
	node* endnode = NULL;
	if ((*mynode) == NULL)
		return;
	if (key < (*mynode)->key)
		Del(&((*mynode)->left), key);
	else if (key > (*mynode)->key)
		Del(&((*mynode)->right), key);
	else if ((*mynode)->right == NULL)
		(*mynode) = (*mynode)->left;
	else if ((*mynode)->left == NULL)
		(*mynode) = (*mynode)->right;
	else {
		endnode = MaxNodeByKey((*mynode)->left);
		(*mynode)->key = endnode->key;
		Del(&((*mynode)->left), endnode->key);
	}
}

int DefineFunc(FILE* file, int* number) {
	char define = getchar();
	if (define == -1)
		return 0;
	fscanf(file, " %d", number);
	getchar();
	if (define == 'a')
		return 1;
	else if (define == 'r')
		return 2;
	else if (define == 'f')
		return 3;
	else
		return 0;
}

void DestroyTree(node* mynode) {
	if (mynode == NULL)
		return;
	DestroyTree(mynode->left);
	DestroyTree(mynode->right);
	free(mynode);
}

int main(void) {
	int func = 0, number = 0;
	node* mynode = NULL;
	func = DefineFunc(stdin, &number);
	if (func == 0)
		return -1;
	do {
		switch (func) {
		case 1:
			mynode = Add(mynode, number);
			break;
		case 2:
			Del(&mynode, number);
			break;
		case 3:
			if (Find(mynode, number) != NULL)
				fprintf(stdout,"yes\n");
			else
				fprintf(stdout, "no\n");
			break;
		default:
			break;
		}
		func = DefineFunc(stdin, &number);
	} while (func != 0);
	return 0;
}