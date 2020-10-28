#ifdef cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "queue.h"

int InitQueue(queue_t *q, int n) {
  if (n <= 0)
    return 0;
  q->array = (int*)malloc(sizeof(int) * n);
  if (q->array == NULL)
    return 0;
  q->size = n;
  q->head = 0;
  q->tail = 0;
  return 1;
}

void CloseQueue(queue_t *q) {
  free(q->array);
  q->array = NULL;
  q->size = 0;
  q->head = 0;
  q->tail = 0;
}

int Push(queue_t *q, int newEl) {
  if (q->array == NULL || q->tail >= q->size)
    return 0;
  q->array[q->tail++] = newEl;
  return 1;
}

int Pop(queue_t *q, int *oldEl) {
  if (q->array == NULL || q->head >= q->tail)
    return 0;
  *oldEl = q->array[q->head++];
  return 1;
}

#ifdef cplusplus
}
#endif
