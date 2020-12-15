#pragma once
#ifndef BINLIBRAR

typedef struct vertex {
  int key;
  struct vertex* left;
  struct vertex* right;
  struct vertex* parent;
  int data;
  int width;
}vertex_t;

typedef struct tree {
  vertex_t* root;
} tree_t;

int DeleteVertex(vertex_t** cur, int key);
int AddVertex(tree_t* tree, int key, int data);
vertex_t* FindVertex(tree_t tree, int key);
int UpdateWidth(vertex_t* t);
void PrintTree(tree_t t);
#endif 

