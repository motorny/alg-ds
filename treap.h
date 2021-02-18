#pragma once
#include<stdio.h>
typedef struct treap {
	int key, prior;
	struct treap* left;
	struct treap* right;
}treap;

treap* getNode(int key);

treap* merge(treap* l, treap* r);

void split(treap* t, int key, treap** l, treap** r);

void add(treap** t, int key);

int delelem(treap** t, int key);

void printTree(treap* t, char* dir, int level);

char* readString();

int find(treap* t, int key);

void destroy(treap* t);