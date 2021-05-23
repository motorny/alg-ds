#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#pragma warning(disable: 4996)

#define K 1

static unsigned hashFunc(char* str, int size) {
  int sum = 0;

  for (int i = 0; str[i] != 0; i++)
    sum += str[i];

  return sum % size;
}

hash_table_t* hashInit(int hashTSize) {
  if (hashTSize <= 0)
    return NULL;

  hash_table_t* table = (hash_table_t*)malloc(sizeof(hash_table_t));

  if (!table)
    return NULL;

  table->size = hashTSize;
  table->table = (hash_elem_t*)malloc(sizeof(hash_elem_t) * hashTSize);

  if (!table->table) {
    free(table);
    return NULL;
  }

  for (int i = 0; i < hashTSize; i++)
    table->table[i].status = FREE;

  return table;
}

int hashAdd(hash_table_t* h, char elem[]) {
  if (!h)
    return MFAIL;

  int pos0 = hashFunc(elem, h->size), curPos = pos0;
  int pos = -1;
  int i = 0;

  do {
    if (h->table[curPos].status == FREE) {
      if (pos == -1)
        pos = curPos;
      break;
    }
    else
      if (h->table[curPos].status == DELETED) {
        if (pos == -1)
          pos = curPos;
      }
      else if (strcmp(h->table[curPos].str, elem) == 0)
        return ALREADYEXISTS;

    i++;
    curPos = (pos0 + i * K) % h->size;
  } while (curPos != pos0);

  if (pos != -1) {
    h->table[pos].str = (char*)malloc(sizeof(char) * (strlen(elem) + 1));

    if (!h->table[pos].str)
      return MFAIL;

    strcpy(h->table[pos].str, elem);
    h->table[pos].status = FULL;

    return MSUCCESS;
  }

  return MFAIL;
}

hash_elem_t* hashFind(hash_table_t* h, char elem[]) {
  if (!h)
    return NULL;

  int pos0 = hashFunc(elem, h->size), curPos = pos0;
  int i = 0;

  do {
    if (h->table[curPos].status == FREE)
      return NULL;

    if (h->table[curPos].status == FULL && strcmp(h->table[curPos].str, elem) == 0)
      return &h->table[curPos];

    i++;
    curPos = (pos0 + i * K) % h->size;
  } while (curPos != pos0);

  return NULL;
}

int hashDelete(hash_table_t* h, char elem[]) {
  if (!h)
    return MFAIL;

  int pos0 = hashFunc(elem, h->size), curPos = pos0;
  int i = 0;

  do {
    if (h->table[curPos].status == FREE)
      return MFAIL;

    if (h->table[curPos].status == FULL && strcmp(h->table[curPos].str, elem) == 0) {
      unsigned pos1 = (pos0 + (i + 1) * K) % h->size;

      free(h->table[curPos].str);
      h->table[curPos].status = DELETED;
      if (h->table[pos1].status == FREE) {
        while (h->table[curPos].status == DELETED) {
          h->table[curPos].status = FREE;
          i--;
          if (i >= 0) {
            curPos = (pos0 + i * K) % h->size;
            if (curPos == pos0)
              break;
          }
          else
            break;
        }
      }

      return MSUCCESS;
    }

    i++;
    curPos = (pos0 + i * K) % h->size;
  } while (curPos != pos0);

  return MFAIL;
}

void clear(hash_table_t* h) {
  if (!h)
    return;

  for (int i = 0; i < h->size; i++)
    if (h->table[i].status == FULL)
      free(h->table[i].str);
  free(h->table);
  free(h);
} 
