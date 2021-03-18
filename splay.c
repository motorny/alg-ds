#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

tree_t* createTree() {
  tree_t* newTree = (tree_t*)malloc(sizeof(tree_t));
  if (newTree)
    newTree->root = NULL;
  return newTree;
}

void left_rotate(tree_t* root, node_t* x) {
  node_t* y = x->right;
  x->right = y->left;
  if (y->left != NULL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL) {
    root->root = y;
  }
  else if (x == x->parent->left) {
    x->parent->left = y;
  }
  else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void right_rotate(tree_t* root, node_t* x) {
  node_t* y = x->left;
  x->left = y->right;
  if (y->right != NULL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL) {
    root->root = y;
  }
  else if (x == x->parent->right) {
    x->parent->right = y;
  }
  else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void splay(tree_t* root, node_t* node) {
  while (node->parent != NULL) {
    if (node->parent == root->root) {
      if (node == node->parent->left) {
        right_rotate(root, node->parent);
      }
      else {
        left_rotate(root, node->parent);
      }
    }
    else {
      node_t* p = node->parent;
      node_t* g = p->parent;

      if (node->parent->left == node && p->parent->left == p) {
        right_rotate(root, g);
        right_rotate(root, p);
      }
      else if (node->parent->right == node && p->parent->right == p) {
        left_rotate(root, g);
        left_rotate(root, p);
      }
      else if (node->parent->right == node && p->parent->left == p) {
        left_rotate(root, p);
        right_rotate(root, g);
      }
      else if (node->parent->left == node && p->parent->right == p) {
        right_rotate(root, p);
        left_rotate(root, g);
      }
    }
  }
}

int searchElem(tree_t* root, int value) {
  node_t* node = root->root;
  if (node == NULL)
    return 0;
  while (node && node->value != value) {
    if (node->value > value)
      node = node->left;
    else
      node = node->right;
  }
  if (node) {
    splay(root, node);
    return TRUE;
  }
  else
    return FALSE;
}

int addElem(tree_t* root, int value) {
  if (root == NULL) {
    return FALSE;
  }
  node_t* curr_node = root->root;
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  node_t* parent = NULL;
  int leftSubtree = 0;

  if (new_node == NULL)
    return FALSE;
  while (curr_node != NULL) {
    parent = curr_node;
    if (curr_node->value < value) {
      curr_node = curr_node->right;
      leftSubtree = 0;
    }
    else if (curr_node->value > value) {
      curr_node = curr_node->left;
      leftSubtree = 1;
    }
    else
      return FALSE;
  }

  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = parent;

  if (!parent) {
    root->root = new_node;
  }
  else {
    if (leftSubtree) {
      parent->left = new_node;
    }
    else {
      parent->right = new_node;
    }
  }
  return TRUE;
}

static node_t* child(node_t* node) {
  node_t* child = node->right;
  while (child->left) {
    child = child->left;
  }
  return child;
}

int deleteElem(tree_t* root, int value) {
  node_t* curr_node = root->root,
    * delete_node, * delete_child;
  if (root == NULL) {
    return FALSE;
  }
  while (curr_node && curr_node->value != value) {
    if (curr_node->value > value)
      curr_node = curr_node->left;
    else
      curr_node = curr_node->right;
  }
  if (curr_node == NULL)
    return FALSE;

  if (!(curr_node->left) || !(curr_node->right))
    delete_node = curr_node;
  else
    delete_node = child(curr_node);

  delete_child = delete_node->left ? delete_node->left : delete_node->right;

  if (delete_child) {
    delete_child->parent = delete_node->parent;
  }
  if (!delete_node->parent) {
    root->root = delete_child;
  }
  else if (delete_node == delete_node->parent->left) {
    delete_node->parent->left = delete_child;
  }
  else {
    delete_node->parent->right = delete_child;
  }
  if (delete_node != curr_node) {
    curr_node->value = delete_node->value;
  }

  return TRUE;
}

void deleteTree(tree_t* root) {
  if (root->root == NULL)
     return;
  else
    root->root = NULL;
}

