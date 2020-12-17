#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "BFS.h"
#include "queue.h"


#define SUCCESS 1
#define FAIL 0


int main(void) {
  int i, j, k;
  adjlist_t list;
  queue_t queue;
  queue_t* ptr = &queue;

  scanf("%i", &list.numOfVert);

  if (!InitialisationOfQueue(ptr, list.numOfVert))
    return 0;

  list.nodes = (node_t*)calloc(list.numOfVert, sizeof(node_t));

  if (!list.nodes) {
    DeletQueue(ptr);
    return 0;
  }

  for (i = 0; i < list.numOfVert; i++) {
    list.nodes[i].adjacency = (int*)calloc(list.numOfVert, sizeof(int));

    if (!list.nodes[i].adjacency) {
      for (j = 0; j < i; j++)
        free(list.nodes[j].adjacency);

      free(list.nodes);
      DeletQueue(ptr);
      return 0;
    }
  }


  for (k = 0; k < list.numOfVert; k++) {

    int cur, tmp;
    char sym;

    scanf("%i%c", &cur, &sym);

    while (sym == ' ') {
      scanf("%i%c", &tmp, &sym);

      list.nodes[cur].adjacency[list.nodes[cur].numOfAdj++] = tmp;
      list.nodes[tmp].adjacency[list.nodes[tmp].numOfAdj++] = cur;
    }
  }


  BFS(&list, ptr);

  for (i = 0; i < queue.tail; i++)
    printf("%i ", queue.array[i]);

  for (i = 0; i < list.numOfVert; i++)
    free(list.nodes[i].adjacency);

  free(list.nodes);
  DeletQueue(ptr);
  return 0;
}
