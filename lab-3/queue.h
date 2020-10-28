#pragma once

#ifdef cplusplus
extern "C" {
#endif

#ifndef __QUEUE_H_INCLUDED
#define __QUEUE_H_INCLUDED

typedef struct {
  int *array;
  int head, tail;
  int size;
} queue_t;

int InitQueue(queue_t *q, int n);
void CloseQueue(queue_t *q);
int Push(queue_t *q, int newEl);
int Pop(queue_t *q, int *oldEl);

#endif /* __QUEUE_H_INCLUDED */

#ifdef cplusplus
}
#endif
