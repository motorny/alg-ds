#include <stdio.h>
#include "tree.h"

#pragma warning (disable: 4996)

int main() {
  char op = 1;
  int key;
  tree_t* t = TreeCreate();

  while (1) {
    op = getchar();
    if (op == EOF) {
      break;
    }
    scanf("%i", &key);
    getchar();
    switch (op) {
      case 'a':
        TreeInsert(t, key);
        break;
      case 'f':
        if (TreeSearch(t, key)) {
          printf("yes\n");
        }
        else {
          printf("no\n");
        }
        break;
      case 'r':
        TreeDelete(t, key);
        break;
      default:
        break;
    }
   // TreePrint(t);
  }

  TreeFree(t);

  return 0;
}