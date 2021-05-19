#include "23plus_trees.h"

int UnTwoNodes(ttTree_t** tree, ttTree_t* nodeInTree, ttTree_t* newNode) {
  ttTree_t* nodeParent = nodeInTree->parent;

  // rebuild tree top
  if (nodeParent == NULL) {
    ttTree_t* newTreeTop = (ttTree_t*)malloc(sizeof(ttTree_t));
    if (!newTreeTop)
      return LABI_FALSE;

    newTreeTop->isLeaf = newTreeTop->data = newTreeTop->rightNum = 0;
    newTreeTop->childsCnt = 2;
    newTreeTop->right = newTreeTop->parent = NULL;
    newTreeTop->maxSubtreeData = newNode->maxSubtreeData;
    newTreeTop->leftNum = nodeInTree->maxSubtreeData;
    newTreeTop->left = nodeInTree;
    newTreeTop->middle = newNode;
    newNode->parent = nodeInTree->parent = newTreeTop;

    *tree = newTreeTop;
    return LABI_TRUE;
  }
  else if (nodeParent->childsCnt == 2) {
    nodeParent->childsCnt = 3;
    newNode->parent = nodeParent;

    if (newNode->maxSubtreeData < nodeParent->left->maxSubtreeData) {
      nodeParent->right = nodeParent->middle;
      nodeParent->middle = nodeParent->left;
      nodeParent->left = newNode;
    }
    else if (newNode->maxSubtreeData > nodeParent->left->maxSubtreeData && newNode->maxSubtreeData < nodeParent->middle->maxSubtreeData) {
      nodeParent->right = nodeParent->middle;
      nodeParent->middle = newNode;
    }
    else
      nodeParent->right = newNode;

    nodeParent->leftNum = nodeParent->left->maxSubtreeData;
    nodeParent->rightNum = nodeParent->middle->maxSubtreeData;
    nodeParent->maxSubtreeData = nodeParent->right->maxSubtreeData;

    // update max element in parents trees
    nodeParent = nodeParent->parent;
    while (nodeParent != NULL) {
      if (newNode->maxSubtreeData > nodeParent->maxSubtreeData)
        nodeParent->maxSubtreeData = newNode->maxSubtreeData;
      else
        break;

      nodeParent = nodeParent->parent;
    }

    return LABI_TRUE;
  }
  else {
    ttTree_t* newParentElement = (ttTree_t*)malloc(sizeof(ttTree_t)),
      * leaf1, * leaf2, * leaf3, * leaf4;
    if (!newParentElement)
      return LABI_FALSE;

    // sort 4 elements
    if (newNode->maxSubtreeData < nodeParent->left->maxSubtreeData)
      leaf1 = newNode, leaf2 = nodeParent->left, leaf3 = nodeParent->middle, leaf4 = nodeParent->right;
    else if (newNode->maxSubtreeData > nodeParent->left->maxSubtreeData && newNode->maxSubtreeData < nodeParent->middle->maxSubtreeData)
      leaf1 = nodeParent->left, leaf2 = newNode, leaf3 = nodeParent->middle, leaf4 = nodeParent->right;
    else if (newNode->maxSubtreeData > nodeParent->middle->maxSubtreeData && newNode->maxSubtreeData < nodeParent->right->maxSubtreeData)
      leaf1 = nodeParent->left, leaf2 = nodeParent->middle, leaf3 = newNode, leaf4 = nodeParent->right;
    else
      leaf1 = nodeParent->left, leaf2 = nodeParent->middle, leaf3 = nodeParent->right, leaf4 = newNode;

    // remake some nodes
    nodeParent->rightNum = 0;
    nodeParent->childsCnt = 2;
    nodeParent->leftNum = leaf1->maxSubtreeData;
    nodeParent->left = leaf1;
    nodeParent->middle = leaf2;
    nodeParent->right = NULL;
    nodeParent->maxSubtreeData = leaf2->maxSubtreeData;
    leaf1->parent = leaf2->parent = nodeParent;

    newParentElement->isLeaf = newParentElement->data = newParentElement->rightNum = 0.0;
    newParentElement->childsCnt = 2;
    newParentElement->leftNum = leaf3->maxSubtreeData;
    newParentElement->left = leaf3;
    newParentElement->middle = leaf4;
    newParentElement->right = NULL;
    newParentElement->maxSubtreeData = leaf4->maxSubtreeData;
    leaf3->parent = leaf4->parent = newParentElement;

    // rebuild tree
    return UnTwoNodes(tree, nodeParent, newParentElement);
  }
}

int AddToTTTree(ttTree_t** tree, double newElement) {
  ttTree_t* newTtTreeLeaf = (ttTree_t*)malloc(sizeof(ttTree_t)), * tmp = *tree, * tmpParent = NULL;
  if (!newTtTreeLeaf)
    return LABI_FALSE;
  newTtTreeLeaf->isLeaf = 1;
  newTtTreeLeaf->data = newTtTreeLeaf->maxSubtreeData = newElement;

  newTtTreeLeaf->childsCnt = 0;
  newTtTreeLeaf->leftNum = newTtTreeLeaf->rightNum = 0;
  newTtTreeLeaf->left = newTtTreeLeaf->right = newTtTreeLeaf->middle = NULL;

  if (*tree != NULL) {
    // go to leaf
    while (tmp != NULL && tmp->isLeaf == 0) {
      tmpParent = tmp;

      if (tmp->childsCnt == 2) {
        if (newElement <= tmp->leftNum)
          tmp = tmp->left;
        else
          tmp = tmp->middle;
      }
      else {
        if (newElement <= tmp->leftNum)
          tmp = tmp->left;
        else if (tmp->leftNum < newElement && newElement <= tmp->rightNum)
          tmp = tmp->middle;
        else if (tmp->rightNum < newElement)
          tmp = tmp->right;
      }
    }
    // if these leaf already our new element: clear new leaf and exit
    if (tmp != NULL && tmp->data == newElement) {
      free(newTtTreeLeaf);
      return LABI_FALSE;
    }

    // look into parent
    if (tmpParent != NULL) {
      // if can put one element in parent node
      if (tmpParent->childsCnt == 2) {
        tmpParent->childsCnt = 3;
        newTtTreeLeaf->parent = tmpParent;

        if (newElement < tmpParent->left->data) {
          tmpParent->leftNum = newElement;
          tmpParent->rightNum = tmpParent->left->data;
          tmpParent->right = tmpParent->middle;
          tmpParent->middle = tmpParent->left;
          tmpParent->left = newTtTreeLeaf;
        }
        else if (newElement < tmpParent->middle->data && newElement > tmpParent->left->data) {
          tmpParent->rightNum = newElement;
          tmpParent->right = tmpParent->middle;
          tmpParent->middle = newTtTreeLeaf;
        }
        else {
          tmpParent->rightNum = tmpParent->middle->data;
          tmpParent->right = newTtTreeLeaf;
        }
        tmpParent->maxSubtreeData = tmpParent->right->data;

        // update max element in parents trees
        tmpParent = tmpParent->parent;
        while (tmpParent != NULL) {
          if (newElement > tmpParent->maxSubtreeData)
            tmpParent->maxSubtreeData = newElement;
          else
            break;

          tmpParent = tmpParent->parent;
        }

        return LABI_TRUE;
      }
      // if cannot -> split parent block and rebuild tree
      else {
        ttTree_t* newParentElement = (ttTree_t*)malloc(sizeof(ttTree_t)),
          * leaf1, * leaf2, * leaf3, * leaf4;
        if (!newParentElement) {
          free(newTtTreeLeaf);
          return LABI_FALSE;
        }

        // sort 4 elements
        if (newElement < tmpParent->left->data)
          leaf1 = newTtTreeLeaf, leaf2 = tmpParent->left, leaf3 = tmpParent->middle, leaf4 = tmpParent->right;
        else if (newElement > tmpParent->left->data && newElement < tmpParent->middle->data)
          leaf1 = tmpParent->left, leaf2 = newTtTreeLeaf, leaf3 = tmpParent->middle, leaf4 = tmpParent->right;
        else if (newElement > tmpParent->middle->data && newElement < tmpParent->right->data)
          leaf1 = tmpParent->left, leaf2 = tmpParent->middle, leaf3 = newTtTreeLeaf, leaf4 = tmpParent->right;
        else
          leaf1 = tmpParent->left, leaf2 = tmpParent->middle, leaf3 = tmpParent->right, leaf4 = newTtTreeLeaf;

        // remake some nodes
        tmpParent->childsCnt = 2;
        tmpParent->rightNum = 0;
        tmpParent->leftNum = leaf1->data;
        tmpParent->left = leaf1;
        tmpParent->middle = leaf2;
        tmpParent->right = NULL;
        tmpParent->maxSubtreeData = leaf2->data;
        leaf1->parent = leaf2->parent = tmpParent;

        newParentElement->isLeaf = newParentElement->data = newParentElement->rightNum = 0;
        newParentElement->childsCnt = 2;
        newParentElement->leftNum = leaf3->data;
        newParentElement->left = leaf3;
        newParentElement->middle = leaf4;
        newParentElement->right = NULL;
        newParentElement->maxSubtreeData = leaf4->data;
        leaf3->parent = leaf4->parent = newParentElement;

        // rebuild tree
        return UnTwoNodes(tree, tmpParent, newParentElement);
      }
    }
    // if no parent -> only one element in tree
    else {
      ttTree_t* newParentElement = (ttTree_t*)malloc(sizeof(ttTree_t));
      if (!newParentElement) {
        free(newTtTreeLeaf);
        return LABI_FALSE;
      }
      newTtTreeLeaf->parent = tmp->parent = newParentElement;

      newParentElement->parent = NULL;
      newParentElement->childsCnt = 2;
      newParentElement->isLeaf = newParentElement->data = newParentElement->rightNum = 0;
      newParentElement->right = NULL;

      if (tmp->data < newElement) {
        newParentElement->left = tmp;
        newParentElement->leftNum = tmp->data;
        newParentElement->middle = newTtTreeLeaf;
      }
      else {
        newParentElement->left = newTtTreeLeaf;
        newParentElement->leftNum = newTtTreeLeaf->data;
        newParentElement->middle = tmp;
      }
      newParentElement->maxSubtreeData = newParentElement->middle->data;

      *tree = newParentElement;
      return LABI_TRUE;
    }
  }
  // no element in tree -> add in tree top
  else {
    newTtTreeLeaf->parent = NULL;
    *tree = newTtTreeLeaf;
  }

  return LABI_TRUE;
}