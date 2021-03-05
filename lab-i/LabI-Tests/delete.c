#include "23plus_trees.h"

static void CorrectNodePath(ttTree_t* node) {
  ttTree_t* tmp = node, * tmpParent = NULL;

  if (tmp != NULL)
    tmpParent = tmp->parent;

  while (tmp != NULL && tmpParent != NULL) {
    if (tmpParent->childsCnt == 2) {
      if (tmp == tmpParent->left)
        tmpParent->leftNum = tmp->maxSubtreeData;
      else if (tmp == tmpParent->middle)
        tmpParent->maxSubtreeData = tmp->maxSubtreeData;
    }
    else {
      if (tmp == tmpParent->left)
        tmpParent->leftNum = tmp->maxSubtreeData;
      else if (tmp == tmpParent->middle)
        tmpParent->rightNum = tmp->maxSubtreeData;
      else if (tmp == tmpParent->right)
        tmpParent->maxSubtreeData = tmp->maxSubtreeData;
    }

    tmp = tmpParent;
    tmpParent = tmpParent->parent;
  }
}

static void Correct2ParentsTreesWithLowChildCnt(ttTree_t* nodeToCorrect, ttTree_t* nodeToDelete) {
  ttTree_t* nodeToDeleteParent = nodeToDelete->parent;

  // rebuild tree
  if (nodeToCorrect->childsCnt == 2 && nodeToCorrect->left->childsCnt == 2 && nodeToCorrect->middle->childsCnt == 2) {
    if (nodeToDeleteParent == nodeToCorrect->left) {
      // fix pointers
      nodeToCorrect->middle->right = nodeToCorrect->middle->middle;
      nodeToCorrect->middle->middle = nodeToCorrect->middle->left;

      if (nodeToDelete == nodeToDeleteParent->left)
        nodeToCorrect->middle->left = nodeToDeleteParent->middle;
      else
        nodeToCorrect->middle->left = nodeToDeleteParent->left;
      nodeToCorrect->middle->left->parent = nodeToCorrect->middle;

      // fix node structure
      nodeToCorrect->middle->childsCnt = 3;
      nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
      nodeToCorrect->middle->rightNum = nodeToCorrect->middle->middle->maxSubtreeData;
    }
    else {
      // fix pointers
      if (nodeToDelete == nodeToDeleteParent->left)
        nodeToCorrect->left->right = nodeToDeleteParent->middle;
      else
        nodeToCorrect->left->right = nodeToDeleteParent->left;
      nodeToCorrect->left->right->parent = nodeToCorrect->left;

      // fix node structure
      nodeToCorrect->left->childsCnt = 3;
      nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxSubtreeData;
      nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->right->maxSubtreeData;

      nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
    }
  }

  CorrectNodePath(nodeToCorrect);
  return;
}

static void Correct2ParentsTrees(ttTree_t* nodeToCorrect, ttTree_t* nodeToDelete) {
  double deleteElement = nodeToDelete->data;
  ttTree_t* nodeToDeleteParent = nodeToDelete->parent;

  if (nodeToCorrect->left == nodeToDeleteParent) {
    if (nodeToDeleteParent->left == nodeToDelete) {
      nodeToDeleteParent->left = nodeToDeleteParent->middle;
      nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
    }
    nodeToDeleteParent->middle = nodeToCorrect->middle->left;
    nodeToDeleteParent->middle->parent = nodeToDeleteParent;
    nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

    nodeToCorrect->middle->left = nodeToCorrect->middle->middle;
    nodeToCorrect->middle->middle = nodeToCorrect->middle->right;
    nodeToCorrect->middle->right = NULL;
    nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
    nodeToCorrect->middle->rightNum = 0;

    nodeToCorrect->middle->childsCnt = 2;
    nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
  }
  else {
    if (nodeToDeleteParent->middle == nodeToDelete)
      nodeToDeleteParent->middle = nodeToDeleteParent->left;
    nodeToDeleteParent->left = nodeToCorrect->left->right;
    nodeToDeleteParent->left->parent = nodeToDeleteParent;
    nodeToCorrect->leftNum = nodeToDeleteParent->left->maxSubtreeData;
    nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

    nodeToCorrect->left->childsCnt = 2;
    nodeToCorrect->left->rightNum = 0;
    nodeToCorrect->left->right = NULL;
    nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->middle->maxSubtreeData;

    nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;

    nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
    nodeToCorrect->maxSubtreeData = nodeToCorrect->middle->maxSubtreeData;
  }

  CorrectNodePath(nodeToCorrect);
  return;
}

static void Correct3ParentsTrees(ttTree_t* nodeToCorrect, ttTree_t* nodeToDelete) {
  double deleteElement = nodeToDelete->data;
  ttTree_t* nodeToDeleteParent = nodeToDelete->parent;

  if (nodeToCorrect->left->childsCnt + nodeToCorrect->middle->childsCnt + nodeToCorrect->right->childsCnt == 6) {
    if (nodeToCorrect->left == nodeToDeleteParent) {
      // connect all pointers
      nodeToCorrect->middle->right = nodeToCorrect->middle->middle;
      nodeToCorrect->middle->middle = nodeToCorrect->middle->left;

      if (nodeToDeleteParent->left == nodeToDelete)
        nodeToCorrect->middle->left = nodeToDeleteParent->middle;
      else
        nodeToCorrect->middle->left = nodeToDeleteParent->left;
      nodeToCorrect->middle->left->parent = nodeToCorrect->middle;

      nodeToCorrect->left = nodeToCorrect->middle;
      nodeToCorrect->middle = nodeToCorrect->right;
      nodeToCorrect->right = NULL;

      // correct nodes info
      nodeToCorrect->childsCnt = 2;
      nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
      nodeToCorrect->rightNum = 0;
      nodeToCorrect->left->childsCnt = 3;
      nodeToCorrect->left->leftNum = nodeToCorrect->left->left->maxSubtreeData;
      nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxSubtreeData;
    }
    else if (nodeToCorrect->middle == nodeToDeleteParent) {
      // connect all pointers
      if (nodeToDeleteParent->left == nodeToDelete)
        nodeToCorrect->left->right = nodeToDeleteParent->middle;
      else
        nodeToCorrect->left->right = nodeToDeleteParent->left;
      nodeToCorrect->left->right->parent = nodeToCorrect->left;

      nodeToCorrect->middle = nodeToCorrect->right;
      nodeToCorrect->right = NULL;

      // correct nodes info
      nodeToCorrect->childsCnt = 2;
      nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->right->maxSubtreeData;
      nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
      nodeToCorrect->rightNum = 0;
      nodeToCorrect->left->childsCnt = 3;
      nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxSubtreeData;
    }
    else if (nodeToCorrect->right == nodeToDeleteParent) {
      // connect all pointers
      if (nodeToDeleteParent->left == nodeToDelete)
        nodeToCorrect->middle->right = nodeToDeleteParent->middle;
      else
        nodeToCorrect->middle->right = nodeToDeleteParent->left;
      nodeToCorrect->middle->right->parent = nodeToCorrect->middle;
      nodeToCorrect->right = NULL;

      // correct nodes info
      //
      nodeToCorrect->childsCnt = 2;
      nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
      nodeToCorrect->rightNum = 0;
      nodeToCorrect->middle->maxSubtreeData = nodeToCorrect->middle->right->maxSubtreeData;
      nodeToCorrect->maxSubtreeData = nodeToCorrect->middle->maxSubtreeData;
      nodeToCorrect->middle->childsCnt = 3;
      nodeToCorrect->middle->rightNum = nodeToCorrect->middle->middle->maxSubtreeData;
    }

    free(nodeToDeleteParent);
  }
  else {
    if (nodeToCorrect->left == nodeToDeleteParent) {
      // correct left child of corrected node
      if (nodeToDeleteParent->left == nodeToDelete)
        nodeToDeleteParent->left = nodeToDeleteParent->middle;
      nodeToDeleteParent->middle = nodeToCorrect->middle->left;
      nodeToDeleteParent->middle->parent = nodeToDeleteParent;
      nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
      nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

      // correct middle child of corrected node
      nodeToCorrect->middle->left = nodeToCorrect->middle->middle;
      if (nodeToCorrect->middle->childsCnt == 2) {
        nodeToCorrect->middle->middle = nodeToCorrect->right->left;
        nodeToCorrect->middle->middle->parent = nodeToCorrect->middle;

        nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
        nodeToCorrect->middle->maxSubtreeData = nodeToCorrect->middle->middle->maxSubtreeData;

        // correct right child of corrected node
        nodeToCorrect->right->left = nodeToCorrect->right->middle;
        nodeToCorrect->right->middle = nodeToCorrect->right->right;

        nodeToCorrect->right->childsCnt = 2;
        nodeToCorrect->right->rightNum = 0;
        nodeToCorrect->right->right = NULL;
        nodeToCorrect->right->leftNum = nodeToCorrect->right->left->maxSubtreeData;
        nodeToCorrect->right->maxSubtreeData = nodeToCorrect->right->middle->maxSubtreeData;
      }
      else {
        nodeToCorrect->middle->childsCnt = 2;
        nodeToCorrect->middle->middle = nodeToCorrect->middle->right;
        nodeToCorrect->middle->rightNum = 0;
        nodeToCorrect->middle->right = NULL;
        nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
      }

      // correct corrected node
      nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
      nodeToCorrect->rightNum = nodeToCorrect->middle->maxSubtreeData;
      nodeToCorrect->maxSubtreeData = nodeToCorrect->right->maxSubtreeData;
    }
    else if (nodeToCorrect->middle == nodeToDeleteParent) {
      if (nodeToCorrect->left->childsCnt == 3) {
        // correct middle child of corrected node
        if (nodeToDeleteParent->middle == nodeToDelete)
          nodeToDeleteParent->middle = nodeToDeleteParent->left;
        nodeToDeleteParent->left = nodeToCorrect->left->right;
        nodeToDeleteParent->left->parent = nodeToDeleteParent;
        nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
        nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

        // correct left child of corrected node
        nodeToCorrect->left->childsCnt = 2;
        nodeToCorrect->left->rightNum = 0;
        nodeToCorrect->left->right = NULL;
        nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->middle->maxSubtreeData;
      }
      else {
        // correct middle child of corrected node
        if (nodeToDeleteParent->left == nodeToDelete)
          nodeToDeleteParent->left = nodeToDeleteParent->middle;
        nodeToDeleteParent->middle = nodeToCorrect->right->left;
        nodeToDeleteParent->middle->parent = nodeToDeleteParent;
        nodeToDeleteParent->left->parent = nodeToDeleteParent;
        nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
        nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

        // correct left child of corrected node
        nodeToCorrect->right->left = nodeToCorrect->right->middle;
        nodeToCorrect->right->middle = nodeToCorrect->right->right;
        nodeToCorrect->right->childsCnt = 2;
        nodeToCorrect->right->rightNum = 0;
        nodeToCorrect->right->right = NULL;
        nodeToCorrect->right->leftNum = nodeToCorrect->right->left->maxSubtreeData;
        nodeToCorrect->right->maxSubtreeData = nodeToCorrect->right->middle->maxSubtreeData;
      }

      // correct corrected node
      nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
      nodeToCorrect->rightNum = nodeToCorrect->middle->maxSubtreeData;
      nodeToCorrect->maxSubtreeData = nodeToCorrect->right->maxSubtreeData;
    }
    else {
      // correct right child of corrected node
      if (nodeToDeleteParent->middle == nodeToDelete)
        nodeToDeleteParent->middle = nodeToDeleteParent->left;

      if (nodeToCorrect->middle->childsCnt == 2) {
        nodeToDeleteParent->left = nodeToCorrect->middle->middle;
        nodeToDeleteParent->left->parent = nodeToDeleteParent;

        nodeToCorrect->middle->middle = nodeToCorrect->middle->left;

        nodeToCorrect->middle->left = nodeToCorrect->left->right;
        nodeToCorrect->middle->left->parent = nodeToCorrect->middle;

        nodeToCorrect->left->childsCnt = 2;
        nodeToCorrect->left->rightNum = 0;
        nodeToCorrect->left->right = NULL;
        nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->middle->maxSubtreeData;

        nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
        nodeToCorrect->middle->maxSubtreeData = nodeToCorrect->middle->middle->maxSubtreeData;
      }
      else {
        nodeToDeleteParent->left = nodeToCorrect->middle->right;
        nodeToDeleteParent->left->parent = nodeToDeleteParent;

        nodeToCorrect->middle->childsCnt = 2;
        nodeToCorrect->middle->rightNum = 0;
        nodeToCorrect->middle->right = NULL;
        nodeToCorrect->middle->maxSubtreeData = nodeToCorrect->middle->middle->maxSubtreeData;
      }
      nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
      nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

      // correct corrected node
      nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
      nodeToCorrect->rightNum = nodeToCorrect->middle->maxSubtreeData;
      nodeToCorrect->maxSubtreeData = nodeToCorrect->right->maxSubtreeData;
    }
  }

  CorrectNodePath(nodeToCorrect);
  return;
}

static void DeleteBadNodesInTree(ttTree_t** tree, ttTree_t* badNodeParent, ttTree_t* badNode) {
  // if main node
  if (badNodeParent->parent == NULL && badNodeParent->childsCnt == 2) {
    if (badNodeParent->left == badNode)
      *tree = badNodeParent->middle;
    else
      *tree = badNodeParent->left;
    (*tree)->parent = NULL;

    free(badNodeParent);
    free(badNode);
  }
  else if (badNodeParent->parent == NULL) {
    badNodeParent->childsCnt = 2;
    if (badNodeParent->left == badNode) {
      badNodeParent->left = badNodeParent->middle;
      badNodeParent->middle = badNodeParent->right;
    }
    else if (badNodeParent->middle == badNode) {
      badNodeParent->middle = badNodeParent->right;
    }
    badNodeParent->right = NULL;
    badNodeParent->rightNum = 0;
    badNodeParent->maxSubtreeData = badNodeParent->middle->maxSubtreeData;
    badNodeParent->leftNum = badNodeParent->left->maxSubtreeData;
    free(badNode);
  }
  else {
    // rebuild tree
    if (badNodeParent->parent->childsCnt == 2 && badNodeParent->parent->left->childsCnt == 2 && badNodeParent->parent->middle->childsCnt == 2) {
      Correct2ParentsTreesWithLowChildCnt(badNodeParent->parent, badNode);
      DeleteBadNodesInTree(tree, badNodeParent->parent, badNodeParent);
    }
    // if parent of tmpParent has 2 childs, but has in this more than 5 leafs
    else if (badNodeParent->parent->childsCnt == 2) {
      Correct2ParentsTrees(badNodeParent->parent, badNode);
      free(badNode);
    }
    // if parent of tmpParent has 3 childs
    else {
      Correct3ParentsTrees(badNodeParent->parent, badNode);
      free(badNode);
    }
  }
}

int DeleteInTTTree(ttTree_t** tree, double deleteElement) {
  ttTree_t* tmp = *tree, * tmpParent = NULL;

  if (*tree == NULL)
    return LABI_FALSE;

  // go to leaf
  while (tmp != NULL && tmp->isLeaf == 0) {
    tmpParent = tmp;

    if (tmp->childsCnt == 2) {
      if (deleteElement <= tmp->leftNum)
        tmp = tmp->left;
      else
        tmp = tmp->middle;
    }
    else {
      if (deleteElement <= tmp->leftNum)
        tmp = tmp->left;
      else if (tmp->leftNum < deleteElement && deleteElement <= tmp->rightNum)
        tmp = tmp->middle;
      else if (tmp->rightNum < deleteElement)
        tmp = tmp->right;
    }
  }
  // if this leaf not our element or this leaf is empty: clear new leaf and exit
  if (tmp == NULL || (tmp != NULL && tmp->data != deleteElement))
    return LABI_FALSE;

  // if our leaf is tree top
  if (tmpParent == NULL)
    *tree = NULL;
  // if our leaf is child of tree top
  else if (tmpParent->parent == NULL) {
    if (tmpParent->childsCnt == 2) {
      if (tmp == tmpParent->left)
        *tree = tmpParent->middle;
      else
        *tree = tmpParent->left;

      (*tree)->parent = NULL;
      free(tmpParent);
    }
    else {
      tmpParent->childsCnt = 2;
      if (tmpParent->left == tmp) {
        tmpParent->left = tmpParent->middle;
        tmpParent->middle = tmpParent->right;
      }
      else if (tmpParent->middle == tmp) {
        tmpParent->middle = tmpParent->right;
      }
      tmpParent->maxSubtreeData = tmpParent->middle->data;
      tmpParent->leftNum = tmpParent->left->data;
      tmpParent->right = NULL;
      tmpParent->rightNum = 0;

      CorrectNodePath(tmpParent);
    }
  }
  // if our leaf isn't child of tree top (our leaf's parent also has parent)
  else {
    // if parent have 3 childs
    if (tmpParent->childsCnt == 3) {
      tmpParent->childsCnt = 2;
      if (tmpParent->left == tmp) {
        tmpParent->left = tmpParent->middle;
        tmpParent->middle = tmpParent->right;
      }
      else if (tmpParent->middle == tmp) {
        tmpParent->middle = tmpParent->right;
      }
      tmpParent->maxSubtreeData = tmpParent->middle->data;
      tmpParent->leftNum = tmpParent->left->data;
      tmpParent->right = NULL;
      tmpParent->rightNum = 0;

      CorrectNodePath(tmpParent);
    }
    // if parent has 2 childs
    else {
      // rebuild tree
      if (tmpParent->parent->childsCnt == 2 && tmpParent->parent->left->childsCnt == 2 && tmpParent->parent->middle->childsCnt == 2) {
        Correct2ParentsTreesWithLowChildCnt(tmpParent->parent, tmp);
        DeleteBadNodesInTree(tree, tmpParent->parent, tmpParent);
      }
      // if parent of tmpParent has 2 childs, but has in this more than 5 leafs
      else if (tmpParent->parent->childsCnt == 2)
        Correct2ParentsTrees(tmpParent->parent, tmp);
      // if parent of tmpParent has 3 childs
      else
        Correct3ParentsTrees(tmpParent->parent, tmp);
    }
  }

  free(tmp);
  return LABI_TRUE;
}