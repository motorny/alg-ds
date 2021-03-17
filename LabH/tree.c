#include"tree.h"
#pragma warning(disable:4996)
void  PrintTree(Treap* T) {
  printf("x->%i y->%i \n", T->x, T->y);
  if (T->left) {
    PrintTree(T->left);
  }
  if (T->right) {
    PrintTree(T->right);
  }
}

Treap* GetNodeByValue(Treap* root, int value) {
  while (root) {
    if (root->x > value) {
      root = root->left;
      continue;
    }
    else if (root->x < value) {
      root = root->right;
      continue;
    }
    return root;
  }
  return NULL;
}

void GetTreeFromConsole(Treap** root) {
  int value;

  char buffer = getchar();
  while (buffer != EOF) {
    scanf("%d", &value);
    if (buffer == 'a') {
      Add(root, value);
    }
    else if (buffer == 'r') {
      Remove(root, value);
    }
    else if (buffer == 'f') {
      Treap* checkNode = GetNodeByValue(*root, value);
      if (checkNode != ERRORNULL) {
        printf("yes\n");
      }
      else {
        printf("no\n");
      }
    }
    else {
      printf("Incorrect input");
      return;
    }
    buffer = getchar();
    if (buffer == '\r' || buffer == '\n')
      buffer = getchar();
  }
  return;
}

void DestroyTree(Treap** root) {
  if (*root) {
    DestroyTree(&((*root)->left));
    DestroyTree(&((*root)->right));
    free(*root);
    *root = NULL;
  }
}