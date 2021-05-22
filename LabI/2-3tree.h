#pragma once
#include <stdio.h>
#include <stdlib.h>

#define EMP (-1)

typedef struct Tree {
  struct Tree* left;
  struct Tree* middle;
  struct Tree* right;
  int left_value;
  int right_value;
  int max_child;
  struct Tree* left1;
  struct Tree* right1;
} Tree;


Tree* newN(int val);

Tree* Add(Tree* root, int value);

Tree* AddN(Tree* root, int value);

Tree* deleteT(Tree* root, int value);

Tree* deleteN(Tree* root, int value);

Tree* deleteN1(Tree* root, int value);


Tree* Search(Tree* root, int value);


void free(Tree* node);

void FreeTree(Tree* root);