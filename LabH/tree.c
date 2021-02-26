#include "tree.h"
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

#define STACK_SIZE 100

typedef struct node_t {
  struct node_t* left;
  struct node_t* right;
  struct node_t* prev;
  data_t data;
} node_t;

struct tree_t {
  node_t* root;
};

static node_t* Successor(node_t* node) {
  node_t* successor = node->right;
  while (successor->left) {
    successor = successor->left;
  }
  return successor;
}

static void Zig(tree_t* tree, node_t* node) {
  if (node->prev->left == node) {
    node->prev->left = node->right;
    if (node->right) {
      node->right->prev = node->prev;
    }

    node->right = node->prev;
    node->prev->prev = node;
  }
  else {
    node->prev->right = node->left;
    if (node->left) {
      node->left->prev = node->prev;
    }

    node->left = node->prev;
    node->prev->prev = node;
  }
  tree->root = node;
  node->prev = NULL;
}

static void ZigZigLeft(tree_t* tree, node_t* node) {
  node_t* father = node->prev;
  node_t* grandFather = node->prev->prev;
  node_t* greatGrandFather = grandFather->prev;

  if (greatGrandFather) {
    node->prev = greatGrandFather;
    if (greatGrandFather->left == grandFather) {
      greatGrandFather->left = node;
    }
    else {
      greatGrandFather->right = node;
    }
  }
  else {
    node->prev = NULL;
    tree->root = node;
  }

  grandFather->left = father->right;
  if (father->right) {
    father->right->prev = grandFather;
  }

  father->right = grandFather;
  grandFather->prev = father;

  father->left = node->right;
  if (node->right) {
    node->right->prev = father;
  }

  node->right = father;
  father->prev = node;
}

static void ZigZigRight(tree_t* tree, node_t* node) {
  node_t* father = node->prev;
  node_t* grandFather = node->prev->prev;
  node_t* greatGrandFather = grandFather->prev;

  if (greatGrandFather) {
    node->prev = greatGrandFather;
    if (greatGrandFather->left == grandFather) {
      greatGrandFather->left = node;
    }
    else {
      greatGrandFather->right = node;
    }
  }
  else {
    node->prev = NULL;
    tree->root = node;
  }

  grandFather->right = father->left;
  if (father->left) {
    father->left->prev = grandFather;
  }

  father->left = grandFather;
  grandFather->prev = father;

  father->right = node->left;
  if (node->left) {
    node->left->prev = father;
  }

  node->left = father;
  father->prev = node;
}

static void ZigZagLeft(tree_t* tree, node_t* node) {
  node_t* father = node->prev;
  node_t* grandFather = node->prev->prev;
  node_t* greatGrandFather = grandFather->prev;

  if (greatGrandFather) {
    node->prev = greatGrandFather;
    if (greatGrandFather->left == grandFather) {
      greatGrandFather->left = node;
    }
    else {
      greatGrandFather->right = node;
    }
  }
  else {
    node->prev = NULL;
    tree->root = node;
  }

  father->right = node->left;
  if (node->left) {
    node->left->prev = father;
  }

  node->left = father;
  father->prev = node;

  grandFather->left = node->right;
  if (node->right) {
    node->right->prev = grandFather;
  }

  node->right = grandFather;
  grandFather->prev = node;
}

static void ZigZagRight(tree_t* tree, node_t* node) {
  node_t* father = node->prev;
  node_t* grandFather = node->prev->prev;
  node_t* greatGrandFather = grandFather->prev;

  if (greatGrandFather) {
    node->prev = greatGrandFather;
    if (greatGrandFather->left == grandFather) {
      greatGrandFather->left = node;
    }
    else {
      greatGrandFather->right = node;
    }
  }
  else {
    node->prev = NULL;
    tree->root = node;
  }

  father->left = node->right;
  if (node->right) {
    node->right->prev = father;
  }

  node->right = father;
  father->prev = node;

  grandFather->right = node->left;
  if (node->left) {
    node->left->prev = grandFather;
  }

  node->left = grandFather;
  grandFather->prev = node;
}

static void Splay(tree_t* tree, node_t* node) {
  while (tree->root != node)
    if (node->prev == tree->root) {
      Zig(tree, node);
    }
    else if (node->prev->prev->left && node->prev->prev->left->left == node) {
      ZigZigLeft(tree, node);
    }
    else if (node->prev->prev->right && node->prev->prev->right->right == node) {
      ZigZigRight(tree, node);
    }
    else if (node->prev->prev->left && node->prev->prev->left->right == node){
      ZigZagLeft(tree, node);
    }
    else {
      ZigZagRight(tree, node);
    }
}

static compare_t* Compare = NULL;
void SetCompareFunc(compare_t* f) {
  Compare = f;
}

tree_t* TreeCreate() {
  tree_t* newTree = malloc(sizeof(tree_t));
  if (newTree) {
    newTree->root = NULL;
  }

  return newTree;
}

int TreeInsert(tree_t* tree, const data_t data) {
  node_t* cur = tree->root;
  node_t* prev = NULL;
  node_t* newNode;
  int goneLeft = 0;
  int resOfCompare = 0;
  if (!Compare) {
    return FAIL;
  }

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

  newNode = malloc(sizeof(node_t));
  if (!newNode) {
    return FAIL;
  }
  newNode->data = data;
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

  return SUCCESS;
}

int TreeSearch(tree_t* tree, const data_t key) {
  node_t* p = tree->root;
  if (!Compare) {
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
  if (p) {
    Splay(tree, p);
    return SUCCESS;
  }
  else {
    return FAIL;
  }
}

int TreeDelete(tree_t* tree, const data_t key) {
  node_t* cur = tree->root;
  node_t* node2del;
  node_t* node2delChild;

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
    cur->data = node2del->data;
  }
  free(node2del);

  return SUCCESS;
}

void TreeFree(tree_t* tree) {
  node_t** stack;
  int size = STACK_SIZE;
  int top = 0;
  node_t* p;
  if (!tree->root) {
    free(tree);
    return;
  }
  stack = malloc(sizeof(node_t*) * STACK_SIZE);
  stack[top] = tree->root;

  while (top >= 0) {
    p = stack[top];
    --top;
    while (p->left || p->right) {
      ++top;
      if (top == size) {
        size += STACK_SIZE;
        stack = realloc(stack, sizeof(node_t*) * size);
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
    free(p);
  }

  free(tree);
  free(stack);
}
