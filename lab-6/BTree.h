#pragma once

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define TRUE 1
#define FALSE 0

typedef struct BNode BNode;
struct BNode
{
  int n;   // Number of keys
  int *keys;        //Array of keys
  BNode **child;   // Array of pointers to children.  
};

typedef struct
{
  int M;    // Number of keys
  BNode *root;   // Array of pointers to children.  
} BTree;

int BTreeSearch(BTree Tree, int Key);
void BTreeDisplay(BNode* ptr);
void BTreeClear(BTree* Tree);
int BTreeInsert(BTree* Tree, int Key);
int BTreeDelete(BTree* Tree, int Key);
