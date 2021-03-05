#include <stdio.h>

#include "23plus_trees.h"

#pragma warning (disable: 4996)

static int CheckNodeSort(ttTree_t* node) {
  if (node->left->childsCnt == 2) {
    if (node->left->middle->data >= node->middle->left->data)
      return LABI_FALSE;
  }
  else
    if (node->left->right->data >= node->middle->left->data)
      return LABI_FALSE;

  if (node->childsCnt == 3) {
    if (node->middle->childsCnt == 2) {
      if (node->middle->middle->data >= node->right->left->data)
        return LABI_FALSE;
    }
    else
      if (node->middle->right->data >= node->right->left->data)
        return LABI_FALSE;
  }
}

int CheckTree(ttTree_t* tree, ttTree_t* treeParent) {
  if (tree == NULL)
    return LABI_TRUE;

  if (tree->parent != treeParent)
    return LABI_FALSE;

  if (tree->isLeaf == 1) {
    if (tree->parent != NULL) {
      ttTree_t* tmpParent = tree->parent;
      if (!(tmpParent->childsCnt == 2 && tmpParent->left->data < tmpParent->middle->data) &&
        !(tmpParent->childsCnt == 3 && tmpParent->left->data < tmpParent->middle->data && tmpParent->middle->data < tmpParent->right->data))
        return LABI_FALSE;
      else if (tmpParent->parent != NULL)
        return CheckNodeSort(tmpParent->parent);
      else
        return LABI_TRUE;
    }
    else
      return LABI_TRUE;
  }
  else if ((tree->childsCnt == 3 && tree->right == NULL) || ((tree->childsCnt == 2 && (tree->right != NULL || tree->rightNum != 0))) ||
    (tree->leftNum == tree->rightNum && tree->leftNum != 0) ||
    (tree->childsCnt == 2 && (tree->leftNum != tree->left->maxSubtreeData || tree->maxSubtreeData != tree->middle->maxSubtreeData)) ||
    (tree->childsCnt == 3 && (tree->leftNum != tree->left->maxSubtreeData || tree->rightNum != tree->middle->maxSubtreeData || tree->maxSubtreeData != tree->right->maxSubtreeData)) ||
    (tree->childsCnt == 2 && (tree->leftNum >= tree->maxSubtreeData)) ||
    (tree->childsCnt == 3 && (tree->leftNum >= tree->rightNum || tree->rightNum >= tree->maxSubtreeData)))
    return LABI_FALSE;
  else if (tree->childsCnt == 3) {
    int res1 = CheckTree(tree->left, tree),
      res2 = CheckTree(tree->middle, tree),
      res3 = CheckTree(tree->right, tree);
    if (res1 * res2 * res3 == 0)
      return LABI_FALSE;
    return LABI_TRUE;
  }
  else if (tree->childsCnt == 2) {
    int res1 = CheckTree(tree->left, tree),
      res2 = CheckTree(tree->middle, tree);

    if (res1 * res2 == 0)
      return LABI_FALSE;
    return LABI_TRUE;
  }

  return LABI_TRUE;
}

int ReadFuncAndNum(double* data) {
  char ch = getchar(), chTmp;

  if (ch == -1)
    return LABI_FALSE;

  scanf("%lf", data);

  // to avoid conflict between 'getchar()' and 'scanf()'
  chTmp = getchar();

  if (ch == 'a')
    return LABI_ADD;
  else if (ch == 'f')
    return LABI_FIND;
  else if (ch == 'r')
    return LABI_REMOVE;
  else
    return LABI_FALSE;
}

int main(void) {
  double data;
  int var, i = 0, res, delRes = 0, delay = 8;
  ttTree_t* tree1 = NULL, * tree2 = NULL, * tree3 = NULL;

  AddToTTTree(&tree1, 10);
  AddToTTTree(&tree1, 20);
  AddToTTTree(&tree1, 30);
  AddToTTTree(&tree1, 15);
  AddToTTTree(&tree1, 12);
  AddToTTTree(&tree1, 11);

  SplitTTTree(tree1, &tree2, &tree3, 15);
  if (CheckTree(tree2, NULL) == LABI_FALSE)
    printf("STRUCT ERROR - 2\n");
  if (CheckTree(tree3, NULL) == LABI_FALSE)
    printf("STRUCT ERROR - 3\n");

  /*while (i < 200) {
    res = rand() % 3;
    AddToTTTree(&tree1, (double)(i * res % delay));
    AddToTTTree(&tree2, delay + (double)(i * res % 3));
    i++;
  }

  UnionTTTree(&tree3, tree2, tree1);
  if (CheckTree(tree3, NULL) == LABI_FALSE)
    printf("STRUCT ERROR\n");

  /*while (i < 999999999) {
    res = rand() % 3;
    if (res == 0) {
      if (i == 688)
        printf("%i\n", i);
      AddToTTTree(&tree1, (double)(i % 64));
    }
    else if (res == 1)
      SearchInTTTree(tree1, (double)(i % 64));
    else if (res == 2) {
      if (i == 668)
        printf("%i\n", i);
      delRes = DeleteInTTTree(&tree1, (double)(i % 64));
      if (delRes == LABI_TRUE)
        printf("%i - yes\n", i);
      else
        printf("%i - no\n", i);

      if (delRes == LABI_TRUE && SearchInTTTree(tree1, (double)(i % 64)) == LABI_TRUE)
        printf("%i - DELETE ERROR\n", i);
    }
    if (CheckTree(tree1, NULL) == LABI_FALSE)
      printf("%i - STRUCT ERROR\n", i);
    i++;
  }*/

  /*
  var = ReadFuncAndNum(&data);
  while (var) {
    if (var == LABI_ADD)
      AddToTTTree(&tree1, data);
    else if (var == LABI_FIND) {
      if (SearchInTTTree(tree1, data) == LABI_TRUE)
        printf("yes\n");
      else
        printf("no\n");
    }
    else if (var == LABI_REMOVE)
      DeleteInTTTree(&tree1, data);

    var = ReadFuncAndNum(&data);
  } */

  return 0;
}