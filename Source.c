#pragma warning (disable:4996)
#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE 
{
  int leftValue;
  int rightValue;
  int maxSon;
  struct NODE* left;
  struct NODE* middle;
  struct NODE* right;
  struct NODE* left1;
  struct NODE* right1;
} NODE;

void Unite(NODE* left, NODE* middle, NODE* right)
{

  if (left != NULL)
    left->right1 = middle;

  middle->left1 = left;
  middle->right1 = right;

  if (right != NULL)
    right->left1 = middle;
}

void Separate(NODE* left, NODE* middle, NODE* right) 
{
  if (left != NULL)
    left->right1 = right;
  if (right != NULL)
    right->left1 = left;
}

NODE* AddNode(int val) 
{
  NODE* node = (NODE*)malloc(sizeof(NODE));
  if (node != NULL) 
  {
    node->left = NULL;
    node->right = NULL;
    node->middle = NULL;
    node->leftValue = val;
    node->rightValue = -1;
    node->left1 = NULL;
    node->right1 = NULL;
    node->maxSon = val;
  }
  return node;
}

void DeleteNode(NODE* node)
{

  if (node != NULL) {
    node->left1 = NULL;
    node->right1 = NULL;
    node->left = NULL;
    node->middle = NULL;
    node->right = NULL;
    node->leftValue = -1;
    node->rightValue = -1;
    node->maxSon = -1;
    free(node);
  }
}

void DestroyTree(NODE* tree)
{

  if (tree != NULL) 
  {
    DestroyTree(tree->left);
    DestroyTree(tree->middle);
    DestroyTree(tree->right);
    DeleteNode(tree);
  }
}

NODE* Update(NODE* tree, NODE* left, NODE* middle, NODE* right) 
{

  if (tree != NULL) 
  {
    tree->left = left;
    tree->leftValue = (tree->left == NULL ? -1 : tree->left->maxSon);
    tree->middle = middle;
    tree->rightValue = (tree->middle == NULL ? -1 : tree->middle->maxSon);
    tree->right = right;
    tree->maxSon = (tree->right == NULL ? tree->middle == NULL ? tree->left->maxSon : -1 : tree->right->maxSon);
  }
  return tree;
}

NODE* Split(NODE* A, NODE* node, NODE* B, NODE* del, NODE* a, NODE* b, NODE* c, NODE* d)
{

  A = Update(A == NULL ? AddNode(-1) : A, a, NULL, b);
  B = Update(B == NULL ? AddNode(-1) : B, c, NULL, d);
  node = Update(node == NULL ? AddNode(-1) : node, A, NULL, B);
  DeleteNode(del);
  return node;
}

int Has2Sons(NODE* node)
{

  return node != NULL && node->left != NULL && node->middle == NULL && node->right != NULL;
}

NODE* Merge(NODE* tree, NODE* left, NODE* middle, NODE* right, NODE* del) 
{

  if (Has2Sons(left) && Has2Sons(middle) && Has2Sons(right)) 
  {
    left = Update(left, left->left, left->right, middle->left);
    right = Update(right, middle->right, right->left, right->right);
    tree = Update(tree, left, NULL, right);
    DeleteNode(middle);
  }
  else
    tree = Update(tree, left, middle, right);
  DeleteNode(del);
  return tree;
}

int Has3Sons(NODE* node)
{
  return node != NULL && node->left != NULL && node->middle != NULL && node->right != NULL;
}

NODE* Balance(NODE* tree, NODE* a, NODE* b, NODE* c, NODE* d, NODE* toFree)
{
  if (Has2Sons(a) && Has2Sons(b) && Has2Sons(c) && tree->right == d)
  {
    toFree = Merge(toFree, a, b, c, NULL);
    return Merge(tree, toFree->left, toFree->right, d, toFree);
  }
  else if (Has2Sons(b) && Has2Sons(c) && Has2Sons(d)) 
  {
    toFree = Merge(toFree, b, c, d, NULL);
    return Merge(tree, a, toFree->left, toFree->right, toFree);
  }
  else if (Has3Sons(c) && Has2Sons(d)) 
  {
    a = Merge(a, a->left, a->right, b->left, NULL);
    b = Merge(b, b->right, c->left, c->middle, NULL);
    c = Merge(c, c->right, d->left, d->right, d);
    return Merge(tree, a, b, c, toFree);
  }
  else if (Has3Sons(b) && Has2Sons(a)) 
  {
    d = Merge(d, c->right, d->left, d->right, NULL);
    c = Merge(c, b->middle, b->right, c->left, NULL);
    b = Merge(b, a->left, a->right, b->left, a);
    return Merge(tree, b, c, d, toFree);
  }
  return Split(tree->left == a ? NULL : toFree, tree->middle == b || tree->middle == c ? NULL : toFree, tree->right == d ? NULL : toFree, tree, a, b, c, d);
}

int Check2(NODE* node)
{

  return node != NULL && node->leftValue == node->maxSon;
}

NODE* Insert(NODE* tree, int val)
{

  if (tree == NULL) 
  {
    NODE* node = AddNode(val);
    NODE* tmp = AddNode(val);
    node->left = tmp;
    return node;
  }
  NODE* node = AddNode(val);
  if (val < tree->leftValue) 
  {
    Unite(tree->left->left1, node, tree->left);
    return Check2(tree) ? Update(tree, node, NULL, tree->left) :
      Has2Sons(tree) ? Merge(tree, node, tree->left, tree->right, NULL) : Split(NULL, NULL, NULL, tree, node, tree->left, tree->middle, tree->right);
  }
  else if (val > tree->maxSon) 
  {
    if (Check2(tree)) 
    {
      Unite(tree->left, node, tree->left->right1);
      return Update(tree, tree->left, NULL, node);
    }
    Unite(tree->right, node, tree->right->right1);
    return Has2Sons(tree) ? Merge(tree, tree->left, tree->right, node, NULL) : Split(NULL, NULL, NULL, tree, tree->left, tree->middle, tree->right, node);
  }
  else if (Has2Sons(tree) && val > tree->leftValue && val < tree->maxSon)
  {
    Unite(tree->left, node, tree->right);
    return Merge(tree, tree->left, node, tree->right, NULL);
  }
  else if (Has3Sons(tree)) 
  {
    if (val < tree->rightValue && val > tree->leftValue) 
    {
      Unite(tree->left, node, tree->middle);
      return Split(NULL, NULL, NULL, tree, tree->left, node, tree->middle, tree->right);
    }

    else if (val < tree->maxSon && val > tree->rightValue) 
    {
      Unite(tree->middle, node, tree->right);
      return Split(NULL, NULL, NULL, tree, tree->left, tree->middle, node, tree->right);
    }
  }
  return tree;
}

int Check1(NODE* node) 
{

  return node != NULL && (node->left != NULL && node->left->left == NULL || node->right != NULL && node->right->left == NULL ||
    node->middle != NULL && node->middle->left == NULL) || node == NULL;
}

NODE* InsertNode(NODE* tree, int val) 
{

  if (Check1(tree))
    return Insert(tree, val);
  NODE* node;
  if (val < tree->leftValue) 
  {
    node = InsertNode(tree->left, val);
    if (node != tree->left) 
    {
      if (Has2Sons(tree))
        return Merge(tree, node->left, node->right, tree->right, node);
      return Balance(tree, node->left, node->right, tree->middle, tree->right, node);
    }
  }
  else if (Has3Sons(tree) && val < tree->rightValue && val > tree->leftValue) 
  {
    node = InsertNode(tree->middle, val);
    if (node != tree->middle)
      return Balance(tree, tree->left, node->left, node->right, tree->right, node);
  }
  else if (val > (Has2Sons(tree) ? tree->leftValue : tree->rightValue)) 
  {
    node = InsertNode(tree->right, val);

    if (tree->right != node)
    {
      if (Has2Sons(tree))
        return Merge(tree, tree->left, node->left, node->right, node);
      return Balance(tree, tree->left, tree->middle, node->left, node->right, node);
    }
  }
  return Update(tree, tree->left, tree->middle, tree->right);
}

NODE* Delete1(NODE* tree, int val) 
{

  if (tree == NULL || Check2(tree) && tree->leftValue == val) 
  {
    DestroyTree(tree);
    return NULL;
  }

  if (val == tree->leftValue)
  {
    Separate(tree->left->left1, tree->left, tree->left->right1);
    if (Has2Sons(tree))
      return Merge(tree, tree->right, NULL, NULL, tree->left);
    return Merge(tree, tree->middle, NULL, tree->right, tree->left);
  }
  else if (val == tree->maxSon) 
  {
    Separate(tree->right->left1, tree->right, tree->right->right1);
    return Merge(tree, tree->left, NULL, tree->middle, tree->right);
  }
  else if (Has3Sons(tree) && val == tree->rightValue) 
  {
    Separate(tree->middle->left1, tree->middle, tree->middle->right1);
    return Merge(tree, tree->left, NULL, tree->right, tree->middle);
  }

  return tree;
}

NODE* Delete2(NODE* tree, NODE* left, NODE* middle, NODE* right) 
{

  if (Check2(left)) 
  {
    if (Has2Sons(middle)) 
    {
      left = Merge(left, left->left, middle->left, middle->right, middle);
      return Update(tree, left, NULL, right);
    }

    middle = Split(left, NULL, middle, NULL, left->left, middle->left, middle->middle, middle->right);
    return Merge(tree, middle->left, middle->right, right, middle);
  }
  else if (Check2(middle)) 
  {
    if (Has2Sons(left))
    {
      middle = Merge(middle, left->left, left->right, middle->left, left);
      return Update(tree, middle, NULL, right);
    }

    else if (Has2Sons(right)) 
    {
      middle = Merge(middle, middle->left, right->left, right->right, right);
      return Update(tree, left, NULL, middle);
    }

    left = Split(left, NULL, middle, NULL, left->left, left->middle, left->right, middle->left);
    return Merge(tree, left->left, left->right, right, left);
  }

  else if (Check2(right))
  {
    if (Has2Sons(middle)) 
    {
      right = Merge(right, middle->left, middle->right, right->left, middle);
      return Update(tree, left, NULL, right);
    }

    middle = Split(middle, NULL, right, NULL, middle->left, middle->middle, middle->right, right->left);
    return Merge(tree, left, middle->left, middle->right, middle);
  }

  return Update(tree, left, middle, right);
}

NODE* Delete(NODE* tree, int val)
{

  if (Check1(tree))
    return Delete1(tree, val);
  NODE* node = NULL;
  if (val <= tree->leftValue) 
  {
    node = Delete(tree->left, val);
    if (Check2(node)) 
    {
      if (Has2Sons(tree)) 
      {
        if (Has2Sons(tree->right)) 
        {
          node->left = Merge(tree, node->left, tree->right->left, tree->right->right, tree->right);
          return node;
        }
        return Split(node, tree, tree->right, NULL, node->left, tree->right->left, tree->right->middle, tree->right->right);
      }
      return Delete2(tree, node, tree->middle, tree->right);
    }
  }
  else if (Has3Sons(tree) && val <= tree->rightValue && val > tree->leftValue)
  {
    node = Delete(tree->middle, val);
    if (Check2(node))
      return Delete2(tree, tree->left, node, tree->right);
  }
  else if (val > Has3Sons(tree) ? tree->rightValue : tree->leftValue && val <= tree->maxSon) 
  {
    node = Delete(tree->right, val);
    if (Check2(node)) {
      if (Has2Sons(tree)) 
      {
        if (Has2Sons(tree->left)) 
        {
          node->left = Merge(tree, tree->left->left, tree->left->right, node->left, tree->left);
          return node;
        }
        return Split(tree->left, tree, node, NULL, tree->left->left, tree->left->middle, tree->left->right, node->left);
      }
      return Delete2(tree, tree->left, tree->middle, node);
    }
  }
  return Merge(tree, tree->left, tree->middle, tree->right, NULL);
}

NODE* DeleteFromTree(NODE* tree, int val) 
{

  tree = Delete(tree, val);
  if (Check2(tree) && !Check1(tree))
  {
    NODE* node = tree->left;
    DeleteNode(tree);
    return node;
  }
  return tree;
}

NODE* FindVal(NODE* tree, int val)
{

  if (tree != NULL) 
  {
    if (tree->left == NULL && tree->right == NULL && tree->middle == NULL)
      return val == tree->leftValue ? tree : NULL;
    else if (val <= tree->leftValue)
      return FindVal(tree->left, val);
    else if (tree->middle != NULL && val <= tree->rightValue && val > tree->leftValue)
      return FindVal(tree->middle, val);
    return FindVal(tree->right, val);
  }
  return NULL;
}

void PrintTree(NODE* tree) 
{

  if (tree == NULL)
    return;
  while (!Check1(tree))
    tree = tree->left;
  if (tree != NULL) 
  {
    tree = tree->left;
    do {
      printf("%d ", tree->leftValue);
    } while ((tree = tree->right1) != NULL);
  }
}



int main(void) 
{
  NODE* tree = NULL;
  int command, key;

  command = getchar();
  while (command != EOF)
  {
    scanf("%d", &key);
    switch (command)
    {
    case 'a':
      tree = InsertNode(tree, key);
      break;
    case 'f':
      if (FindVal(tree, key))
        printf("yes\n");
      else
        printf("no\n");
      break;
    case 'r':
      tree = DeleteFromTree(tree, key);
      break;
    default:
      DestroyTree(tree);
      return 0;
    }
    command = getchar();
    if (command == '\n')
      command = getchar();
  }
  DestroyTree(tree);



  return 0;


}