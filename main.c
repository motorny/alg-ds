#include "treap.h"


int main() {
  node* root = NULL;
  char* command = (char*)malloc(MAX_LENGTH * sizeof(char));
  int value = 0;
  bool_t deleted = FALSE;
  bool_t contains = FALSE;

  while (fgets(command, MAX_LENGTH, stdin)) {
    value = strtol(command + 2, NULL, 10);

    switch (command[0]) {
      case 'a':
        Insert(value, GetNodeCount(root), &root);
        break;
      case 'r':
        deleted = FALSE;
        DeleteValue(value, &root, &deleted);
        break;
      case 'f':
        contains = FALSE;
        Check(value, root, &contains);
        if (contains == TRUE)
          printf("yes\n");
        else
          printf("no\n");
        break;
    }
  }

  FreeTree(root);
  free(command);
  return 0;
}