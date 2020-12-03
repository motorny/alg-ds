#include <stdio.h>
#include "tree.h"

int Read(int* num) {
  char ch = (char)getchar();

  if (ch == EOF)
    return 0;

  scanf("%i", num);
  getchar();

  switch (ch) {
    case 'a':
      return 1;
    case 'f':
      return 2;
    case 'r':
      return 3;
    default:
      return 0;
  }
}

int main(void) {
  int num, var;
  node_t* tree = NULL;

  var = Read(&num);
  while (var) {
    switch (var) {
      case 1:
        TreeAdd(&tree, num);
        break;
      case 2:
        if (TreeFind(tree, num) != NULL)
          printf("yes\n");
        else
          printf("no\n");
        break;
      default:
        TreeDel(&tree, num);
        break;
    }

    var = Read(&num);
  }

  TreeClear(&tree);
  return 0;
}