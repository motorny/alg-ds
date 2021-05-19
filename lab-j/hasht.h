#ifndef HASHT_H
#define HASHT_H

#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

typedef enum {
  NOT_INTENTED = 0,
  NOT_FREE,
  FREE
}STATUS;


typedef struct _ht_t {
  char str[100];
  unsigned size;
  STATUS status;  // 0 not inited, 2 - free, 1 - not free
}ht_t;

typedef enum{
  ERROR = 0,
  OK
}ERR_STATUS;

ERR_STATUS Init(ht_t** ht, int htSize);

ERR_STATUS Add(ht_t* ht, char* str);
ERR_STATUS Find(ht_t* ht, char* str);
ERR_STATUS Remove(ht_t* ht, char* str);

ERR_STATUS Delete(ht_t** ht);

#endif // HASHT_H