#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

char s = ' ';

typedef char* type;

typedef struct {
  type* data;
  int n;
} hash_t;

hash_t* Create(int n) {

  hash_t* newHash = (hash_t*)malloc(sizeof(hash_t));
  if (!newHash)
    return NULL;
  newHash->data = (type*)calloc(n, sizeof(type));
  if (!newHash->data) {
    free(newHash);
    return NULL;
  }
  newHash->n = n;
  return newHash;
}

int Insert(hash_t* table, const type val) {

  int i = 0;
  int j = 0;
  int start = 0;
  int m = table->n;
  while (val[i])
    start += val[i++];
  start = start % m;
  i = start;
  do {
    if (!table->data[i] || table->data[i] == &s) {
      table->data[i] = (type)malloc(sizeof(char) * (strlen(val) + 1));
      if (!table->data[i])
        return 0;
      strcpy(table->data[i], val);
      return 1;
    }
    if (strcmp(table->data[i], val) == 0)
      return 1;
    i = (i + 2 * j + 1) % m;
    ++j;
  } while (i != start);
  return 1;
}

int Find(const hash_t* table, const type val) {

  int i = 0;
  int j = 0;
  int start = 0;
  int m = table->n;
  while (val[i])
    start += val[i++];
  start = start % m;
  i = start;
  do {
    if (!table->data[i])
      return 0;
    if (table->data[i] != &s && strcmp(table->data[i], val) == 0)
      return 1;
    i = (i + 2 * j + 1) % m;
    ++j;
  } while (i != start);
  return 0;
}

int Delete(hash_t* table, const type val) {

  int i = 0;
  int j = 0;
  int start = 0;
  int m = table->n;
  while (val[i])
    start += val[i++];
  start = start % m;
  i = start;
  do {
    if (!table->data[i])
      return 0;
    if (table->data[i] != &s && strcmp(table->data[i], val) == 0) {
      free(table->data[i]);
      table->data[i] = &s;
      return 1;    }

    i = (i + 2 * j + 1) % m;
    ++j;
  } while (i != start);
  return 0;
}

void Free(hash_t* table) {

  int i = 0;
  for (i = 0; i < table->n; ++i) {
    if (table->data[i] && table->data != (type*)&s)
      free(table->data[i]);
  }
  free(table->data);
  free(table);
}

int main() {

  char symb = 1;
  char val[64];
  hash_t* table = Create(5);

  while (1) {
    symb = getchar();
    if (symb == EOF)
      break;
    scanf("%s", &val);
    getchar();
    switch (symb) {
    case 'a':
      Insert(table, val);
      break;
    case 'f':
      if (Find(table, val))
        printf("yes\n");
      else 
        printf("no\n");
      break;
    case 'r':
      Delete(table, val);
      break;
    default:
      break;
    }
  }
  Free(table);
  return 0;
}