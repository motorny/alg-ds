#include "hash.h"

#include <stdlib.h>
#include <string.h>

#pragma warning (disable: 4996)

char deleted = ' ';

hash_table_t* HashCreate(int size) {
  hash_table_t* newHash = malloc(sizeof(hash_table_t));
  if (!newHash)
    return NULL;

  newHash->data = calloc(size, sizeof(T));
  if (!newHash->data) {
    free(newHash);
    return NULL;
  }
 
  newHash->size = size;
  return newHash;
}

int hash(T key, int m) {
  int hash = 0;
  int i = 0;
  while (key[i]) 
    hash += key[i++];
  
  return hash % m ;
}

int HashInsert(hash_table_t* t, const T key) {
  int i = 0;
  int j = 0;
  int start;
  int m = t->size;

  start = hash(key, m);
  i = start;
  do {
    if (t->data[i] == NULL || t->data[i] == &deleted) {
      t->data[i] = malloc(sizeof(char) * (strlen(key) + 1));
      if (!t->data[i])
        return FAIL;
      strcpy(t->data[i], key);
      return SUCCESS;
    }

    if (strcmp(t->data[i], key) == 0)
      return FAIL;

    i = (i + 2 * j + 1) % m;
    ++j;
  } while (i != start);

  return SUCCESS;
}

int HashSearch(const hash_table_t* t, const T key) {
  int i = 0;
  int j = 0;
  int start;
  int m = t->size;

  start = hash(key, m);
  i = start;
  do {
    if (t->data[i] == NULL)
      return FAIL;
 
    if (t->data[i] != &deleted && strcmp(t->data[i], key) == 0)
      return SUCCESS;
    
    i = (i + 2 * j + 1) % m;
    ++j;
  } while (i != start);

  return FAIL;
}

int HashDelete(hash_table_t* t, const T key) {
  int i = 0;
  int j = 0;
  int start;
  int m = t->size;

  start = hash(key, m);
  i = start;
  do {
    if (t->data[i] == NULL)
      return FAIL;

    if (t->data[i] != &deleted && strcmp(t->data[i], key) == 0) {
      free(t->data[i]);
      t->data[i] = &deleted;
      return SUCCESS;
    }

    i = (i + 2 * j + 1) % m;
    ++j;
  } while (i != start);

  return FAIL;
}

void HashFree(hash_table_t* t) {
  int i = 0;
  for (i = 0; i < t->size; ++i) {
    if (t->data[i] && t->data != &deleted)
      free(t->data[i]);
  }
  free(t->data);
  free(t);
}
