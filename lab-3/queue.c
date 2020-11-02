#include "queue.h"
#include <stdlib.h>
#include <assert.h>

queue_t* CreateQueue() {
  queue_t* newQueue = malloc(sizeof(queue_t));
  newQueue->start = NULL;
  newQueue->end = NULL;
  return newQueue;
}

int QueuePush(queue_t* queue, int data) {
  if (!queue)
    return FAIL;
  node_t* newNode = malloc(sizeof(node_t));
  newNode->vertex = data;
  newNode->next = NULL;
  if (queue->end != NULL) {
    queue->end->next = newNode;
  }
  else {
    queue->start = newNode;
  }
  queue->end = newNode;

  return SUCCESS;
}

int QueuePop(queue_t* queue) {
  assert(queue);
  assert(queue->start);
  int res = queue->start->vertex;
  queue->start = queue->start->next;
  if (queue->start == NULL) {
    queue->end = NULL;
  }
  return res;
}

void RemoveQueue(queue_t* queue) {
  if (!queue)
    return;
  node_t* p = queue->start;
  node_t* next;
  while (p != NULL) {
    next = p->next;
    free(p);
    p = next;
  }
  free(queue);
}

char QueueIsEmpty(queue_t* queue) {
  return queue->start == NULL ? 1 : 0;
}
