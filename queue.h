#ifndef QUEUE_H_INCLUDED__
#define QUEUE_H_INCLUDED__
#pragma once
#define SUCCESS 1
#define FAIL -1

typedef struct list {
  int data;
  struct list* next;
} list_t;
typedef struct queue {
  list_t* head, * tail;
} queue_t;

queue_t* createQueue(void);
int pushQueue(queue_t* queue, int data);
int popQueue(queue_t* queue);
void destroyQueue(queue_t* queue);

#endif