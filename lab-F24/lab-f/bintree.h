#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum err{
  ERROR = -1,
  OK,
}ERR_STATUS;

typedef struct sec{
  int l;
  int r;
}sec_t;

typedef struct sbtree{
  struct sbtree* p;
  struct sbtree* right;
  struct sbtree* left;
  sec_t* sec;
  int key;
}sbtree_t;

sbtree_t* SBtreeInsert(sbtree_t* tree, sbtree_t* newEl);
sbtree_t* SBtreeInsertMod(sbtree_t* tree, int l, int r);
sbtree_t* SBtreeDeletePtr(sbtree_t* tree, sbtree_t* toDel);
sbtree_t* SBtreeDelete(sbtree_t* tree, int l, int r);
sbtree_t* SBtreeSuccessor(sbtree_t* tree, sbtree_t* elem);
sbtree_t* SBtreeMin(sbtree_t* tree);

ERR_STATUS SBTreeInsectSecMod(sbtree_t* tree, int l, int r, int* numOfInsect);
ERR_STATUS SBtreeSearchMod(sbtree_t* tree, int l, int r);
sbtree_t* SBtreeSearch(sbtree_t* tree, int l, int r);
void SBtreeFree(sbtree_t** tree);

sbtree_t* CreateNode(int l, int r);

void PrintTreeBad(sbtree_t* tree, int numSpaces);
void SBtreeInorderWalk(sbtree_t* tree);
void SBtreeInorderWalkR(sbtree_t* tree);

#endif /*BTREE_H*/