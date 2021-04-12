#ifndef AVLTREE_H_INCLUDED__
#define AVLTREE_H_INCLUDED__
#pragma once

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#define NOT_FOUND NULL

enum {
	NOT_FINISHED = 0,
	FINISHED,
	NEED_BALANCE,
	ERROR,
};

typedef struct tree_t {
	int key;
	int balance;
	struct tree_t* left;
	struct tree_t* right;
}tree_t;

tree_t* RightRotate(tree_t* tree);
tree_t* LeftRotate(tree_t* tree);
int Balance(tree_t** tree, int flag, int balanceCase);
int AddNodeByKey(tree_t** tree, int key);
tree_t* FindByKey(tree_t* tree, int key);
int DeleteByKey(tree_t** tree, int key);
int DestroyTree(tree_t* tree);
void PrintTree(tree_t* tree, int n);

#endif AVLTREE_H_INCLUDED
