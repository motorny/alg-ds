#include"treap.h"
#include<stdio.h>
#include<stdlib.h>

char* readString() {
	char* str = NULL, * ptr = NULL;
	int i = 0;
	int k = 2;
	str = (char*)malloc(2 * sizeof(char));
	if (!str)
		return NULL;
	while ((str[i] = fgetc(stdin)) != EOF) {
		i++;
		if (i >= k) {
			k += 8;
			ptr = realloc(str, (k) * sizeof(char));
			if (ptr)
				str = ptr;
			else
				return NULL;
		}

	}
	str[i] = 0;
	return str;
}


treap* merge(treap* l, treap* r) {
	if (!l || !r)
		return l ? l : r;
	if (l->prior > r->prior) {
		l->right = merge(l->right, r);
		return l;
	}
	else {
		r->left = merge(l, r->left);
		return r;
	}
}

void split(treap* t, int key, treap** l, treap** r) {
	if (!t) {
		(*l) = (*r) = NULL;
		return;
	}
	if (t->key < key) {
		split(t->right, key, &(t->right), r);
		(*l) = t;
	}
	else {
		split(t->left, key, l, &(t->left));
		(*r) = t;
	}
}

treap* getNode(int key) {
	treap* t = (treap*)malloc(sizeof(treap));
	if (t) {
		t->left = t->right = NULL;
		t->key = key;
		t->prior = rand();
	}
	return t;
}
void add(treap** t, int key) {
	if (!(*t)) {
		(*t) = getNode(key);
		return;
	}
	treap* less = NULL, *greater = NULL;
	split(*t, key, &less, &greater);
	(*t) = merge(merge(less, getNode(key)) , greater);
}

int find(treap* t, int key) {
	int res = 0;
	treap* less = NULL, * greater = NULL, * equal = NULL;
	split(t, key, &less, &greater);
	split(greater, key + 1, &equal, &greater);
	if (equal)
		res = 1;
	t = merge(merge(less, equal), greater);
	return res;
}

int delelem(treap** t, int key) {
	int res = 0;
	treap* less = NULL, * greater = NULL, * equal = NULL;
	split(*t, key, &less, &greater);
	split(greater, key + 1, &equal, &greater);
	if (equal)
		res = 1;
	free(equal);
	(*t) = merge(less, greater);
	return res;
}

void printTree(treap* t, char* dir, int level) {
	if (t) {
		printf("lvl %d %s = %d  prior = %i\n", level, dir, t->key, t->prior);
		printTree(t->left, "left", level + 1);
		printTree(t->right, "right", level + 1);
	}
}

void destroy(treap* t) {
	if (t) {
		destroy(t->left);
		destroy(t->right);
		free(t);
	}
}
