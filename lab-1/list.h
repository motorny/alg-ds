#pragma once

#ifndef __LIST_H_INCLUDED
#define __LIST_H_INCLUDED

#include "list_common.h"

typedef struct list_node_t {
  struct list_node_t *next;
  int key;
} list_node_t;

typedef struct {
  list_node_t *start;
} list_t;

int ListIni(list_t *l);
void ListClose(list_t *l);
int ListInsert(list_t *l, int key);
int ListFind(list_t const *l, int key);
int ListExtract(list_t *l, int key);

#endif /* __LIST_H_INCLUDED */
