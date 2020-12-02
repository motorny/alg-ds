#include "queue.h"

ERR_STATUS CreateQueue(queue_t* queue, int size) {
  if (size <= 0)
    return ERROR;

  queue->arr = (int*)malloc(size * sizeof(int));
  if (queue->arr == NULL)
    return EMPTY;

  queue->headP = 0;
  queue->tailP = 0;
  queue->size = size;

  return OK;
}

ERR_STATUS Enqueue(queue_t* queue, int elem) {
  if (queue == NULL || queue->arr == NULL || queue->tailP >= queue->size)
    return ERROR;

  queue->arr[queue->tailP] = elem;
  queue->tailP++;

  return OK;
}


ERR_STATUS Dequeue(queue_t* queue, int* elem) {
  if (queue == NULL || queue->arr == NULL)
    return ERROR;

  if (queue->headP >= queue->tailP)
    return EMPTY;

  *elem = queue->arr[queue->headP];
  queue->headP++;
  
  return OK;
}


ERR_STATUS DeleteQueue(queue_t* queue) {
  if (queue == NULL || queue->arr == NULL)
    return ERROR;

  free(queue->arr);
  queue->headP = 0;
  queue->tailP = 0;
  queue->size = 0;

  return OK;
}