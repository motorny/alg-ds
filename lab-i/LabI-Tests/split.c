#include "23plus_trees.h"

typedef struct treeStackNode_t treeStackNode_t;
struct treeStackNode_t {
  ttTree_t* currentTree;
  treeStackNode_t *nextTree;
};

int Push(treeStackNode_t** stack, ttTree_t* newTree) {
  treeStackNode_t* newNode = (treeStackNode_t *)malloc(sizeof(treeStackNode_t));
  if (newTree == NULL || newNode == NULL)
    return LABI_FALSE;

  newNode->currentTree = newTree;
  newNode->nextTree = *stack;
  *stack = newNode;
  return LABI_TRUE;
}

int Pop(treeStackNode_t** stack, ttTree_t** treeFromStack) {
  treeStackNode_t* nodeToDelete = *stack;
  if (*stack == NULL) {
    *treeFromStack = NULL;
    return LABI_FALSE;
  }

  *treeFromStack = (*stack)->currentTree;
  *stack = (*stack)->nextTree;
  free(nodeToDelete);
  return LABI_TRUE;
}


int SplitTTTree(ttTree_t* tree, ttTree_t** tree1, ttTree_t** tree2, double elementToSplit ) {
  ttTree_t* tmp = tree, *tmpParent = NULL, *leftTree = NULL, *rightTree = NULL, *nodeToDelete, *leafNode;
  treeStackNode_t *stackTreeLeft = NULL, *stackTreeRight = NULL;

  *tree1 = *tree2 = NULL;

  if (tree == NULL)
    return LABI_FALSE;

  // go to leaf
  while (tmp != NULL && tmp->isLeaf == 0) {
    tmpParent = tmp;

    if (tmp->childsCnt == 2) {
      if (elementToSplit <= tmp->leftNum)
        tmp = tmp->left;
      else
        tmp = tmp->middle;
    }
    else {
      if (elementToSplit <= tmp->leftNum)
        tmp = tmp->left;
      else if (tmp->leftNum < elementToSplit && elementToSplit <= tmp->rightNum)
        tmp = tmp->middle;
      else if (tmp->rightNum < elementToSplit)
        tmp = tmp->right;
    }
  }
  // if this leaf not our element or this leaf is empty: clear new leaf and exit
  if (tmp == NULL || (tmp != NULL && tmp->data != elementToSplit))
    return LABI_FALSE;

  // if our leaf is tree top
  if (tmpParent == NULL) {
    *tree1 = tmp;
    *tree2 = NULL;
  }
  else {
    Push(&stackTreeLeft, tmp);

    while (tmpParent != NULL) {
      if (tmpParent->childsCnt == 2 && tmp == tmpParent->left) {
        tmpParent->middle->parent = NULL;
        Push(&stackTreeRight, tmpParent->middle);
      }
      else if (tmpParent->childsCnt == 2 && tmp == tmpParent->middle) {
        tmpParent->left->parent = NULL;
        Push(&stackTreeLeft, tmpParent->left);
      }
      else if (tmpParent->childsCnt == 3 && tmp == tmpParent->left) {
        tmpParent->middle->parent = tmpParent->right->parent = NULL;
        Push(&stackTreeRight, tmpParent->middle);
        Push(&stackTreeRight, tmpParent->right);
      }
      else if (tmpParent->childsCnt == 3 && tmp == tmpParent->middle) {
        tmpParent->left->parent = tmpParent->right->parent = NULL;
        Push(&stackTreeLeft, tmpParent->left);
        Push(&stackTreeRight, tmpParent->right);
      }
      else if (tmpParent->childsCnt == 3 && tmp == tmpParent->right) {
        tmpParent->middle->parent = tmpParent->left->parent = NULL;
        Push(&stackTreeLeft, tmpParent->left);
        Push(&stackTreeLeft, tmpParent->middle);
      }

      nodeToDelete = tmp;
      tmpParent = tmpParent->parent;
      if (tmp->isLeaf == 1) {
        leafNode = tmp;
        tmp = tmp->parent;
        leafNode->parent = NULL;
      }
      else
        tmp = tmp->parent;
      if (nodeToDelete->isLeaf == 0)
        free(nodeToDelete);
    }

    while (stackTreeLeft != NULL) {
      Pop(&stackTreeLeft, &tmp);
      UnionTTTree(&leftTree, leftTree, tmp);
    }
    *tree1 = leftTree;

    while (stackTreeRight != NULL) {
      Pop(&stackTreeRight, &tmp);
      UnionTTTree(&rightTree, rightTree, tmp);
    }
    *tree2 = rightTree;
  }

  return LABI_TRUE;
}