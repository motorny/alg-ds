#include <stdlib.h>
#include "queue.h"

int EmptyQueueArr(queueArr_t queue) {
  return queue.head == queue.tail;
}

int SizeQueueArr(queueArr_t queue) {
  if (queue.head > queue.tail) {
    return queue.size - queue.head + queue.tail;
  }
  else {
    return queue.tail - queue.head;
  }
}

void PushQueueArr(elem_t newElem, queueArr_t* queue) {
  if (SizeQueueArr(*queue) < queue->size - 1) {
    queue->data[queue->tail] = newElem;
    queue->tail = (queue->tail + 1) % queue->size;
  }
}

elem_t* PopQueueArr(queueArr_t* queue) {
  elem_t* elem;
  if (EmptyQueueArr(*queue)) {
    return NULL;
  }
  else {
    elem = &(queue->data[queue->head]);
    queue->head = (queue->head + 1) % queue->size;
    return elem;
  }
}

int EmptyQueueList(queueList_t queue) {
  return queue.size == 0;
}

void PushQueueList(elem_t elem, queueList_t* queue) {
  if (queue->tail == NULL) {
    queue->tail = malloc(sizeof(node_t));
    queue->head = queue->tail;
  }
  else {
    queue->tail->next = malloc(sizeof(elem_t));
    queue->tail = queue->tail->next;
  }
  if (queue->tail != NULL) {
    queue->tail->next = NULL;
    queue->tail->data = elem;
    queue->size++;
  }
}

elem_t* PopQueueList(queueList_t* queue) {
  node_t* t = queue->head;
  elem_t elem;
  if (queue->size != 0) {
    elem = queue->head->data;
    queue->head->next = t->next;
    free(t);
    return (&elem);
  }
  return NULL;
}