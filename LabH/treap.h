#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef struct Treap {
  int x;
  int y;
  struct Treap* left;
  struct Treap* right;
} Treap;

Treap* Merge(Treap* L, Treap* R);
void Split(Treap* T, Treap** outL, Treap** outR, int x);
void Add(Treap** T, int x);
void Remove(Treap** T, int x);