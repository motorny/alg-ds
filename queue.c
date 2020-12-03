#include <stdlib.h>
#include "queue.h"

int InitQueue(struct queue* q, int n){
  if (n <= 0) {
    return FALSE;
  }
  q->arr = (int*)malloc(sizeof(int) * n);
  if (q->arr == NULL) {
    return FALSE;
  }
  q->size = n;
  q->first = 0;
  q->last = 0;
  return TRUE;
}
int Push(struct queue* q, int elem){
  if (q->arr == NULL || q->last >= q->size){
    return FALSE;
  }
  q->arr[q->last++] = elem;
  return TRUE;
}
int Pop(struct queue* q, int* elem){
  if (q->first >= q->last || q->arr == NULL ){
    return FALSE;
  }
  *elem = q->arr[q->first++];
  return TRUE;
}
int RemoveQueue(struct queue* q){
  free(q->arr);
  q->arr = NULL;
  q->size = 0;
  q->first = 0;
  q->last = 0;
  return TRUE;
}
