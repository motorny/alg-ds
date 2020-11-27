#include "tree.h"
#if 1
void main(void)
{
  tree T = {0};
  node *N;

  TreeAddElement(&T, 5);
  TreeAddElement(&T, 100);
  TreeAddElement(&T, 50);
  TreeAddElement(&T, 60);
  TreeAddElement(&T, 70);
  TreeAddElement(&T, 65);
  TreeAddElement(&T, 63);
  TreeAddElement(&T, 69);
  TreeAddElement(&T, 61);
  TreeAddElement(&T, 64);
  N = TreeFindElement(T, 70);
  N = TreeKLower(N, 300);
  printf("Hello");
}
#endif