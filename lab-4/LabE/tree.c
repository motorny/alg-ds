#include <stdio.h>
#include <string.h>
#include "tree.h"

#pragma warning(disable: 4996)
#define STR_INPUT 10000

static int ParseStr(node_t** tree, char *str, int pos, int bracketsCnt) {
  int i = pos, iNode = 0, res;
  char emptyStr[MAX_STR] = "\0", wasLeft = 0, wasRight = 0;
  node_t* newNode = (node_t*)malloc(sizeof(node_t));
  // check for 'malloc' error
  if (newNode == NULL)
    return FALSE;
  // clear new node
  strncpy(newNode->keyStr, emptyStr, MAX_STR);
  newNode->left = newNode->right = NULL;
  // analyze the string
  while (str[i] != 0) {
    // if new child
    if (str[i] == '(') {
      bracketsCnt++;
      // create left child
      if (wasLeft == 0) {
        res = ParseStr(&(newNode->left), str, i + 1, bracketsCnt);
        if (res == FALSE) {
          free(newNode);
          return FALSE;
        }
        i = res;
        wasLeft = 1;
      }
      // create right child
      else if (wasRight == 0) {
        res = ParseStr(&(newNode->right), str, i + 1, bracketsCnt);
        if (res == FALSE) {
          free(newNode);
          return FALSE;
        }
        i = res;
        wasRight = 1;
      }
      // too many childs for 1 parent node
      else {
        free(newNode);
        return FALSE;
      }
    }
    // end of reading node
    else if (str[i] == ')') {
      bracketsCnt--;
      if (bracketsCnt < 0) {
        free(newNode);
        return FALSE;
      }
      if (wasLeft == 1 && wasRight == 1) {
        free(newNode);
        return FALSE;
      }
      (newNode->keyStr)[iNode] = 0;
      if (strcmp(newNode->keyStr, emptyStr) == 0) {
        *tree = NULL;
        free(newNode);
      }
      else
        *tree = newNode;
      return i;
    }
    // unexpected symbols
    else if (i >= 1 && str[i - 1] == ')' && str[i] != '(') {
      free(newNode);
      return FALSE;
    }
    else {
      if (iNode < MAX_STR - 1)
        (newNode->keyStr)[iNode++] = str[i];
    }
    i++;
  }
  // this mean, that there is no ')' which must exist
  if (str[i] == 0 && pos != 0) {
    free(newNode);
    return FALSE;
  }
  *tree = newNode;
  return i;
}

int ReadTreeFromFile(node_t** tree, char* filename) {
  char str[STR_INPUT] = "\0";
  int res;
  FILE* F = fopen(filename, "rt");

  *tree = NULL;
  if (F == NULL)
    return FALSE;

  fgets(str, STR_INPUT, F);
  res = ParseStr(tree, str, 0, 0);

  if (res == FALSE) {
    *tree = NULL;
    return FALSE;
  }

  fclose(F);
  return TRUE;
}

void PrintTree(node_t* tree) {
  if (tree == NULL)
    return;

  if (tree->left == NULL && tree->right != NULL) {
    printf("%s()(%s)\n", tree->keyStr, tree->right->keyStr);
    PrintTree(tree->right);
  }
  if (tree->left != NULL && tree->right == NULL) {
    printf("%s(%s)()\n", tree->keyStr, tree->left->keyStr);
    PrintTree(tree->left);
  }
  if (tree->left == NULL && tree->right == NULL)
    printf("%s()()\n", tree->keyStr);
  if (tree->left != NULL && tree->right != NULL) {
    printf("%s(%s)(%s)\n", tree->keyStr, tree->left->keyStr, tree->right->keyStr);
    PrintTree(tree->left);
    PrintTree(tree->right);
  }
}

static void DeleteFromTree(node_t** tree) {
  node_t* elemToDel, ** tmp;

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
    strncpy((*tree)->keyStr, (*tmp)->keyStr, MAX_STR);
    elemToDel = *tmp;
    (*tmp) = (*tmp)->left;
  }

  free(elemToDel);
}

void ClearTree(node_t** tree) {
  while ((*tree) != NULL)
    DeleteFromTree(tree);
}
