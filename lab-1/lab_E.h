#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#pragma warning(disable:4996)

#define MAX_INPUT_STR 10000
#define STEP_FOR_MALLOC 10

#define SPACE ' '
#define BRACKET_LEFT '('
#define BRACKET_RIGHT ')'

typedef struct node_t {
    char* keyWord;
    struct node_t* left;
    struct node_t* right;
}node_t;

node_t* ReadTree(FILE* fp);
void PrintTree(node_t* t);
void DestroyTree(node_t* t);
