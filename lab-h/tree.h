#ifndef __TREE_H__
#define __TREE_H__

typedef struct treap_t treap_t;
struct treap_t {
  double data;
  double prior;

  treap_t* parent;
  treap_t* left, * right;
};

enum returns {
  LABH_ADD = 5,
  LABH_REMOVE = 4,
  LABH_FIND = 3,

  LABH_TRUE = 1,
  LABH_FALSE = 0
};

int TreapFind(treap_t* treap, double data);
int TreapAdd(treap_t** treap, double data);
int TreapRemove(treap_t** treap, double data);

#endif
