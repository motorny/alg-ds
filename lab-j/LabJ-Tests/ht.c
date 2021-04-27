#include <stdlib.h>
#include <string.h>
#include "ht.h"

int HtInit(htCell_t** ht, int htSize) {
  *ht = (htCell_t*)malloc(sizeof(htCell_t) * htSize);

  if (*ht == NULL)
    return LABJ_FALSE;

  for (int i = 0; i < htSize; i++)
    (*ht)[i].status = 0;
  return LABJ_TRUE;
}

unsigned int HashFunc1(char *str, int size) {
  unsigned int res = 0;

  for (int i = 0; str[i] != 0; i++) {
    res += (unsigned int)str[i];
    res %= size;
  }

  return res;
}

unsigned int HashFunc2(char *str, int size) {
  unsigned int res = 0;

  for (int i = 0; str[i] != 0; i++) {
    res += (unsigned int)str[i] + res * 2;
    res %= size;
  }

  return res;

  return res == 0 ? 1 : res;
}

int HtInsert(htCell_t* ht, int htSize, char *str) {
  unsigned int x, y;

  if (strlen(str) > 100)
    return LABJ_FALSE;

  x = HashFunc1(str, htSize), y = HashFunc2(str, htSize);
  for (int i = 0; i < htSize; i++) {
    if (ht[x].status == 0 || ht[x].status == 2) {
      strcpy(ht[x].str, str);
      ht[x].status = 1;
      return LABJ_TRUE;
    }
    else if (ht[x].status == 1 && strcmp(ht[x].str, str) == 0)
      return LABJ_FALSE;
    else
      x = (x + y) % htSize;
  }
  return LABJ_FALSE;
}

int HtFind(htCell_t* ht, int htSize, char *str) {
  unsigned int x, y;

  if (strlen(str) > 100)
    return LABJ_FALSE;

  x = HashFunc1(str, htSize), y = HashFunc2(str, htSize);
  for (int i = 0; i < htSize; i++) {
    if (ht[x].status == 1 && strcmp(ht[x].str, str) == 0)
      return LABJ_TRUE;
    else if (ht[x].status == 0)
      return LABJ_FALSE;

    x = (x + y) % htSize;
  }
  return LABJ_FALSE;
}

int HtDelete(htCell_t* ht, int htSize, char *str) {
  unsigned int x, y;

  if (strlen(str) > 100)
    return LABJ_FALSE;

  x = HashFunc1(str, htSize), y = HashFunc2(str, htSize);
  for (int i = 0; i < htSize; i++) {
    if (ht[x].status == 1 && strcmp(ht[x].str, str) == 0) {
      ht[x].status = 2;
      return LABJ_TRUE;
    }
    else if (ht[x].status == 0)
      return LABJ_FALSE;

    x = (x + y) % htSize;
  }
  return LABJ_FALSE;
}

int HtClear(htCell_t** ht, int htSize) {
  free(*ht);
  *ht = NULL;
  return LABJ_TRUE;
}