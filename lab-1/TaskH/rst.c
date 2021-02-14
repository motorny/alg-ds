#ifdef cplusplus
extren "C" {
#endif

#include <stdlib.h>
#include "rst.h"

rst_t * GetTree(void) {
  rst_t *res = (rst_t *)malloc(sizeof(rst_t));
  if (res == NULL)
    return NULL;
  res->root = NULL;
  return res;
}

static void _deleteNodes(node_t *node) {
  if (node == NULL)
    return;
  _deleteNodes(node->left);
  _deleteNodes(node->right);
  free(node);
}

void DeleteTree(rst_t *tree) {
  if (tree != NULL) {
    _deleteNodes(tree->root);
    free(tree);
  }
}

static void _balanceNew(rst_t *tree, node_t *start) {
  if (start == NULL)
    return;
  while (start->parent != NULL && start->prior < start->parent->prior) {
    node_t
      *parent = start->parent,
      *left = start->left,
      *right = start->right;

    start->parent = parent->parent;
    parent->parent = start;
    if (parent->left == start) {
      parent->left = right;
      start->right = parent;
      if (right != NULL)
        right->parent = parent;
    }
    else {
      parent->right = left;
      start->left = parent;
      if (left != NULL)
        left->parent = parent;
    }
    if (start->parent != NULL)
      if (start->parent->left == parent)
        start->parent->left = start;
      else
        start->parent->right = start;
  }
  if (start->parent == NULL)
    tree->root = start;
}

int Insert(rst_t *tree, int key) {
  node_t *cur, *prev;
  enum {
    ROT_LEFT,
    ROT_RIGHT,
    ROT_NOT_DEFINED
  } rot = ROT_NOT_DEFINED;

  if (tree == NULL)
    return RST_FIND_NULL_TREE;

  cur = tree->root;
  prev = NULL;

  while (cur != NULL && cur->key != key) {
    prev = cur;
    if (key < cur->key) {
      cur = cur->left;
      rot = ROT_LEFT;
    }
    else {
      cur = cur->right;
      rot = ROT_RIGHT;
    }
  }

  if (cur == NULL) {
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    if (newNode == NULL)
      return RST_INSERT_FAILED_ALLOC;

    newNode->key = key;
    newNode->prior = rand();
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = prev;

    if (prev == NULL) {
      tree->root = newNode;
      return RST_INSERT_NODE_ADDED;
    }
    if (rot == ROT_LEFT)
      prev->left = newNode;
    else
      prev->right = newNode;
    _balanceNew(tree, newNode);
    return RST_INSERT_NODE_ADDED;
  }
  return RST_INSERT_NODE_ALREADY_EXIST;
}

static void _leftRotate(rst_t *tree, node_t *downNode) {
  if (tree == NULL || downNode == NULL)
    return;
  node_t
    *parent = downNode->parent,
    *newTop = downNode->right,
    *newRight = newTop->left;
  if (parent == NULL)
    tree->root = newTop;
  else
    if (parent->left == downNode)
      parent->left = newTop;
    else
      parent->right = newTop;
  newTop->parent = parent;
  newTop->left = downNode;
  downNode->parent = newTop;
  downNode->right = newRight;
  if (newRight != NULL)
    newRight->parent = downNode;
}

static void _rightRotate(rst_t *tree, node_t *downNode) {
  if (tree == NULL || downNode == NULL)
    return;
  node_t
    *parent = downNode->parent,
    *newTop = downNode->left,
    *newLeft = newTop->right;
  if (parent == NULL)
    tree->root = newTop;
  else
    if (parent->left == downNode)
      parent->left = newTop;
    else
      parent->right = newTop;
  newTop->parent = parent;
  newTop->right = downNode;
  downNode->parent = newTop;
  downNode->left = newLeft;
  if (newLeft != NULL)
    newLeft->parent = downNode;
}

int Delete(rst_t *tree, int key) {
  node_t *cur, *prev;
  enum {
    ROT_LEFT,
    ROT_RIGHT,
    ROT_NOT_DEFINED
  } rot = ROT_NOT_DEFINED;

  if (tree == NULL)
    return RST_DELETE_NULL_TREE;

  cur = tree->root;
  prev = NULL;

  while (cur != NULL && cur->key != key) {
    prev = cur;
    if (key < cur->key) {
      cur = cur->left;
      rot = ROT_LEFT;
    }
    else {
      cur = cur->right;
      rot = ROT_RIGHT;
    }
  }

  if (cur != NULL) {
    while (cur->left != NULL || cur->right != NULL)
      if (cur->left == NULL)
        _leftRotate(tree, cur);
      else if (cur->right == NULL)
        _rightRotate(tree, cur);
      else if (cur->left->prior > cur->right->prior)
        _leftRotate(tree, cur);
      else
        _rightRotate(tree, cur);

    prev = cur->parent;
    if (prev == NULL)
      tree->root = NULL;
    else
      if (prev->left == cur)
        prev->left = NULL;
      else
        prev->right = NULL;
    free(cur);
    return RST_DELETE_NODE_DELETED;
  }
  return RST_DELETE_NODE_DOESNT_EXIST;
}

int Find(rst_t *tree, int key) {
  node_t *cur;

  if (tree == NULL)
    return RST_FIND_NULL_TREE;

  cur = tree->root;

  while (cur != NULL && cur->key != key)
    if (key < cur->key)
      cur = cur->left;
    else
      cur = cur->right;

  if (cur == NULL)
    return RST_FIND_NODE_DOESNT_EXIST;
  return RST_FIND_NODE_EXIST;
}


#ifdef cplusplus
}
#endif