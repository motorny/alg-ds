#include "tree.h"

int AddToTree(node_t** tree, node_t* father, int key) {
  node_t* newNode = (node_t*)malloc(sizeof(node_t));

  if (newNode == NULL)
    return FALSE;

  if (*tree == NULL) {
    newNode->numberOfNodes = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = key;
    newNode->father = father;
    (*tree) = newNode;
  }
  else {
    if (key < (*tree)->key) {
      if (AddToTree(&((*tree)->left), *tree, key))
        (*tree)->numberOfNodes += 1;
    }
    else if (key > (*tree)->key) {
      if (AddToTree(&((*tree)->right), *tree, key))
        (*tree)->numberOfNodes += 1;
    }
    else
      return FALSE;
  }
  return TRUE;
}

static int Size(node_t* node) {
  if (node == NULL || node->left == NULL)
    return 0;
  return node->left->numberOfNodes;
}

static node_t* FindNodeInTree(node_t* tree, int key) {
  if (tree == NULL)
    return NULL;
  if (tree->key == key)
    return tree;
  else if (tree->key < key)
    return FindNodeInTree(tree->right, key);
  else if (tree->key > key)
    return FindNodeInTree(tree->left, key);
}

// return index of node from 1 to nodes count
int Number(node_t* tree, node_t* t, char isMain) {
  node_t* f;
  int r = Size(t);

  while (t->father != NULL) {
    f = t->father;
    if (t == f->right) {
      r += Number(tree, f, 0) + 1;
      break;
    }
    t = t->father;
  }

  if (isMain)
    r++;

  return r;
}

// return node with index from 1 to nodes count
static node_t* GetKLow(node_t* tree, int k) {
  int r;

  if (tree->left) {
    r = tree->left->numberOfNodes + 1;
  }
  else
    r = 1;

  if (r != k) {
    if (k < r)
      tree = GetKLow(tree->left, k);
    else
      tree = GetKLow(tree->right, k - r);
  }

  return tree;
}

node_t* FindKLowerTree(node_t* tree, int key, int k) {
  int currentNodeK;

  node_t* currentNode = FindNodeInTree(tree, key);
  if (currentNode == NULL)
    return NULL;

  currentNodeK = Number(tree, currentNode, 1);
  if (currentNodeK - k <= 0 || currentNodeK - k > tree->numberOfNodes)
    return NULL;

  return GetKLow(tree, currentNodeK - k);
}

static void DeleteFromTree(node_t** tree) {
  node_t* elemToDel, ** tmp;

  elemToDel = *tree;

  if ((*tree)->left == NULL && (*tree)->right == NULL)
    (*tree) = NULL;
  else if ((*tree)->left == NULL)
    (*tree) = (*tree)->right;
  else if ((*tree)->right == NULL)
    (*tree) = (*tree)->left;
  else {
    tmp = &(*tree)->left;
    while ((*tmp)->right != NULL)
      tmp = &(*tmp)->right;
    (*tree)->key = (*tmp)->key;
    elemToDel = *tmp;
    (*tmp) = (*tmp)->left;
  }

  free(elemToDel);
}

void ClearTree(node_t** tree) {
  while ((*tree) != NULL)
    DeleteFromTree(tree);
}
