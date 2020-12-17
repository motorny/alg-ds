#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

//#include "BFS.h"
//#include "queue.h"


#define SUCCESS 1
#define FAIL 0

typedef struct {
  int* array;
  int size;
  int head;
  int tail;
} queue_t;

typedef struct {
  int numOfAdj;
  int* adjacency;
} node_t;

typedef struct {
  int numOfVert;
  node_t* nodes;
} adjlist_t;



int InitialisationOfQueue(queue_t* queue, int size) {
  queue->array = NULL;

  if (size > 0) {
    queue->array = (int*)calloc(size, sizeof(int));
  }

  if (queue->array) {
    queue->size = size;
    queue->head = 0;
    queue->tail = 0;

    return SUCCESS;
  }

  return FAIL;
}

int Push(queue_t* queue, int newElem) {
  if (queue->array != NULL && queue->size > queue->tail) {
    queue->array[queue->tail++] = newElem;

    return SUCCESS;
  }

  return FAIL;
}

int Pop(queue_t* queue, int* oldElem) {
  if (queue != NULL && queue->head != queue->tail) {
    *oldElem = queue->array[queue->head++];

    return SUCCESS;
  }

  return FAIL;
}

void DeletQueue(queue_t* queue) {
  free(queue->array);

  queue->array = NULL;
  queue->size = 0;
  queue->head = 0;
  queue->tail = 0;
}


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
