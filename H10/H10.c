#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

#include "H10.h"

static int _max(int a, int b) {
  return (a > b) ? a : b;
}

static int _h(AVL_t* node) {
  return (node == NULL) ? 0 : node->h;
}

static AVL_t* _newNode(int key) {
  struct AVL_t* node = (AVL_t*)malloc(sizeof(AVL_t));
  if (node == NULL)
    return node;
  node->key = key;
  node->l = NULL;
  node->r = NULL;
  node->h = 1;
  return node;
}

static AVL_t* _rRotate(AVL_t* y) {
  struct AVL_t* x = y->l;
  struct AVL_t* tmp = x->r;

  x->r = y;
  y->l = tmp;

  y->h = _max(_h(y->l), _h(y->r)) + 1;
  x->h = _max(_h(x->l), _h(x->r)) + 1;

  return x;
}

static AVL_t* _lRotate(AVL_t* x) {
  struct AVL_t* y = x->r;
  struct AVL_t* tmp = y->l;

  y->l = x;
  x->r = tmp;

  x->h = _max(_h(x->l), _h(x->r)) + 1;
  y->h = _max(_h(y->l), _h(y->r)) + 1;

  return y;
}

static int _bal(AVL_t* node) {
  return (node == NULL) ? 0 : _h(node->l) - _h(node->r);
}

AVL_t* AddKey(AVL_t* node, int key) {
  int bal;

  if (node == NULL)
    return(_newNode(key));

  if (key < node->key)
    node->l = AddKey(node->l, key);
  else if (key > node->key)
    node->r = AddKey(node->r, key);
  else
    return node;

  node->h = 1 + _max(_h(node->l), _h(node->r));
  bal = _bal(node);

  if (bal > 1 && key < node->l->key)
    return _rRotate(node);
  if (bal > 1 && key > node->l->key) {
    node->l = _lRotate(node->l);
    return _rRotate(node);
  }

  if (bal < -1 && key > node->r->key)
    return _lRotate(node);
  if (bal < -1 && key < node->r->key) {
    node->r = _rRotate(node->r);
    return _lRotate(node);
  }

  return node;
}

static AVL_t* _findMinKey(AVL_t* node) {
  struct AVL_t* cur = node;

  while (cur->l != NULL)
    cur = cur->l;

  return cur;
}

AVL_t* RemoveKey(AVL_t* node, int key) {
  int bal;

  if (node == NULL)
    return node;

  if (key < node->key)
    node->l = RemoveKey(node->l, key);
  else if (key > node->key)
    node->r = RemoveKey(node->r, key);
  else {
    if ((node->l == NULL) || (node->r == NULL)) {
      AVL_t* tmp = node->l ? node->l :
        node->r;
      if (tmp == NULL) {
        tmp = node;
        node = NULL;
      }
      else
        *node = *tmp;
      free(tmp);
    }
    else {
      AVL_t* tmp = _findMinKey(node->r);
      node->key = tmp->key;
      node->r = RemoveKey(node->r, tmp->key);
    }
  }

  if (node == NULL)
    return node;

  node->h = 1 + _max(_h(node->l), _h(node->r));
  bal = _bal(node);

  if (bal > 1 && _bal(node->l) >= 0)
    return _rRotate(node);
  if (bal > 1 && _bal(node->l) < 0) {
    node->l = _lRotate(node->l);
    return _rRotate(node);
  }

  if (bal < -1 && _bal(node->r) <= 0)
    return _lRotate(node);
  if (bal < -1 && _bal(node->r) > 0) {
    node->r = _rRotate(node->r);
    return _lRotate(node);
  }

  return node;
}

AVL_t* FindKey(AVL_t* node, int key, int* isFound) {

  if (node == NULL)
    *isFound = 0;
  else {
    if (key < node->key)
      node->l = FindKey(node->l, key, isFound);
    else if (key > node->key)
      node->r = FindKey(node->r, key, isFound);
    else
      *isFound = 1;
  }

  return node;
}

void DestroyTree(AVL_t* node) {
  if (node != NULL) {
    DestroyTree(node->l);
    DestroyTree(node->r);
    free(node);
  }
}

void Run(void) {
  AVL_t* root = NULL;
  char act, ch;
  int key;
  int isFound;

  act = getchar();
  while (act != EOF) {
    ch = getchar();
    scanf("%i", &key);
    ch = getchar();

    switch (act) {
    case 'a':
      root = AddKey(root, key);
      break;
    case 'r':
      root = RemoveKey(root, key);
      break;
    case 'f':
      FindKey(root, key, &isFound);
      if (isFound == 1)
        printf("yes\n");
      else
        printf("no\n");
      break;
    default:
      break;
    }
    act = getchar();
  }
  DestroyTree(root);
}