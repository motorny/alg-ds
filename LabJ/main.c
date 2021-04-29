#include <stdio.h>
#include "hash.h"

#pragma warning (disable: 4996)

int main() {
  char op = 1;
  char key[64];
  hash_table_t* t = HashCreate(5);

  while (1) {
    op = getchar();
    if (op == EOF) {
      break;
    }
    scanf("%s", &key);
    getchar();
    switch (op) {
      case 'a':
        HashInsert(t, key);
        break;
      case 'f':
        if (HashSearch(t, key)) {
          printf("yes\n");
        }
        else {
          printf("no\n");
        }
        break;
      case 'r':
        HashDelete(t, key);
        break;
      default:
        break;
    }
  }

  HashFree(t);

  return 0;
}