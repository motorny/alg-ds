#include <stdio.h>
#include "tree.h"

#pragma warning (disable: 4996)

int compare(int a, int b) {
  if (a > b)
    return 1;
  else if (a < b)
    return -1;
  else
    return 0;
}

int main() {
  char op = 1;
  int key;
  tree_t* t = TreeCreate();
  SetCompareFunc(&compare);

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
  }

  TreeFree(t);

  return 0;
}