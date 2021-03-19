#pragma once

typedef struct node_t {
  int prior; // приоритет вершины
  int size; // размер поддерева
  int val;
  struct node_t* left;
  struct node_t* right;
} node_t;

// Получение размера поддерева
int GetSize(node_t* tree);

// Пересчёт размера поддерева
void UpdateSize(node_t* tree);

// Создание нового узла
node_t* Insert(int val);

// Объединение
node_t* Merge(node_t* tree1, node_t* tree2);

// Разделение
void Split(int val, node_t* tree, node_t** tree1, node_t** tree2, int n);

// Добавление узла
void AddNode(node_t** tree, int n, int val);

// Удаление узла
void DeleteNode(node_t** tree, int n);

// удалить элемент
void DeleteVal(node_t** tree, int val);

// Поиск узла
void IsFind(node_t* tree, int val, int* find);

// Печать дерева
void PrintTree(node_t* tree);

// Удаление дерева
void DestroyTree(node_t* tree);
