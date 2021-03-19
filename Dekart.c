#include <stdio.h>                                              
#include <stdlib.h>
#include "Dekart.h"

// Получение размера поддерева
int GetSize(node_t* tree) {

  if (tree == NULL)
    return 0;
  return tree->size;
}

// Пересчёт размера поддерева
void UpdateSize(node_t* tree) {

  if (tree == NULL)
    return;
  tree->size = 1 + GetSize(tree->left) + GetSize(tree->right);
}

// Создание нового узла
node_t* Insert(int val) {

  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  if (new_node == NULL)
    return NULL;
  new_node->prior = rand();
  new_node->size = 1;
  new_node->val = val;
  new_node->left = new_node->right = NULL;
  return new_node;
}

// Объединение
node_t* Merge(node_t* tree1, node_t* tree2) {

  if (tree1 == NULL) {
    UpdateSize(tree2);
    return tree2;
  }
  else if (tree2 == NULL) {
    UpdateSize(tree1);
    return tree1;
  }
  else if (tree1->prior > tree2->prior) {
    tree1->right = Merge(tree1->right, tree2);
    UpdateSize(tree1);
    return tree1;
  }
  else {
    tree2->left = Merge(tree1, tree2->left);
    UpdateSize(tree2);
    return tree2;
  }
}

// Разделение
void Split(int val, node_t* tree, node_t** tree1, node_t** tree2, int n) {

  if (tree == NULL) {
    *tree1 = *tree2 = NULL;
    return;
  }
  if (val <= GetSize(tree->left) + n) {
    Split(val, tree->left, tree1, &(tree->left), n);
    *tree2 = tree;
  }
  else {
    Split(val, tree->right, &(tree->right), tree2, n + 1 + GetSize(tree->left));
    *tree1 = tree;
  }
  UpdateSize(tree);
}

// Добавление узла
void AddNode(node_t** tree, int n, int val) {

  node_t* new_tree = Insert(val);
  node_t* tree1 = NULL;
  node_t* tree2 = NULL;
  if (n < 0 || new_tree == NULL)
    return;
  Split(n, *tree, &tree1, &tree2, 0);
  *tree = Merge(Merge(tree1, new_tree), tree2);
}

// Удаление узла
void DeleteNode(node_t** tree, int n) {

  node_t* tree1 = NULL;
  node_t* tree2 = NULL;
  node_t* tree3 = NULL;
  node_t* tree4 = NULL;
  if (n < 0)
    return;
  Split(n, *tree, &tree1, &tree2, 0);
  Split(1, tree2, &tree3, &tree4, 0);
  if (tree3) 
    free(tree3);
  *tree = Merge(tree1, tree4);
}

// удалить элемент
void DeleteVal(node_t** tree, int val) {

  if (*tree == NULL)
    return;
  if ((*tree)->val == val) {
    node_t* tree1 = (*tree)->left;
    node_t* tree2 = (*tree)->right;
    free(*tree);
    *tree = Merge(tree1, tree2);
    return;
  }
  DeleteVal(val, &((*tree)->left));
  DeleteVal(val, &((*tree)->right));
}

// Поиск узла
void IsFind(node_t* tree, int val, int* indicator) {

  if (tree == NULL)
    return;
  if (tree->val == val) 
    *indicator = 1;
  IsFind(tree->left, val, indicator);
  IsFind(tree->right, val, indicator);
}

// Печать дерева
void PrintTree(node_t* tree) {

  if (tree == NULL)
    return;
  PrintTree(tree->left);
  printf("%i ", tree->val);
  PrintTree(tree->right);
}

// Удаление дерева
void DestroyTree(node_t* tree) {

  if (tree) {
    DestroyTree(tree->left);
    DestroyTree(tree->right);
    free(tree);
  }
}