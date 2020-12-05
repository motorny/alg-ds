#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SUCCESS 1
#define FAIL 0

#define SPACE 10

#define STACK_SIZE 100

typedef struct node_t {
  struct node_t* left;
  struct node_t* right;
  struct node_t* prev;
  int subTreeWidth;
  data_t data;
} node_t;

struct tree_t {
  node_t* root;
};

static node_t* Successor(node_t* node) {
  if (!node) {
    return NULL;
  }
  node_t* successor = node->right;
  while (successor->left) {
    successor = successor->left;
  }
  return successor;
}

static compare_t* Compare = NULL;
void SetCompareFunc(compare_t* f) {
  Compare = f;
}

static printData_t* PrintData = NULL;
void SetPrintDataFunc(printData_t* f) {
  PrintData = f;
}

static dataWidthCounter_t* WidthCounter = NULL;
void SetDataWidthCounter(dataWidthCounter_t* f) {
  WidthCounter = f;
}

static copyFunc_t* CopyData = NULL;
void SetDataCopyFunc(copyFunc_t* f) {
  CopyData = f;
}

static freeFunc_t* FreeData = NULL;
void SetFreeDataFunc(freeFunc_t* f) {
  FreeData = f;
}

tree_t* TreeCreate() {
  tree_t* newTree = malloc(sizeof(tree_t));
  if (newTree) {
    newTree->root = NULL;
  }

  return newTree;
}

static int CountSubtreeWidth(node_t* node) {
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
  if (!Compare || !CopyData) {
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
#ifdef LabE
  CountSubtreeWidth(tree->root);
#endif

  return SUCCESS;
}

int TreeSearch(const tree_t* tree, const data_t key) {
  node_t* p = tree->root;
  if (!tree) {
    return FAIL;
  }
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
  if (FreeData) {
    FreeData(node2del->data);
  }
  free(node2del);

#ifdef LabE
  CountSubtreeWidth(tree->root);
#endif

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
  stack = malloc(sizeof(node_t*) * STACK_SIZE);
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
        tmp = realloc(stack, sizeof(node_t*) * size);
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
    if (FreeData) {
      FreeData(p->data);
    }
    free(p);
  }

  free(tree);
  free(stack);
}

static void PrintSubtree(node_t* node, int space) {
  int i;
  if (!node) {
    return;
  }
  space += SPACE;
  PrintSubtree(node->right, space);
  printf("\n");
  for (i = 0; i < space; ++i) {
    printf(" ");
  }
  PrintData(node->data);
  printf("\n");
#ifdef LabE
  for (i = 0; i < space; ++i) {
    printf(" ");
  }
  printf("%i\n", node->subTreeWidth);
#endif
  PrintSubtree(node->left, space);
  }

void TreePrint(tree_t* tree) {
  if (!tree || !PrintData)
    return;
  PrintSubtree(tree->root, 0);
}

#ifdef LabF
void FindIntersect(tree_t* tree, interval_t inter) {
  node_t* p = tree->root;
  node_t* stack[STACK_SIZE];
  int top = 0;
  stack[top] = tree->root;
  printf("This interval insect with:\n");
  while (top >= 0) {
    p = stack[top];
    --top;
    if (p) {
      if (p->data.right > inter.left && p->data.left < p->data.right) {
        printf("%lf %lf\n", p->data.left, p->data.right);
      }
      ++top;
      stack[top] = p->left;
      ++top;
      stack[top] = p->right;
    }
  }
}

#endif