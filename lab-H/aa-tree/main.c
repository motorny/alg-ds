#include "aatree.h"

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
  aatree_t* root = NULL;

  var = Read(&num);
  while (var) {
    switch (var) {
    case 1:
      Insert(&root, num);
      break;
    case 2:
      if (Find(root, num) != NULL)
        printf("yes\n");
      else
        printf("no\n");
      break;
    default:
      Delete(&root, num, root);
      break;
    }

    var = Read(&num);
  }

  Clear(&root);
  return 0;
}