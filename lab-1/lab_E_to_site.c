#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node_t {
	int key;
	struct node_t* left;
	struct node_t* right;
}node_t;

enum mode_t{
	ADD,
	DELETE,
	FIND,
	ERROR = -1
};

node_t* Add(node_t* t, int key) {

	if (t == NULL) {
		t = (node_t*)malloc(sizeof(node_t));
		if (t == NULL)
			return NULL;
		t->key = key;
		t->left = t->right = NULL;
	}
	else {
		if (key < t->key)
			t->left = Add(t->left, key);
		else {
			if (key > t->key)
				t->right = Add(t->right, key);
		}
	}
	return t;
}

node_t* Find(node_t* t, int key) {
	node_t* temp = NULL;

	if (t == NULL)
		return NULL;

	if (t->key == key)
		return t;
	else {
		if (key < t->key)
			temp = Find(t->left, key);
		else
			temp = Find(t->right, key);
	}
	return temp;
}

node_t* MaxNodeByKey(node_t* t) {
	while (t->right != NULL)
		t = t->right;
	return t;
}

void Del(node_t** t, int key) {
	if ((*t) == NULL) 
		return;

	node_t* max = NULL;

	if (key < (*t)->key)
		Del(&((*t)->left), key);
	else {
		if (key > (*t)->key)
			Del(&((*t)->right), key);
		else {
			if ((*t)->right == NULL)
				(*t) = (*t)->left;
			else {
				if ((*t)->left == NULL)
					(*t) = (*t)->right;
				else {
					max = MaxNodeByKey((*t)->left);
					(*t)->key = max->key;
					Del(&((*t)->left), max->key);
				}
			}
		}
	}
}

int ReadAction(FILE* fp, int* key) {
	char c, n;
	int check;
	check = fscanf(fp, "%c", &c);
	if (check == -1)
		return ERROR;

	fscanf(fp, " %d", key);
	fscanf(fp, "%c", &n); //it's for \n

	switch (c) {
	case 'a':
		return ADD;
	case 'r':
		return DELETE;
	case 'f':
		return FIND;
	default:
		return ERROR;
	}
}

void DestroyTree(node_t* t) {
	if (t == NULL)
		return;
	DestroyTree(t->left);
	DestroyTree(t->right);
	free(t);
}

int main(void) {
	int mode = 0, num = 0;
	node_t* tree = NULL;

	mode = ReadAction(stdin, &num);
	if (mode == ERROR)
		return -1;
	
	do {
		switch (mode) {
		case ADD:
			tree = Add(tree, num);
			break;
		case DELETE:
			Del(&tree, num);
			break;
		case FIND:
			if (Find(tree, num) != NULL)
				printf("yes\n");
			else
				printf("no\n");
			break;
		default:
			break;
		}
		mode = ReadAction(stdin, &num);
		
	} while (mode != ERROR);

	return 0;
}