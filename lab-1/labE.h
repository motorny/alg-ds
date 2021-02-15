#pragma once
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#define TRUE 1
#define FALSE 0
typedef int Tree;
struct tree {
    Tree value;
    struct tree* left;
    struct tree* right;
};
void STL(struct tree** tree, int** number, int* level);
void Input(struct tree** tree, char action, int value, int** output);
void Delete(struct tree* tree);
void Print(struct tree* root, int level);
int RBV(struct tree** tree, Tree value);
int FBV(struct tree* root, Tree value, struct tree** outPtr);
int Inst(struct tree** head, int value);
struct tree* GNN(Tree value);
