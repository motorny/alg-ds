#pragma once

typedef struct node_t {
  int prior; // ��������� �������
  int size; // ������ ���������
  int val;
  struct node_t* left;
  struct node_t* right;
} node_t;

// ��������� ������� ���������
int GetSize(node_t* tree);

// �������� ������� ���������
void UpdateSize(node_t* tree);

// �������� ������ ����
node_t* Insert(int val);

// �����������
node_t* Merge(node_t* tree1, node_t* tree2);

// ����������
void Split(int val, node_t* tree, node_t** tree1, node_t** tree2, int n);

// ���������� ����
void AddNode(node_t** tree, int n, int val);

// �������� ����
void DeleteNode(node_t** tree, int n);

// ������� �������
void DeleteVal(node_t** tree, int val);

// ����� ����
void IsFind(node_t* tree, int val, int* find);

// ������ ������
void PrintTree(node_t* tree);

// �������� ������
void DestroyTree(node_t* tree);
