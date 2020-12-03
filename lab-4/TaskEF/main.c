#include <stdio.h>
#include "bst.h"

int main(void) {
  char c = ' ';
  int key;
  tree_t *tree = GetTree();

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
        if (Find(tree, key) == BST_NODE_FINDED)
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
