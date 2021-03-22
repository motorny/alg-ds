#include "aatree.h"

static aanode_t* CreateNode(const int key, aanode_t* btm) {
  aanode_t* node = (aanode_t*)malloc(sizeof(aanode_t));
  if (node == NULL)
    return NULL;

  node->key = key;
  node->level = 1;
  node->l = node->r = btm;
  return node;
}

aatree_t* Create() {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));
  if (tree == NULL)
    return NULL;

  aanode_t* btm = (aanode_t*)malloc(sizeof(aanode_t));
  if (btm == NULL) {
    free(tree);
    return NULL;
  }

  btm->level = 0;
  btm->l = btm->r = btm;
  tree->root = tree->bottom = btm;
  tree->todel = NULL;
  return tree;
}

/*static*/ void Delete_(aatree_t* tree, aanode_t* node) {
  assert(node);
  if (node == tree->bottom)
    return;
  if (node->l != tree->bottom)
    Delete_(tree, node->l);
  if (node->r != tree->bottom)
    Delete_(tree, node->r);

  free(node);
}

void Delete(aatree_t* tree) {
  assert(tree && tree->root);
  Delete_(tree, tree->root);
  free(tree->bottom);
  free(tree);
}

static aanode_t* Skew(aanode_t* node) {
  assert(node && node->l);
  if (node->level != node->l->level)
    return node;

  aanode_t* left = node->l;
  node->l = left->r;
  left->r = node;
  node = left;
  return node;
}

static aanode_t* Split(aanode_t* node) {
  assert(node && node->r && node->r->r);
  if (node->r->r->level != node->level)
    return node;

  aanode_t* right = node->r;
  node->r = right->l;
  right->l = node;
  node = right;
  node->level++;
  return node;
}

static aanode_t* Search_(aanode_t* node,const aanode_t* btm, const int key) {
  if (node == btm)
    return NULL;
  else if (node->key > key)
    return Search_(node->l, btm, key);
  else if (node->key < key)
    return Search_(node->r, btm, key);
  else
    return node;
}

ERR_STATUS Search(const aatree_t* tree, const int key) {
  if (Search_(tree->root, tree->bottom, key) != NULL)
    return FOUND;
  return NOT_FOUND;
}

static aanode_t* Add_(aatree_t* tree, aanode_t* node, const int key) {
  if (node == tree->bottom) {
    node = CreateNode(key, tree->bottom);
    return node;
  }

  if (key < node->key)
    node->l = Add_(tree, node->l, key);
  else if (key > node->key)
    node->r = Add_(tree, node->r, key);
  else
    return node;

  node = Skew(node);
  node = Split(node);
  return node;
}

void Add(aatree_t* tree, const int key) {
  tree->root = Add_(tree, tree->root, key);
}

static aanode_t* Remove_(aatree_t* tree, aanode_t* node, const int key) {
  if (node == tree->bottom)
    return node;
  tree->last = node;
  if (key < node->key)
    node->l = Remove_(tree, node->l, key);
  else {
    tree->todel = node;
    node->r = Remove_(tree, node->r, key);
  }
  //Delete
  if(node == tree->last && tree->todel != tree->bottom && key == tree->todel->key){
    tree->todel->key = node->key;
    tree->todel = tree->bottom;
    node = node->r;
    free(tree->last);
  }
  //Optimize
  else if (node->l->level < node->level - 1 || node->r->level < node->level - 1) {
    node->level--;
    if (node->r->level > node->level)
      node->r->level = node->level;

    node = Skew(node);
    node->r = Skew(node->r);
    node->r->r = Skew(node->r->r);
    node = Split(node);
    node->r = Split(node->r);
  }

  return node;
}

void Remove(aatree_t* tree, const int key) {
  tree->root = Remove_(tree, tree->root, key);
}


void PrintTree(aanode_t* node, aanode_t* btm, int n){
  int i;
  if (node != btm){
    PrintTree(node->r, btm, n + 1);
    for (i = 0; i < n; i++) 
      putchar(' ');
    printf("%i\n", node->key);
    PrintTree(node->l, btm, n + 1);
  }
}

