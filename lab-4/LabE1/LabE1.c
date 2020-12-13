#include "..\BST_Lib\BST_Lib.h"
#include <stdlib.h>
#include <stdio.h>

#pragma warning(disable:4996)

int main(void)
{
  char* command;
  int arg1, arg2;
  Tree* tree_p = TreeGet();
  if (tree_p == NULL)
  {
    return -1;
  }
  command = malloc(3);
  if (command == NULL)
  {
    return -1;
  }

  scanf("%*[ \n]");
  while (!feof(stdin) && 2 == scanf("%2s %i", command, &arg1))
  {
    switch (command[0])
    {
    case 'a':
      if (getchar() == '\n' || feof(stdin)) {
        //a key
        TreeAdd(tree_p, arg1, 0);
      }
      else if (1 == scanf("%i", &arg2))
      {
        //a key val
        TreeAdd(tree_p, arg1, arg2);
      }
      break;
    case 'r':
      //r key
      TreeRemove(tree_p, arg1);
      break;
    case 'f':
      //f key
      if (TreeFind(tree_p, arg1) != NULL)
      {
        printf("yes\n");
      }
      else
      {
        printf("no\n");
      }
      break;
    case 'p':
      switch (command[1])
      {
      case '\0':
        //p size
        TreePrint(tree_p, arg1, TreeItemGetKey);
        break;
      case 'v':
        //pv size
        TreePrint(tree_p, arg1, TreeItemGetValue);
        break;
      case 'h':
        //ph size
        TreeHightDifToValue(tree_p);
        TreePrint(tree_p, arg1, TreeItemGetValue);
        break;
      default:
        printf("Incorrect Command\n");
        break;
      }
      break;
    case 'h':
      //h ~
      TreeHightDifToValue(tree_p);
      break;
    default:
      printf("Incorrect Command\n");
      break;
    }
    scanf("%*[ \n]");
  }
  TreeFree(tree_p);
  return 0;
}
