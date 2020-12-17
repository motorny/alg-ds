#pragma once

#define SUCCESS 1
#define FAIL 0

typedef struct {
  int* array;
  int size;
  int head;
  int tail;
} queue_t;


int InitialisationOfQueue(queue_t* q, int size);

int Push(queue_t* q, int newEl);

int Pop(queue_t* q, int* oldEl);

void DeletQueue(queue_t* queue);