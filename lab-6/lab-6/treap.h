#pragma once

#define MAX_INPUT_LENGTH 12 // command(1) + space(1) + key(max - 10, as log10(max_int) = 10)
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SOMETHING_DELETED 0
#define NOTHING_DELETED 1
#define DEFAULT_ADD_VAL 0
typedef struct node {
	int val;
	int prior;
	int count;
	struct node* left;
	struct node* right;
} node;



node* init_node(int val);
int get_count(node* p);
void update_count(node* p);
node* merge(node* l, node* r);
void split(int key, node* root, node** l, node** r, int add);
void insert(int val, int pos, node** root);
void print(node* root);
int del(int pos, node** root);
void check(int val, node* root, bool* contains);

void find(int val, node* root, node** result);
void del_val(int val, node** root, bool* deleted);
void free_tree(node* root);