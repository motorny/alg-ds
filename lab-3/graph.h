#pragma once
#ifndef GRAPH_9836238
#define GRAPH_9836238

#include <stdio.h>

typedef struct {
  int a;
  int b;
} data_t;

data_t* ReadData(int* numOfVertex, int* numOfEdges);
void BFS(data_t* data, int numOfVertex, int numOfEdges);

#endif // !GRAPH_9836238
