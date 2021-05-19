#ifdef __cpluslpus
extern "C" {
#endif /* __cpluslpus */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

struct node_t {
  int
    size,
    keys[3];
  struct node_t
    *childs[4],
    *parent;
};

static int _findKey(node_t *node, int key) {
  int i;
  for (i = 0; i < node->size; i++)
    if (node->keys[i] == key)
      return 1;
  return 0;
}

static node_t * _find(node_t *root, int key) {
  if (root == NULL)
    return NULL;
  if (_findKey(root, key))
    return root;
  if (key < root->keys[0])
    return _find(root->childs[0], key);
  if (root->size == 2 && key < root->keys[1] || root->size == 1)
    return _find(root->childs[1], key);
  return _find(root->childs[2], key);
}

static void _swap(int *x, int *y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

static void _sort2(int *x, int *y) {
  if (*x > *y)
    _swap(x, y);
}

static void _sort3(int *x, int *y, int *z) {
  if (*x > *y)
    _swap(x, y);
  if (*x > *z)
    _swap(x, z);
  if (*y > *z)
    _swap(y, z);
}

static void _sort(node_t *n) {
  if (n->size == 1)
    return;
  if (n->size == 2)
    _sort2(&n->keys[0], &n->keys[1]);
  if (n->size == 3)
    _sort3(&n->keys[0], &n->keys[1], &n->keys[2]);
}

static void _nodeInsert(node_t *n, int key) {
  n->keys[n->size] = key;
  n->size++;
  _sort(n);
}

static void _nodeRemove(node_t *n, int key) {
  if (n->size >= 1 && n->keys[0] == key) {
    n->keys[0] = n->keys[1];
    n->keys[1] = n->keys[2];
    n->size--;
  }
  else if (n->size == 2 && n->keys[1] == key) {
    n->keys[1] = n->keys[2];
    n->size--;
  }
}

static void _createNode2(node_t *n, int key, node_t *first, node_t *second) {
  n->keys[0] = key;
  n->size = 1;
  n->parent = NULL;
  n->childs[0] = first;
  n->childs[1] = second;
  n->childs[2] = NULL;
  n->childs[3] = NULL;
}

static int _isLeaf(node_t *n) {
  return n->childs[0] == NULL;
}

static node_t * _getNode(int key) {
  node_t *res = (node_t *)malloc(sizeof(node_t));
  if (res == NULL)
    return NULL;
  res->size = 1;
  res->keys[0] = key;
  res->parent = res->childs[0] = res->childs[1] = res->childs[2] = res->childs[3] = NULL;
  return res;
}

static node_t * _split(node_t *item) {
  node_t *x, *y;
  if (item == NULL)
    return NULL;
  if (item->size < 3)
    return item;
  x = (node_t *)malloc(sizeof(node_t));
  if (x == NULL)
    return NULL;
  x->size = 1;
  x->keys[0] = item->keys[0];
  x->parent = item->parent;
  x->childs[0] = item->childs[0];
  x->childs[1] = item->childs[1];
  x->childs[2] = NULL;
  x->childs[3] = NULL;
  y = (node_t *)malloc(sizeof(node_t));
  if (y == NULL) {
    free(x);
    return NULL;
  }
  y->size = 1;
  y->keys[0] = item->keys[2];
  y->parent = item->parent;
  y->childs[0] = item->childs[2];
  y->childs[1] = item->childs[3];
  y->childs[2] = NULL;
  y->childs[3] = NULL;

  if (x->childs[0] != NULL)
    x->childs[0]->parent = x;
  if (x->childs[1] != NULL)
    x->childs[1]->parent = x;
  if (y->childs[0] != NULL)
    y->childs[0]->parent = y;
  if (y->childs[1] != NULL)
    y->childs[1]->parent = y;

  if (item->parent != NULL) {
    node_t *tmp;
    _nodeInsert(item->parent, item->keys[1]);

    if (item->parent->childs[0] == item)
      item->parent->childs[0] = NULL;
    else if (item->parent->childs[1] == item)
      item->parent->childs[1] = NULL;
    else if (item->parent->childs[2] == item)
      item->parent->childs[2] = NULL;

    if (item->parent->childs[0] == NULL) {
      item->parent->childs[3] = item->parent->childs[2];
      item->parent->childs[2] = item->parent->childs[1];
      item->parent->childs[1] = y;
      item->parent->childs[0] = x;
    }
    else if (item->parent->childs[1] == NULL) {
      item->parent->childs[3] = item->parent->childs[2];
      item->parent->childs[2] = y;
      item->parent->childs[1] = x;
    }
    else {
      item->parent->childs[3] = y;
      item->parent->childs[2] = x;
    }

    tmp = item->parent;
    free(item);
    return tmp;
  }
  else {
    x->parent = item;
    y->parent = item;
    _createNode2(item, item->keys[1], x, y);
    return item;
  }
}

static node_t * _insert(node_t *p, int key) {
  if (p == NULL)
    return _getNode(key);
  if (_isLeaf(p))
    _nodeInsert(p, key);
  else if (key <= p->keys[0])
    _insert(p->childs[0], key);
  else if (p->size == 1 || p->size == 2 && key <= p->keys[1])
    _insert(p->childs[1], key);
  else
    _insert(p->childs[2], key);
  return _split(p);
}

int Insert(node_t **root, int key) {
  node_t *tmp = NULL;
  if (root == NULL)
    return TREE_INSERT_NULL_TREE;
  if (_find(*root, key) != NULL)
    return TREE_INSERT_NODE_ALREADY_EXIST;
  tmp = _insert(*root, key);
  if (tmp == NULL) {
    DeleteTree(*root);
    *root = NULL;
    return TREE_INSERT_FAILED_ALLOC;
  }
  *root = tmp;
  return TREE_INSERT_NODE_ADDED;
}

static node_t * _getMin(node_t *node) {
  node_t *cur = node, *prev = NULL;
  while (cur != NULL) {
    prev = cur;
    cur = cur->childs[0];
  }
  return prev;
}

static node_t * _redistributeTree(node_t *leaf) {
  node_t
    *parent = leaf->parent,
    *first = parent->childs[0],
    *second = parent->childs[1],
    *third = parent->childs[2];

  if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
    if (first == leaf) {
      parent->childs[0] = parent->childs[1];
      parent->childs[1] = parent->childs[2];
      parent->childs[2] = NULL;
      _nodeInsert(parent->childs[0], parent->keys[0]);
      parent->childs[0]->childs[2] = parent->childs[0]->childs[1];
      parent->childs[0]->childs[1] = parent->childs[0]->childs[0];

      if (leaf->childs[0] != NULL) parent->childs[0]->childs[0] = leaf->childs[0];
      else if (leaf->childs[1] != NULL) parent->childs[0]->childs[0] = leaf->childs[1];

      if (parent->childs[0]->childs[0] != NULL) parent->childs[0]->childs[0]->parent = parent->childs[0];

      _nodeRemove(parent, parent->keys[0]);
      free(first);
    }
    else if (second == leaf) {
      _nodeInsert(first, parent->keys[0]);
      _nodeRemove(parent, parent->keys[0]);
      if (leaf->childs[0] != NULL) first->childs[2] = leaf->childs[0];
      else if (leaf->childs[1] != NULL) first->childs[2] = leaf->childs[1];

      if (first->childs[2] != NULL) first->childs[2]->parent = first;

      parent->childs[1] = parent->childs[2];
      parent->childs[2] = NULL;

      free(second);
    }
    else if (third == leaf) {
      _nodeInsert(second, parent->keys[1]);
      parent->childs[2] = NULL;
      _nodeRemove(parent, parent->keys[1]);
      if (leaf->childs[0] != NULL) second->childs[2] = leaf->childs[0];
      else if (leaf->childs[1] != NULL) second->childs[2] = leaf->childs[1];

      if (second->childs[2] != NULL)  second->childs[2]->parent = second;

      free(third);
    }
  }
  else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
    if (third == leaf) {
      if (leaf->childs[0] != NULL) {
        leaf->childs[1] = leaf->childs[0];
        leaf->childs[0] = NULL;
      }

      _nodeInsert(leaf, parent->keys[1]);
      if (second->size == 2) {
        parent->keys[1] = second->keys[1];
        _nodeRemove(second, second->keys[1]);
        leaf->childs[0] = second->childs[2];
        second->childs[2] = NULL;
        if (leaf->childs[0] != NULL)
          leaf->childs[0]->parent = leaf;
      }
      else if (first->size == 2) {
        parent->keys[1] = second->keys[0];
        leaf->childs[0] = second->childs[1];
        second->childs[1] = second->childs[0];
        if (leaf->childs[0] != NULL)
          leaf->childs[0]->parent = leaf;

        second->keys[0] = parent->keys[0];
        parent->keys[0] = first->keys[1];
        _nodeRemove(first, first->keys[1]);
        second->childs[0] = first->childs[2];
        if (second->childs[0] != NULL)
          second->childs[0]->parent = second;
        first->childs[2] = NULL;
      }
    }
    else if (second == leaf) {
      if (third->size == 2) {
        if (leaf->childs[0] == NULL) {
          leaf->childs[0] = leaf->childs[1];
          leaf->childs[1] = NULL;
        }
        _nodeInsert(second, parent->keys[1]);
        parent->keys[1] = third->keys[0];
        _nodeRemove(third, third->keys[0]);
        second->childs[1] = third->childs[0];
        if (second->childs[1] != NULL)
          second->childs[1]->parent = second;
        third->childs[0] = third->childs[1];
        third->childs[1] = third->childs[2];
        third->childs[2] = NULL;
      }
      else if (first->size == 2) {
        if (leaf->childs[1] == NULL) {
          leaf->childs[1] = leaf->childs[0];
          leaf->childs[0] = NULL;
        }
        _nodeInsert(second, parent->keys[0]);
        parent->keys[0] = first->keys[1];
        _nodeRemove(first, first->keys[1]);
        second->childs[0] = first->childs[2];
        if (second->childs[0] != NULL)
          second->childs[0]->parent = second;
        first->childs[2] = NULL;
      }
    }
    else if (first == leaf) {
      if (leaf->childs[0] == NULL) {
        leaf->childs[0] = leaf->childs[1];
        leaf->childs[1] = NULL;
      }
      _nodeInsert(first, parent->keys[0]);
      if (second->size == 2) {
        parent->keys[0] = second->keys[0];
        _nodeRemove(second, second->keys[0]);
        first->childs[1] = second->childs[0];
        if (first->childs[1] != NULL)
          first->childs[1]->parent = first;
        second->childs[0] = second->childs[1];
        second->childs[1] = second->childs[2];
        second->childs[2] = NULL;
      }
      else if (third->size == 2) {
        parent->keys[0] = second->keys[0];
        second->keys[0] = parent->keys[1];
        parent->keys[1] = third->keys[0];
        _nodeRemove(third, third->keys[0]);
        first->childs[1] = second->childs[0];
        if (first->childs[1] != NULL)
          first->childs[1]->parent = first;
        second->childs[0] = second->childs[1];
        second->childs[1] = third->childs[0];
        if (second->childs[1] != NULL)
          second->childs[1]->parent = second;
        third->childs[0] = third->childs[1];
        third->childs[1] = third->childs[2];
        third->childs[2] = NULL;
      }
    }
  }
  else if (parent->size == 1) {
    _nodeInsert(leaf, parent->keys[0]);

    if (first == leaf && second->size == 2) {
      parent->keys[0] = second->keys[0];
      _nodeRemove(second, second->keys[0]);

      if (leaf->childs[0] == NULL)
        leaf->childs[0] = leaf->childs[1];

      leaf->childs[1] = second->childs[0];
      second->childs[0] = second->childs[1];
      second->childs[1] = second->childs[2];
      second->childs[2] = NULL;
      if (leaf->childs[1] != NULL)
        leaf->childs[1]->parent = leaf;
    }
    else if (second == leaf && first->size == 2) {
      parent->keys[0] = first->keys[1];
      _nodeRemove(first, first->keys[1]);

      if (leaf->childs[1] == NULL)
        leaf->childs[1] = leaf->childs[0];

      leaf->childs[0] = first->childs[2];
      first->childs[2] = NULL;
      if (leaf->childs[0] != NULL)
        leaf->childs[0]->parent = leaf;
    }
  }
  return parent;
}

static node_t * _mergeTree(node_t *leaf) {
  node_t *parent = leaf->parent;

  if (parent->childs[0] == leaf) {
    _nodeInsert(parent->childs[1], parent->keys[0]);
    parent->childs[1]->childs[2] = parent->childs[1]->childs[1];
    parent->childs[1]->childs[1] = parent->childs[1]->childs[0];

    if (leaf->childs[0] != NULL)
      parent->childs[1]->childs[0] = leaf->childs[0];
    else if (leaf->childs[1] != NULL)
      parent->childs[1]->childs[0] = leaf->childs[1];

    if (parent->childs[1]->childs[0] != NULL)
      parent->childs[1]->childs[0]->parent = parent->childs[1];

    _nodeRemove(parent, parent->keys[0]);
    free(parent->childs[0]);
    parent->childs[0] = NULL;
  }
  else if (parent->childs[1] == leaf) {
    _nodeInsert(parent->childs[0], parent->keys[0]);

    if (leaf->childs[0] != NULL)
      parent->childs[0]->childs[2] = leaf->childs[0];
    else if (leaf->childs[1] != NULL)
      parent->childs[0]->childs[2] = leaf->childs[1];

    if (parent->childs[0]->childs[2] != NULL)
      parent->childs[0]->childs[2]->parent = parent->childs[0];

    _nodeRemove(parent, parent->keys[0]);
    free(parent->childs[1]);
    parent->childs[1] = NULL;
  }

  if (parent->parent == NULL) {
    node_t *tmp = NULL;
    if (parent->childs[0] != NULL)
      tmp = parent->childs[0];
    else
      tmp = parent->childs[1];
    tmp->parent = NULL;
    free(parent);
    return tmp;
  }
  return parent;
}

static node_t * _fixTree(node_t *leaf) {
  node_t *parent;
  if (leaf->size == 0 && leaf->parent == NULL) {
    free(leaf);
    return NULL;
  }
  if (leaf->size != 0) {
    if (leaf->parent)
      return _fixTree(leaf->parent);
    else
      return leaf;
  }

  parent = leaf->parent;
  if (parent->childs[0]->size == 2 || parent->childs[1]->size == 2 || parent->size == 2)
    leaf = _redistributeTree(leaf);
  else if (parent->size == 2 && parent->childs[2]->size == 2)
    leaf = _redistributeTree(leaf);
  else
    leaf = _mergeTree(leaf);

  return _fixTree(leaf);
}

int Delete(node_t **root, int key) {
  node_t *cur, *min = NULL;
  if (root == NULL)
    return TREE_DELETE_NULL_TREE;

  cur = _find(*root, key);
  if (cur == NULL)
    return TREE_DELETE_NODE_DOESNT_EXIST;

  if (cur->keys[0] == key)
    min = _getMin(cur->childs[1]);
  else
    min = _getMin(cur->childs[2]);

  if (min != NULL) {
    if (key == cur->keys[0])
      _swap(&cur->keys[0], &min->keys[0]);
    else
      _swap(&cur->keys[1], &min->keys[0]);
    cur = min;
  }
  _nodeRemove(cur, key);
  *root = _fixTree(cur);

  return TREE_DELETE_NODE_DELETED;
}

int Find(node_t *root, int key) {
  if (_find(root, key) == NULL)
    return TREE_FIND_NODE_DOESNT_EXIST;
  return TREE_FIND_NODE_EXIST;
}

static void _printNode(node_t *node, int level) {
  int i;
  if (node == NULL)
    return;
  for (i = 0; i < level; i++)
    printf("  ");
  if (node->size == 1)
    printf("(%i)", node->keys[0]);
  else
    printf("(%i, %i)", node->keys[0], node->keys[1]);
  if (node->childs[0] != NULL) {
    printf(" {\n");
    for (i = 0; i <= node->size; i++)
      _printNode(node->childs[i], level + 1);
    for (i = 0; i < level; i++)
      printf("  ");
    printf("}");
  }
  printf("\n");
}

void Print(node_t *root) {
  _printNode(root, 0);
}

void DeleteTree(node_t *root) {
  int i;
  if (root == NULL)
    return;
  for (i = 0; i <= root->size; i++)
    DeleteTree(root->childs[i]);
  free(root);
}

#ifdef __cpluslpus
}
#endif /* __cpluslpus */
