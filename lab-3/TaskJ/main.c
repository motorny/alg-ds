#include <stdio.h>
#include "hash.h"

int main(void) {
  char c = ' ';
  char key[256];
  hash_t *hash = GetHash(100000);

  while (1) {
    c = getchar();
    if (c == EOF)
      break;
    scanf("%s", &key);
    switch (c) {
      case 'a':
        HashAdd(hash, key);
        break;
      case 'r':
        HashRemove(hash, key);
        break;
      case 'f':
        if (HashFind(hash, key) == HASH_FIND_SUCCESS)
          printf("yes\n");
        else
          printf("no\n");
        break;
    }
    scanf("%c", &c);
  }

  DeleteHash(hash);

  return 0;
}
