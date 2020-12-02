#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <ctype.h>

typedef enum {
  ERROR = -1,
  OK,
  EMPTY, 
  DONE, 
  NOT_DONE
}ERR_STATUS;

typedef struct {
  int* arr;
  int headP;
  int tailP;
  int size;
}queue_t;

ERR_STATUS CreateQueue(queue_t* queue, int size);

ERR_STATUS Enqueue(queue_t* queue, int elem);
ERR_STATUS Dequeue(queue_t* queue, int* elem);

ERR_STATUS DeleteQueue(queue_t* queue);


#endif /*QUEUE_H*/