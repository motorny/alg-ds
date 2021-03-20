#define _CRT_SECURE_NO_WARNINGS
#include "H30.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0


Treap* new_node(int key)
{
	Treap* t = (Treap*)malloc(sizeof(Treap));
	if (!t) {
		return FAIL;
	}

	t->key = key;
	t->priority = rand();
	t->left = NULL;
	t->right = NULL;


	return t;
}

Treap* merge(Treap* l, Treap* r) {
	if (!l)
		return r;
	if (!r)
		return l;
	if (!r)
		return l;
	if (l->priority > r->priority) {
		l->right = merge(l->right, r);
		return l;
	}
	else {
		r->left = merge(l, r->left);
		return r;
	}
}


void split(Treap* t, Treap** l, Treap** r, int key) {
	if (!t) {
		(*l) = (*r) = NULL;
		return;
	}
	if (t->key < key) {
		split(t->right, &(t->right), r, key);
		(*l) = t;
	}
	else {
		split(t->left, l, &(t->left), key);
		(*r) = t;
	}
}

void add_elem(Treap** t, int key)
{
	if (!(*t)) {
		(*t) = new_node(key);
		return;
	}

	Treap* left = NULL;
	Treap* right = NULL;

	split(*t, &left, &right, key);

	(*t) = merge(merge(left, new_node(key)), right);
}

void delete_elem(Treap** t, int key)
{
	Treap* left = NULL;
	Treap* right = NULL;
	Treap* curr = NULL;

	split(*t, &left, &right, key);
	split(right, &curr, &right, key + 1);
	free(curr);

	(*t) = merge(left, right);
}


int find_elem(Treap* t, int key)
{
	Treap* left = NULL;
	Treap* right = NULL;
	Treap* curr = NULL;

	split(t, &left, &right, key);
	split(right, &curr, &right, key + 1);
	t = merge(merge(left, curr), right);
	if (curr)
		return 1;
	return 0;
}


void destroy(Treap* t)
{
	if (t != NULL) {
		destroy(t->left);
		destroy(t->right);
		free(t);
	}
}

int main(void) {
	char c = 1;
	int key;
	Treap* t = NULL;
	while (1) {
		c = getchar();
		if (c == EOF) {
			break;
		}
		scanf("%i", &key);
		getchar();
		switch (c) {
		case 'a':
			add_elem(&t, key);
			break;
		case 'f':
			if (find_elem(t, key)) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
			break;
		case 'r':
			delete_elem(&t, key);
			break;
		default:
			break;
		}
	}

	destroy(t);
	return 0;
}
