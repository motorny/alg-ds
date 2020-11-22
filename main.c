#include <stdio.h>
#include <stdlib.h>
#include "DFS.h"
#pragma warning(disable : 4996)

int main() {
  int i, j;
  adjList_t adj;
  adj.sizeList = 0;
  adj.vertex = NULL;

  scanf("%i", &adj.sizeList);

  adj.vertex = (vertex_t*)calloc(adj.sizeList, sizeof(vertex_t));

  for (i = 0; i < adj.sizeList; i++) {
    adj.vertex[i].edges = (int*)calloc(adj.sizeList, sizeof(int));

    if (!adj.vertex[i].edges) {
      for (j = 0; j < i; j++)
        free(adj.vertex[j].edges);

      free(adj.vertex);
      return 0;
    }
  }

  CreateAdjList(&adj);
  DFS(&adj, 0);
}