#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "bfs.h"

int main(void) {
  int i, j;
  adj_list_t adj;
  queue_t q;

  scanf("%i", &adj.n);
  if (InitQueue(&q, adj.n) == 0)
    return 0;
  adj.nodes = calloc(adj.n, sizeof(node_t));
  if (adj.nodes == NULL) {
    CloseQueue(&q);
    return 0;
  }
  for (i = 0; i < adj.n; i++) {
    adj.nodes[i].adjNodes = calloc(adj.n, sizeof(int));
    if (adj.nodes[i].adjNodes == NULL) {
      for (j = 0; j < i; j++)
        free(adj.nodes[j].adjNodes);
      free(adj.nodes);
      CloseQueue(&q);
      return 0;
    }
  }

  for (i = 0; i < adj.n; i++) {
    int curVert, tmpVert;
    char space;

    scanf("%i%c", &curVert, &space);
    while (space == ' ') {
      scanf("%i%c", &tmpVert, &space);
      adj.nodes[tmpVert].adjNodes[adj.nodes[tmpVert].numOfList++] = curVert;
      adj.nodes[curVert].adjNodes[adj.nodes[curVert].numOfList++] = tmpVert;
    }
  }

  BFS(&adj, &q);

  for (i = 0; i < q.tail; i++)
    printf("%i ", q.array[i]);

  for (i = 0; i < adj.n; i++)
    free(adj.nodes[i].adjNodes);
  free(adj.nodes);
  CloseQueue(&q);
  return 0;
}
