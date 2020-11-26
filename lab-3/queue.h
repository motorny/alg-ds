#pragma once

#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef struct {
  int *arr;
  int head, last;
  int size;
}queue_t;

int InitQ(queue_t* q, int n);

int push(queue_t* q, int x);

int pop(queue_t* q, int* x);

int RemoveQ(queue_t* q);