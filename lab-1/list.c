#include <stdlib.h>
#include <limits.h>

#include "list.h"

int ListIni(list_t *l) {
  list_node_t *NILnode;

  if (l == NULL)
    return LIST_FAIL;

  NILnode = (list_node_t *)malloc(sizeof(list_node_t));
  if (NILnode == NULL)
    return LIST_FAIL;

  NILnode->next = NULL;
  NILnode->key = NIL_KEY;
  l->start = NILnode;
  return LIST_SUCCESS;
}

void ListClose(list_t *l) {
  int key;
  list_node_t *n1, *n2;

  if (l == NULL)
    return;
  n1 = l->start;
  do {
    key = n1->key;
    n2 = n1->next;
    free(n1);
    n1 = n2;
  } while (key != NIL_KEY);
}

int ListInsert(list_t *l, int key) {
  list_node_t *nBefore, *nAfter, *newNode;

  if (l == NULL)
    return LIST_FAIL;
  nBefore = l->start;
  nAfter = l->start;
  while (nAfter->key < key) {
    nBefore = nAfter;
    nAfter = nAfter->next;
  }
  if (nAfter->key == key)
    return LIST_CONTAINS_KEY;

  newNode = (list_node_t *)malloc(sizeof(list_node_t));
  if (newNode == NULL)
    return LIST_FAIL;

  newNode->key = key;
  if (nAfter == nBefore) {
    newNode->next = l->start;
    l->start = newNode;
  }
  else {
    newNode->next = nAfter;
    nBefore->next = newNode;
  }
  return LIST_SUCCESS;
}

int ListFind(list_t const* l, int key) {
  list_node_t *nBefore, *nAfter;

  if (l == NULL)
    return LIST_FAIL;
  nBefore = l->start;
  nAfter = l->start;
  while (nAfter->key < key) {
    nBefore = nAfter;
    nAfter = nAfter->next;
  }
  if (nAfter->key == key)
    return LIST_SUCCESS;
  return LIST_FAIL;
}

int ListExtract(list_t *l, int key) {
  list_node_t *nBefore, *nAfter;

  if (l == NULL)
    return LIST_FAIL;
  nBefore = l->start;
  nAfter = l->start;
  if (key == NIL_KEY)
    return LIST_EXTRACT_NIL;

  while (nAfter->key < key) {
    nBefore = nAfter;
    nAfter = nAfter->next;
  }

  if (nAfter->key == key) {
    nBefore->next = nAfter->next;
    if (nAfter == l->start)
      l->start = nAfter->next;
    free(nAfter);
    return LIST_SUCCESS;
  }
  return LIST_FAIL;
}
