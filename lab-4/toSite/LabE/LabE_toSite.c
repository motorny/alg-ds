#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

#define TRUE 1
#define FALSE 0

typedef struct node node_t;
struct node {
  int key;
  node_t* left, * right;
};

int AddToTree(node_t **tree, int number) {
  node_t* newNode = (node_t*)malloc(sizeof(node_t));

  if (newNode == NULL)
    return FALSE;

  newNode->key = number;
  newNode->left = NULL;
  newNode->right = NULL;

  if (*tree == NULL)
    (*tree) = newNode;
  else {
    while (*tree != NULL)
      if ((*tree)->key < number)
        tree = &((*tree)->right);
      else if ((*tree)->key > number)
        tree = &((*tree)->left);
      else if ((*tree)->key == number)
        return FALSE;

    (*tree) = newNode;
  }
  return TRUE;
}

int DeleteFromTree(node_t** tree, int number) {
  node_t* elemToDel, **tmp;

  while (*tree != NULL) {
    if ((*tree)->key < number)
      tree = &((*tree)->right);
    else if ((*tree)->key > number)
      tree = &((*tree)->left);
    else {
      elemToDel = *tree;

      if ((*tree)->left == NULL && (*tree)->right == NULL)
        (*tree) = NULL;
      else if ((*tree)->left == NULL)
        (*tree) = (*tree)->right;
      else if ((*tree)->right == NULL)
        (*tree) = (*tree)->left;
      else {
        tmp = &(*tree)->left;
        while ((*tmp)->right != NULL)
          tmp = &(*tmp)->right;
        (*tree)->key = (*tmp)->key;
        elemToDel = *tmp;
        (*tmp) = (*tmp)->left;
      }

      free(elemToDel);
      return TRUE;
    }
  }
  return FALSE;
}

int FindInTree(node_t* tree, int number) {
  if (tree == NULL)
    return FALSE;
  else if (tree->key == number)
    return TRUE;
  else if (tree->key < number)
    FindInTree(tree->right, number);
  else if (tree->key > number)
    FindInTree(tree->left, number);
}

int ReadFuncAndNum(int* number) {
  char ch = getchar(), chTmp;

  if (ch == -1)
    return 0;

  scanf("%i", number);

  // to avoid conflict between 'getchar()' and 'scanf()'
  chTmp = getchar();

  if (ch == 'a')
    return 1;
  else if (ch == 'f')
    return 2;
  else if (ch == 'r')
    return 3;
  else
    return 0;
}

int main(void) {
  int number, var;
  node_t* tree = NULL;

  var = ReadFuncAndNum(&number);
  while (var) {
    if (var == 1)
      AddToTree(&tree, number);
    else if (var == 2)
      if (FindInTree(tree, number) == TRUE)
        printf("yes\n");
      else
        printf("no\n");
    else if (var == 3)
      DeleteFromTree(&tree, number);

    var = ReadFuncAndNum(&number);
  }
  return 0;
}