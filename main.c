#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#include "queue.h"
struct node {
  int number;
  int visited;
  int* adjacency;
};
struct adjacencylist {
  int n;
  struct node* nodes;
};
int BFS(struct adjacencylist* adj, struct queue* q) {
  int i;
  int current;
  if (q->arr == NULL || adj->n == 0 || adj->nodes == NULL || adj->n > q->size) {
    return FALSE;
  }
  Push(q, 0);
  adj->nodes[0].visited = 1;
  while (Pop(q, &current)) {
    for (i = 0; i < adj->nodes[current].number; i++){
      if (adj->nodes[adj->nodes[current].adjacency[i]].visited == 0) {
        Push(q, adj->nodes[current].adjacency[i]);
        adj->nodes[adj->nodes[current].adjacency[i]].visited = 1;
      }
    }
  }
  return TRUE;
}
int main(void) {
  int i;
  int j;
  struct adjacencylist adj;
  struct queue q;
  scanf("%d", &adj.n);
  if (InitQueue(&q, adj.n) == 0) {
    return FALSE;
  }
  adj.nodes = (struct node*)calloc(adj.n, sizeof(struct node));
  if (adj.nodes == NULL) {
    RemoveQueue(&q);
    return FALSE;
  }
  for (i = 0; i < adj.n; i++) {
    adj.nodes[i].adjacency = (int*)calloc(adj.n, sizeof(int));
    if (adj.nodes[i].adjacency == NULL) {
      for (j = 0; j < i; j++) {
        free(adj.nodes[j].adjacency);
      }
      free(adj.nodes);
      RemoveQueue(&q);
      return FALSE;
    }
  }
  for (i = 0; i < adj.n; i++) {
    int curv;
    int tmp;
    char space;
    scanf("%i%c", &curv, &space);
    while (space != '\n' && space != '\r' && space != 'EOF') {
      scanf("%i%c", &tmp, &space);
      adj.nodes[tmp].adjacency[adj.nodes[tmp].number++] = curv;
      adj.nodes[curv].adjacency[adj.nodes[curv].number++] = tmp;
    }
  }
  BFS(&adj, &q);
  for (i = 0; i < q.last; i++) {
    printf("%d ", q.arr[i]);
  }
  for (i = 0; i < adj.n; i++) {
    free(adj.nodes[i].adjacency);
  }
  free(adj.nodes);
  RemoveQueue(&q);
  return FALSE;
}
