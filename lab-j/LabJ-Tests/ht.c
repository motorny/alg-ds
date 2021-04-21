#include <stdlib.h>
#include <string.h>
#include "ht.h"

int HtInit(htCell_t** ht, int htSize) {
  if (htSize <= 0)
    return ht_false;

  *ht = (htCell_t*)malloc(sizeof(htCell_t) * htSize);
  
  if (*ht == NULL)
    return ht_false;

  for (int i = 0; i < htSize; i++) {
    (*ht)[i].isFree = 1;
    (*ht)[i].str = NULL;
  }
  return ht_true;
}

unsigned int HashFunc1(char* str) {
  int res = 0, i = 0;

  while (str[i] != 0) {
    res += str[i++];
    res %= 4294967010;
  }

  return res;
}

unsigned int HashFunc2(char* str) {
  unsigned int hash = 5381;
  int c, i = 0;

  while (str[i] != 0) {
    c = str[i++];
    hash = hash * 33 + c;
    hash %= 130150524;
  }

  return hash;
}

int HtInsert(htCell_t* ht, int htSize, char* str) {
  unsigned int x = HashFunc1(str) % htSize, y = HashFunc2(str);

  for (int i = 0; i < htSize; i++) {
    if (ht[x].isFree == 1) {
      ht[x].str = str;
      ht[x].isFree = 0;
      return ht_true;
    }
    x = (x + y) % htSize;
  }
  return ht_false;
}

int HtFind(htCell_t* ht, int htSize, char* str) {
  unsigned int x = HashFunc1(str) % htSize, y = HashFunc2(str);

  for (int i = 0; i < htSize; i++) {
    if (ht[x].isFree == 0 && ht[x].str == str)
      return x;

    x = (x + y) % htSize;
  }
  return ht_false;
}

int HtDelete(htCell_t* ht, int htSize, char* str) {
  unsigned int x = HashFunc1(str) % htSize, y = HashFunc2(str);

  for (int i = 0; i < htSize; i++) {
    if (ht[x].isFree == 0 && ht[x].str == str) {
      ht[x].isFree = 1;
      ht[x].str = NULL;
      return ht_true;
    }

    x = (x + y) % htSize;
  }
  return ht_false;
}

int HtClear(htCell_t** ht, int htSize) {
  free(*ht);
  *ht = NULL;
  return ht_true;
}
