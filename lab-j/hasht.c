#include "hasht.h"

ERR_STATUS Init(ht_t** ht, int htSize) {
  *ht = (ht_t*)malloc(sizeof(ht_t) * htSize);

  if (*ht == NULL)
    return ERROR;

  (**ht).size = htSize;
  for (int i = 0; i < htSize; i++)
    (*ht)[i].status = NOT_INTENTED;
  return OK;
}

unsigned HF1(char* str, int size) {
  unsigned res = 0;

  for (int i = 0; str[i] != 0; i++) {
    res += (unsigned)str[i];
    res %= size;
  }

  return res;
}

unsigned HF2(char* str, int size) {
  unsigned res = 0;

  for (int i = 0; str[i] != 0; i++) {
    res += (unsigned)str[i] + res * 2;
    res %= size;
  }

  return res;
}

int Add(ht_t* ht, char* str) {
  unsigned x, y;
  unsigned htSize = (*ht).size;

  if (strlen(str) > 100)
    return ERROR;

  x = HF1(str, htSize);
  y = HF2(str, htSize);

  for (unsigned i = 0; i < htSize; i++) {
    if (ht[x].status == NOT_INTENTED || ht[x].status == FREE) {
      strcpy(ht[x].str, str);
      ht[x].status = NOT_FREE;
      return OK;
    }
    else if (ht[x].status == NOT_FREE && strcmp(ht[x].str, str) == 0)
      return ERROR;
    else
      x = (x + y) % htSize;
  }
  return ERROR;
}

int Find(ht_t* ht, char* str) {
  unsigned x, y;
  unsigned htSize = (*ht).size;

  if (strlen(str) > 100)
    return ERROR;

  x = HF1(str, htSize), y = HF2(str, htSize);
  for (unsigned i = 0; i < htSize; i++) {
    if (ht[x].status == NOT_FREE && strcmp(ht[x].str, str) == 0)
      return OK;
    else if (ht[x].status == NOT_INTENTED)
      return ERROR;

    x = (x + y) % htSize;
  }
  return ERROR;
}

ERR_STATUS Remove(ht_t* ht, char* str) {
  unsigned x, y;
  unsigned htSize = (*ht).size;

  if (strlen(str) > 100)
    return ERROR;

  x = HF1(str, htSize);
  y = HF2(str, htSize);
  for (unsigned i = 0; i < htSize; i++) {
    if (ht[x].status == NOT_FREE && strcmp(ht[x].str, str) == 0) {
      ht[x].status = FREE;
      return OK;
    }
    else if (ht[x].status == NOT_INTENTED)
      return ERROR;

    x = (x + y) % htSize;
  }
  return ERROR;
}

ERR_STATUS Delete(ht_t** ht) {
  free(*ht);
  *ht = NULL;

  return OK;
}