#pragma once
#include<stdio.h>
#include<stdlib.h>
#define ERRORNULL NULL

typedef int T;

typedef struct Node {
  T value;
  struct Node* left;
  struct Node* right;
  struct Node* parent;
} Node;

void InsertInTree(Node** root, T value);
Node* CreateFreeNode(T value, Node* parent);
Node* GetMinNode(Node* root);
Node* GetMaxNode(Node* root);
Node* GetNodeByValue(Node* root, T value);
void RemoveNodeByPtr(Node* target);
void DeleteValue(Node* root, T value);
void PrintTree(Node* root, const char* dir, int level);
void DestroyTree(Node** root);
void GetTreeFromConsole(Node** root);
void MinHeightLeaves(Node* root);