#pragma once
#include<stdio.h>

#define FOUND 1
#define NOTFOUND 0

typedef struct treap {
	struct treap* left;
	struct treap* right;
	int key;
	int priority;
}treap;


treap* Merge(treap* l, treap* r);

void Split(treap* t, int key, treap** l, treap** r);

void Add(treap** t, int key);

void Delete(treap** t, int key);

int Find(treap* t, int key);

void TreapOff(treap* t);