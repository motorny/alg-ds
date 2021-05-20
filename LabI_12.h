#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#define T 2
typedef enum bool_t {
	NO = 0,
	YES
}bool_t;

typedef enum err_t {
	ERR_NO = -1,
	SUCCESS,
	FAIL,
	ERR_MEM,
	ERR_KEYS
}err_t;

static char ErrMess[2][40] = {
	"yes",
	"no"
};

typedef struct node_t {
	bool_t isleaf;
	int n;
	int key[2 * T - 1];
	struct node_t* children[2 * T];
}node_t;

node_t* ROOT = NULL;

void Add(int key);
err_t Search(int key);
void Remove(int key);
void PrintTree();
void FreeTree();
