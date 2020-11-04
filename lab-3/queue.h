#pragma once
#ifndef QUEUE_34531
#define QUEUE_34531

#define SUCCESS 1
#define FAIL 0

typedef struct node_t {
  int vertex;
  struct node_t* next;
} node_t;

typedef struct {
  node_t* start;
  node_t* end;
} queue_t;

queue_t* CreateQueue();
int QueuePush(queue_t* queue, int data);
int QueuePop(queue_t* queue);
char QueueIsEmpty(queue_t* queue);
void RemoveQueue(queue_t* queue);

#endif // !QUEUE_34531
