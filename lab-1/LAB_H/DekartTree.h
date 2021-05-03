#pragma once

int GetSize(node_t* tree);

void PrintTree(node_t* tree);

void DestroyTree(node_t* tree);

node_t* Insert(int val);

void ChangeSize(node_t* tree);

node_t* Merge(node_t* treeA, node_t* treeB);

void Split(int n, int val, node_t* tree, node_t** treeA, node_t** treeB);

void AddNode(int n, int val, node_t** tree);

void DeleteNode(int n, node_t** tree);

void DeleteVal(int val, node_t** tree);

void IsItFind(node_t* tree, int val, int* find);
