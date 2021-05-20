#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define STR_SIZE 100
#pragma warning (disable:4996)

//double hashing: two hash functions

typedef unsigned int uint;

typedef enum {
  NOT_INITED = 0,
  NOT_FREE=1,
  FREE=2
}status_t;

typedef struct{
  char str[STR_SIZE];
  status_t status; //can be 0(NULL), 1(free), 2(filled)
} elem_t;

bool TableInit(elem_t** table, int tableSize) {
  (*table) = (elem_t*)malloc(tableSize*sizeof(elem_t));

  if (!(*table))
    return false;

  for (int i = 0; i < tableSize; i++)
    (*table)[i].status = NOT_INITED;
  return true;
}

uint HashFunc1(char* str, int size) {
  uint res = 0;
  for (int i = 0; str[i] !='\0'; i++) {
    res += (uint)str[i];
    res %= size;
  }
  return res;
}

uint HashFunc2(char* str, int size) {
  uint res = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    res += (uint)str[i] + 2*res;
    res %= size;
  }

  return res;
}

int ElemAdd(elem_t* table, char* str, const int tableSize) {
  uint x = HashFunc1(str, tableSize);
  uint y = HashFunc2(str, tableSize);

  for (uint i = 0; i < tableSize; i++) {

    //if cell is free
    if (table[x].status == NOT_INITED || table[x].status == FREE) {
      strcpy(table[x].str, str);
      table[x].status = NOT_FREE;
      return true;
    }
    //if equal strings, do not copy new string
    else if (table[x].status == NOT_FREE && strcmp(table[x].str, str) == 0)
      return false;
    else
      x = (x + y) % tableSize;
  }
  return false;
}

int ElemFind(elem_t* table, char* str, const int tableSize) {
  uint x = HashFunc1(str, tableSize);
  uint y = HashFunc2(str, tableSize);

  for (uint i = 0; i < tableSize; i++) {

    //exists
    if (table[x].status == NOT_FREE && strcmp(table[x].str, str) == 0)
      return true;
    //this and next cells are not inited
    else if (table[x].status == NOT_INITED)
      return false;

    x = (x + y) % tableSize;
  }
  return false;
}

bool ElemRemove(elem_t* table, char* str, const int tableSize) {
  uint x = HashFunc1(str, tableSize);
  uint y = HashFunc2(str, tableSize);

  for (uint i = 0; i < tableSize; i++) {
    //found string
    if (table[x].status == NOT_FREE && strcmp(table[x].str, str) == 0) {
      table[x].status = FREE;
      return true;
    }
    //this and next cells are not inited
    else if (table[x].status == NOT_INITED)
      return false;

    x = (x + y) % tableSize;
  }
  return false;
}

int main() {
  char comand;
  char str[STR_SIZE];
  const int TABLE_SIZE = 1230013; //must be big prime number
  elem_t* table = NULL;

  if (!TableInit(&table, TABLE_SIZE))
    return 1;

  while (true) {
    comand = (char)fgetc(stdin);

    if (comand == EOF || comand == '\n')
      break;

    scanf("%s", str);

    //comands
    if (comand == 'a') //append
      ElemAdd(table, str, TABLE_SIZE);

    else if (comand == 'f') { //find
      if (ElemFind(table, str, TABLE_SIZE))
        printf("yes\n");
      else
        printf("no\n");
    }

    else if (comand == 'r')//remove
      ElemRemove(table, str, TABLE_SIZE);

    comand = (char)fgetc(stdin); //get '\n' from stdin
  }

  free(table);
  return 0;
}