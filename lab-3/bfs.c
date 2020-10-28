#ifdef cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "bfs.h"

int BFS(adj_list_t *adj, queue_t *q) {
  int curVert, i;

  if (adj->n == 0 || adj->nodes == NULL || adj->n > q->size || q->array == NULL)
    return 0;
  Push(q, 0);
  adj->nodes[0].wasVisit = 1;
  while (Pop(q, &curVert)) {
    for (i = 0; i < adj->nodes[curVert].numOfList; i++)
      if (adj->nodes[adj->nodes[curVert].adjNodes[i]].wasVisit == 0) {
        Push(q, adj->nodes[curVert].adjNodes[i]);
        adj->nodes[adj->nodes[curVert].adjNodes[i]].wasVisit = 1;
      }
  }

  return 1;
}

#ifdef cplusplus
}
#endif
