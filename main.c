#pragma warning (disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "hash.h"

#define SIZE 10000

int main(void) {

  hashTable_t* hashTable;
  hashTable = hashCreate(SIZE);
  char keyStr[100];
  char regimeWork;
  int avoidError;

  while (1) {
    regimeWork = getchar();
    if (regimeWork == EOF)
      break;
    while (regimeWork == '\0' || regimeWork == '\n' || isspace(regimeWork) != 0)
      avoidError = getchar();
    avoidError = scanf("%s", &keyStr);
    switch (regimeWork) {
      case('a'):
        hashInsert(hashTable, keyStr, SIZE);
        break;
      case('r'):
        hashDelete(hashTable, keyStr, SIZE);
        break;
      case('f'):
        if (hashFind(hashTable, keyStr, SIZE) == FOUND)
          printf("yes\n");
        else
          printf("no\n");
        break;
      default:
        break;
    }
    avoidError = getchar();
  }

  hashDestroy(hashTable, SIZE);

  return 0;

}