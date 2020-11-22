#include <stdio.h>
#include <stdlib.h>

#include "DFS.h"

#pragma warning(disable : 4996)
void CreateAdjList(adjList_t* adj) {
  int i, curVertex, nextVertex;
  char space;
  for (i = 0; i < adj->sizeList; i++) {
    scanf("%i%c", &curVertex, &space);
    while (space == ' ') {
      scanf("%i%c", &nextVertex, &space);
      adj->vertex[nextVertex].edges[adj->vertex[nextVertex].numOfList++] = curVertex;
      adj->vertex[curVertex].edges[adj->vertex[curVertex].numOfList++] = nextVertex;
    }
  }
}

int DFS(adjList_t* adj, int vert) {
  int i, j;
  if (adj == NULL || vert < 0)
    return 0;
  adj->vertex[vert].visided = 1;
  printf("%i ", vert);
  for (i = 0; i < adj->sizeList; i++) {
    for (j = 0; j < adj->vertex[vert].numOfList; j++)
      if (adj->vertex[vert].edges[j] == i && adj->vertex[i].visided == 0)
        DFS(adj, i);

    for (j = 0; j < adj->vertex[i].numOfList; j++)
      if (adj->vertex[i].edges[j] == vert && adj->vertex[i].visided == 0)
        DFS(adj, i);
  }
  return 1;
}

