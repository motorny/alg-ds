#ifndef __trees_h__
#define __trees_h__

#include <stdlib.h>

typedef struct ttTree_t ttTree_t;
struct ttTree_t {
  // leaf data
  int isLeaf;
  double data;

  // childs ptrs info
  int childsCnt;
  double leftNum, rightNum;
  ttTree_t* left, * middle, * right;

  // parent ptr
  double maxSubtreeData;              // <-- max data in subtree
  ttTree_t* parent;
};

enum returns {
  LABI_UNION = 7,
  LABI_SPLIT = 6,
  LABI_ADD = 5,
  LABI_REMOVE = 4,
  LABI_FIND = 3,

  LABI_TRUE = 1,
  LABI_FALSE = 0
};

// help func
int UnTwoNodes(ttTree_t** tree, ttTree_t* nodeInTree, ttTree_t* newNode);

int AddToTTTree(ttTree_t** tree, double newElement);
int SearchInTTTree(ttTree_t* tree, double element);
int DeleteInTTTree(ttTree_t** tree, double deleteElement);

int UnionTTTree(ttTree_t** tree, ttTree_t* tree1, ttTree_t* tree2);
int SplitTTTree(ttTree_t* tree, ttTree_t** tree1, ttTree_t** tree2, double elementToSplit);

#endif