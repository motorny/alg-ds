#include <stdlib.h>

#include "queue.h"


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