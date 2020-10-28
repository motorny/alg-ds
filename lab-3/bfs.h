#pragma once

#ifdef cplusplus
extern "C" {
#endif

#ifndef __BFS_H_INCLUDED
#define __BFS_H_INCLUDED

#include "queue.h"

typedef struct {
  int numOfList, wasVisit;
  int *adjNodes;
} node_t;

typedef struct {
  int n;
  node_t *nodes;
} adj_list_t;

int BFS(adj_list_t *adj, queue_t *q);

#endif /* __BFS_H_INCLUDED */

#ifdef cplusplus
}
#endif
