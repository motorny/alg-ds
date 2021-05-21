#pragma once

#include <stdio.h>
#include <stdlib.h>

#define EMPTY (-1)

typedef struct Tree {
  struct Tree* left;
  struct Tree* middle;
  struct Tree* right;
  int left_value;
  int right_value;
  int max_child;
  struct Tree* left1;
  struct Tree* right1;
} Tree_t;

void freeN(Tree_t* node);
void freeTr(Tree_t* root);
Tree_t* newN(int val);
Tree_t* insert(Tree_t* root, int value);
Tree_t* insertN(Tree_t* root, int value);
Tree_t* deleteT(Tree_t* root, int value);
Tree_t* deleteN(Tree_t* root, int value);
Tree_t* deleteN1(Tree_t* root, int value);
Tree_t* findN(Tree_t* root, int value);
void print(Tree_t* root);