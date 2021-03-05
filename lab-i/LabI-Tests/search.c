#include "23plus_trees.h"

int SearchInTTTree(ttTree_t* tree, double element) {
  ttTree_t* tmp = tree;

  // go to leaf
  while (tmp != NULL && tmp->isLeaf == 0) {
    if (tmp->childsCnt == 2) {
      if (element <= tmp->leftNum)
        tmp = tmp->left;
      else
        tmp = tmp->middle;
    }
    else {
      if (element <= tmp->leftNum)
        tmp = tmp->left;
      else if (tmp->leftNum < element && element <= tmp->rightNum)
        tmp = tmp->middle;
      else if (tmp->rightNum < element)
        tmp = tmp->right;
    }
  }

  if (tmp == NULL)
    return LABI_FALSE;
  else if (tmp->data == element)
    return LABI_TRUE;
  else
    return LABI_FALSE;
}