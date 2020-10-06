#pragma once

#ifndef __SKIP_LIST_H_INCLUDED
#define __SKIP_LIST_H_INCLUDED

#include "list_common.h"

#define NUMBER_OF_LEVEL 10

typedef struct skip_list_node_t {
  struct skip_list_node_t *next[NUMBER_OF_LEVEL];
  int key;
} skip_list_node_t;

typedef struct {
  skip_list_node_t *start;
} skip_list_t;

int SkipListIni(skip_list_t *l);
void SkipListClose(skip_list_t *l);
int SkipListInsert(skip_list_t *l, int key);
int SkipListFind(skip_list_t const *l, int key);
int SkipListExtract(skip_list_t *l, int key);

#endif /* __SKIP_LIST_H_INCLUDED */
