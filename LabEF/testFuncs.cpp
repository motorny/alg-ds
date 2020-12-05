#include "pch.h"
#include <stdlib.h>
#include <math.h>

#define SUCCESS 1
#define FAIL 0

#define SPACE 10

#define STACK_SIZE 100

typedef int data_t;

typedef struct node_t {
  struct node_t* left;
  struct node_t* right;
  struct node_t* prev;
  int subTreeWidth;
  data_t data;
} node_t;

typedef struct {
  node_t* root;
} tree_t;


int Compare(int a, int b) {
  if (a < b) {
    return -1;
  }
  return a > b;
};
int WidthCounter(int a) {
  return 1;
}
int CopyData(int a) {
  return a;
}
void FreeData(int a) {};

node_t* Successor(node_t* node) {
  if (!node) {
    return NULL;
  }
  node_t* successor = node->right;
  while (successor->left) {
    successor = successor->left;
  }
  return successor;
}

tree_t* TreeCreate() {
  tree_t* newTree = (tree_t*)malloc(sizeof(tree_t));
  if (newTree) {
    newTree->root = NULL;
  }

  return newTree;
}

int CountSubtreeWidth(node_t* node) {
  if (!node) {
    return 0;
  }
  if (!node->right && !node->left) {
    node->subTreeWidth = WidthCounter(node->data);
  }
  else if (!node->right) {
    node->subTreeWidth = WidthCounter(node->data) + CountSubtreeWidth(node->left);
  }
  else if (!node->left) {
    node->subTreeWidth = WidthCounter(node->data) + CountSubtreeWidth(node->right);
  }
  else {
    node->subTreeWidth = WidthCounter(node->data) + CountSubtreeWidth(node->left) + CountSubtreeWidth(node->right);
  }

  return  node->subTreeWidth;
}

int TreeInsert(tree_t* tree, const data_t data) {
  if (!tree) {
    return FAIL;
  }
  node_t* cur = tree->root;
  node_t* prev = NULL;
  node_t* newNode;
  int goneLeft = 0;
  int resOfCompare = 0;

  while (cur) {
    prev = cur;
    resOfCompare = Compare(cur->data, data);
    if (resOfCompare > 0) {
      cur = cur->left;
      goneLeft = 1;
    }
    else if (resOfCompare < 0) {
      cur = cur->right;
      goneLeft = 0;
    }
    else {
      return FAIL;
    }
  }

  newNode = (node_t*)malloc(sizeof(node_t));
  if (!newNode) {
    return FAIL;
  }
  newNode->data = CopyData(data);
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->prev = prev;

  if (!prev) {
    tree->root = newNode;
  }
  else {
    if (goneLeft) {
      prev->left = newNode;
    }
    else {
      prev->right = newNode;
    }
  }

  CountSubtreeWidth(tree->root);

  return SUCCESS;
}

int TreeSearch(const tree_t* tree, const data_t key) {
  node_t* p = tree->root;
  if (!tree) {
    return FAIL;
  }
  while (p && Compare(p->data, key) != 0) {
    if (Compare(p->data, key) > 0) {
      p = p->left;
    }
    else {
      p = p->right;
    }
  }
  return p ? SUCCESS : FAIL;
}

int TreeDelete(tree_t* tree, const data_t key) {
  node_t* cur = tree->root;
  node_t* node2del;
  node_t* node2delChild;
  if (!tree) {
    return FAIL;
  }

  while (cur && Compare(cur->data, key) != 0) {
    if (Compare(cur->data, key) > 0) {
      cur = cur->left;
    }
    else {
      cur = cur->right;
    }
  }
  if (!cur) {
    return FAIL;
  }

  if (!cur->left || !cur->right) {
    node2del = cur;
  }
  else {
    node2del = Successor(cur);
  }
  node2delChild = node2del->left ? node2del->left : node2del->right;

  if (node2delChild) {
    node2delChild->prev = node2del->prev;
  }
  if (!node2del->prev) {
    tree->root = node2delChild;
  }
  else if (node2del == node2del->prev->left) {
    node2del->prev->left = node2delChild;
  }
  else {
    node2del->prev->right = node2delChild;
  }
  if (node2del != cur) {
    cur->data = CopyData(node2del->data);
  }
  FreeData(node2del->data);
  free(node2del);

  CountSubtreeWidth(tree->root);

  return SUCCESS;
}

void TreeFree(tree_t* tree) {
  node_t** stack;
  node_t** tmp;
  int size = STACK_SIZE;
  int top = 0;
  node_t* p;
  if (!tree) {
    return;
  }
  if (!tree->root) {
    free(tree);
    return;
  }
  stack = (node_t**)malloc(sizeof(node_t*) * STACK_SIZE);
  if (!stack) {
    return;
  }
  stack[top] = tree->root;

  while (top >= 0) {
    p = stack[top];
    --top;
    while (p->left || p->right) {
      ++top;
      if (top == size) {
        size += STACK_SIZE;
        tmp = (node_t**)realloc(stack, sizeof(node_t*) * size);
        if (!tmp) {
          free(stack);
          return;
        }
        else {
          stack = tmp;
        }
      }
      stack[top] = p;
      p = p->left ? p->left : p->right;
    }
    if (top >= 0) {
      if (stack[top]->left == p) {
        stack[top]->left = NULL;
      }
      else {
        stack[top]->right = NULL;
      }
    }
    FreeData(p->data);
    free(p);
  }

  free(tree);
  free(stack);
}