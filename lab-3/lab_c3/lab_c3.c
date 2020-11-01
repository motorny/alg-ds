#include <stdio.h>
#include <stdlib.h>

#include "func_for_test.h"

void ReadAdjList(adj_list_t* list) {
  int counter;
  int curVert, tmpVert;
  char ch;

  for (counter = 0; counter < list->numOfVertex; counter++) {
    scanf("%i%c", &curVert, &ch);

    while (ch == ' ') {
      scanf("%i%c", &tmpVert, &ch);
      list->nodes[curVert].edges[list->nodes[curVert].numOfEdges++] = tmpVert;
      list->nodes[tmpVert].edges[list->nodes[tmpVert].numOfEdges++] = curVert;
    }
  }
}

int main(void) {
  int counter1, counter2;
  adj_list_t list;
  queue_t q;
  queue_t* qptr = &q;

  scanf("%i", &list.numOfVertex);

  if (!InitQueue(qptr, list.numOfVertex))
    return 0;

  list.nodes = (node_t*)calloc(list.numOfVertex, sizeof(node_t));

  if (!list.nodes) {
    DelQueue(qptr);
    return 0;
  }

  for (counter1 = 0; counter1 < list.numOfVertex; counter1++) {
    list.nodes[counter1].edges = (int*)calloc(list.numOfVertex, sizeof(int));

    if (!list.nodes[counter1].edges) {
      for (counter2 = 0; counter2 < counter1; counter2++)
        free(list.nodes[counter2].edges);

      free(list.nodes);
      DelQueue(qptr);
      return 0;
    }
  }

  ReadAdjList(&list);

  BFS(&list, qptr);

  for (counter1 = 0; counter1 < q.tail; counter1++)
    printf("%i ", q.arr[counter1]);

  for (counter1 = 0; counter1 < list.numOfVertex; counter1++)
    free(list.nodes[counter1].edges);

  free(list.nodes);
  DelQueue(qptr);
  return 0;
}