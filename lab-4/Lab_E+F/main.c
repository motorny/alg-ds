#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#pragma warning(disable: 4996)

int main(void) {
  char comand;
  int key;
  int k;
  int err;
  tree_t tree = { NULL };
  while (fscanf(stdin, "%c", &comand) != EOF) {
    switch (comand) {
    case 'a':
      fscanf(stdin, " %d", &key);
      err = Add(&tree, key);
      if (err == 1) {
        return 1;
      }
      break;
    case 'r':
      fscanf(stdin, " %d", &key);
      Delete(&tree, key);
      break;
    case 'f':
      fscanf(stdin, " %d", &key);
      fprintf(stdout, Find(&tree, key) != NULL ? "yes\n" : "no\n");
      break;
    case 'c':
      CountLeaves(&tree);
      break;
    case 'p':
      Print(&tree);
      break;
    case 's':
      fscanf(stdin, " %d %d", &key, &k);
      fprintf(stdout, "%d", FindShiftK(&tree, k, key));
    default:
      break;
    };
  }
  ClearTree(&tree);
  return 0;
}

/*a 5
a 1
a 20
a 18
a 25
a 14
a 19
a 16
a 17
a 15*/