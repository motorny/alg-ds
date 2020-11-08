#include "graph.h"

int main() {
  int numOfVertex, numOfEdges;
  data_t* data = ReadData(&numOfVertex, &numOfEdges);
  BFS(data, numOfVertex, numOfEdges);
  free(data);
  return 0;
}