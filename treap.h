#pragma once

#define MAX_LENGTH 16
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  int value;
  int prior;
  int count;
  struct node* left;
  struct node* right;
} node;

typedef enum bool_t {
  FALSE = 0,
  TRUE = 1
} bool_t;

node* CreateNode(int value);
int GetNodeCount(node* node);
void UpdateNodeCount(node* node);

node* Merge(node* left, node* right);
void Split(int key, node* root, node** left, node** right, int add);

void Insert(int value, int position, node** root);
int Delete(int position, node** root);
void Find(int value, node* root, node** result);

void Check(int value, node* root, bool_t* contains);
void DeleteValue(int value, node** root, bool_t* deleted);
void FreeTree(node* root);