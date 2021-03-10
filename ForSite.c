#include <stdlib.h>
#include<stdio.h>
#pragma warning (disable:4996)

typedef struct treap {
	int key;
	int prior;
	struct treap* left;
	struct treap* right;
}treap;

treap* Merge(treap* l, treap* r) {
	if (!l)
		return r;
	if (!r)
		return l;
	if (l->prior > r->prior) {
		l->right = Merge(l->right, r);
		return l;
	}
	else {
		r->left = Merge(l, r->left);
		return r;
	}
}

void Split(treap* t, int key, treap** l, treap** r) {
	if (!t) {
		(*l) = NULL;
		(*r) = NULL;
		return;
	}
	if (t->key < key) {
		Split(t->right, key, &(t->right), r);
		(*l) = t;
	}
	else {
		Split(t->left, key, l, &(t->left));
		(*r) = t;
	}
}

treap* NewElem(int key) {
	treap* t = (treap*)malloc(sizeof(treap));
	if (t) {
		t->key = key;
		t->prior = rand();
		t->left = NULL;
		t->right = NULL;
	}
	return t;
}
void AddElem(treap** t, int key) {
	if (!(*t)) {
		(*t) = NewNode(key);
		return;
	}
	treap* l = NULL, * r = NULL;
	Split(*t, key, &l, &r);
	(*t) = Merge(Merge(l, NewNode(key)), r);
}

int FindElem(treap* t, int key) {
	treap* l = NULL, * r = NULL, * cur = NULL;
	Split(t, key, &l, &r);
	Split(r, key + 1, &cur, &r);
	t = Merge(Merge(l, cur), r);
	if (cur)
		return 1;
	return 0;
}

void DeleteElem(treap** t, int key) {
	treap* l = NULL, * r = NULL, * cur = NULL;
	Split(*t, key, &l, &r);
	Split(r, key + 1, &cur, &r);
	if (cur)
		free(cur);
	(*t) = Merge(l, r);
}


void FreeTreap(treap* t) {
	if (t) {
		FreeTreap(t->left);
		FreeTreap(t->right);
		free(t);
	}
}

int main(void) {
	char command = 1;
	int key;
	treap* t = NULL;
	while (1) {
		command = getchar();
		if (command == EOF) {
			break;
		}
		scanf("%i", &key);
		getchar();
		switch (command) {
		case 'a':
			AddElem(&t, key);
			break;
		case 'f':
			if (FindElem(t, key)) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
			break;
		case 'r':
			DeleteElem(&t, key);
			break;
		default:
			break;
		}
	}
	FreeTreap(t);
	return 0;
}
