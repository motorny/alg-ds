#pragma once
#include<stdio.h>

typedef struct Treap
{
	int priority, key;
	struct Treap* left;
	struct Treap* right;
} Treap;


Treap* new_node(int key);

Treap* merge(Treap* left, Treap* right);

void split(Treap* t, Treap** left, Treap** right, int key);

void add_elem(Treap** t, int key);

void delete_elem(Treap** t, int key);

int find_elem(Treap* t, int key);

void destroy(Treap* t);