#include <stdio.h>

#include "tree.h"

int main(void) {
  char c = ' ';
  int key;
  node_t *root = NULL;

  while (1) {
    c = getchar();
    if (c == EOF)
      break;
    scanf("%i[\n]", &key);
    switch (c) {
      case 'a':
        Insert(&root, key);
        break;
      case 'r':
        Delete(&root, key);
        break;
      case 'f':
        if (Find(root, key) == TREE_FIND_NODE_EXIST)
          printf("yes\n");
        else
          printf("no\n");
        break;
    }
    // Print(root);
    scanf("%c", &c);
  }

  DeleteTree(root);

  return 0;
}
