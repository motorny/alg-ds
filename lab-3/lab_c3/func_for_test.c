#include <stdlib.h>

#include "func_for_test.h"

int InitQueue(queue_t* q, int size) {
  q->arr = NULL;

  if (size > 0) {
    q->arr = (int*)calloc(size, sizeof(int));
  }

  if (q->arr) {
    q->size = size;
    q->head = 0;
    q->tail = 0;

    return M_SUCCESS;
  }

  return M_FAIL;
}

int Put(queue_t* q, int newEl) {
  if (q->arr != NULL && q->size > q->tail) {
    q->arr[q->tail++] = newEl;

    return M_SUCCESS;
  }

  return M_FAIL;
}

int Get(queue_t* q, int* oldEl) {
  if (q != NULL && q->head != q->tail) {
    *oldEl = q->arr[q->head++];

    return M_SUCCESS;
  }

  return M_FAIL;
}

void DelQueue(queue_t* q) {
  free(q->arr);
  q->arr = NULL;
  q->size = 0;
  q->head = 0;
  q->tail = 0;
}

int BFS(adj_list_t* list, queue_t* q) {
  int counter;
  int curVertex;
  int* used = (int*)calloc(list->numOfVertex, sizeof(int));

  if (list->numOfVertex != 0 && list->nodes != NULL && q->arr != NULL && list->numOfVertex <= q->size && used != NULL) {
    Put(q, 0);
    used[0] = 1;

    while (Get(q, &curVertex)) {
      for (counter = 0; counter < list->nodes[curVertex].numOfEdges; counter++)
        if (!used[list->nodes[curVertex].edges[counter]]) {
          Put(q, list->nodes[curVertex].edges[counter]);
          used[list->nodes[curVertex].edges[counter]] = 1;
        }
    }

    free(used);
    return M_SUCCESS;
  }

  free(used);
  return M_FAIL;
}