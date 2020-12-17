#pragma once
#include "queue.h"

typedef struct {
  int numOfAdj;
  int* adjacency;
} node_t;

typedef struct {
  int numOfVert;
  node_t* nodes;
} adjlist_t;


int BFS(adjlist_t* list, queue_t* queue);