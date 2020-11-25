#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "graph.h"

int main(void) {
  graph_t* graph;
  graph = readGraph();
  BFS(graph);
  freeGraph(graph);
  return 0;
}