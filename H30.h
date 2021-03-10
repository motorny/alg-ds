#pragma once
#include<stdio.h>

typedef struct treap {
	int key;
	int prior;
	struct treap* left;
	struct treap* right;
}treap;


treap* Merge(treap* l, treap* r);

void Split(treap* t, int key, treap** l, treap** r);

treap* NewElem(int key);

void AddElem(treap** t, int key);

int FindElem(treap* t, int key);

void DeleteElem(treap** t, int key);

void FreeTreap(treap* t);