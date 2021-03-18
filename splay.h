#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

#define TRUE 1
#define FALSE 0

typedef struct node_t {
  int value;
  struct node_t* left;
  struct node_t* right;
  struct node_t* parent;
}node_t;

typedef struct tree_t {
  node_t* root;
}tree_t;

tree_t* createTree();
void left_rotate(tree_t* root, node_t* x);
void right_rotate(tree_t* root, node_t* x);
void splay(tree_t* root, node_t* node);
int searchElem(tree_t* root, int value);
int addElem(tree_t* root, int value);
static node_t* child(node_t* node);
int deleteElem(tree_t* root, int value);
void deleteTree(tree_t* root);