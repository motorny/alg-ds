#ifndef BPLUS_H
#define BPLUS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define DEG 5 // min deg of B-tree

typedef enum {
  ERROR,
  OK, 
  FOUND, 
  NOT_FOUND
} ERR_STATUS;


typedef struct node_t {
  ERR_STATUS leaf;
  int keyNum;
  int key[2 * DEG];
  struct node_t* parent;
  struct node_t* child[2 * DEG + 1];
  struct node_t* left;
  struct node_t* right;
} node_t;

typedef struct {
  node_t* root;
}bplus_t;

bplus_t* BplusCreate();
ERR_STATUS BplusInsert(bplus_t* tree, const int key);
ERR_STATUS BplusSearch(const bplus_t* tree, const int key);
ERR_STATUS BplusDelete(bplus_t* tree, const int key);
void BplusFree(bplus_t* tree);
bplus_t* Merge(bplus_t* t1, bplus_t* t2);
void BplusSplit(bplus_t* tree, int key, bplus_t* t1, bplus_t* t2);
void BplusPrint(bplus_t* tree);

#endif //BPLUS_H