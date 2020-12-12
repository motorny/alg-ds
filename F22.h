#ifndef F22_H_INCLUDED__
#define F22_H_INCLUDED__
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include <Windows.h>

#define N 100
#define SMALLNUMBER -9999999
#define FOUND 1
#define NOTFOUND -1

typedef struct tree {
  int low;
  int high;
  int max;
  struct tree* left;
  struct tree* right;
} tree_t;

tree_t* addTree(tree_t* tree, int low, int high);
tree_t* delTree(tree_t* tree, int low, int high);
int findTree(tree_t* tree, int low, int high);
void intersect(tree_t* tree, int low, int high);
void printTree(tree_t* tree, int index);
void freeTree(tree_t* tree);

#endif