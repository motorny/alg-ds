#pragma warning (disable: 4996)
#include"E1.h"
#include<stdio.h>
#include<stdlib.h>

static int countHeight(tree_t* tree) {
  int heightLeft = 0, heightRight = 0;
  if (tree == NULL)
    return 0;
  else {
    if (tree->left == NULL && tree->right == NULL)
      return 0;
    else {
      heightLeft = countHeight(tree->left);
      heightRight = countHeight(tree->right);
    if (heightLeft > heightRight)
      return heightLeft + 1;
    else
      return heightRight + 1;
    }
  }
}
static tree_t* replaceHeight(tree_t* tree){
  int heightLeft = 0, heightRight = 0;
  if (tree != NULL){
    if (tree->left != NULL) {
      heightLeft = countHeight(tree->left);
      tree->left = replaceHeight(tree->left);
    }
    if (tree->right != NULL) {
      heightRight = countHeight(tree->right);
      tree->right = replaceHeight(tree->right);
    }
    tree->height = abs(heightLeft - heightRight);
  }
  return tree;
}
tree_t* addTree(tree_t* tree, int key) {
  if (tree == NULL) {
    tree = (tree_t*)malloc(sizeof(tree_t));
    if (tree == NULL)
      return NULL;
    tree->key = key;
    tree->height = 0;
    tree->left = NULL;
    tree->right = NULL;
  }
  else {
    if (key < tree->key)
      tree->left = addTree(tree->left, key);
    else {
      if (key > tree->key)
        tree->right = addTree(tree->right, key);
    }
  }
  tree = replaceHeight(tree);
  return tree;
}
static tree_t* minimumTree(tree_t* tree) {
  if (tree->left == NULL)
    return tree;
  return minimumTree(tree->left);
}
tree_t* delTree(tree_t* tree, int key) {
  if (tree == NULL)
    return tree;
  if (key < tree->key)
    tree->left = delTree(tree->left, key);
  else {
    if (key > tree->key)
      tree->right = delTree(tree->right, key);
    else {
        if (tree->left != NULL && tree->right != NULL) {
            tree->key = minimumTree(tree->right)->key;
            tree->right = delTree(tree->right, tree->key);
        }
        else {
          if (tree->left != NULL)
            tree = tree->left;
          else
            if (tree->right != NULL)
              tree = tree->right;
            else {
              tree_t* tmp = tree;
              tree = NULL;
              free(tmp);
            }
        }
    }
  }
  tree = replaceHeight(tree);
  return tree;
}
int findTree(tree_t* tree, int key) {
  tree_t* tmp = tree;
  while (tmp != NULL) {
    if (key > tmp->key)
      tmp = tmp->right;
    else
      if (key < tmp->key)
        tmp = tmp->left;
      else
        return FOUND;
  }
  return NOTFOUND;
}
void printTree(tree_t* tree, int index) {
  if (tree != NULL) {
    printf("level:%i key:%i difference in height:%i\n", index, tree->key, tree->height);
    printTree(tree->left, index + 1);
    printTree(tree->right, index + 1);
  }
}
void freeTree(tree_t* tree) {
  if (tree != NULL) {
    freeTree(tree->right);
    freeTree(tree->left);
    free(tree);
  }
}
tree_t* readString(tree_t* tree) {
  char regimeWork;
  int key, avoidError;

  while (1) {
    regimeWork = getchar();
    if (regimeWork == EOF)
      return tree;
    while (regimeWork == '\0' || regimeWork == '\n' || isspace(regimeWork) != 0)
      avoidError = getchar();
    avoidError = scanf("%i", &key);
    switch (regimeWork) {
      case('a'):
        tree = addTree(tree, key);
        break;
      case('r'):
        tree = delTree(tree, key);
        break;
      case('f'):
        if (findTree(tree, key) == FOUND)
          printf("yes\n");
        else
          printf("no\n");
        break;
      default:
        break;
    }
    avoidError = getchar();
  }
}
