
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"
#pragma warning(disable:4996)

unsigned int Height(node_t* p) {
  if (p != NULL)
	return p->height;
  else return 0;
}

void FixHeight(node_t* p) {
  int left = Height(p->left);
  int right = Height(p->right);
  if (left > right)
	p->height = left + 1;
  else p->height = right + 1;
}

int GetBalancedFactor(node_t* tree) {
  return Height(tree->right) - Height(tree->left);
}

node_t* RotateRight(node_t* t) {
  node_t* p = t->left;
  t->left = p->right;
  p->right = t;
  FixHeight(t);
  FixHeight(p);
  return p;
}

node_t* RotateLeft(node_t* t) {
  node_t* p = t->right;
  t->right = p->left;
  p->left = t;
  FixHeight(t);
  FixHeight(p);
  return p;
}

node_t* Balance(node_t* p) {
  FixHeight(p);
  if (GetBalancedFactor(p) == 2) {
	if (GetBalancedFactor(p->right) < 0)
	  p->right = RotateRight(p->right);
	return RotateLeft(p);
  }
  if (GetBalancedFactor(p) == -2) {
	if (GetBalancedFactor(p->left) > 0)
	  p->left = RotateLeft(p->left);
	return RotateRight(p);
  }
  return p;
}

node_t* FindVertex(node_t* p, int k) {
  if (p == NULL)
	return NULL;
  while (p != NULL) {
	if (p->key == k)
	  return p;
	else if (p->key < k) {
	  p = p->right;
	}
	else {
	  p = p->left;
	}
  }
  return NULL;
}

node_t* AddVertex(node_t* p, int k) {
  if (p == NULL) {
	p = (node_t*)malloc(sizeof(node_t));
    if (!p)
      return NULL;
	p->key = k;
	p->left = 0;
	p->right = 0;
	p->height = 1;
	return p;
  }
  if (k < p->key)
	p->left = AddVertex(p->left, k);
  if (k > p->key)
	p->right = AddVertex(p->right, k);
  return Balance(p);
}

node_t* FindMin(node_t* p) {
  if (p->left != NULL)
	return FindMin(p->left);
  else return p;
}

node_t* RemoveMin(node_t* p) {
  if (p->left == 0)
	return p->right;
  p->left = RemoveMin(p->left);
  return Balance(p);
}

node_t* DeleteVertex(node_t* p, int k) {
  if (p == NULL)
	return NULL;
  if (k < p->key)
	p->left = DeleteVertex(p->left, k);
  if (k > p->key)
	p->right = DeleteVertex(p->right, k);
  if (k == p->key) {
	node_t* q = p->left;
	node_t* r = p->right;
	free(p);
	if (r == NULL)
	  return q;
	node_t* min = FindMin(r);
	min->right = RemoveMin(r);
	min->left = q;
	return Balance(min);
  }
  return Balance(p);
}

void DestroyTree(node_t* p) {
  if (p == NULL)
	return;
  DestroyTree(p->left);
  DestroyTree(p->right);
  free(p);
}

/*
int main() {

  node_t* root = NULL;
  int c = getchar(), number;

  while (c != EOF) {
    scanf("%d", &number);
    switch (c) {
    case 'a':
      root = AddVertex(root, number);
      break;
    case 'f':
      printf(FindVertex(root, number) == NULL ? "no\n" : "yes\n");
      break;
    case 'r':
      root = DeleteVertex(root, number);
      break;
    default:
      return 0;
    }

    if ((c = getchar()) == '\n')
      c = getchar();
  }
  DestroyTree(root);

  return 0;
}
*/