#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t* createQueue(void) {//initialize queue
  queue_t* queue = (queue_t*)malloc(sizeof(queue_t));

  if (queue == NULL)
    return NULL;
  queue->head = NULL;
  queue->tail = NULL;

  return queue;
}
int pushQueue(queue_t* queue, int data) {//add elem to queue
  //if q is NULL
  if (queue == NULL)
    return FAIL;
  //create new node
  list_t* tmp = (list_t*)malloc(sizeof(list_t));
  if (tmp == NULL)
    return FAIL;
  tmp->data = data;
  tmp->next = NULL;
  //if queue is empty
  if (queue->tail == NULL) {
    queue->head = tmp;
    queue->tail = tmp;
    return SUCCESS;
  }
  queue->tail->next = tmp;
  queue->tail = tmp;

  return SUCCESS;
}

int popQueue(queue_t* queue) {//take elem from queue
  int result;
  list_t* tmp;

  if (queue == NULL || queue->head == NULL)
    return FAIL;
  tmp = queue->head;
  result = tmp->data;
  queue->head = queue->head->next;
  free(tmp);
  if (queue->head == NULL)
    queue->tail = NULL;

  return result;
}
void destroyQueue(queue_t* queue) {
  list_t* tmp;
  list_t* next;
  if (queue == NULL)
    return;

  tmp = queue->head;
  while (tmp != NULL) {
    next = tmp->next;
    free(tmp);
    tmp = next;
  }
  free(queue);
}