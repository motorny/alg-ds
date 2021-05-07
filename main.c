#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct treap_t{
  int val;
  int prior;
  int size;
  struct treap_t* left;
  struct treap_t* right;
} treap_t;



int Read(int* num) {
  char ch = (char)getchar();

  if (ch == EOF)
    return 0;

  scanf("%i", num);
  getchar();

  switch (ch) {
  case 'a':
    return 1;
  case 'f':
    return 2;
  case 'r':
    return 3;
  default:
    return 0;
  }
}


int Size(treap_t* tree) {
  if (tree == NULL)
    return 0;

  return tree->size;
}


void NewSize(treap_t* tree) {
  if (tree == NULL)
    return;

  tree->size = 1 + Size(tree->left) + Size(tree->right);
}


treap_t* Merge(treap_t* left_tree, treap_t* right_tree) {

  if (!left_tree) {
    NewSize(right_tree);
    return right_tree;
  }

  else if (!right_tree) {
    NewSize(left_tree);
    return left_tree;
  }

  else if (left_tree->prior > right_tree->prior) {
    left_tree->right = Merge(left_tree->right, right_tree);
    NewSize(left_tree);
    return left_tree;
  }

  else {
    right_tree->left = Merge(left_tree, right_tree->left);
    NewSize(right_tree);
    return right_tree;
  }
}


void Split(int key, treap_t* tree, treap_t** left_tree, treap_t** right_tree, int add) {

  if (!tree) {
    *left_tree = *right_tree = NULL;
    return;
  }

  if (key <= Size(tree->left) + add) {
    Split(key, tree->left, left_tree, &(tree->left), add);
    *right_tree = tree;
  }

  else {
    Split(key, tree->right, &(tree->right), right_tree, add + 1 + Size(tree->left));
    *left_tree = tree;
  }
  NewSize(tree);
}


void* Insert(int val, int key, treap_t** tree) {

  treap_t* head = NULL, *tail = NULL;

  treap_t* new_tree = (treap_t*)malloc(sizeof(treap_t));
  if (!new_tree)
    return;

  new_tree->left = NULL;
  new_tree->right = NULL;
  new_tree->val = val;
  new_tree->prior = rand();
  new_tree->size = 1;
  
//  if (key < 0 || !new_tree)
//    return;

  Split(key, *tree, &head, &tail, 0);
  *tree = Merge(Merge(head, new_tree), tail);
}



void Finding(int val, treap_t* tree, int* flag) {

  if (!tree)
    return;

  if (tree->val == val)
    *flag = 1;
  Finding(val, tree->left, flag);
  Finding(val, tree->right, flag);
}


void DeleteVal(treap_t** tree, int val) {
  treap_t* left_tree, * right_tree;

  if (!(*tree))
    return;

  if ((*tree)->val == val) {

    left_tree = (*tree)->left;
    right_tree = (*tree)->right;
    free(*tree);

    *tree = Merge(left_tree, right_tree);
    return;
  }

  DeleteVal(&((*tree)->left), val);
  DeleteVal(&((*tree)->right), val);
}


void FreeTree(treap_t* tree) {

  if (tree) {
    FreeTree((tree)->left);
    FreeTree((tree)->right);

    free(tree);
    tree = NULL;
  }
}



int main() {

  int command, val, flag;
  treap_t* tree = NULL;

  command = Read(&val);

  while (command) {

    switch (command) {
    case 1:
      Insert(val, Size(tree), &tree);
      break;
    case 2:
      flag = 0;
      Finding(val, tree, &flag);
      if (flag == 1)
        printf("yes\n");
      else
        printf("no\n");
      break;
    case 3:
      DeleteVal(&tree, val);
      break;
    }

    command = Read(&val);
  }

  FreeTree(tree);
	return 0;
}