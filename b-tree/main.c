#include "btree.h"
#pragma warning(disable: 4996)

int Read(int* data) {
  char ch = (char)getchar();

  if (ch == EOF)
    return 0;

  scanf("%i", data);
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
  b_tree_t tree;

  BTreeInit(&tree);
  var = Read(&num);
  while (var) {
    switch (var) {
    case 1:
      BTreeInsert(&tree, num);
      break;
    case 2:
      if (BTreeFind(&tree, num) != NULL)
        printf("yes\n");
      else
        printf("no\n");
      break;
    default:
      BTreeRemove(&tree, num);
      break;
    }

    var = Read(&num);
  }

  BTreeClear(&tree);
  return 0;
}