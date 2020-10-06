#include <stdlib.h>
#include <limits.h>

#include "skip_list.h"

static int _coin(void) {
  return (int)((double)rand() / (RAND_MAX + 1) * 2);
}

int SkipListIni(skip_list_t *l) {
  skip_list_node_t* NILnode;

  if (l->start == NULL)
    return LIST_FAIL;
  NILnode = (skip_list_node_t*)malloc(sizeof(skip_list_node_t));
  if (NILnode == NULL)
    return LIST_FAIL;

  for (int i = 0; i < NUMBER_OF_LEVEL; i++)
    NILnode->next[i] = NILnode;
  NILnode->key = NIL_KEY;
  l->start = NILnode;
  return LIST_SUCCESS;
}

void SkipListClose(skip_list_t *l) {
  int key;
  skip_list_node_t *n1, *n2;

  if (l->start == NULL)
    return;
  n1 = l->start->next[0];
  do {
    key = n1->key;
    n2 = n1->next[0];
    free(n1);
    n1 = n2;
  } while (key != NIL_KEY);
}

int SkipListInsert(skip_list_t *l, int key) {
  skip_list_node_t *nBefore, *nAfter, *path[NUMBER_OF_LEVEL], *newNode;

  if (l == NULL)
    return LIST_FAIL;
  nBefore = l->start;
  for (int i = NUMBER_OF_LEVEL - 1; i >= 0; i--) {
    nAfter = nBefore->next[i];
    while (nAfter->key < key) {
      nBefore = nAfter;
      nAfter = nAfter->next[i];
    }
    if (nAfter->key == key)
      return LIST_CONTAINS_KEY;
    path[i] = nBefore;
  }

  newNode = (skip_list_node_t*)malloc(sizeof(skip_list_node_t));
  if (newNode == NULL)
    return LIST_FAIL;

  newNode->key = key;
  int i = 0;
  do {
    newNode->next[i] = path[i]->next[i];
    path[i]->next[i] = newNode;
    i++;
  } while (_coin() && i < NUMBER_OF_LEVEL);
  for (; i < NUMBER_OF_LEVEL; i++)
    newNode->next[i] = 0;
  return LIST_SUCCESS;
}

int SkipListFind(skip_list_t const *l, int key) {
  skip_list_node_t *nBefore, *nAfter;

  if (l == NULL)
    return LIST_FAIL;
  nBefore = l->start;
  for (int i = NUMBER_OF_LEVEL - 1; i >= 0; i--) {
    nAfter = nBefore->next[i];
    while (nAfter->key < key) {
      nBefore = nAfter;
      nAfter = nAfter->next[i];
    }
    if (nAfter->key == key)
      return LIST_SUCCESS;
  }
  return LIST_FAIL;
}

int SkipListExtract(skip_list_t *l, int key) {
  skip_list_node_t *nBefore, *nAfter;

  if (l == NULL)
    return LIST_FAIL;
  nBefore = l->start;
  if (key == NIL_KEY)
    return LIST_EXTRACT_NIL;

  for (int i = NUMBER_OF_LEVEL - 1; i >= 0; i--) {
    nAfter = nBefore->next[i];
    while (nAfter->key < key) {
      nBefore = nAfter;
      nAfter = nAfter->next[i];
    }
    if (nAfter->key == key)
      nBefore->next[i] = nAfter->next[i];
  }
  if (nAfter->key == key) {
    free(nAfter);
    return LIST_SUCCESS;
  }
  return LIST_FAIL;
}
