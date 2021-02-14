#include <stdio.h>

#include "rst.h"

int main(void) {
  char c = ' ';
  int key;
  rst_t *tree = GetTree();

  while (1) {
    c = getchar();
    if (c == EOF)
      break;
    scanf("%i[\n]", &key);
    switch (c) {
      case 'a':
        Insert(tree, key);
        break;
      case 'r':
        Delete(tree, key);
        break;
      case 'f':
        if (Find(tree, key) == RST_FIND_NODE_EXIST)
          printf("yes\n");
        else
          printf("no\n");
        break;
    }
    scanf("%c", &c);
  }

  DeleteTree(tree);

  return 0;
}
