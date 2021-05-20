#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)

#define OK 1
#define FAIL -1
#define SIZE 400

typedef enum {
  STATUS_FREE,
  STATUS_FILLED,
  STATUS_DELETED
}status_t;

typedef struct {
  char* data;
  int status;
}hash_t;

hash_t* CreateHash(int size) {
  hash_t* table;
  table = (hash_t*)malloc(sizeof(hash_t) * size);
  if (!table)
    return NULL;
  for (int i = 0; i < size; i++)
    table[i].status = STATUS_FREE;
  return table;
}

static int Hash(char* str, int size) {
  int ind = 0;

  for (int i = 0; str[i] != 0; i++) {
    ind += str[i];
  }
  ind %= size;
  return ind;
}

void Insert(hash_t* table, char* elem, int size) {
  int key = Hash(elem, size);
  int ind = key;
  for (int pos = 0; pos < size; pos++) {

    if (table[ind].status == STATUS_FREE 
      || table[ind].status == STATUS_DELETED) {

      table[ind].data = (char*)malloc((strlen(elem) + 1) * sizeof(char));
      strcpy(table[ind].data, elem);
      table[ind].status = STATUS_FILLED;
      return;
    
    }
    else
      if (table[ind].status == STATUS_FILLED && strcmp(table[ind].data, elem) == 0)
        return;
    ind = (ind + 2 * pos + 1) % size;
  }
}

int Search(hash_t* table, char* elem, int size) {
  int key = Hash(elem, size);
  int ind = key;
  for (int pos = 0; pos < size; pos++) {
    if (table[ind].status == STATUS_FILLED && strcmp(table[ind].data, elem) == 0) {
      return OK;
    }
    else if (table[ind].status == STATUS_FREE) {
      return FAIL;
    }
    ind = (ind + 2 * pos + 1) % size;
  }
  return FAIL;
}

void Delete(hash_t* table, char* elem, int size) {
  int key = Hash(elem, size);
  int ind = key;
  for (int pos = 0; pos < size; pos++) {
    if (table[ind].status == STATUS_FILLED && (strcmp(table[ind].data, elem) == 0)) {
      free(table[ind].data);
      table[ind].status = STATUS_DELETED;
      return;
    }
    else
      if (table[ind].status == STATUS_FREE)
        return;
    ind = (ind + 2 * pos + 1) % size;
  }
}

void FreeHash(hash_t* table, int size) {
  for (int i = 0; i < size; i++) {
    if (table[i].status == STATUS_FILLED)
      free(table[i].data);
  }
  free(table);
}

int main() {

  hash_t* table;
  table = CreateHash(SIZE);
  char elem[100];
  char symbol, command;
  int number;
  while (OK) {
    command = getchar();
    if (command != EOF) {
      while (command == '\0' || command == '\n' || isspace(command) != 0)
        symbol = getchar();
      scanf("%s", &elem);
      switch (command) {
      case('a'):
        Insert(table, elem, SIZE);
        break;
      case('r'):
        Delete(table, elem, SIZE);
        break;
      case('f'):
        if (Search(table, elem, SIZE) == OK)
          printf("yes\n");
        else
          printf("no\n");
        break;
      default:
        break;
      }
      symbol = getchar();
    }
    else 
      break;
  }
  FreeHash(table, SIZE);
  return 0;
}