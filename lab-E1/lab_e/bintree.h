#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
  ERROR = -1,
  OK,
  FOUND
}ERR_STATUS;

typedef struct btree_t {
  struct btree_t* p;
  struct btree_t* right;
  struct btree_t* left;
  int key;
  int difNods;
}btree_t;

btree_t* BtreeInsert(btree_t* tree, btree_t* newEl);
btree_t* BtreeInsertMod(btree_t* tree, int key);
btree_t* BtreeDeletePtr(btree_t* tree, btree_t* toDel);
btree_t* BtreeDelete(btree_t* tree, int key);
btree_t* BtreeSuccessor(btree_t* tree, btree_t* elem);
btree_t* BtreeMin(btree_t* tree);

ERR_STATUS BtreeSearchMod(btree_t* tree, int key);
void BtreeFree(btree_t** tree);
btree_t* BtreeSubHeightDif(btree_t* tree);

btree_t* CreateNode(int data);
int BtreeHeight(btree_t* tree);

void PrintTreeBad(btree_t* tree, int numSpaces);
void BtreeInorderWalk(btree_t* tree);
void BtreeInorderWalkSubNods(btree_t* tree);


#endif // !BTREE_H