#ifndef INTERVALTREE_H_INCLUDED__
#define INTERVALTREE_H_INCLUDED__
#pragma once

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define NOT_FOUND NULL
#define INCORRECT_INPUT NULL;
#define MEMORY_WAS_NOT_ALLOCATED NULL

enum {
	NOT_FINISHED = 0,
	FINISHED,
	ERROR
};

typedef struct tree_t {
	int leftBorder;
	int rightBorder;
	struct tree_t* left;
	struct tree_t* right;
	struct tree_t* parent;
}tree_t;

typedef struct {
	int leftBorder;
	int rightBorder;
}segment_t;

typedef struct {
	segment_t* segments;
	int count;
}answer_t;

tree_t* CreateNode(tree_t* parent, int left, int right);
int AddByLeftBorder(tree_t** tree, int left, int right);
tree_t* FindByBorders(tree_t* tree, int left, int right);
void EquateNodes(tree_t* deleted, tree_t* newSon);
int DeleteByBorders(tree_t* needed);
int DestroyTree(tree_t* tree);

int WriteAnswer(int left, int right, answer_t* answer);
int IntersectionCheck(tree_t* tree, int left, int right, answer_t* answer);
int SearchIntersecting(tree_t* tree, int left, int right, answer_t* answer);
void PrintAnswer(answer_t* answer);
int FreeAnswer(answer_t* answer);
void PrintTree(tree_t* tree);

#endif INTERVALTREE_H_INCLUDED
