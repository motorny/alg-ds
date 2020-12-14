#ifndef TREE_H_INCLUDED__
#define TREE_H_INCLUDED__
#pragma once

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define ABS(x) ((x)>=0?(x):-(x))
#define DIFFERENCE(left, right) (ABS(left - right))
#define IS_NUMBER(ch) ( ch >= '0' && ch <= '9')
#define NOT_FOUND NULL
#define ZERO_CODE 48
#define FACTOR 10
#define MAX_WIDTH 15

enum {
	NOT_FINISHED = 0,
	FINISHED,
	ERROR
};

typedef struct tree_t {
	int key;
	int height;
	int differense;
	struct tree_t* left;
	struct tree_t* right;
}tree_t;

int CountHeight(tree_t* tree);
int AddNodeByKey(tree_t** tree, int key);
tree_t* FindByKey(tree_t* tree, int key);
int DeleteByKey(tree_t** tree, int key);
int DestroyTree(tree_t* tree);
void PrintTree(tree_t* tree, int n);

#endif TREE_H_INCLUDED
