#ifndef TREE_H_INCLUDED__
#define TREE_H_INCLUDED__
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#pragma warning (disable: 4996)

#define TRUE 1
#define FALSE 0
#define SIZE 100

typedef struct node node_t;
struct node {
  int left_border;
  int right_border;
  node_t* left;
  node_t* right;
};

typedef struct interval{
  int left_border;
  int right_border;
}inter_t;

int addInter(node_t** tree, int left_border, int right_border);
int deleteInter(node_t** tree, int left_border, int right_border);
int findInter(node_t* tree, int left_border, int right_border);
void intersectInterval(node_t* tree, int left_border, int right_border, inter_t(*arr)[SIZE], int* level);
void printInterTree(node_t* tree, int level);
#endif