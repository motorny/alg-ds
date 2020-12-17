#include <stdlib.h>

#include "BFS.h"
#include "queue.h"


int BFS(adjlist_t* list, queue_t* queue) {
  int i, curVert;
  int* visited = (int*)calloc(list->numOfVert, sizeof(int));

  if (list->numOfVert != 0 && list->nodes != NULL && queue->array != NULL && list->numOfVert <= queue->size && visited != NULL) {
    Push(queue, 0);
    visited[0] = 1;

    while (Pop(queue, &curVert)) {
      for (i = 0; i < list->nodes[curVert].numOfAdj; i++) {

        if (!visited[list->nodes[curVert].adjacency[i]]) {
          Push(queue, list->nodes[curVert].adjacency[i]);
          visited[list->nodes[curVert].adjacency[i]] = 1;
        }
      }
    }

    free(visited);
    return SUCCESS;
  }

  free(visited);
  return FAIL;
}