#pragma warning (disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#include "tree.h"

int main(void) {
  tree_t* root = NULL;

  char regimeWork;
  int key, avoidError;

  while (1) {
    regimeWork = getchar();
    if (regimeWork == EOF)
      break;
    while (regimeWork == '\0' || regimeWork == '\n' || isspace(regimeWork) != 0)
      avoidError = getchar();
    avoidError = scanf("%i", &key);
    switch (regimeWork) {
      case('a'):
        insertKey(&root, key);
        break;
      case('r'):
        deleteKey(&root, key);
        break;
      case('f'):
        if (findKey(root, key) != NULL)
          printf("yes\n");
        else
          printf("no\n");
        break;
      default:
        break;
    }
    avoidError = getchar();
  }
  deleteTree(root);

  return 0;
}