#include <stdio.h>
#include "hash.h"

int main(void) {
  char c = ' ';
  char key[256];
  hash_t* hash = GetHash(100000);
  while (1) {
    c = getchar();
    if (c == EOF) {
      break;
    }
    scanf("%s", &key);
    switch (c) {
    case 'a':
      Add(hash, key);
      break;
    case 'r':
      Remove(hash, key);
      break;
    case 'f':
      if (Find(hash, key) == HASH_FIND_SUCCESS) {
        printf("yes\n");
      }
      else {
        printf("no\n");
      }
      break;
    }
    scanf("%c", &c);
  }
  Delete(hash);
  return 0;
}