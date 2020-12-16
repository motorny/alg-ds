#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "E3.h"

#pragma warning (disable:4996)

void DestroyTree(tree_t* t) {
  if (t != NULL) {
    DestroyTree(t->left);
    DestroyTree(t->right);
    free(t);
  }
}

static void _updateMinAndMaxH(tree_t* t) {
  if (t->rH <= t->lH) {
    t->minH = t->rH;
    t->maxH = t->lH;
  }
  else {
    t->minH = t->lH;
    t->maxH = t->rH;
  }
}

tree_t* AddNode(tree_t* t, int keyNew, int* flagDone) {

  if (t == NULL) {
    t = (tree_t*)malloc(sizeof(tree_t));
    t->key = keyNew;
    t->lH = t->rH = 0;
    t->minH = t->maxH = 0;
    t->left = t->right = NULL;
    (*flagDone) = 1;
  }
  else {
    if (keyNew < t->key) {
      t->left = AddNode(t->left, keyNew, flagDone);
      if ((*flagDone) == 1) {
        t->lH = t->left->maxH + 1;
        _updateMinAndMaxH(t);
      }
    }
    else if (keyNew > t->key) {
      t->right = AddNode(t->right, keyNew, flagDone);
      if ((*flagDone) == 1) {
        t->rH = t->right->maxH + 1;
        _updateMinAndMaxH(t);
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
    if (from->right != NULL)
      from->rH = from->right->maxH + 1;
    else
      from->rH = 0;
    _updateMinAndMaxH(from);
  }
  else {
    to->key = from->key;
    toKill = from;
    if (prev->left == toKill) {
      prev->left = from->left;
    }
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
        if (t->left != NULL)
          t->lH = t->left->maxH + 1;
        else
          t->lH = 0;
        _updateMinAndMaxH(t);
      }
    }
    else if (keyNew > t->key) {
      t->right = DelNode(t->right, keyNew, flagDone);
      if ((*flagDone) == 1) {
        if (t->right != NULL)
          t->rH = t->right->maxH + 1;
        else
          t->rH = 0;
        _updateMinAndMaxH(t);
      }
    }
    else {
      toKill = t;
      if (t->right == NULL)
        t = t->left;
      else if (t->left == NULL)
        t = t->right;
      else {
        toKill = _replaceNode(t->left, t, t);
        if (t->left != NULL)
          t->lH = t->left->maxH + 1;
        else
          t->lH = 0;
        _updateMinAndMaxH(t);
      }
      free(toKill);
      (*flagDone) = 1;
    }
  }
  else
    (*flagDone) = 0;

  return t;
}

tree_t* FindNode(tree_t* t, int key, int* flagDone) {

  if (t == NULL)
    *flagDone = 0;
  else {
    if (key < t->key)
      t->left = FindNode(t->left, key, flagDone);
    else if (key > t->key)
      t->right = FindNode(t->right, key, flagDone);
    else
      *flagDone = 1;
  }

  return t;
}

static int _countNodes(tree_t* t) {
  int l, r;

  if (t == NULL)
    return 0;
  else {
    l = _countNodes(t->left);
    r = _countNodes(t->right);
    return (l + r + 1);
  }
}

void FillCells(tree_t* t, cell_t* a, int m, int* x, int y) {
  if (t != NULL) {
    FillCells(t->left, a, m, x, y + 1);
    a[y * m + (*x)].data = t->minH;
    a[y * m + (*x)].flagFilled = 1;
    (*x)++;
    FillCells(t->right, a, m, x, y + 1);
  }
}

void PrintTree(tree_t* t) {
  int n = (t->lH < t->rH ? t->rH : t->lH) + 1;
  int m = _countNodes(t);
  cell_t* a = (cell_t*)malloc(sizeof(cell_t) * n * m);
  int x = 0, y = 0;

  FillCells(t, a, m, &x, y);

  for (y = 0; y < n; y++) {
    for (x = 0; x < m; x++) {
      if (a[y * m + x].flagFilled == 1)
        printf("%2i", a[y * m + x].data);
      else
        printf("  ");
    }
    printf("\n");
  }

  free(a);
}

void Run(void) {
  tree_t* t = NULL;
  char act, ch;
  int key, i;
  int flag;

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
      FindNode(t, key, &flag);
      if (flag == 1)
        printf("yes\n");
      else
        printf("no\n");
      break;
    case 'p':
      if (t != NULL)
        PrintTree(t);
      break;
    default:
      break;
    }

    act = getchar();
  }
  DestroyTree(t);
}