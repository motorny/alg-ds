#include "tree.h"

int main(void) {
  Tree_t* root = NULL;
  int c = getchar();
  int number;
  while (c != EOF){
    scanf("%d", &number);
    switch (c) {
    case 'a':
      root = insertN(root, number);
      break;
    case 'f':
      printf(findN(root, number) == NULL ? "no\n" : "yes\n");
      break;
    case 'r':
      root = deleteN(root, number);
      break;
    default:
      freeTr(root);
      return 0;
    }
    if ((c = getchar()) == '\n') {
      c = getchar();
    }
  }
  freeTr(root);
  return 0;
}