#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void ClearTree(tree_t* tree) {
  tree_t rightTree, leftTree;
  tree->root->data = 0;

  if (tree->root->left != NULL) {
    leftTree.root = tree->root->left;
    ClearTree(&leftTree);
  }

  if (tree->root->right != NULL) {
    rightTree.root = tree->root->right;
    ClearTree(&rightTree);
  }

  free(tree->root);
}

node_t* CreateNode(int key) {
  node_t* node;
  node = malloc(sizeof(node_t));
  if (node != NULL) {
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->p = NULL;
    node->data = 0;
    node->numOfNode = 1;
    return node;
  }
  return NULL;
}

node_t* Find(tree_t* tree, int key) {
  node_t* node = tree->root;
  while (node != NULL && node->key != key) {
    if (node->key > key) {
      node = node->left;
    }
    else {
      node = node->right;
    }
  }
  return node;
}

int Add(tree_t* tree, int key) {
  node_t* parentNewNode = NULL, * son = tree->root;
  node_t* newNode;
  newNode = CreateNode(key);
  if (newNode == NULL) {
    return 1;
  }
  while (son != NULL) {
    parentNewNode = son;
    if (newNode->key < son->key) {
      son = son->left;
    }
    else if (newNode->key > son->key) {
      son = son->right;
    }
    else {
      son = NULL;
    }
  }
  newNode->p = parentNewNode;
  if (parentNewNode == NULL) {
    tree->root = newNode;
  }
  else if (newNode->key < parentNewNode->key) {
    parentNewNode->left = newNode;
    while (parentNewNode != NULL) {
      parentNewNode->numOfNode++;
      parentNewNode = parentNewNode->p;
    }
  }
  else if (newNode->key > parentNewNode->key) {
    parentNewNode->right = newNode;
    while (parentNewNode != NULL) {
      parentNewNode->numOfNode++;
      parentNewNode = parentNewNode->p;
    }
  }
  return 0;
}

void Transplant(tree_t* tree, node_t* u, node_t* v) {
  if (u->p == NULL) {
    tree->root = v;
  }
  else if (u == u->p->left) {
    u->p->left = v;
  }
  else {
    u->p->right = v;
  }
  if (v != NULL) {
    v->p = u->p;
  }
}

void Delete(tree_t* tree, int key) {
  node_t* node = Find(tree, key), * rightMin, * parent;
  if (node == NULL) {
    return;
  }
  if (node->left == NULL) {
    Transplant(tree, node, node->right);
    parent = node->p;

  }
  else if (node->right == NULL) {
    Transplant(tree, node, node->left);
    parent = node->p;
  }
  else {
    rightMin = node->right;
    while (rightMin->left != NULL) {
      rightMin = rightMin->left;
    }
    parent = rightMin->p;
    if (rightMin->p != node) {
      Transplant(tree, rightMin, rightMin->right);
      rightMin->right = node->right;
      rightMin->right->p = rightMin;
    }
    Transplant(tree, node, rightMin);
    rightMin->left = node->left;
    rightMin->left->p = rightMin;
    rightMin->numOfNode = node->numOfNode;
  }
  while (parent != NULL) {
    parent->numOfNode--;
    parent = parent->p;
  }
  free(node);
}

void CountLeaves(tree_t* tree) {
  tree_t rightTree, leftTree;
  tree->root->data = 0;

  if (tree->root->left != NULL) {
    leftTree.root = tree->root->left;
    CountLeaves(&leftTree);
    if (leftTree.root->data == 0) {
      tree->root->data += 1;
    }
    else {
      tree->root->data += leftTree.root->data;
    }
  }

  if (tree->root->right != NULL) {
    rightTree.root = tree->root->right;
    CountLeaves(&rightTree);
    if (rightTree.root->data == 0) {
      tree->root->data += 1;
    }
    else {
      tree->root->data += rightTree.root->data;
    }
  }
}

void functionForPrint(node_t* node, int* x, int y, data_t matrix[], int width) {
  if (node->left != NULL) {
    y++;
    functionForPrint(node->left, x, y, matrix, width);
    y--;
  }
  matrix[y * width + *x] = node->data;
  (*x)++;
  if (node->right != NULL) {
    y++;
    functionForPrint(node->right, x, y, matrix, width);
    y--;
  }
}

void Print(tree_t* tree) {
  int x = 0;
  int i, j, k;
  data_t* matrix;
  matrix = (data_t*)malloc(sizeof(data_t) * tree->root->numOfNode * tree->root->numOfNode);
  if (matrix == NULL) {
    return;
  }
  for (i = 0; i < tree->root->numOfNode * tree->root->numOfNode; i++) {
    matrix[i] = -1;
  }
  functionForPrint(tree->root, &x, 0, matrix, tree->root->numOfNode);
  for (i = 0; i < tree->root->numOfNode * tree->root->numOfNode; i++) {
    k = 0;
    for (j = i; j < i + tree->root->numOfNode; j++) {
      if (matrix[j] == -1) {
        k++;
      }
    }
    if (k != tree->root->numOfNode) {
      if (matrix[i] != -1) {
        printf("%d", matrix[i]);
      }
      else {
        printf(" ");
      }
      if ((i + 1) % (int)tree->root->numOfNode == 0) {
        printf("\n");
      }
    }
  }
  free(matrix);
}

int FindNumber(tree_t* tree, int key) {
  node_t* node = Find(tree, key);
  int number = 0;
  if (node != NULL) {
    number = number + (node->numOfNode - (node->right != NULL ? node->right->numOfNode : 0));
    while (node->p != NULL) {
      if (node->p->right == node) {
        number = number + (node->p->numOfNode - (node->p->right != NULL ? node->p->right->numOfNode : 0));
      }
      node = node->p;
    }
  }
  return number;
}

int FindKMin(tree_t* tree, int k) {
  int key = 0;
  tree_t nextTree;

  if (tree->root->numOfNode - (tree->root->right != NULL ? tree->root->right->numOfNode : 0) == k) {
    return tree->root->key;
  }
  else if (tree->root->numOfNode - (tree->root->right != NULL ? tree->root->right->numOfNode : 0) < k) {
    if (tree->root->right != NULL) {
      nextTree.root = tree->root->right;
      key = FindKMin(&nextTree, k - (tree->root->left != NULL ? tree->root->left->numOfNode : 0) - 1);
    }
    else {
      return -1;
    }
  }
  else {
    if (tree->root->left != NULL) {
      nextTree.root = tree->root->left;
      key = FindKMin(&nextTree, k);
    }
    else {
      return 0;
    }
  }
  return key;
}

int FindShiftK(tree_t* tree, int k, int key) {
  return FindKMin(tree, (FindNumber(tree, key) - k));
}

/*
a 18
a 10
a 20
a 5
a 14
a 19
a 24
a 2
a 7
a 12
a 16
a 22
a 26
a 1
a 3
a 6
a 8
a 11
a 13
a 15
a 17
a 21
a 23
a 25
a 27*/