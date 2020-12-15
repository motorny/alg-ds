#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

int GetWidthList(int data) {
  int len = 0;
  if (data < 0)
    len++;
  data = abs(data);
  while (data > 0) {
    data /= 10;
    len++;
  }
  return len;
} 

int AddNode(vertex_t** cur, int const data, int const key){
  //если поддерево пустое, записываем туда вершину
  if (*cur == NULL) {
    vertex_t *add = (vertex_t*)malloc(sizeof(vertex_t));
    if (!add) {
      return 0;
    }
    add->data = data;
    add->key = key;
    add->left = NULL;
    add->parent = NULL;
    add->right = NULL;
    add->width = GetWidthList(data);
    *cur = add;
    return 1;
  }
  if (key > (*cur)->key){
    if (AddNode(&((*cur)->right), data, key)) {
      (*cur)->right->parent = (*cur);
      return 1;
    }
    else
      return 0;
  }
  if (key < (*cur)->key){
    if (AddNode(&((*cur)->left),data, key)) {
      (*cur)->left->parent = (*cur);
      return 1;
    }
    else
      return 0;
  }
  return 0;
}

int DeleteVertex( vertex_t** cur, int key){
  if (cur == NULL || (*cur) == NULL)
    return 0;
  if (key > (*cur)->key){
    return DeleteVertex(&(*cur)->right, key);
  }
  if (key < (*cur)->key){
    return DeleteVertex(&(*cur)->left, key);
  }
  vertex_t* elem = *cur;
  vertex_t** tmp;
  if ((*cur)->left == NULL && (*cur)->right == NULL)
    *cur = NULL;
  else if ((*cur)->right == NULL)
    *cur = (*cur)->left;
  else if ((*cur)->left == NULL)
    *cur = (*cur)->right;
  else{
    tmp = &(*cur)->left;
    while ((*tmp)->right != NULL)
      tmp = &(*tmp)->right;
    (*cur)->key = (*tmp)->key;
    elem = *tmp;
    (*tmp) = (*tmp)->left;
  }
  free(elem);
  return 1;
}


int AddVertex(tree_t* tree, int key, int data)
{
  if (!tree)
    return 0;
  return AddNode(&tree->root, data,key);
}


vertex_t* FindVertex(tree_t tree, int key)
{
  vertex_t* cur = tree.root;
  while (cur){
    if (cur == NULL)
      break;
    else if (key > cur->key) {
      cur = cur->right;
    }
    else if (key < cur->key) {
      cur = cur->left;
    }
    else
      return cur;
  }
  return cur;
}



int UpdateWidth(vertex_t* t)
{
  //если пусто
  if (t == NULL) {
    return 0;
  }
  //если лист
  if (!t->left && !t->right) {
    return t->width = GetWidthList(t->key);
  }
  //если нет левого поддерева
  if (!t->left) {
    return t->width = GetWidthList(t->key) + UpdateWidth(t->right) + 1;
  }
  //если нет правого поддерева
  if (!t->right) {
    return t->width = GetWidthList(t->key) + UpdateWidth(t->left) + 1;
  }
  //если есть 2 сына
  return t->width = GetWidthList(t->key) + UpdateWidth(t->left) + UpdateWidth(t->right) + 2;
}


void LevelPrint(vertex_t* t) {
  if (t) {
    if (t->left) {
      printf("key:   %i      -->     %i\n", t->key, t->left->key);
      printf("data:  %i              %i\n", t->data, t->left->width);
      printf("widtn: %i              %i\n\n", t->width, t->left->width);
      LevelPrint(t->left);
    }
    if (t->right) {
      printf("key:   %i      -->     %i\n", t->key, t->right->key);
      printf("data:  %i              %i\n", t->data, t->right->width);
      printf("widtn: %i              %i\n\n", t->width, t->right->width);
      LevelPrint(t->right);
    }
  }
}

void PrintTree(tree_t t)
{
  int level = 0, isEnd = 0;
  vertex_t* cur;
  if (!t.root)
    return;
  cur = t.root;
  UpdateWidth(t.root);
  LevelPrint(cur);
}

void FreeVertex(vertex_t* cur)
{
  if (cur == NULL)
    return;
  FreeVertex(cur->left);
  FreeVertex(cur->right);
  free(cur);
}

void TreeFree(tree_t* tree)
{
  if (tree == NULL)
    return;
  FreeVertex(tree->root);
  tree->root = NULL;
}

//for tokens
/*
  int main() {
  int key = 0;
  tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
  if (!tree)
    return 0;
  tree->root = NULL;
  
  char oper = getchar();
  while (oper != EOF) {
    scanf("%i", &key);

    switch (oper) {
    case 'a':
      AddVertex(tree, key, 1);
      break;

    case 'r':
      DeleteVertex(&(tree->root), key);
      break;

    case 'f':
      if (FindVertex(*tree, key))
        printf("yes\n");
      else
        printf("no\n");
      break;

    default:
      return 0;

    }
    oper = getchar();
    if (oper == '\r')
      oper = getchar();
    if (oper == '\n')
      oper = getchar();
  }
//  TreePrint(*tree);
  TreeFree(tree);
  return 0;
}
*/
