#include <stdio.h>
#include <stdlib.h>

#include "F21.h"

#pragma warning (disable:4996)

void DestroyTree(tree_t* t) {
  if (t != NULL) {
    DestroyTree(t->left);
    DestroyTree(t->right);
    free(t);
  }
}

tree_t* AddNode(tree_t* t, int keyNew, int* flagDone) {

  if (t == NULL) {
    t = (tree_t*)malloc(sizeof(tree_t));
    if (t == NULL)
      return NULL;
    t->key = keyNew;
    t->subnodesQ = 1;
    t->left = t->right = NULL;
    t->father = NULL;
    (*flagDone) = 1;
  }
  else {
    if (keyNew < t->key) {
      t->left = AddNode(t->left, keyNew, flagDone);
      if ((*flagDone) == 1) {
        t->subnodesQ++;
        t->left->father = t;
      }
    }
    else if (keyNew > t->key) {
      t->right = AddNode(t->right, keyNew, flagDone);
      if ((*flagDone) == 1) {
        t->subnodesQ++;
        t->right->father = t;
      }
    }
    else
      (*flagDone) = 0;
  }

  return t;
}

static tree_t* _replaceNode(tree_t* from, tree_t* prev, tree_t* to) {
  tree_t* toKill;

  if (from->right != NULL) {
    toKill = _replaceNode(from->right, from, to);
    from->subnodesQ--;
    if (from->right != NULL)
      from->right->father = from;
  }
  else {
    to->key = from->key;
    toKill = from;
    if (prev->left == toKill)
      prev->left = from->left;
    else if (prev->right == toKill)
      prev->right = from->left;
  }
  return toKill;
}

tree_t* DelNode(tree_t* t, int keyNew, int* flagDone) {
  tree_t* toKill;

  if (t != NULL) {
    if (keyNew < t->key) {
      t->left = DelNode(t->left, keyNew, flagDone);
      if ((*flagDone) == 1) {
        t->subnodesQ--;
        if (t->left != NULL)
          t->left->father = t;
      }
    }
    else if (keyNew > t->key) {
      t->right = DelNode(t->right, keyNew, flagDone);
      if ((*flagDone) == 1) {
        t->subnodesQ--;
        if (t->right != NULL)
          t->right->father = t;
      }
    }
    else {
      toKill = t;
      if (t->right == NULL) {
        if (t->left != NULL)
          t->left->father = t->father;
        t = t->left;
      }
      else if (t->left == NULL) {
        if (t->right != NULL)
          t->right->father = t->father;
        t = t->right;
      }
      else {
        toKill = _replaceNode(t->left, t, t);
        t->subnodesQ--;
        if (t->left != NULL)
          t->left->father = t;
      }
      free(toKill);
      (*flagDone) = 1;
    }
  }
  else
    (*flagDone) = 0;

  return t;
}

tree_t* FindNode(tree_t* t, int key, tree_t** ans) {

  if (t == NULL)
    *ans = NULL;
  else {
    if (key < t->key)
      t->left = FindNode(t->left, key, ans);
    else if (key > t->key)
      t->right = FindNode(t->right, key, ans);
    else
      *ans = t;
  }

  return t;
}

static int _findNumberOfNode(tree_t* t, tree_t* node) {
  tree_t *tmp;
  int num = (node->left != NULL ? node->left->subnodesQ : 0) + 1;

  while (node != t){
    tmp = node->father;
    if (node == tmp->right)
      num += (tmp->left != NULL ? tmp->left->subnodesQ : 0) + 1;
    node = node->father;
  }

  return num;
}

static tree_t* _findKMin(tree_t* t, int k) {
  tree_t* ans;
  int  num;

  if (t == NULL)
    return NULL;

  if (t->left != NULL)
    num = t->left->subnodesQ + 1;
  else
    num = 1;

  if (num != k) {
    if (num > k)
      ans = _findKMin(t->left, k);
    else
      ans = _findKMin(t->right, k - num);
  }
  else
    ans = t;

  return ans;
}

tree_t* FindNodeSmallerByK(tree_t* t, int key, int k) {
  tree_t* node = NULL;
  tree_t* ans = NULL;
  int num;

  FindNode(t, key, &node);
  if (node != NULL) {
    num = _findNumberOfNode(t, node);
    ans = _findKMin(t, num - k);
  }

  return ans;
}

void Run(void) {
  tree_t* t = NULL;
  tree_t* ans = NULL;
  char act, ch;
  int key;
  int flag;
  int k = 2;

  act = getchar();
  while (act != EOF) {
    ch = getchar();
    scanf("%i", &key);
    ch = getchar();

    switch (act) {
    case 'a':
      t = AddNode(t, key, &flag);
      break;
    case 'r':
      t = DelNode(t, key, &flag);
      break;

    case 'f':
      t = FindNode(t, key, &ans);
      if (ans != NULL)
        printf("yes\n");
      else
        printf("no\n");
      break;

    case 'k':
      ans = FindNodeSmallerByK(t, key, k);  // default value of parameter k is 2. It can be changed in list of variables of this function
      if (ans == NULL)
        printf("No such node found.\n");
      else
        printf("The key of needed node is %i\n", ans->key);
      break;

    default:
      printf("Wrong input.\n");
      break;
    }

    act = getchar();
  }
  DestroyTree(t);
}