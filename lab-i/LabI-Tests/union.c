#include "23plus_trees.h"

static int GetTreeHeight(ttTree_t* tree) {
  int i = 0;
  ttTree_t *tmp = tree;

  while (tmp != NULL)
    i++, tmp = tmp->left;

  return i;
}

static double GetTreeMinElement(ttTree_t* tree) {
  ttTree_t* tmp = tree;

  while (tmp != NULL && tmp->isLeaf == 0)
    tmp = tmp->left;

  if (tmp == NULL)
    return 0;
  else
    return tmp->data;
}

int UnTwoFromLeft(ttTree_t** tree, ttTree_t* treeNewInLeft, ttTree_t* treeBroOfNew) {
  ttTree_t *broParent = treeBroOfNew->parent;

  if (broParent == 0) {
    ttTree_t* newParent = (ttTree_t*)malloc(sizeof(ttTree_t));
    if (newParent == NULL)
      return LABI_FALSE;

    newParent->isLeaf = newParent->data = newParent->rightNum = 0;
    newParent->leftNum = treeNewInLeft->maxSubtreeData;
    newParent->maxSubtreeData = treeBroOfNew->maxSubtreeData;
    newParent->childsCnt = 2;

    newParent->left = treeNewInLeft;
    newParent->middle = treeBroOfNew;
    newParent->right = newParent->parent = NULL;
    treeNewInLeft->parent = treeBroOfNew->parent = newParent;

    *tree = newParent;
    return LABI_TRUE;
  }
  if (broParent->childsCnt == 2) {
    broParent->childsCnt = 3;
    broParent->right = broParent->middle;
    broParent->middle = broParent->left;
    broParent->left = treeNewInLeft;
    treeNewInLeft->parent = broParent;

    broParent->rightNum = broParent->middle->maxSubtreeData;
    broParent->leftNum = broParent->left->maxSubtreeData;

    return LABI_TRUE;
  }
  if (broParent->childsCnt == 3) {
    ttTree_t* newNodeToNewLeft = (ttTree_t*)malloc(sizeof(ttTree_t));
    if (newNodeToNewLeft == NULL)
      return LABI_FALSE;

    newNodeToNewLeft->isLeaf = newNodeToNewLeft->data = newNodeToNewLeft->rightNum = 0;
    newNodeToNewLeft->childsCnt = 2;

    newNodeToNewLeft->left = treeNewInLeft;
    newNodeToNewLeft->middle = broParent->left;
    newNodeToNewLeft->right = newNodeToNewLeft->parent = NULL;

    newNodeToNewLeft->leftNum = treeNewInLeft->maxSubtreeData;
    newNodeToNewLeft->maxSubtreeData = newNodeToNewLeft->middle->maxSubtreeData;

    treeNewInLeft->parent = treeBroOfNew->parent = newNodeToNewLeft;

    broParent->childsCnt = 2;
    broParent->left = broParent->middle;
    broParent->middle = broParent->right;
    broParent->right = NULL;
    broParent->rightNum = 0;
    broParent->leftNum = broParent->left->maxSubtreeData;
    
    return UnTwoFromLeft(tree, newNodeToNewLeft, broParent);
  }
}

int UnTwoFromRight(ttTree_t** tree, ttTree_t* treeNewInRight, ttTree_t* treeBroOfNew) {
  ttTree_t* broParent = treeBroOfNew->parent, *tmp;

  if (broParent == 0) {
    ttTree_t* newParent = (ttTree_t*)malloc(sizeof(ttTree_t));
    if (newParent == NULL)
      return LABI_FALSE;

    newParent->isLeaf = newParent->data = newParent->rightNum = 0;
    newParent->leftNum = treeBroOfNew->maxSubtreeData;
    newParent->maxSubtreeData = treeNewInRight->maxSubtreeData;
    newParent->childsCnt = 2;

    newParent->left = treeBroOfNew;
    newParent->middle = treeNewInRight;
    newParent->right = newParent->parent = NULL;
    treeNewInRight->parent = treeBroOfNew->parent = newParent;

    *tree = newParent;
    return LABI_TRUE;
  }
  if (broParent->childsCnt == 2) {
    broParent->childsCnt = 3;
    broParent->right = treeNewInRight;
    treeNewInRight->parent = broParent;

    broParent->rightNum = broParent->middle->maxSubtreeData;
    broParent->maxSubtreeData = broParent->right->maxSubtreeData;

    // correct all previos nodes
    broParent = broParent->parent;
    while (broParent != NULL) {
      if (treeNewInRight->maxSubtreeData > broParent->maxSubtreeData)
        broParent->maxSubtreeData = treeNewInRight->maxSubtreeData;
      else
        break;

      broParent = broParent->parent;
    }

    return LABI_TRUE;
  }
  if (broParent->childsCnt == 3) {
    ttTree_t* newNodeToNewRight = (ttTree_t*)malloc(sizeof(ttTree_t));
    if (newNodeToNewRight == NULL)
      return LABI_FALSE;

    newNodeToNewRight->isLeaf = newNodeToNewRight->data = newNodeToNewRight->rightNum = 0;
    newNodeToNewRight->childsCnt = 2;

    newNodeToNewRight->left = broParent->right;
    newNodeToNewRight->middle = treeNewInRight;
    newNodeToNewRight->right = newNodeToNewRight->parent = NULL;

    newNodeToNewRight->leftNum = newNodeToNewRight->left->maxSubtreeData;
    newNodeToNewRight->maxSubtreeData = newNodeToNewRight->middle->maxSubtreeData;

    treeNewInRight->parent = treeBroOfNew->parent = newNodeToNewRight;

    broParent->childsCnt = 2;
    broParent->right = NULL;
    broParent->rightNum = 0;
    broParent->maxSubtreeData = broParent->middle->maxSubtreeData;

    // correct all previos nodes
    double prevMax = newNodeToNewRight->left->maxSubtreeData;
    tmp = broParent->parent;
    while (tmp != NULL) {
      if (tmp->maxSubtreeData == prevMax)
        if (tmp->childsCnt == 2)
          tmp->maxSubtreeData = tmp->middle->maxSubtreeData;
        else
          tmp->maxSubtreeData = tmp->right->maxSubtreeData;
      else
        break;

      tmp = tmp->parent;
    }

    return UnTwoFromRight(tree, newNodeToNewRight, broParent);
  }
}

int UnionTTTree(ttTree_t** tree, ttTree_t* tree1, ttTree_t* tree2) {
  int firstLen = GetTreeHeight(tree1), secondLen = GetTreeHeight(tree2), tmpLen;
  double firstMin = GetTreeMinElement(tree1), secondMin = GetTreeMinElement(tree2), tmpMin;
  ttTree_t* tmp, *oldTreePtr = *tree, *tmpParent;

  if (tree1 == NULL && tree2 == NULL) {
    *tree = NULL;
    return LABI_FALSE;
  }
  else if (tree1 == NULL) {
    *tree = tree2;
    return LABI_TRUE;
  }
  else if (tree2 == NULL) {
    *tree = tree1;
    return LABI_TRUE;
  }

  if (!(secondMin > tree1->maxSubtreeData || firstMin > tree2->maxSubtreeData)) {
    *tree = NULL;
    return LABI_FALSE;
  }

  // sort tree by highest
  if (firstLen < secondLen) {
    tmp = tree2;
    tree2 = tree1;
    tree1 = tmp;

    tmpLen = firstLen;
    firstLen = secondLen;
    secondLen = tmpLen;
    tmpMin = firstMin;
    firstMin = secondMin;
    secondMin = tmpMin;
  }

  // if same height
  if (firstLen == secondLen) {
    ttTree_t *newTreeTop = (ttTree_t*)malloc(sizeof(ttTree_t));
    if (newTreeTop == NULL)
      return LABI_FALSE;

    newTreeTop->isLeaf = newTreeTop->data = newTreeTop->rightNum = 0;
    newTreeTop->childsCnt = 2;
    newTreeTop->right = NULL;
    newTreeTop->parent = NULL;
    tree1->parent = tree2->parent = newTreeTop;

    // add to right of first tree
    if (secondMin > tree1->maxSubtreeData) {
      newTreeTop->left = tree1;
      newTreeTop->middle = tree2;
    }
    // add to left of first tree 
    else {
      newTreeTop->left = tree1;
      newTreeTop->middle = tree2;
    }
    newTreeTop->leftNum = newTreeTop->left->maxSubtreeData;
    newTreeTop->maxSubtreeData = newTreeTop->middle->maxSubtreeData;
    *tree = newTreeTop;
    return LABI_TRUE;
  }
  // if first taller than second
  else {
    tmp = tree1;
    tmpParent = NULL;
    // add to right of first tree
    if (firstMin > tree2->maxSubtreeData) {
      // go down to correct level
      for (int i = 0; i < firstLen - secondLen; i++)
        tmpParent = tmp, tmp = tmp->left;

      // push node in tree
      UnTwoFromLeft(tree, tree2, tmp);
      if (*tree == oldTreePtr)
        *tree = tree1;
    }
    // add to left of first tree 
    else {
      // go down to correct level
      for (int i = 0; i < firstLen - secondLen; i++) {
        tmpParent = tmp;
        if (tree1->childsCnt == 2)
          tmp = tmp->middle;
        else
          tmp = tmp->right;
      }

      // push node in tree
      UnTwoFromRight(tree, tree2, tmp);
      if (*tree == oldTreePtr)
        *tree = tree1;
    }
  }
  return LABI_TRUE;
}
