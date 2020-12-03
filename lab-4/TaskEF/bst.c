#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct node_t {
  struct node_t *left, *right, *parent;
  int key, numOfLeaves, numOfNodes;
} node_t;

typedef struct tree_t {
  node_t *root;
  int numOfNodes;
} tree_t;

tree_t * GetTree(void) {
  tree_t *t = (tree_t*)malloc(sizeof(tree_t));
  if (t == NULL)
    return NULL;
  t->numOfNodes = 0;
  t->root = NULL;
  return t;
}

static node_t * _createLeaf(int key, node_t* parent) {
  node_t *res = (node_t*)malloc(sizeof(node_t));
  if (res == NULL)
    return NULL;

  res->key = key;
  res->numOfLeaves = 0;
  res->numOfNodes = 1;
  res->parent = parent;
  res->left = NULL;
  res->right = NULL;

  return res;
}

int Insert(tree_t *t, int key) {
  node_t *n;

  if (key <= 0)
    return BST_FAIL;
  if (t == NULL)
    return BST_FAIL;
  n = t->root;
  if (n == NULL) {
    t->root = _createLeaf(key, NULL);
    if (t->root == NULL)
      return BST_FAIL;
    t->numOfNodes++;
    return BST_NODE_INSERTED;
  }

  while (1) {
    if (n->key == key)
      return BST_NODE_EXIST;
    if (n->key > key)
      if (n->left != NULL)
        n = n->left;
      else {
        n->left = _createLeaf(key, n);
        if (n->left == NULL)
          return BST_FAIL;
        while (n != NULL) {
          n->numOfNodes++;
          n = n->parent;
        }
        t->numOfNodes++;
        return BST_NODE_INSERTED;
      }
    else
      if (n->right != NULL)
        n = n->right;
      else {
        n->right = _createLeaf(key, n);
        if (n->right == NULL)
          return BST_FAIL;
        while (n != NULL) {
          n->numOfNodes++;
          n = n->parent;
        }
        t->numOfNodes++;
        return BST_NODE_INSERTED;
    }
  }
}

int Delete(tree_t *t, int key) {
  node_t *n, *nPrev = NULL;
  char side = 0;

  if (t == NULL)
    return BST_FAIL;
  n = t->root;
  if (n == NULL)
    return BST_NODE_NOT_FINDED;

  while (n != NULL) {
    if (n->key == key) {
      node_t *tmp, *nodeToInsert = NULL;
      if (n->left == NULL)
        nodeToInsert = n->right;
      else if (n->right == NULL)
        nodeToInsert = n->left;

      if (n->left == NULL || n->right == NULL) {
        if (nodeToInsert != NULL)
          nodeToInsert->parent = nPrev;
        if (side == 'r')
          nPrev->right = nodeToInsert;
        else if (side == 'l')
          nPrev->left = nodeToInsert;
        else
          t->root = nodeToInsert;
        free(n);
        while (nPrev != NULL) {
          nPrev->numOfNodes--;
          nPrev = nPrev->parent;
        }
      }
      else {
        nPrev = n;
        tmp = n->left;
        while (tmp->right != NULL) {
          tmp->numOfNodes--;
          nPrev = tmp;
          tmp = tmp->right;
        }
        n->key = tmp->key;

        if (nPrev == n)
          nPrev->left = tmp->left;
        else
          nPrev->right = tmp->left;

        while (n != NULL) {
          n->numOfNodes--;
          n = n->parent;
        }
        free(tmp);
      }
      t->numOfNodes--;

      return BST_NODE_DELETED;
    }
    nPrev = n;
    if (n->key > key) {
      n = n->left;
      side = 'l';
    }
    else {
      n = n->right;
      side = 'r';
    }
  }
  return BST_NODE_NOT_FINDED;
}

int Find(tree_t *t, int key) {
  node_t *n;

  if (t == NULL)
    return BST_FAIL;
  n = t->root;
  if (n == NULL)
    return BST_NODE_NOT_FINDED;

  while (n != NULL) {
    if (n->key == key)
      return BST_NODE_FINDED;
    if (n->key > key)
      n = n->left;
    else
      n = n->right;
  }
  return BST_NODE_NOT_FINDED;
}

static void _printNode(node_t* n, int* x, int* y, int* yMax, int matrix[], int len) {
  if (n == NULL) {
    if (*y > *yMax)
      *yMax = *y;
    return;
  }
  (*y)++;
  _printNode(n->left, x, y, yMax, matrix, len);
  (*y)--;
  matrix[*y * len + *x] = n->key;
  (*x)++;
  (*y)++;
  _printNode(n->right, x, y, yMax, matrix, len);
  (*y)--;
}

void PrintKeys(tree_t *t) {
  int i, x = 0, y = 0, yMax = 0;
  int *matrix;

  if (t == NULL)
    return;
  matrix = (int*)calloc(sizeof(int), t->numOfNodes * t->numOfNodes);
  if (matrix == NULL)
    return;
  for (i = 0; i < t->numOfNodes * t->numOfNodes; i++)
    matrix[i] = -1;

  _printNode(t->root, &x, &y, &yMax, matrix, t->numOfNodes);

  for (y = 0; y < yMax; y++) {
    for (x = 0; x < t->numOfNodes; x++)
      if (matrix[y * t->numOfNodes + x] == -1)
        printf("     ");
      else
        printf("%4i ", matrix[y * t->numOfNodes + x]);
    printf("\n");
  }

  free(matrix);
}

int _getNumOfLeaves(node_t* n) {
  if (n == NULL)
    return 0;
  if (n->left == NULL && n->right == NULL) {
    n->numOfLeaves = 0;
    return 1;
  }
  n->numOfLeaves = _getNumOfLeaves(n->left) + _getNumOfLeaves(n->right);
  return n->numOfLeaves;
}

static void _printLeaves(node_t* n, int* x, int* y, int* yMax, int matrix[], int len) {
  if (n == NULL) {
    if (*y > *yMax)
      *yMax = *y;
    return;
  }
  (*y)++;
  _printLeaves(n->left, x, y, yMax, matrix, len);
  (*y)--;
  matrix[*y * len + *x] = n->numOfLeaves;
  (*x)++;
  (*y)++;
  _printLeaves(n->right, x, y, yMax, matrix, len);
  (*y)--;
}

void PrintNumOfLeaves(tree_t *t) {
  int i, x = 0, y = 0, yMax = 0;
  int* matrix;

  if (t == NULL)
    return;
  matrix = (int*)calloc(sizeof(int), t->numOfNodes * t->numOfNodes);
  if (matrix == NULL)
    return;

  for (i = 0; i < t->numOfNodes * t->numOfNodes; i++)
    matrix[i] = -1;

  _getNumOfLeaves(t->root);
  _printLeaves(t->root, &x, &y, &yMax, matrix, t->numOfNodes);

  for (y = 0; y < yMax; y++) {
    for (x = 0; x < t->numOfNodes; x++)
      if (matrix[y * t->numOfNodes + x] == -1)
        printf("     ");
      else
        printf("%4i ", matrix[y * t->numOfNodes + x]);
    printf("\n");
  }

  free(matrix);
}

int _kMin(node_t *root, int k) {
  int r;
  if (root == NULL)
    return BST_FAIL;
  if (root->left != NULL)
    r = root->left->numOfNodes + 1;
  else
    r = 1;
  if (r == k)
    return root->key;
  if (k < r)
    return _kMin(root->left, k);
  else
    return _kMin(root->right, k - r);
}

int KeyKLess(tree_t *t, int key, int k) {
  node_t *n, *nk;
  int sum = 0;

  if (t == NULL)
    return BST_FAIL;
  n = t->root;
  if (n == NULL)
    return BST_NODE_NOT_FINDED;

  while (n != NULL && n->key != key) {
    if (n->key > key)
      n = n->left;
    else
      n = n->right;
  }
  if (n == NULL)
    return BST_NODE_NOT_FINDED;

  nk = n;

  while (nk != NULL && (nk->left != NULL ? sum + nk->left->numOfNodes < k : sum + 1 <= k)) {
    if (nk->left != NULL)
      sum += nk->left->numOfNodes + 1;
    else
      sum++;
    nk = nk->parent;
  }
  if (nk == NULL)
    return BST_FAIL;

  if (k != sum)
    if (nk->right == NULL)
      return _kMin(nk, nk->numOfNodes - k + sum);
    else
      return _kMin(nk, nk->numOfNodes - nk->right->numOfNodes - k + sum);
  return nk->key;
}

static void _nodeFree(node_t *n) {
  if (n == NULL)
    return;
  _nodeFree(n->left);
  _nodeFree(n->right);
  free(n);
}

void DeleteTree(tree_t *t) {
  if (t == NULL)
    return;
  _nodeFree(t->root);
  free(t);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
